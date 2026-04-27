#ifndef __COPTER_GPIO_H__
#define __COPTER_GPIO_H__

#include "defines.h"

typedef enum GPIO_Dir {
    GPIO_DIR_INPUT,
    GPIO_DIR_INPUT_PULLUP,
    GPIO_DIR_OUTPUT
} GPIO_Dir;

typedef enum GPIO_Level {
    GPIO_LEVEL_HIGH,
    GPIO_LEVEL_LOW
} GPIO_Level;

typedef enum GPIO_Port {
    GPIO_PORT_A,
    GPIO_PORT_B
} GPIO_Port;

typedef struct GPIO {
    GPIO_Port port;
    GPIO_Dir dir;
    GPIO_Pin_t pin;
} GPIO_t;


void GPIO_Init(GPIO_t*);

void GPIO_SetDir(GPIO_t*, GPIO_Dir);

void GPIO_Write(GPIO_t*, GPIO_Level);

GPIO_Level GPIO_Read(const GPIO_t*);

void GPIO_SetHigh(GPIO_t*);

void GPIO_SetLow(GPIO_t*);

void GPIO_SetToggle(GPIO_t*);


#endif // __COPTER_GPIO_H__