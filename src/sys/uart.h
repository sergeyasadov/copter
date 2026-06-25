#ifndef __UART_H__
#define __UART_H__

#include "defines.h"
#include "gpio.h"


#define UART_BIT PA2
#define UART_MASK_TX (1 << UART_BIT)
#define UART_PORT_TX PORTA
#define UART_DDR_TX DDRA

#define UART_DELAY_BIT_US() _delay_us(26)


static __inline__ void UART_Init(void) {
    GPIO_SET_OUTPUT(UART_DDR_TX, UART_MASK_TX);
    GPIO_SET_HIGH(UART_PORT_TX, UART_MASK_TX);
}

static __inline__ void UART_PutChar(char c) {
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

static __inline__ void UART_Print(const char *s) {
    while(*s) {
        UART_PutChar(*s++);
    }
}

static __inline__ void UART_PrintDec(uint16_t n) {
    char buf[7];
    uint8_t i = 6;
    buf[i] = '\0';
    if(n == 0) {
        buf[--i] = '0';
    } else {
        while(n) {
            buf[--i] = '0' + (n % 10);
            n /= 10;
        }
    }
    UART_Print(&buf[i]);
}



static __inline__ void UART_PutHexNibble(uint8_t nibble) {
    nibble &= 0x0F;
    if (nibble < 10) {
        UART_PutChar('0' + nibble);
    } else {
        UART_PutChar('A' + (nibble - 10));
    }
}

static __inline__ void UART_PrintHex8(uint8_t b) {
    UART_PutHexNibble(b >> 4);
    UART_PutHexNibble(b);
}

#endif // __UART_H__
