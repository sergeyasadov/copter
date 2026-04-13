#include "defines.h"
#include "gpio.h"
#include "utils.h"


int main(void) {
    GPIO led0 = {
        .pin = GPIO_PIN_0,
        .dir = GPIO_DIR__OUTPUT
    };

    GPIO_Init(&led0);

    // TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
    // TCCR0B = _BV(CS00);

    while(1) {
        // for(uint8_t i = 0; i < 0xff; i++) {
        //     OCR0A = i;
        //     OCR0B = i;
        //     delayMs(5);
        // }
        // for(uint8_t i = 0xff; i; i--) {
        //     OCR0A = i;
        //     OCR0B = i;
        //     delayMs(5);
        // }

        GPIO_SetToggle(&led0);
        delayMs(250);
    }
}