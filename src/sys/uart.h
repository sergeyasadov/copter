#ifndef __UART_H__
#define __UART_H__

#include "defines.h"
#include "gpio.h"


#define UART_BIT PA2
#define UART_MASK_TX (1 << UART_BIT)
#define UART_PORT_TX PORTA
#define UART_DDR_TX DDRA

#define UART_MASK_RX (1 << UART_BIT)
#define UART_PORT_RX PORTA
#define UART_DDR_RX DDRA

#define UART_DELAY_BIT_US() _delay_us(104)


static __inline__ void UART_TX_Init(void) {
    GPIO_SET_OUTPUT(UART_DDR_TX, UART_MASK_TX);
    GPIO_SET_HIGH(UART_PORT_TX, UART_MASK_TX);
}


static __inline__ void UART_RX_Init(void) {
    GPIO_SET_INPUT(UART_DDR_RX, UART_MASK_RX);
    GPIO_SET_HIGH(UART_PORT_RX, UART_MASK_RX);
}


static __inline__ void UART_SendByte(uint8_t c) {
    GPIO_SET_LOW(UART_PORT_TX, UART_MASK_TX);
    UART_DELAY_BIT_US();

    for(register uint8_t i = 0; i < 8; i++) {
        if(c & 0x01)
            GPIO_SET_HIGH(UART_PORT_TX, UART_MASK_TX);
        else
            GPIO_SET_LOW(UART_PORT_TX, UART_MASK_TX);
        c >>= 1;
        UART_DELAY_BIT_US();
    }
    GPIO_SET_HIGH(UART_PORT_TX, UART_MASK_TX);
    UART_DELAY_BIT_US();
}


static __inline__ uint8_t UART_GetByte(void) {
    uint8_t c = 0;
    for(register uint8_t i = 0; i < 8; i++) {
        UART_DELAY_BIT_US();
        if(GPIO_READ(PINA, UART_MASK_RX))
            c |= (1 << i);
    }
    return c;
}



#endif // __UART_H__
