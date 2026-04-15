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
typedef __gpio_port_t GPIO_Port_t;

typedef struct GPIO {
    GPIO_Port_t port;
    GPIO_Dir_t dir;
    GPIO_Pin_t pin;
} GPIO_t;


void GPIO_Init(GPIO_t*);

void GPIO_SetDir(GPIO_t*, GPIO_Dir_t);

void GPIO_Write(GPIO_t*, GPIO_Level_t);

GPIO_Level_t GPIO_Read(const GPIO_t*);

void GPIO_SetHigh(GPIO_t*);

void GPIO_SetLow(GPIO_t*);

void GPIO_SetToggle(GPIO_t*);


#endif // __COPTER_GPIO_H__