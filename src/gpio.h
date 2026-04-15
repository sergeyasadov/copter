#ifndef __COPTER_GPIO_H__
#define __COPTER_GPIO_H__

#include "defines.h"

typedef enum GPIO_Dir {
    GPIO_DIR__INPUT,
    GPIO_DIR__OUTPUT
} GPIO_Dir_t;

typedef enum GPIO_Level {
    GPIO_LEVEL__HIGH,
    GPIO_LEVEL__LOW
} GPIO_Level_t;


typedef __gpio_pin_t GPIO_Pin_t;
typedef __gpio_value_t GPIO_Value_t;


typedef struct GPIO {
    GPIO_Dir_t dir;
    GPIO_Pin_t pin;
} GPIO;


void GPIO_Init(GPIO*);

void GPIO_SetDir(GPIO*, GPIO_Dir_t);

void GPIO_Write(GPIO*, GPIO_Level_t);
GPIO_Level_t GPIO_Read(const GPIO*);

void GPIO_SetHigh(GPIO*);
void GPIO_SetLow(GPIO*);
void GPIO_SetToggle(GPIO*);


#endif // __COPTER_GPIO_H__