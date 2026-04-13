#ifndef __COPTER_GPIO_H__
#define __COPTER_GPIO_H__

#include "defines.h"


typedef enum GPIO_Dir {
    GPIO_DIR__INPUT,
    GPIO_DIR__OUTPUT
} GPIO_Dir;


extern uint8_t GPIO_PIN_0;
extern uint8_t GPIO_PIN_1;
extern uint8_t GPIO_PIN_2;
extern uint8_t GPIO_PIN_3;
extern uint8_t GPIO_PIN_4;
extern uint8_t GPIO_PIN_5;

/// @brief  GPIO Digital
typedef struct GPIO_Digital {
    uint_fast8_t pin;    
    uint_fast8_t value;
    GPIO_Dir dir;
} GPIO_Digital;

void GPIO_Digital_Init(GPIO_Digital*);

void GPIO_Digital_Set(GPIO_Digital*);
uint_fast8_t GPIO_Digital_Read(GPIO_Digital*);

void GPIO_Digital_SetDir(GPIO_Digital*);


#endif // __COPTER_GPIO_H__