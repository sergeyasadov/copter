#ifndef DEBUG_LED_POWER_H
#define DEBUG_LED_POWER_H

#include "../../defines.h"
#include "../../iodefs.h"


__STATIC_FORCEINLINE void DebugLed_Power_Init(void) {
    GPIOB->CRH = (GPIOB->CRH & ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8))
                | GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1;
}


__STATIC_FORCEINLINE void DebugLed_Power_On(void) {
    GPIOB->BSRR |= GPIO_DL0_POWER;
}


__STATIC_FORCEINLINE void DebugLed_Power_Off(void) {
    GPIOB->BRR |= GPIO_DL0_POWER;
}


#endif // DEBUG_LED_POWER_H
