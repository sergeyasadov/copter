#ifndef UTILS_TON_H
#define UTILS_TON_H


#include <stdint.h>


struct TON {
    uint8_t IN;
    uint32_t PT;

    uint8_t Q;
    uint32_t ET;

    uint32_t startTime;
    uint8_t prevIN;

    uint32_t (*fGetCurrentMS)(void);
};

void TON_Init(struct TON* timer, uint32_t(*fGetCurrentMS)(void));

void TON_Update(struct TON* timer);

#endif // UTILS_TON_H
