#ifndef __PACKET_TX_H__
#define __PACKET_TX_H__


#include "packet_common.h"
#include "defines.h"
#include "sys/gpio.h"

#define PACKET_TX_DATA_SET(PORT, BIT, VAL) do {\
    if (VAL) {\
        GPIO_SET_HIGH(PORT, (1 << BIT));\
    } else {\
        GPIO_SET_LOW(PORT, (1 << BIT));\
    }\
} while(0)

#define PACKET_TX_CMD_SET(VAL) PACKET_TX_DATA_SET(PACKET_TX_DATA_PORT, PACKET_TX_CMD_BIT, VAL)
#define PACKET_TX_D0_SET(VAL) PACKET_TX_DATA_SET(PACKET_TX_DATA_PORT, PACKET_TX_D0_BIT, VAL)
#define PACKET_TX_D1_SET(VAL) PACKET_TX_DATA_SET(PACKET_TX_DATA_PORT, PACKET_TX_D1_BIT, VAL)
#define PACKET_TX_DATA_SEND(D0, D1) do {\
    PACKET_TX_D0_SET(D0);\
    PACKET_TX_D1_SET(D1);\
} while(0)

#define PACKET_TX_PWM_SET(VAL) (PACKET_TX_PWM_OCR = (VAL))


static __inline__ void Packet_TX_Init(void) {
    GPIO_SET_OUTPUT(PACKET_TX_DATA_DDR, PACKET_TX_CMD_BIT);
    GPIO_SET_OUTPUT(PACKET_TX_DATA_DDR, PACKET_TX_D0_BIT);
    GPIO_SET_OUTPUT(PACKET_TX_DATA_DDR, PACKET_TX_D1_BIT);
    GPIO_SET_LOW(PACKET_TX_DATA_DDR, PACKET_TX_CMD_BIT);

    // GPIO_SET_OUTPUT(PACKET_TX_PWM_DDR, PACKET_TX_PWM);
    DDRB |= (1 << PB2);
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS00);
    PACKET_TX_PWM_SET(0);
}


static __inline__ void Packet_TX_Send(const uint8_t index, const uint8_t value) {
    switch(index) {
    case PACKET_INDEX_MOTOR_1:
        PACKET_TX_PWM_SET(value);
        PACKET_TX_DATA_SEND(0, 0);
        _delay_us(100);
        PACKET_TX_CMD_SET(1);
        _delay_us(10);
        PACKET_TX_CMD_SET(0);
        break;
    case PACKET_INDEX_MOTOR_2:
        PACKET_TX_PWM_SET(value);
        PACKET_TX_DATA_SEND(0, 1);
        _delay_us(100);
        PACKET_TX_CMD_SET(1);
        _delay_us(10);
        PACKET_TX_CMD_SET(0);
        break;
    case PACKET_INDEX_MOTOR_3:
        PACKET_TX_PWM_SET(value);
        PACKET_TX_DATA_SEND(1, 0);
        _delay_us(100);
        PACKET_TX_CMD_SET(1);
        _delay_us(10);
        PACKET_TX_CMD_SET(0);
        break;
    case PACKET_INDEX_MOTOR_4:
        PACKET_TX_PWM_SET(value);
        PACKET_TX_DATA_SEND(1, 1);
        _delay_us(100);
        PACKET_TX_CMD_SET(1);
        _delay_us(10);
        PACKET_TX_CMD_SET(0);
        break;
    }
}


#endif // __PACKET_TX_H__
