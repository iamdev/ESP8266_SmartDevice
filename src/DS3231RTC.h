#ifndef _DS3231RTC_H
#define _DS3231RTC_H
#include <Wire.h>
#include "DateTime.h"
#define DS3231_I2C_ADDR             0x68

#define DS3231_TIME_CAL_ADDR        0x00
#define DS3231_TEMPERATURE_ADDR     0x11
#define DS3231_CONTROL_ADDR         0x0E
#define DS3231_STATUS_ADDR          0x0F

class DS3231RTC{
    public:
        DS3231RTC(TwoWire *wire);
        DS3231RTC();
        float getTemperature();
        void set(DateTime t);
        void set(time_t t);
        struct DateTime now();
    private:
        void set_addr(const uint8_t addr, const uint8_t val);
        uint8_t get_addr(const uint8_t addr);
        void set_creg(const uint8_t val);
        void set_sreg(const uint8_t val);
        uint8_t get_sreg(void);
        TwoWire *_wire;
};

extern DS3231RTC rtc;
#endif