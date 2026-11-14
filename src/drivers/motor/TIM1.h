#ifndef TIMER1_H
#define TIMER1_H

#include "../../defines.h"
#include "stm32f103xb.h"



__STATIC_INLINE void TIM1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
    GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;


//
//     TIM1->PSC = 72 - 1;
//     TIM1->ARR = 1000 - 1;
//
//     TIM1->CCR1 = 0;
//
//     TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
//     TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
//
//
//     TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
//
//     TIM1->CCER |= TIM_CCER_CC1E;
//
//     TIM1->BDTR |= TIM_BDTR_MOE;
//
//     TIM1->CR1 |= TIM_CR1_ARPE;
//
//     TIM1->CR1 |= TIM_CR1_CEN;
}


__STATIC_INLINE void TIM1_Set(uint_fast8_t v) {
    if(v > 100) v = 100;

    TIM1->CCR1 = (TIM1->ARR + 1) * v / 100;
}


#endif // TIMER1_H
