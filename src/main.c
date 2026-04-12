#include "defines.h"
#include "gpio.h"
#include "utils.h"


int main(void) {
    GPIO led;
    led.MODE = GPIO_MODE__OUTPUT;
    led.PIN = GPIO_PIN_0;
    led.STATE = GPIO_STATE__OFF;

    GPIO_UpdateMode(&led);
    GPIO_UpdateState(&led);

    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
    TCCR0B = _BV(CS00);


    while(1) {
        for(uint8_t i = 0; i < 0xff; i++) {
            OCR0A = i;
            delayMs(5);
        }
        for(uint8_t i = 0xff; i; i--) {
            OCR0A = i;
            delayMs(5);
        }
    }
}