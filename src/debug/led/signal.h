#ifndef DEBUG_LED_SIGNAL_H
#define DEBUG_LED_SIGNAL_H

#include "../../defines.h"

__STATIC_FORCEINLINE void DebugLed_Signal_Init(void) {
    GPIOB->CRL &= ~(0b1111u << (4 * DL1_SIGNAL));
    GPIOB->CRL |= (0b0010u << (4 * DL1_SIGNAL));
}

__STATIC_FORCEINLINE void DebugLed_Signal_On(void) {
    GPIOB->BSRR = (1u << DL1_SIGNAL);
}

__STATIC_FORCEINLINE void DebugLed_Signal_Off(void) {
    GPIOB->BSRR = (1u << DL1_SIGNAL) << 16;
}


#endif // DEBUG_LED_SIGNAL_H
