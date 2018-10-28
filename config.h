#ifndef _CONFIG_H
#define _CONFIG_H

#ifndef SDA 
#define SDA     4
#endif 

#ifndef SCL 
#define SCL     5
#endif 

#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif
#define LED_BUILTIN         2


#define DEBUG

#define EEPROM_I2C_ADDR             0x50
#define EEPROM_SIZE                 0x8000
//#define EEPROM_DEVICE_INFO_ADDR     1
//#define EEPROM_TRANSACTION_ADDR     256
//#define EERROM_FORMAT_SIGNATURE     0x5A
#define DEVICE_SIGNATURE    0x5B

#define DS3231_I2C_ADDR     0x68
#define RTC_INT_PIN         2

#define I2C_SDA             SDA
#define I2C_SCL             SCL
#define BUTTON_PIN          16

static char ntpServer[100] = "pool.ntp.org";
//static int ntpTimeZone = 7 
//static int minutesTimeZone = 0;
#define ntpTimeZone 7
#define minutesTimeZone 0

#define AP_WEBCONFIG_NAME   "ESP-"
#define AP_WEBCONFIG_PASSWORD "88888888"
#include "src/debug.h"
#endif

