#ifndef DEBUG_LED_EXCEPTION_H
#define DEBUG_LED_EXCEPTION_H

#include "../../defines.h"
#include "../../iodefs.h"


__STATIC_FORCEINLINE void DebugLed_Exception_Init(void) {
    GPIOB->CRL = (GPIOB->CRL & ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5))
                | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1;
}

__STATIC_FORCEINLINE void DebugLed_Exception_On(void) {
    GPIOB->BSRR = GPIO_DL2_EXCEPTION;
}

__STATIC_FORCEINLINE void DebugLed_Exception_Off(void) {
    GPIOB->BRR = GPIO_DL2_EXCEPTION;
}

__STATIC_FORCEINLINE void DebugLed_Exception_Toggle(void) {
    GPIOB->ODR ^= GPIO_DL2_EXCEPTION;
}


#endif // DEBUG_LED_EXCEPTION_H
