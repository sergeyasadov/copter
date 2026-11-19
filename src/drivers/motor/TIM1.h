#ifndef TIMER1_H
#define TIMER1_H

#include <stm32f103xb.h>


__STATIC_INLINE void TIM1_GPIO_Channel1_Init(void) {
    GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;
}


__STATIC_INLINE void TIM1_GPIO_Channel2_Init(void) {
    GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
    GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
}


__STATIC_INLINE void TIM1_GPIO_Channel3_Init(void) {
    GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
    GPIOA->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1;
}


__STATIC_INLINE void TIM1_GPIO_Channel4_Init(void) {
    GPIOA->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
    GPIOA->CRH |= GPIO_CRH_MODE11 | GPIO_CRH_CNF11_1;
}

__STATIC_INLINE void TIM1_Channel1_Init(void) {
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
}


__STATIC_INLINE void TIM1_Channel2_Init(void) {
    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM1->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
    TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
}


__STATIC_INLINE void TIM1_Channel3_Init(void) {
    TIM1->CCMR2 &= ~TIM_CCMR2_OC3M;
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
    TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
}


__STATIC_INLINE void TIM1_Channel4_Init(void) {
    TIM1->CCMR2 &= ~TIM_CCMR2_OC4M;
    TIM1->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
    TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
}


__STATIC_INLINE void TIM1_GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

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

    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
    TIM1->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;

    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_ARPE;

    TIM1->CR1 |= TIM_CR1_CEN;
}


__STATIC_INLINE void TIM1_CH1_Set(uint_fast8_t v) {
    if(v > 100) v = 100;
    TIM1->CCR1 = (TIM1->ARR + 1) * v / 100;
}


__STATIC_INLINE void TIM1_CH2_Set(uint_fast8_t v) {
    if(v > 100) v = 100;
    TIM1->CCR2 = (TIM1->ARR + 1) * v / 100;
}


__STATIC_INLINE void TIM1_CH3_Set(uint_fast8_t v) {
    if(v > 100) v = 100;
    TIM1->CCR3 = (TIM1->ARR + 1) * v / 100;
}


__STATIC_INLINE void TIM1_CH4_Set(uint_fast8_t v) {
    if(v > 100) v = 100;
    TIM1->CCR4 = (TIM1->ARR + 1) * v / 100;
}


#endif // TIMER1_H
