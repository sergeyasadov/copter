#ifndef DEBUG_LED_POWER_H
#define DEBUG_LED_POWER_H


#include "../../defines.h"


__STATIC_FORCEINLINE void DebugLed_Power_Init(void) {
    GPIOB->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOB->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1;
}

__STATIC_FORCEINLINE void DebugLed_Power_On(void) {
    GPIOB->BSRR |= (1UL << DL0_POWER);
}

__STATIC_FORCEINLINE void DebugLed_Power_Off(void) {
    GPIOB->BRR |= (1UL << DL0_POWER);
}


#endif // DEBUG_LED_POWER_H
