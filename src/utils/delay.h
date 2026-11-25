#ifndef DELAY_MS
#define DELAY_MS

#include "../defines.h"

extern uint32_t SysTick_Get(void);

__USED __STATIC_INLINE void DelayMs(uint32_t ms) {
    uint32_t start = SysTick_Get();
    while((SysTick_Get() - start) < ms) {
        __NOP();
    }
}


__attribute__((deprecated))
__STATIC_INLINE void _DelayMs(uint32_t ms) {
    if(ms > 0) {
        if(SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk) {
            ms--;
        }
    }
}

#endif //
