#ifndef EMA_FILTER_H
#define EMA_FILTER_H

#ifndef __STATIC_INLINE
#define __STATIC_INLINE
#endif

#include <stdint.h>

__STATIC_INLINE uint16_t EMA_Filter(const uint16_t prev, const uint16_t new_sample) {
    return (uint16_t)(prev + ((new_sample - prev) >> 2u));
}

#endif //
