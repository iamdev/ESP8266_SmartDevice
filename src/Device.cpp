#include "Device.h"

#include "EEPROM_EX.h"
#include "ESP8266TrueRandom.h"

DeviceClass::DeviceClass(unsigned char signature):_signature(signature){
}

void DeviceClass::init(){
    delay(100);
    unsigned char sig = eeprom.read(DEVICE_DATA_SIGNATURE_ADDR);
    if(sig != _signature){
        Device.format();
    }else{
        eeprom.read(DEVICE_DATA_SERIALNO_ADDR,&this->serialno,sizeof(this->serialno));
    }
    this->load();
}

void DeviceClass::load(){
    eeprom.read(DEVICE_DATA_CONFIG_ADDR,&(this->Config),sizeof(this->Config));
}

void DeviceClass::save(){
    eeprom.write(DEVICE_DATA_CONFIG_ADDR,&Config,sizeof(this->Config));
}

void DeviceClass::format(){
    this->serialno = DEVICE_ID_PREFIX + ESP8266TrueRandom.random(DEVICE_ID_MIN,DEVICE_ID_MAX);
    this->Config = {};
    this->save();
    eeprom.write(DEVICE_DATA_SERIALNO_ADDR,&(this->serialno),sizeof(this->serialno));    
    eeprom.write(DEVICE_DATA_SIGNATURE_ADDR,_signature);
}
