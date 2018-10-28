#ifndef _DEVICE_H
#define _DEVICE_H

#define DEVICE_ID_PREFIX    100e7
#define DEVICE_ID_MIN       1000000
#define DEVICE_ID_MAX       9999999

struct DeviceConfig{
    char WifiSsid [64];
    char WifiPassword [64];
    char ServerAddress[32];
    char DeviceName[32];
};

class DeviceClass{
    public :
        DeviceClass(unsigned char signature);        
        void format();
        void init();        
        void load();
        void save();
        struct DeviceConfig Config;
        unsigned long SerialNumber() const {return serialno;}        
    private:  
        unsigned long serialno;
        unsigned char _signature;
}; 

extern DeviceClass Device;
#endif