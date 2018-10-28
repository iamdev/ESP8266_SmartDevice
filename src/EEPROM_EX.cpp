#include "EEPROM_EX.h"
#include <Arduino.h>
#define DEBUG

#ifdef DEBUG
#include "debug.h"
#endif

EEPROM_EX::EEPROM_EX(TwoWire *wire,int deviceAddress)
    :_wire(wire),_deviceAddress(deviceAddress)
{
    _wire->beginTransmission(_deviceAddress);
    _isValid = (_wire->endTransmission()==0);
}

EEPROM_EX::EEPROM_EX(int deviceAddress)
    :EEPROM_EX(&Wire,deviceAddress)
{
}
bool EEPROM_EX::isValid(){
    return _isValid;
}

unsigned char EEPROM_EX::read(unsigned int address){
    int rdata = 0xFF;
    _wire->beginTransmission(_deviceAddress);
    _wire->write((int)(address >> 8)); // MSB
    _wire->write((int)(address & 0xFF)); // LSB
    _wire->endTransmission();
    _wire->requestFrom(_deviceAddress,1);
    if (_wire->available()) rdata = _wire->read();
    delay(EEPROM_RW_DELAY);
#ifdef DEBUG
    SerialDebug_printf("Read EEPROM 1 byte to address %04X : %02X\n",address,(unsigned char)(rdata&0xFF));
#endif
    return (unsigned char)(rdata&0xFF);
}
 
void EEPROM_EX::write(unsigned int address,unsigned char data){
#ifdef DEBUG
    SerialDebug_printf("Write EEPROM 1 byte to address %04X : %02X\n",address,data);
#endif
    int rdata = data;
    _wire->beginTransmission(_deviceAddress);
    _wire->write((int)(address >> 8)); // MSB
    _wire->write((int)(address & 0xFF)); // LSB
    _wire->write(rdata);
    _wire->endTransmission(); 
    delay(EEPROM_RW_DELAY);    
}

void EEPROM_EX::read(unsigned int address,void *buffer,int length){ 
    unsigned char * _buf = (unsigned char *) buffer;
    int remain = length;
#ifdef DEBUG
    int h = 0;
    SerialDebug_printf("Read EEPROM %d bytes from address %04X:\n",length,address);
#endif
    while(remain>0){
        int n = EEPROM_PAGE_SIZE;
        if(n>remain){
            n=remain;
            remain =0;
        }else{
            remain -=n;
        }        
        _wire->beginTransmission(_deviceAddress);
        _wire->write((int)(address >> 8)); // MSB
        _wire->write((int)(address & 0xFF)); // LSB
        _wire->endTransmission();
        _wire->requestFrom(_deviceAddress,n);
        address+=n;
        for (int c = 0; c < n; c++ ){
            if (_wire->available()) *_buf++ = _wire->read()&0xff;                    
#ifdef DEBUG            
            SerialDebug_printf("%02X ",((unsigned char *)buffer)[h]);
            if((++h % 16)==0){
                SerialDebug("\n");
            }
#endif                        
        }
        //delay(EEPROM_RW_DELAY);        
    }
#ifdef DEBUG
    SerialDebug("\n");
#endif
}
#define EEPROM_WRITE_PAGE 0
void EEPROM_EX::write(unsigned int address,void *buffer,int length){
#if EEPROM_WRITE_PAGE > 0    
    unsigned char * _buf = (unsigned char *)buffer;
    int remain = length;
#ifdef DEBUG
    int h = 0;
    SerialDebug_printf("Write EEPROM %d bytes to address %04X:\n",length,address);
#endif
    int s = (address/64)*64;
    while(s<address){
        SerialDebug("-- ");
        if(++s%16 == 0)SerialDebug("\n");
    }
    while(h<length){
        _wire->beginTransmission(_deviceAddress);
        _wire->write((int)(s >> 8)); // MSB
        _wire->write((int)(s & 0xFF)); // LSB
        for (;;){
            Wire.write(*_buf++);
#ifdef DEBUG            
            SerialDebug_printf("%02X ",((unsigned char *)buffer)[h]);
            if((++s % 16)==0){
                SerialDebug("\n");
            }
#endif      
            h++;
            if(s%64==0)
            {
#ifdef DEBUG                   
                for(int i=0;i<16;i++)SerialDebug("---");
                SerialDebug("\n");
#endif                      
                break;
            }
            if(h>=length)break;
        }                
        _wire->endTransmission();
        delay(EEPROM_RW_DELAY);
    }
#ifdef DEBUG
    SerialDebug("\n");
#endif
    
#else
    for(int i=0;i<length;i++){
        _wire->beginTransmission(_deviceAddress);
        _wire->write((int)((address+i) >> 8)); // MSB
        _wire->write((int)((address+i) & 0xFF)); // LSB
        _wire->write(((unsigned char *)buffer)[i]);
        _wire->endTransmission();                 
        delay(EEPROM_RW_DELAY);
    }
#endif


}
