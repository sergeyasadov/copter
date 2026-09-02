#include "delay.h"

void delay_us(const uint32_t us) {
    uint32_t cycles = (SystemCoreClock / 1000000u) * us / 4;
    while(cycles--) __NOP();
}

void delay_ms(const uint32_t ms) {
    delay_us(ms * 1000u);
}
