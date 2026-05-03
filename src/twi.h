#ifndef __COPTER_TWI_H__
#define __COPTER_TWI_H__

#include "defines.h"
#include "gpio.h"

typedef struct TWI {
    GPIO_t sda;
    GPIO_t scl;
} TWI_t;


void TWI_Init(TWI_t*);

void TWI_WriteByte(const uint8_t byte);

void TWI_SendByte(const uint8_t byte);

uint8_t TWI_ReadByte(const uint8_t ack);

#endif // __COPTER_TWI_H__