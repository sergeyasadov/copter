#include "defines.h"
#include "gpio.h"
#include "utils.h"


int main(void) {
    GPIO_Digital led0;
    led0.pin = GPIO_PIN_0;
    led0.dir = GPIO_DIR__OUTPUT;
    led0.value = 1;

    GPIO_Digital_Init(&led0);

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

        led0.value = !GPIO_Digital_Read(&led0);
        GPIO_Digital_Set(&led0);

        delayMs(300);
    }
}