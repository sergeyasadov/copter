#ifndef UART_TX_H
#define UART_TX_H

#include "defines.h"
#include "gpio.h"


#define UART_BAUD 19200
#define UART_BIT_US (1000000UL / UART_BAUD)

#define UART_TX_BIT PA2
#define UART_TX_MASK (1 << UART_TX_BIT)
#define UART_TX_PORT PORTA
#define UART_TX_DDR DDRA

#define UART_DELAY_BIT_US() _delay_us(UART_BIT_US)
// #define UART_DELAY_BIT_US() _delay_us(104)
// #define UART_DELAY_BIT_US() _delay_us(26)


static __inline__ void UART_TX_Init(void) {
    GPIO_SET_OUTPUT(UART_TX_DDR, UART_TX_MASK);
    GPIO_SET_HIGH(UART_TX_PORT, UART_TX_MASK);
}


static __inline__ void UART_SendByte(uint8_t b) {
    GPIO_SET_LOW(UART_TX_PORT, UART_TX_MASK);
    UART_DELAY_BIT_US();

    for(register uint8_t i = 0; i < 8; i++) {
        if(b & 0x01) {
            GPIO_SET_HIGH(UART_TX_PORT, UART_TX_MASK);
        } else {
            GPIO_SET_LOW(UART_TX_PORT, UART_TX_MASK);
        }
        b >>= 1;
        UART_DELAY_BIT_US();
    }
    GPIO_SET_HIGH(UART_TX_PORT, UART_TX_MASK);
    UART_DELAY_BIT_US();
}


static __inline__ void UART_Print(const char *s) {
    while(*s) {
        UART_SendByte(*s++);
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
        UART_SendByte('0' + nibble);
    } else {
        UART_SendByte('A' + (nibble - 10));
    }
}


static __inline__ void UART_PrintHex8(uint8_t b) {
    UART_PutHexNibble(b >> 4);
    UART_PutHexNibble(b);
}



#endif // UART_TX_H
