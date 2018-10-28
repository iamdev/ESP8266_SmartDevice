#ifndef _WIFI_CONFIG_H
#define _WIFI_CONFIG_H
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h> // -- For captive portal
#include <ESP8266HTTPUpdateServer.h>
//#include <ESP8266mDNS.h>


#define DEFAULT_AP_SSID "esp_ap_config"
#define DEFAULT_AP_PASSWORD "88888888"
#define AP_DNS_PORT 53

class WebConfig{
    public :
        WebConfig();
        WebConfig(const char * ap_ssid,const char * ap_password);
        ~WebConfig();
        void begin(void);        
        bool run();
    private:
        void handleRoot(void);
        void handleConfig(void);
        void handleInfo();
        bool isIp(String str);
        String toStringIp(IPAddress ip);
        DNSServer *dnsServer;
        ESP8266WebServer *server;
        bool isCompleted = false;        
        char ap_ssid[32];
        char ap_password[32];
};


#endif
