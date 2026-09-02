#include "../defines.h"


static inline void _dl_exception_init(void) {
    GPIOB->CRL &= ~(0b1111u << (4 * DL2_EXCEPTION));
    GPIOB->CRL |= (0b0010u << (4 * DL2_EXCEPTION));
}

static inline void _dl_exception_on(void) {
    GPIOB->BSRR = (1u << DL2_EXCEPTION);
}

static inline void _dl_exception_off(void) {
    GPIOB->BSRR = (1u << DL2_EXCEPTION) << 16;
}
