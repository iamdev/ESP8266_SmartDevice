#include "AutoUpdate.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "Device.h"
#define DEBUG
#ifdef DEBUG
#include "debug.h"
#else
#define SerialDebug_printf(...)
#define SerialDebug(...)
#endif

bool autoUpdate(const char*serverAddress,const char * currentVersion){
   if(WiFi.status() == WL_CONNECTED){
    char versionUrl[100];
    snprintf(versionUrl,100,"%s/firmware/version",serverAddress);
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin(versionUrl);  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code 
      String payload = http.getString();   //Get the request response payload
      SerialDebug_printf("Payload:\n================\n%s\n================\n",payload.c_str());//Print the response payload
 
    }else{
       SerialDebug("Get firmware version fail!\n");
    }
 
    http.end();   //Close connection
    
    /*
    char binUrl[100];
    snprintf(bin,100,"%s/firmware.bin",updateUrl);
    t_httpUpdate_return ret = ESPhttpUpdate.update("http://192.168.1.101:88/firmware.bin");

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        USE_SERIAL.println("HTTP_UPDATE_OK");
        break;
    }
    */
  }
}
