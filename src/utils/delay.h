#ifndef DELAY_MS
#define DELAY_MS

#include <stdint.h>
#include "../defines.h"
#include "../systick.h"



__STATIC_INLINE void delay_ms(const uint32_t ms) {
    uint32_t start = SysTick_Get();
    while((SysTick_Get() - start) < ms);
}

#endif //
