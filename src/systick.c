#include "systick.h"


static volatile uint32_t sys_ticks;


void SysTick_Handler(void) {
    sys_ticks++;
}


uint32_t SysTick_Get(void) {
    return sys_ticks;
}
