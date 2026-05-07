#ifndef __UART_H__
#define __UART_H__


#include "defines.h"
#include "gpio.h"


#define UART_MASK_TX (1 << PA1)
#define UART_MASK_RX (1 << PA2)
#define UART_PORT_TX PORTA
#define UART_PORT_RX PORTA
#define UART_DDR_TX DDRA
#define UART_DDR_RX DDRA

#define UART_DELAY_BIT_US() _delay_us(104)


static __inline__ void UART_Init(void) {
    GPIO_SET_OUTPUT(UART_DDR_TX, UART_MASK_TX);
    // GPIO_SET_INPUT(UART_DDR_RX, UART_MASK_RX);

    GPIO_SET_HIGH(UART_PORT_TX, UART_MASK_TX);
}


static __ATTR_ALWAYS_INLINE__
void UART_SendBit(const uint8_t bit) {
    if(bit) GPIO_SET_HIGH(UART_PORT_TX, UART_MASK_TX);
    else GPIO_SET_LOW(UART_PORT_TX, UART_MASK_TX);
    UART_DELAY_BIT_US();
} 


static __inline__ void UART_SendByte(uint8_t byte) {
    UART_SendBit(0);

    for(register uint8_t i = 8; i; i--) {
        UART_SendBit(byte & 1);
        byte >>= 1;
    }

    UART_SendBit(1);
}


static void UART_SendString(const char* str) {
    while(*str) {
        UART_SendByte((uint8_t)*str);
        str++;
    }
}


static __inline__ void UART_SendString__ATOMIC(const char* s) {
    const register uint8_t __SREG __asm__("r16") = SREG;
    __asm__ __volatile__("cli" ::: "memory");
    UART_SendString(s);
    SREG = __SREG;
}


#endif // __UART_H__
