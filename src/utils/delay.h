#ifndef DELAY_MS
#define DELAY_MS

#include <stdint.h>
#include "../systick.h"

void delay_ms(const uint32_t ms) {
    uint32_t start = SysTick_Get();
    while((SysTick_Get() - start) < ms);
}

#endif //
