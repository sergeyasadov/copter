#ifndef STATUS_CODE_H
#define STATUS_CODE_H

// #include <cmsis_clang.h>
#include <stdint.h>


#define MAKE_STATUS(__mod, __err)   ((uint32_t)(((__mod) << 16) | (__err)))
#define GET_STATUS(__status)        ((uint32_t)(((__status) >> 16) & 0xFFFF))
#define GET_ERROR(__status)         ((uint32_t)((__status) & 0xFFFF))


enum Status_ModuleID {
    MOD_SYS = 0x0000,
    MOD_UART = 0x0001,
    MOD_CRSF = 0x0002
};


enum Status : uint32_t {
    // Sys
    STATUS_OK = MAKE_STATUS(MOD_SYS, 0x0000),
    STATUS_ERROR = MAKE_STATUS(MOD_SYS, 0x0001),
    STATUS_EXCEPTION = MAKE_STATUS(MOD_SYS, 0x0002),

    // CRSF
    STATUS_CRSF_RECEIVED = MAKE_STATUS(MOD_CRSF, 0x0000),
    STATUS_CRSF_NOT_RECEIVED = MAKE_STATUS(MOD_CRSF, 0x0001),
    STATUS_CRSF_TIMEOUT = MAKE_STATUS(MOD_CRSF, 0x0002),

    // STATUS_UNKNOWN = MAKE_STATUS(MOD_SYS, 0xFFFF)
};


#define STATUS_SWITCH(__status, f_OK, f_ERR, f_EXC) do {\
    switch(__status) {\
        case STATUS_OK: {\
            f_OK;\
            return;\
        }\
        case STATUS_ERROR: {\
            f_ERR;\
            return;\
        }\
        case STATUS_EXCEPTION: {\
            f_EXC;\
            return;\
        }\
        default: return;\
    }\
} while(0)

#endif //
