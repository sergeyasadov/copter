#include "defines.h"
#include "gpio.h"
#include "pwm.h"
#include "utils.h"
#include "adc.h"


int main(void) {

    ADC_t pot = {
        .gpio = {
            .port = GPIO_PORT_PWM_MOTOR_2,
            .pin = PA3,
            .dir = GPIO_DIR_INPUT
        },
        .presc = ADC_PRESCALER_2,
        .ref = ADC_REF_VCC
    };
    ADC_Init(&pot);


    const PWM_t motors[] = {
        (PWM_t){
            .gpio = {
                .dir = GPIO_DIR_OUTPUT,
                .pin = GPIO_PIN_PWM_MOTOR_1,
                .port = GPIO_PORT_PWM_MOTOR_1
            },
            .prescaler = PWM_PRESCALER_1
        },
        (PWM_t){
            .gpio = {
                .dir = GPIO_DIR_OUTPUT,
                .pin = GPIO_PIN_PWM_MOTOR_2,
                .port = GPIO_PORT_PWM_MOTOR_3
            },
            .prescaler = PWM_PRESCALER_1
        },
        (PWM_t){
            .gpio = {
                .dir = GPIO_DIR_OUTPUT,
                .pin = GPIO_PIN_PWM_MOTOR_3,
                .port = GPIO_PORT_PWM_MOTOR_3
            },
            .prescaler = PWM_PRESCALER_1
        },
        (PWM_t){
            .gpio = {
                .dir = GPIO_DIR_OUTPUT,
                .pin = GPIO_PIN_PWM_MOTOR_4,
                .port = GPIO_PORT_PWM_MOTOR_4
            },
            .prescaler = PWM_PRESCALER_1
        }
    };


    ARR_FOREACH(motors, i) {
        PWM_Init(&motors[i]);
    }

    while(1) {
        // for(uint8_t i = 0; i < 0xff; i++) {
        //     PWM_Set(&motor1, i);
        //     delayMs(5);
        // }
        // for(uint8_t i = 0xff; i; i--) {
        //     PWM_Set(&motor1, i);
        //     delayMs(5);
        // }

        // OCR1A = ADC_Read(&pot) >> 2;

        ARR_FOREACH(motors, i) {
            PWM_Set(&motors[i], ADC_Read(&pot) >> 2);
        }

        // PWM_Set(&motor1, ADC_Read(&pot) >> 2);
    }
}