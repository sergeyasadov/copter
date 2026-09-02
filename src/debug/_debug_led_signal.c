#include "../defines.h"

static inline void _dl_signal_init(void) {
    GPIOB->CRL &= ~(0b1111u << (4 * DL1_SIGNAL));
    GPIOB->CRL |= (0b0010u << (4 * DL1_SIGNAL));
}

static inline void _dl_signal_on(void) {
    GPIOB->BSRR = (1u << DL1_SIGNAL);
}

static inline void _dl_signal_off(void) {
    GPIOB->BSRR = (1u << DL1_SIGNAL) << 16;
}
