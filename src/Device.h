#ifndef _DEVICE_H
#define _DEVICE_H

#define DEVICE_ID_PREFIX    100e7
#define DEVICE_ID_MIN       1000000
#define DEVICE_ID_MAX       9999999


#define DEVICE_DATA_ADDR        0
#define DEVICE_DATA_SIGNATURE_ADDR   DEVICE_DATA_ADDR 
#define DEVICE_DATA_SERIALNO_ADDR    (DEVICE_DATA_ADDR+1)
#define DEVICE_DATA_CONFIG_ADDR      64  

struct DeviceConfig{
    char WifiSsid [64];
    char WifiPassword [64];
    char DeviceName[32];
    char ServerAddress[128];
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