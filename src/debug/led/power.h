#ifndef DEBUG_LED_POWER_H
#define DEBUG_LED_POWER_H

#include "../../defines.h"

__STATIC_FORCEINLINE void DebugLed_Power_Init(void) {
    GPIOB->CRL &= ~(0b1111u << (4 * DL0_POWER));
    GPIOB->CRL |= (0b0010u << (4 * DL0_POWER));
}

__STATIC_FORCEINLINE void DebugLed_Power_On(void) {
    GPIOB->BSRR = (1u << DL0_POWER);
}

__STATIC_FORCEINLINE void DebugLed_Power_Off(void) {
    GPIOB->BSRR = (1u << (DL0_POWER + 16UL));
}


#endif // DEBUG_LED_POWER_H
