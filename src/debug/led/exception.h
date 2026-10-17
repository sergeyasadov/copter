#ifndef DEBUG_LED_EXCEPTION_H
#define DEBUG_LED_EXCEPTION_H

#include "../../defines.h"


__STATIC_FORCEINLINE void DebugLed_Exception_Init(void) {
    GPIOB->CRL &= ~(0b1111u << (4 * DL2_EXCEPTION));
    GPIOB->CRL |= (0b0010u << (4 * DL2_EXCEPTION));
}

__STATIC_FORCEINLINE void DebugLed_Exception_On(void) {
    GPIOB->BSRR = (1u << DL2_EXCEPTION);
}

__STATIC_FORCEINLINE void DebugLed_Exception_Off(void) {
    GPIOB->BSRR = (1u << DL2_EXCEPTION) << 16;
}


#endif // DEBUG_LED_EXCEPTION_H
