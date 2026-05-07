#ifndef __GPIO_H__
#define __GPIO_H__

#include "defines.h"


#define GPIO_SET_INPUT(DDR, MASK) \
    CBIT(DDR, MASK)

#define GPIO_SET_OUTPUT(DDR, MASK) \
    SBIT(DDR, MASK)

#define GPIO_SET_HIGH(PORT, MASK) \
    SBIT(PORT, MASK)

#define GPIO_SET_LOW(PORT, MASK) \
    CBIT(PORT, MASK)


#endif // __GPIO_H__