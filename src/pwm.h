#ifndef __COPTER_PWM_H__
#define __COPTER_PWM_H__

#include "defines.h"
#include "gpio.h"


typedef enum {
    PWM_PRESCALER_1 = 1,
    PWM_PRESCALER_8 = 8,
    PWM_PRESCALER_64 = 64,
    PWM_PRESCALER_256 = 256,
    PWM_PRESCALER_1024 = 1024
} PWM_Prescaler;


typedef struct PWM {
    GPIO_t gpio;
    PWM_Duty_t duty; // hz
    PWM_Prescaler prescaler; // 0 .. 1024
} PWM_t;


void PWM_Init(PWM_t*);

void PWM_Set(PWM_t*, const uint8_t);

// void PWM_SetDuty(PWM_t*, const PWM_Duty_t);
// void PWM_SetFreq(PWM_t*, const PWM_Freq_t);


#endif // __COPTER_PWM_H__