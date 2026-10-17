#ifndef DEBUG_LED_H
#define DEBUG_LED_H

#include "led/power.h"
#include "led/signal.h"
#include "led/exception.h"

#include "../status.h"


enum DebugLed_Types {
    DL_TYPE_POWER,
    DL_TYPE_SIGNAL,
    DL_TYPE_EXCEPTION
};


#define STATE_SWITCH(__state, __on, __off) do {\
    switch(__state) {\
        case 0: { __off; }\
        case 1: { __on; }\
    }\
} while(0)

#define TYPE_SWITCH(__type, __t0, __s0, __t1, __s1, __t2, __s2) do{\
    switch(__type) {\
        case DL_TYPE_POWER: {__s0; return;}\
        case DL_TYPE_SIGNAL: {__s1; return;}\
        case DL_TYPE_EXCEPTION: {__s2; return;}\
        default: return;\
    }\
} while(0)


__STATIC_FORCEINLINE void DebugLed_Init(const enum DebugLed_Types t) {
    TYPE_SWITCH(t,
        DL_TYPE_POWER, DebugLed_Power_Init(),
        DL_TYPE_SIGNAL, DebugLed_Signal_Init(),
        DL_TYPE_EXCETPION, DebugLed_Exception_Init()
    );
}


__STATIC_FORCEINLINE void DebugLed_SetState(const enum DebugLed_Types t, const uint_fast8_t state) {
    TYPE_SWITCH(t,
        DL_TYPE_POWER, STATE_SWITCH(state,
            DebugLed_Power_Off(),
            DebugLed_Power_On()
        ),
        DL_TYPE_SIGNAL, STATE_SWITCH(state,
            DebugLed_Signal_Off(),
            DebugLed_Signal_On()
        ),
        DL_TYPE_EXCEPTION, STATE_SWITCH(state,
            DebugLed_Exception_Off(),
            DebugLed_Exception_On()
        )
    );
}


__STATIC_FORCEINLINE void DebugLed_SetStatus(const enum Status status) {
    STATUS_SWITCH(
        status,
        {
            DebugLed_Signal_On();
            DebugLed_Exception_Off();
        },
        {
            DebugLed_Exception_Off();
            DebugLed_Signal_Off();
        },
        {
            DebugLed_Exception_On();
            DebugLed_Signal_Off();
        }
    );
}


#endif // DEBUG_LED_H
