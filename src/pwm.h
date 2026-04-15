#ifndef __COPTER_PWM_H__
#define __COPTER_PWM_H__

#include "defines.h"

typedef __pwm_duty_t  PWM_Duty_t;
typedef __pwm_freq_t  PWM_Freq_t;
typedef __pwm_value_t PWM_Value_t;

typedef enum PWM_Presceller {
    PWM_PRESCALER_1 = 1,
    PWM_PRESCALER_8 = 8,
    PWM_PRESCALER_64 = 64,
    PWM_PRESCALER_256 = 256,
    PWM_PRESCALER_1024 = 1024
} PWM_Presceller_t;

typedef enum PWM_Polar {
    PWM_POLAR_NORMAL = 0,
    PWM_POLAR_INVERTED
} PWM_Polar_t;

typedef struct PWM {
    PWM_Duty_t duty; // hz
    PWM_Freq_t presceller; // 0 .. 1024
    PWM_Polar_t polar;
} PWM_t;

void PWM_Init(PWM_t*);

void PWM_Start(PWM_t*);
void PWM_Stop(PWM_t*);

void PWM_SetDuty(PWM_t*, const PWM_Duty_t);
void PWM_SetFreq(PWM_t*, const PWM_Freq_t);


#endif // __COPTER_PWM_H__