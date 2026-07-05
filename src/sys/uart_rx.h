#ifndef UART_RX_H
#define UART_RX_H

#include "defines.h"
#include "gpio.h"

#define UART_BAUD 19200
#define UART_BIT_US (1000000UL / UART_BAUD)

#define UART_RX_BIT PA2
#define UART_RX_MASK (1 << UART_RX_BIT)
#define UART_RX_PORT PORTA
#define UART_RX_DDR DDRA
#define UART_RX_PIN PINA
#define UART_RX_PCINT_BIT PCINT2

#define UART_RX_HALF_BIT_US (UART_BIT_US / 2)
#define UART_RX_FULL_BIT_US UART_BIT_US

#define UART_RX_PACKET_LEN 5

#define UART_RX_TIMEOUT 80

static volatile uint8_t __uart_rx_buf[UART_RX_PACKET_LEN];
static volatile uint8_t __uart_rx_ready;


static __inline__ void UART_RX_Init(void) {
    GPIO_SET_INPUT(UART_RX_DDR, UART_RX_MASK);
    GPIO_SET_HIGH(UART_RX_PORT, UART_RX_MASK);

    SMBIT(GIFR, PCIF0);
    SMBIT(PCMSK0, UART_RX_PCINT_BIT);
    SMBIT(GIMSK, PCIE0);

    __uart_rx_ready = 0;
}


static __inline__ uint8_t UART_RX_GetPacket(uint8_t* dst) {
    if (!__uart_rx_ready) {
        return 0;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t i = 0; i < UART_RX_PACKET_LEN; i++) {
            dst[i] = __uart_rx_buf[i];
        }
        __uart_rx_ready = 0;
    }
    return 1;
}


ISR(PCINT0_vect) {

    if (GPIO_READ(UART_RX_PIN, UART_RX_MASK)) {
        return;
    }

    CMBIT(PCMSK0, UART_RX_PCINT_BIT);

    _delay_us(UART_RX_HALF_BIT_US);
    if (GPIO_READ(UART_RX_PIN, UART_RX_MASK)) {
        SMBIT(GIFR, PCIF0);
        SMBIT(PCMSK0, UART_RX_PCINT_BIT);
        return;
    }

    _delay_us(UART_RX_FULL_BIT_US);

    for (uint8_t byteN = 0; byteN < UART_RX_PACKET_LEN; byteN++) {
        uint8_t b = 0;

        for (uint8_t bitN = 0; bitN < 8; bitN++) {
            if (GPIO_READ(UART_RX_PIN, UART_RX_MASK)) {
                b |= (1 << bitN);
            }
            _delay_us(UART_RX_FULL_BIT_US);
        }

        if(byteN == 0) {
            if(b != 0xF8) {
                return;
            }
        }

        __uart_rx_buf[byteN] = b;

        if (byteN < UART_RX_PACKET_LEN - 1) {
            _delay_us(UART_RX_FULL_BIT_US);
            _delay_us(UART_RX_FULL_BIT_US);
        }
    }

    __uart_rx_ready = 1;

    SMBIT(GIFR, PCIF0);
    SMBIT(PCMSK0, UART_RX_PCINT_BIT);
}



#endif // UART_RX_H
