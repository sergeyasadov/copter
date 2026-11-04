#ifndef DEBUG_LED_EXCEPTION_H
#define DEBUG_LED_EXCEPTION_H

#include "../../defines.h"


__STATIC_FORCEINLINE void DebugLed_Exception_Init(void) {
    GPIOB->CRL &= ~(0xFUL << (4 * DL2_EXCEPTION));
    GPIOB->CRL |= (0x2UL << (4 * DL2_EXCEPTION));
}

__STATIC_FORCEINLINE void DebugLed_Exception_On(void) {
    GPIOB->BSRR = (1UL << DL2_EXCEPTION);
}

__STATIC_FORCEINLINE void DebugLed_Exception_Off(void) {
    GPIOB->BSRR = (1UL << DL2_EXCEPTION) << 16UL;
}

__STATIC_FORCEINLINE void DebugLed_Exception_Toggle(void) {
    GPIOB->ODR ^= (1UL << DL2_EXCEPTION);
}


#endif // DEBUG_LED_EXCEPTION_H
