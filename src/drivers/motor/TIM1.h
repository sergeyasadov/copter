#ifndef TIMER1_H
#define TIMER1_H

#include "../../defines.h"


__STATIC_INLINE void TIM1_GPIO_Channel1_Init(void) {
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8))
                | GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;
}


__STATIC_INLINE void TIM1_GPIO_Channel2_Init(void) {
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9))
                | GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
}


__STATIC_INLINE void TIM1_GPIO_Channel3_Init(void) {
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10))
                | GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1;
}


__STATIC_INLINE void TIM1_GPIO_Channel4_Init(void) {
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11))
                | GPIO_CRH_MODE11 | GPIO_CRH_CNF11_1;
}

__STATIC_INLINE void TIM1_Channel1_Init(void) {
    TIM1->CCMR1 = (TIM1->CCMR1 & ~TIM_CCMR1_OC1M)
                | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1
                | TIM_CCMR1_OC1PE;
}


__STATIC_INLINE void TIM1_Channel2_Init(void) {
    TIM1->CCMR1 = (TIM1->CCMR1 & ~TIM_CCMR1_OC2M)
                | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1
                | TIM_CCMR1_OC2PE;
}


__STATIC_INLINE void TIM1_Channel3_Init(void) {
    TIM1->CCMR2 = (TIM1->CCMR1 & ~TIM_CCMR2_OC3M)
                | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1
                | TIM_CCMR2_OC3PE;
}


__STATIC_INLINE void TIM1_Channel4_Init(void) {
    TIM1->CCMR2 = (TIM1->CCMR1 & ~TIM_CCMR2_OC4M)
                | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1
                | TIM_CCMR2_OC4PE;
}


__STATIC_INLINE void TIM1_GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN;

    TIM1_GPIO_Channel1_Init();
    TIM1_GPIO_Channel2_Init();
    TIM1_GPIO_Channel3_Init();
    TIM1_GPIO_Channel4_Init();
}


__STATIC_INLINE void TIM1_Init(void) {
    TIM1->PSC = 72 - 1;
    TIM1->ARR = 1000 - 1;

    TIM1_Channel1_Init();
    TIM1_Channel2_Init();
    TIM1_Channel3_Init();
    TIM1_Channel4_Init();

    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E
                | TIM_CCER_CC3E | TIM_CCER_CC4E;

    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}


__STATIC_INLINE void TIM1_CH_Set(const uint_fast8_t ch, uint_fast8_t val) {
    if(val > 100)
        val = 100;

    switch(ch) {
        case 0: { TIM1->CCR1 = (TIM1->ARR + 1) * val / 100; return; }
        case 1: { TIM1->CCR2 = (TIM1->ARR + 1) * val / 100; return; }
        case 2: { TIM1->CCR3 = (TIM1->ARR + 1) * val / 100; return; }
        case 3: { TIM1->CCR4 = (TIM1->ARR + 1) * val / 100; return; }
        default: return;
    }
}




#endif // TIMER1_H
