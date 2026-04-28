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

void UART_SendByte(UART_t* uart, uint8_t byte) {
    uart_tx_bit(0);

    for(register uint8_t i = 8; i; i--) {
        uart_tx_bit(byte & 1);
        byte >>= 1;
    }

    uart_tx_bit(1);
}


void UART_SendString(UART_t* uart, const char* str) {
    while(*str){
        UART_SendByte(uart, (uint8_t)*str);
        str++;
    }
}

// void UART_Init(UART_t* uart) {
//     // uart->rx.dir = GPIO_DIR_INPUT;
//     // uart->tx.dir = GPIO_DIR_OUTPUT;
//     // GPIO_Init(&uart->rx);
//     // GPIO_Init(&uart->tx);
//     // GPIO_SetHigh(&uart->tx);
//     // GPIO_SetHigh(&uart->tx);

//     _UART.RXDDR = (uart->tx.port == GPIO_PORT_A) ? &DDRA : &DDRB;
//     _UART.RXPORT = (uart->tx.port == GPIO_PORT_A) ? &PORTA : &PORTB;
//     _UART.RXMASK = _BV(uart->tx.pin);

//     _UART.TXDDR = (uart->tx.port == GPIO_PORT_A) ? &DDRA : &DDRB;
//     _UART.TXPORT = (uart->tx.port == GPIO_PORT_A) ? &PORTA : &PORTB;
//     _UART.TXMASK = _BV(uart->tx.pin);
    
//     *_UART.RXDDR &= _UART.RXMASK;
//     // *_UART.RXPORT |= _UART.RXMASK;

//     *_UART.TXDDR |= _UART.TXMASK;
//     *_UART.TXPORT |= _UART.TXMASK;
    

//     // *uart->tx.ddr |= uart->tx.mask;
//     // uart_pinHigh(&uart->tx);

//     // *uart->rx.ddr &= ~uart->rx.mask;
//     // uart_pinHigh(&uart->rx);
// }



// void UART_SendByte(UART_t* uart, const uint8_t byte) {
//     uint8_t sreg = SREG;
//     cli();

//     // PORTA &= ~_BV(PA1);
//     *_UART.TXPORT &= ~_UART.TXMASK;
//     // GPIO_SetLow(&uart->tx);
//     // uart_pinLow(&uart->tx);
//     // *uart->tx.port &= ~uart->tx.mask;
//     // uart_delayBit();
//     delayUs(UART_BIT_US);

//     for(uint8_t i = 0; i < 8; i++) {
//         if(byte & (1 << i)) {
//             *_UART.TXPORT |= _UART.TXMASK;
//             // PORTA |= _BV(PA1);
//             // uart_pinHigh(&uart->tx);
//             // *uart->tx.port |= uart->tx.mask;
//         }
//         else {
//             *_UART.TXPORT &= ~_UART.TXMASK;
//             // uart_pinLow(&uart->tx);
//             // *uart->tx.port &= ~uart->tx.mask;
//             // GPIO_SetLow(&uart->tx);
//         }
//         delayUs(UART_BIT_US);
//         // uart_delayBit();
//     }
    
//     *_UART.TXPORT |= _UART.TXMASK;
//     // *uart->tx.port |= uart->tx.mask;
//     // uart_pinHigh(&uart->tx);
//     // PORTA |= _BV(PA1);
//     // GPIO_SetHigh(&uart->tx);

//     delayUs(UART_BIT_US);
//     // uart_delayBit();

//     SREG = sreg;
// }