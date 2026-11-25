#ifndef DEBUG_LED_SIGNAL_H
#define DEBUG_LED_SIGNAL_H

#include "../../defines.h"
#include "../../iodefs.h"


__STATIC_FORCEINLINE void DebugLed_Signal_Init(void) {
    GPIOB->CRH = (GPIOB->CRH & ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9))
                | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;
}


__STATIC_FORCEINLINE void DebugLed_Signal_On(void) {
    GPIOB->BSRR = GPIO_DL1_SIGNAL;
}


__STATIC_FORCEINLINE void DebugLed_Signal_Off(void) {
    GPIOB->BRR = GPIO_DL1_SIGNAL;
}


#endif // DEBUG_LED_SIGNAL_H
