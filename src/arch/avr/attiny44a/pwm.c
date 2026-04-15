#include "pwm.h"


void PWM_Init(PWM_t* pwm) {
    GPIO_Init(&pwm->gpio);

    volatile uint8_t* PWM_TIMER_REG_0 = (void*)0;
    volatile uint8_t* PWM_TIMER_REG_1 = (void*)0;
    
    if(pwm->gpio.port == GPIO_PORT_PWM_MOTOR_1 && pwm->gpio.pin == GPIO_PIN_PWM_MOTOR_1) {
        *PWM_TIMER_REG_0 = TCCR0A;
        *PWM_TIMER_REG_1 = TCCR0B;
    }
    else {
        
    }

    *PWM_TIMER_REG_0 = 0;
    
    switch (pwm->polar) {
        case PWM_POLAR_NORMAL: {
            *PWM_TIMER_REG_0 |= _BV(COM0A1) | _BV(COM0B1);
            break;
        }
        case PWM_POLAR_INVERTED: {
            *PWM_TIMER_REG_0 |= _BV(COM0A0) | _BV(COM0A1) | _BV(COM0B0) | _BV(COM0B1);
            break;
        }
        default:
            break;
    }

    *PWM_TIMER_REG_0 |= _BV(WGM00) | _BV(WGM01);

    switch (pwm->presceller) {
        case PWM_PRESCALER_1: {

            break;
        }
    }
    
}