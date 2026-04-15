#include "defines.h"
#include "gpio.h"
#include "pwm.h"
#include "utils.h"


int main(void) {
    GPIO_t led0 = {
        .port = GPIO_PORT_PWM_MOTOR_1,
        .pin = GPIO_PIN_PWM_MOTOR_1,
        .dir = GPIO_DIR__OUTPUT
    };

    PWM_t motor1 = {
        .gpio = led0,
        .polar = PWM_POLAR_NORMAL,
        .presceller = PWM_PRESCALER_1
    };

    PWM_Init(&motor1);

    // GPIO_Init(&led0);

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

        // GPIO_SetToggle(&led0);
        delayMs(250);
    }
}