#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys/defines.h"

#define MOTOR1_MASK (1 << PB2)
#define MOTOR2_MASK (1 << PA7)
#define MOTOR3_MASK (1 << PA6)
#define MOTOR4_MASK (1 << PA5)
#define MOTOR1_PORT PORTB
#define MOTOR2_PORT PORTA
#define MOTOR3_PORT PORTA 
#define MOTOR4_PORT PORTA
#define MOTOR1_DDR DDRB
#define MOTOR2_DDR DDRA
#define MOTOR3_DDR DDRA
#define MOTOR4_DDR DDRA

#define MOTOR1_VALUE OCR0A
#define MOTOR2_VALUE OCR0B
#define MOTOR3_VALUE OCR1A
#define MOTOR4_VALUE OCR1B

#define MOTOR_SET(N, Val) (MOTOR##N##_VALUE =  (255 - Val))


static __inline__ void Motor_Init(void) {
    SBIT(MOTOR1_DDR, MOTOR1_MASK);
    SBIT(MOTOR2_DDR, MOTOR2_MASK);
    SBIT(MOTOR3_DDR, MOTOR3_MASK);
    SBIT(MOTOR4_DDR, MOTOR4_MASK);

    // T0
    SBIT(TCCR0B, (1 << CS00));
    SBIT(TCCR0A, 
        (1 << WGM00)  | (1 << WGM01)  |
        (1 << COM0A1) | (1 << COM0A0) | 
        (1 << COM0B1) | (1 << COM0B0)        
    );

    // T1
    SBIT(TCCR1B, (1 << WGM12) | (1 << CS10));
    SBIT(TCCR1A, 
        (1 << WGM10)  |
        (1 << COM1A1) | (1 << COM1A0) |
        (1 << COM1B1) | (1 << COM1B0)
    );

    MOTOR_SET(1, 0);
    MOTOR_SET(2, 0);
    MOTOR_SET(3, 0);
    MOTOR_SET(4, 0);
}


#endif // __MOTOR_H__
