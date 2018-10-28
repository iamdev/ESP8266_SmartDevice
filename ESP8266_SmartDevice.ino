#include "config.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "src/EEPROM_EX.h"
#include "src/Device.h"
#include "src/ESP8266TrueRandom.h"
#include "src/DS3231RTC.h"
#include "src/NtpClient.h"
#include "src/WebConfig.h"

EEPROM_EX eeprom(EEPROM_I2C_ADDR); 
DeviceClass Device(DEVICE_SIGNATURE);
DS3231RTC rtc;
bool ntpSuccess = false;

void handleWebConfig(){
  String ssid = AP_WEBCONFIG_NAME;
  ssid += Device.SerialNumber();
  WebConfig wc(ssid.c_str(),AP_WEBCONFIG_PASSWORD);
  wc.begin();
  while(wc.run());
  char buf[256];
  eeprom.read(0,buf,256);
  delay(3000);
}

void setup() {
#ifdef DEBUG
  Serial.begin(115200);  
  delay(100); 
  SerialDebug("\n");
#endif
  SerialDebug("\n");
  Wire.begin(I2C_SDA,I2C_SCL);
  delay(1000);
  Device.init();
  SerialDebug_printf("Device Serial-Number:%d\n",Device.SerialNumber());

  SerialDebug("Connecting to WiFi.\n");
  
  pinMode(16,INPUT);
  if(!digitalRead(16)){
    pinMode(2,OUTPUT);
    digitalWrite(2,LOW);
    handleWebConfig();
    digitalWrite(2,HIGH);
    pinMode(2,INPUT);
    ESP.reset();
  }
  /**********************/

  SerialDebug("Device Confuguration :\n");
  SerialDebug_printf("Wifi SSID:%s\n",Device.Config.WifiSsid);
  SerialDebug_printf("Wifi Password:%s\n",Device.Config.WifiPassword);
  SerialDebug_printf("Server Address:%s\n",Device.Config.ServerAddress);
  SerialDebug_printf("Device name:%s\n",Device.Config.DeviceName);

  WiFi.mode(WIFI_STA);
  WiFi.begin(Device.Config.WifiSsid,Device.Config.WifiPassword);
  {
    long _ms = millis();
    while (WiFi.status() != WL_CONNECTED && millis()<(_ms+5000)) {
      delay(200);
      SerialDebug(".");
    }
  }
  SerialDebug("\n");
  #ifdef DEBUG
  WiFi.printDiag(Serial);
  #endif
  /*NTP Sync*************/  
  if(WiFi.status() == WL_CONNECTED)
  {
    SerialDebug_printf("Start NTP Sync...");
    NtpClient ntp(ntpServer);
    ntp.begin();
    time_t tt = ntp.getTime();
    if(tt>0){
      SerialDebug_printf("success.\n");
      SerialDebug_printf("Unix Time : %u\n",(long)tt);
      rtc.set(tt);
    }else{
      SerialDebug_printf("timeout.\n");
    }
  }
/***********************/ 
  DateTime t = rtc.now();
  SerialDebug_printf("Current DateTime : %02u/%02u/%4u %02u:%02u:%02u \n",t.day,t.month,t.year,t.hour,t.minute,t.second);
}

void loop() {
}

