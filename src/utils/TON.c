#include "TON.h"


void TON_Init(struct TON* timer, uint32_t (*fGetCurrentMS)(void)) {
    timer->IN = 0;
    timer->PT = 0;
    timer->Q = 0;
    timer->ET = 0;
    timer->prevIN = 0;
    timer->fGetCurrentMS = fGetCurrentMS;
}

void TON_Update(struct TON* timer) {
    if(timer->IN == 0) {
        timer->Q = 0;
        timer->ET = 0;
        timer->prevIN = 0;
    }
    else {
        const uint32_t current_ms = timer->fGetCurrentMS();
        if(timer->prevIN == 0) {
            timer->startTime = current_ms;
            timer->prevIN = 1;
        }

        timer->ET = current_ms - timer->startTime;

        if(timer->ET >= timer->PT) {
            timer->Q = 1;
        }
    }
}
