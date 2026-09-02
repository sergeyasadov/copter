#ifndef TON_H
#define TON_H

#include <stm32f1xx.h>

struct TON {
    uint8_t IN;
    uint32_t PT;

    uint8_t Q;
    uint32_t ET;

    uint32_t startTime;
    uint8_t prevIN;

    uint32_t (*fGetCurrentMS)(void);
};

void TON_Init(struct TON* timer, uint32_t (*fGetCurrentMS)(void));

void TON_Update(struct TON* timer);

#endif
