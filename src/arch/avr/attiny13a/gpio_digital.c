#include "gpio.h"

#define __sbi(_Reg, _Port) ((_Reg) |= (1 << (_Port)))
#define __cbi(_Reg, _Port) ((_Reg) &= ~(1 << (_Port))) 


uint8_t GPIO_PIN_0 = PB0;
uint8_t GPIO_PIN_1 = PB1;
uint8_t GPIO_PIN_2 = PB2;
uint8_t GPIO_PIN_3 = PB3;
uint8_t GPIO_PIN_4 = PB4;
uint8_t GPIO_PIN_5 = PB5;


void GPIO_Digital_Init(GPIO_Digital* gpio) {
    GPIO_Digital_SetDir(gpio);
    GPIO_Digital_Set(gpio);
}


void GPIO_Digital_Set(GPIO_Digital* gpio) {
    if(gpio->value) {
        __sbi(PORTB, gpio->pin);
    }
    else {
        __cbi(PORTB, gpio->pin);
    }
}


uint_fast8_t GPIO_Digital_Read(GPIO_Digital* gpio) {
    return PINB & _BV(gpio->pin);
}


void GPIO_Digital_SetDir(GPIO_Digital* gpio) {
    if(gpio->dir == GPIO_DIR__OUTPUT) {
        __sbi(DDRB, gpio->pin);
    }
    else {
        __cbi(DDRB, gpio->pin);
    }
}