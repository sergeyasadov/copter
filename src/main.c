#include "defines.h"
#include "gpio.h"

int main(void) {
    // DDRB |= _BV(PB2);
    GPIO gpio = {
        .MODE = GPIO_MODE__OUTPUT,
        .PIN = GPIO_PIN_2,
        .STATE = GPIO_STATE__ON   
    };
    GPIO_UpdateMode(&gpio);

    GPIO_UpdateState(&gpio);

    while(1) {
        // PORTB ^= _BV(PB2);
        delayMs(500);
    }
}