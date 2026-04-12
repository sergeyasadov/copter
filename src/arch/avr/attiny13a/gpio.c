#include "gpio.h"

#define __sbi(_Reg, _Port) ((_Reg) |= (1 << (_Port)))
#define __cbi(_Reg, _Port) ((_Reg) &= ~(1 << (_Port))) 

uint8_t GPIO_PIN_0 = PB0;
uint8_t GPIO_PIN_1 = PB1;
uint8_t GPIO_PIN_2 = PB2;
uint8_t GPIO_PIN_3 = PB3;
uint8_t GPIO_PIN_4 = PB4;
uint8_t GPIO_PIN_5 = PB5;


void GPIO_UpdateMode(GPIO* gpio) {
    if(gpio->MODE == GPIO_MODE__INPUT) {
        __cbi(DDRB, gpio->PIN);
    }    
    else {
        __sbi(DDRB, gpio->PIN);
    }
}


void GPIO_UpdateState(GPIO* gpio) {
    if(gpio->STATE == GPIO_STATE__OFF) {
        __cbi(PORTB, gpio->PIN);
    }
    else { // GPIO_STATE_ON
        __sbi(PORTB, gpio->PIN);
    }
}


