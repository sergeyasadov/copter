#ifndef __COPTER_UART_H__
#define __COPTER_UART_H__

#include "defines.h"
#include "gpio.h"

#define UART_BAUD 4800
#define UART_BIT_US ((double)((D_FREQ_MCU) / (UART_BAUD)))
#define UART_DELAY_BIT_US() delayUs(UART_BIT_US)
#define UART_DELAY_HALF_BIT_US ((UART_BIT_US) / 2)


typedef struct UART {
    GPIO_t rx;
    GPIO_t tx;
} UART_t;


void UART_Init(UART_t*);

void UART_SendByte(UART_t*, const uint8_t);

void UART_SendString(UART_t*, const char*);

uint8_t UART_ReadByte(UART_t*);


#endif // __COPTER_UART_H__