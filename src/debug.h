#ifdef DEBUG
    #define SerialDebug(...) Serial.print(__VA_ARGS__)
    #define SerialDebug_printf(...) { \
        char _buf[100]; \
        snprintf(_buf,100,__VA_ARGS__); \
        Serial.print(_buf);\
    }
#else
    #define SerialDebug(...)
    #define SerialDebug_printf(...)
#endif
