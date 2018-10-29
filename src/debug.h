#ifdef DEBUG
    #define SerialDebug(...) Serial.print(__VA_ARGS__)
    #define SerialDebug_printf(...) { \
        char _buf[256]; \
        snprintf(_buf,256,__VA_ARGS__); \
        Serial.print(_buf);\
    }
#else
    #define SerialDebug(...)
    #define SerialDebug_printf(...)
#endif
