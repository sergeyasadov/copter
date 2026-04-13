#include "gpio.h"

#define __sbi(_Reg, _Port) ((_Reg) |= (1 << (_Port)))
#define __cbi(_Reg, _Port) ((_Reg) &= ~(1 << (_Port))) 


const uint8_t GPIO_PIN_0 = PB0;
const uint8_t GPIO_PIN_1 = PB1;
const uint8_t GPIO_PIN_2 = PB2;
const uint8_t GPIO_PIN_3 = PB3;
const uint8_t GPIO_PIN_4 = PB4;
const uint8_t GPIO_PIN_5 = PB5;



void GPIO_Init(GPIO* gpio) {
    GPIO_SetDir(gpio, gpio->dir);
    GPIO_Write(gpio, GPIO_LEVEL__LOW);
}


void GPIO_Write(GPIO* gpio, GPIO_Level_t level) {
    if(level == GPIO_LEVEL__HIGH) {
        __sbi(PORTB, gpio->pin);
    }
    else {
        __cbi(PORTB, gpio->pin);
    }
}


GPIO_Level_t GPIO_Read(const GPIO* gpio) {
    return PINB & _BV(gpio->pin);
}


void GPIO_SetDir(GPIO* gpio, GPIO_Dir_t ndir) {
    gpio->dir = ndir;
    if(gpio->dir == GPIO_DIR__OUTPUT) {
        __sbi(DDRB, gpio->pin);
    }
    else {
        __cbi(DDRB, gpio->pin);
    }
}


void GPIO_SetHigh(GPIO* gpio) {
    __sbi(PORTB, gpio->pin);
}


void GPIO_SetLow(GPIO* gpio) {
    __cbi(PORTB, gpio->pin);
}


void GPIO_SetToggle(GPIO* gpio) {
    GPIO_Write(gpio, GPIO_Read(gpio) == GPIO_LEVEL__LOW);
}