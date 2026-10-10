#ifndef MAFILTER_H
#define MAFILTER_H


#include "../../defines.h"

#define MAF_LENGTH 16
#define MAF_DIV_SHIFT 4


struct MAFilter {
    uint16_t buffer[MAF_LENGTH];
    uint16_t index;
    uint32_t accum;
};


__STATIC_INLINE void MAFilter_Init(struct MAFilter* maf) {
    maf->accum = 0;
    maf->index = 0;

    for(uint_fast16_t i = 0; i < MAF_LENGTH; i++) {
        maf->buffer[i] = 0;
    }
}


__STATIC_INLINE uint16_t MAFilter_Update(struct MAFilter* maf, const uint16_t new_sample) {
    if(maf->accum >= maf->buffer[maf->index]) {
        maf->accum -= maf->buffer[maf->index];
    }
    else {
        maf->accum = 0;
    }

    maf->buffer[maf->index] = new_sample;

    maf->accum += new_sample;

    maf->index++;
    if(maf->index >= MAF_LENGTH) {
        maf->index = 0;
    }

    return (uint16_t)(maf->accum >> MAF_DIV_SHIFT);
}

#endif //
