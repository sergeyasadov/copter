#ifndef __PACKET_RX_H__
#define __PACKET_RX_H__

#include "packet_common.h"

#include "defines.h"
#include "sys/gpio.h"

static volatile uint8_t __packet_rx_ready = 0;
static volatile uint8_t __packet_rx_data = 0;
static volatile uint8_t __packet_rx_pwm_data = 0;
static volatile uint8_t __packet_rx_busy = 0;


static __inline__ void Packet_RX_Init(void) {
    GPIO_SET_INPUT(PACKET_RX_DATA_DDR, BIT_MASK(PACKET_RX_CMD_BIT));
    GPIO_SET_INPUT(PACKET_RX_DATA_DDR, BIT_MASK(PACKET_RX_D0_BIT));
    GPIO_SET_INPUT(PACKET_RX_DATA_DDR, BIT_MASK(PACKET_RX_D1_BIT));
    GPIO_SET_INPUT(PACKET_RX_DATA_DDR, BIT_MASK(PACKET_RX_ANALOG_BIT));

    SMBIT(DIDR0, ADC1D);

    SMBIT(ADMUX, MUX0);
    SMBIT(ADMUX, ADLAR);
    SMBIT(ADCSRA, ADEN);
    SMBIT(ADCSRA, ADPS1);
    SMBIT(ADCSRA, ADPS2);
    SMBIT(ADCSRA, ADIE);

    SMBIT(MCUCR, ISC00);
    SMBIT(MCUCR, ISC01);

    // SMBIT(GIMSK, INT0);
    SMBIT(GIMSK, PCIE0);
    SMBIT(PCMSK0, PCINT0);
}

static __inline__ __attribute__((always_inline)) uint8_t Packet_RX_Available(void) {
    return __packet_rx_ready;
}

static __inline__ __attribute__((always_inline)) void Packet_RX_Clear(void) {
    __packet_rx_ready = 0;
}

static __inline__ __attribute__((always_inline)) uint8_t Packet_RX_GetData(void) {
    return __packet_rx_data;
}

static __inline__ __attribute__((always_inline)) uint8_t Packet_RX_GetPWMData(void) {
    return __packet_rx_pwm_data;
}



ISR(PCINT0_vect) {
    if (__packet_rx_busy) return;

    SMBIT(ADCSRA, ADSC);

    uint8_t index = 0;
    if (PACKET_RX_DATA_PIN & (1 << PACKET_RX_D0_BIT)) index |= (1 << 0);
    if (PACKET_RX_DATA_PIN & (1 << PACKET_RX_D1_BIT)) index |= (1 << 1);

    __packet_rx_busy = 1;
    __packet_rx_data = index;
}


ISR(ADC_vect) {
    __packet_rx_pwm_data = ADCH;
    __packet_rx_busy = 0;
    __packet_rx_ready = 1;
}


#endif // __PACKET_RX_H__
