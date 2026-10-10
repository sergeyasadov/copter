#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "../defines.h"

extern uint32_t SystemCoreClock;


__STATIC_INLINE void ClockConfig_8MHz_HSI(void) {
    RCC->CR |= RCC_CR_HSION;
    while(!(RCC->CR & RCC_CR_HSIRDY));

    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_0;

    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1;

    RCC->CR &= ~RCC_CR_PLLON;

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_HSI;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

    SystemCoreClock = 8000000;
    SysTick_Config(SystemCoreClock / 1000);
}


__STATIC_INLINE int ClockConfig_72MHz_HSE(void) {
    uint32_t t;

    RCC->CR |= RCC_CR_HSEON;
    for(t = 0; t < 200000 && !(RCC->CR & RCC_CR_HSERDY); t++);
    if(!(RCC->CR & RCC_CR_HSERDY)) {
        RCC->CR &= ~RCC_CR_HSEON;
        SystemCoreClock = 8000000;
        SysTick_Config(SystemCoreClock / 1000);
        return -1;
    }

    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_2 | FLASH_ACR_PRFTBE;

    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2
                             | RCC_CFGR_PLLMULL | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC))
              | RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1
              | RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC;

    RCC->CR |= RCC_CR_PLLON;
    for(t = 0; t < 200000 && !(RCC->CR & RCC_CR_PLLRDY); t++);
    if(!(RCC->CR & RCC_CR_PLLRDY)) {
        RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_HSEON);
        SystemCoreClock = 8000000;
        SysTick_Config(SystemCoreClock / 1000);
        return -2;
    }

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    SystemCoreClock = 72000000;
    SysTick_Config(SystemCoreClock / 1000);
    return 0;
}




#endif //
