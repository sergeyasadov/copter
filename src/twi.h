#ifndef __COPTER_TWI_H__
#define __COPTER_TWI_H__

#include "defines.h"
#include "gpio.h"

typedef struct TWI {
    GPIO_t sda;
    GPIO_t scl;
} TWI_t;

#endif // __COPTER_TWI_H__