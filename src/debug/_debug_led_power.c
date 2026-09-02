#include "../defines.h"

static inline void _dl_power_init(void) {
    GPIOB->CRL &= ~(0b1111u << (4 * DL0_POWER));
    GPIOB->CRL |= (0b0010u << (4 * DL0_POWER));
}

static inline void _dl_power_on(void) {
    GPIOB->BSRR = (1u << DL0_POWER);
}

static inline void _dl_power_off(void) {
    GPIOB->BRR = (1u << DL0_POWER) << 16;
}
