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


typedef struct GPIO {
    uint8_t PIN;
    GPIO_State STATE;
    GPIO_Mode MODE;
} GPIO;

extern uint8_t GPIO_PIN_1;
extern uint8_t GPIO_PIN_2;


void GPIO_Init(GPIO*);

void GPIO_UpdateMode(GPIO*);

void GPIO_UpdateState(GPIO*);


#endif // __COPTER_GPIO_H__