#ifndef DELAY_MS
#define DELAY_MS

#include <stdint.h>
#include "../defines.h"
#include "../systick.h"



__USED __STATIC_INLINE void delay_ms(uint32_t ms) {
    uint32_t start = SysTick_Get();
    while((SysTick_Get() - start) < ms) {
        __NOP();
    }
    // if(ms > 0) {
    //     if(SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk) {
    //         ms--;
    //     }
    // }
}

#endif //
