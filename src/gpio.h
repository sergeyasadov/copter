#ifndef __COPTER_GPIO_H__
#define __COPTER_GPIO_H__


#include "defines.h"

typedef enum GPIO_State {
    GPIO_STATE__OFF,
    GPIO_STATE__ON
} GPIO_State;

typedef enum GPIO_Mode {
    GPIO_MODE__INPUT,
    GPIO_MODE__OUTPUT
} GPIO_Mode;


typedef struct GPIO_Digital {
    GPIO_State state;
} GPIO_Digital;

typedef struct GPIO_PWM {
    
} GPIO_PWM;

typedef struct GPIO {
    uint8_t pin;
    GPIO_Mode mode;

    GPIO_Digital Digital;
    GPIO_PWM PWM;
} GPIO;


extern uint8_t GPIO_PIN_0;
extern uint8_t GPIO_PIN_1;
extern uint8_t GPIO_PIN_2;
extern uint8_t GPIO_PIN_3;
extern uint8_t GPIO_PIN_4;
extern uint8_t GPIO_PIN_5;


void GPIO_Init(GPIO*);

void GPIO_UpdateMode(GPIO*);

void GPIO_UpdateState(GPIO*);


#endif // __COPTER_GPIO_H__