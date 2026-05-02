#include "uart.h"
#include <avr/interrupt.h>

// void
// uart_tx_string__atomic(const char* s)
// {
//     const uint8_t __SREG = SREG;
//     __asm__ __volatile__("cli" ::: "memory");
//     uart_tx_string(s);
//     SREG = __SREG;
// }


typedef struct SoftwareUART {
    __volatile__ uint8_t* RXDDR;
    __volatile__ uint8_t* RXPORT;
    __volatile__ uint8_t* RXPIN;
    uint8_t RXMASK;                 

    __volatile__ uint8_t* TXDDR;
    __volatile__ uint8_t* TXPORT;
    uint8_t TXMASK;
} SoftwareUART;


static SoftwareUART _UART0;


static inline __ATTR_ALWAYS_INLINE__ void uart_tx_bit(const uint8_t bit) {
    if(bit) {
        *_UART0.TXPORT |= _UART0.TXMASK;
    }
    else {
        *_UART0.TXPORT &= ~_UART0.TXMASK;
    }
    UART_DELAY_BIT_US();
}


void UART_Init(UART_t* uart) {
    _UART0.TXDDR = (uart->tx.port == GPIO_PORT_A) ? &DDRA : &DDRB;
    _UART0.TXPORT = (uart->tx.port == GPIO_PORT_A) ? &PORTA : &PORTB;
    _UART0.TXMASK = _BV(uart->tx.pin);

    *_UART0.TXDDR |= _UART0.TXMASK;
    *_UART0.TXPORT |= _UART0.TXMASK;
}

void UART_SendByte(uint8_t byte) {
    uart_tx_bit(0);

    for(register uint8_t i = 8; i; i--) {
        uart_tx_bit(byte & 1);
        byte >>= 1;
    }

    uart_tx_bit(1);
}


void UART_SendString(const char* str) {
    while(*str){
        UART_SendByte((uint8_t)*str);
        str++;
    }
}

