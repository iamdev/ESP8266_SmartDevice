#include "WebConfig.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Device.h"

#define DEBUG

#ifdef DEBUG
#include "debug.h"
#endif

WebConfig::WebConfig(const char * ap_ssid,const char * ap_password){
  strncpy(this->ap_ssid,ap_ssid,sizeof(this->ap_ssid));
  strncpy(this->ap_password,ap_password,sizeof(this->ap_password));
}

WebConfig::WebConfig():WebConfig(DEFAULT_AP_SSID,DEFAULT_AP_PASSWORD){

}

bool WebConfig::run(){
  this->server->handleClient();
  return !isCompleted;
}

void WebConfig::handleRoot(){
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>ESP8266 - Smart Device</title></head><body>OK</body></html>\n";
  server->send(200, "text/html", s);
}

void WebConfig::handleConfig(){  
  #ifdef DEBUG 
  SerialDebug("Handle Configuration request data :");
  SerialDebug(server->arg("plain"));
  SerialDebug("\n");
  #endif
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, server->arg("plain"));
    if (error) {
    #ifdef DEBUG 
    SerialDebug(F("deserializeJson() failed: "));
    SerialDebug(error.c_str());    
    #endif
    return server->send(500, "text/json", "{success:false}");
  }
  JsonObject data = doc.as<JsonObject>();
  strncpy(Device.Config.DeviceName,(const char *)data["deviceName"],sizeof(Device.Config.DeviceName));
  strncpy(Device.Config.ServerAddress,(const char *)data["serverAddress"],sizeof(Device.Config.ServerAddress));
  strncpy(Device.Config.WifiSsid,(const char *)data["ssid"],sizeof(Device.Config.WifiSsid));
  strncpy(Device.Config.WifiPassword,(const char *)data["password"],sizeof(Device.Config.WifiPassword));
  Device.save();
  isCompleted = true;
  server->send ( 200, "text/json", "{success:true}" );
}

void WebConfig::handleInfo(){
  String s = "{\"serialNo\":\"";
  s+=Device.SerialNumber();
  s+="\",\"deviceName\":\"";
  s+=Device.Config.DeviceName;
  s+="\",\"serverAddress\":\"";
  s+=Device.Config.ServerAddress;
  s+="\"}";
  server->send ( 200, "text/json", s );
}

void WebConfig::begin(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid,ap_password);
  //dnsServer = new DNSServer();
  server = new ESP8266WebServer(80);
  server->on("/", [this]{handleRoot();});
  server->on("/config",HTTP_POST, [this]{handleConfig();});
  server->on("/info", [this]{handleInfo();});

  //MDNS.begin(this->ap_ssid);
  //MDNS.addService("http", "tcp", 80);
  WiFi.hostname(this->ap_ssid);
  server->begin();
  //dnsServer->start(AP_DNS_PORT, "*", WiFi.softAPIP());
#ifdef DEBUG
  IPAddress myIP = WiFi.softAPIP();
  SerialDebug("SoftAP Address : ");
  SerialDebug(myIP);
  SerialDebug("\n");
#endif
}

WebConfig::~WebConfig(){
  server->stop(); 
}


