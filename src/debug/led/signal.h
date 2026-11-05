#ifndef DEBUG_LED_SIGNAL_H
#define DEBUG_LED_SIGNAL_H

#include "../../defines.h"

__STATIC_FORCEINLINE void DebugLed_Signal_Init(void) {
    GPIOB->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
    GPIOB->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;
}

__STATIC_FORCEINLINE void DebugLed_Signal_On(void) {
    GPIOB->BSRR = (1UL << DL1_SIGNAL);
}

__STATIC_FORCEINLINE void DebugLed_Signal_Off(void) {
    GPIOB->BSRR = (1UL << (DL1_SIGNAL + 16));
}


#endif // DEBUG_LED_SIGNAL_H
