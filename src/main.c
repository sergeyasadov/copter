#include "defines.h"
#include "gpio.h"
#include "pwm.h"
#include "utils.h"
#include "adc.h"
#include "uart.h"
#include "twi.h"

#include <stdio.h>
#include <avr/interrupt.h>


int main(void) {

    // ADC_t pot = {
    //     .gpio = {
    //         .port = GPIO_PORT_PWM_MOTOR_2,
    //         .pin = PA3,
    //         .dir = GPIO_DIR_INPUT
    //     },
    //     .presc = ADC_PRESCALER_2,
    //     .ref = ADC_REF_VCC
    // };
    // ADC_Init(&pot);


    // const PWM_t motors[] = {
    //     (PWM_t){
    //         .gpio = {
    //             .dir = GPIO_DIR_OUTPUT,
    //             .pin = GPIO_PIN_PWM_MOTOR_1,
    //             .port = GPIO_PORT_PWM_MOTOR_1
    //         },
    //         .prescaler = PWM_PRESCALER_1
    //     },
    //     (PWM_t){
    //         .gpio = {
    //             .dir = GPIO_DIR_OUTPUT,
    //             .pin = GPIO_PIN_PWM_MOTOR_2,
    //             .port = GPIO_PORT_PWM_MOTOR_3
    //         },
    //         .prescaler = PWM_PRESCALER_1
    //     },
    //     (PWM_t){
    //         .gpio = {
    //             .dir = GPIO_DIR_OUTPUT,
    //             .pin = GPIO_PIN_PWM_MOTOR_3,
    //             .port = GPIO_PORT_PWM_MOTOR_3
    //         },
    //         .prescaler = PWM_PRESCALER_1
    //     },
    //     (PWM_t){
    //         .gpio = {
    //             .dir = GPIO_DIR_OUTPUT,
    //             .pin = GPIO_PIN_PWM_MOTOR_4,
    //             .port = GPIO_PORT_PWM_MOTOR_4
    //         },
    //         .prescaler = PWM_PRESCALER_1
    //     }
    // };
    // ARR_FOREACH(motors, i) {
    //     PWM_Init(&motors[i]);
    // }

    

    
    UART_t uart = {
        .tx = {
            .port = GPIO_PORT_UART_TX,
            .pin = GPIO_PIN_UART_TX
        },
        .rx = {
            .port = GPIO_PORT_UART_RX,
            .pin = GPIO_PIN_UART_RX
        }
    };
    UART_Init(&uart);


    TWI_t twi = {
        .sda = {
            .port = GPIO_PORT_TWI_SDA,
            .pin = GPIO_PIN_UART_TX
        },
        .scl = {
            .port = GPIO_PORT_TWI_SCL,
            .pin = GPIO_PIN_TWI_SCL
        }
    };
    TWI_Init(&twi);
    

    char str[32];

    while(1) {
        // ARR_FOREACH(str, i) {
        //     UART_SendByte(&uart, (uint8_t)str[i]);
        // }

        // register uint8_t res = ADC_Read(&pot) >> 2;

        
        uint8_t twi_byte = TWI_ReadByte(0);
        
        sprintf(str, "%d\r\n", twi_byte);

        UART_SendString(str);

        delayMs(120);


        // for(uint8_t i = 0; i < 0xff; i++) {
        //     PWM_Set(&motor1, i);
        //     delayMs(5);
        // }
        // for(uint8_t i = 0xff; i; i--) {
        //     PWM_Set(&motor1, i);
        //     delayMs(5);
        // }

        // OCR1A = ADC_Read(&pot) >> 2;

        // ARR_FOREACH(motors, i) {
        //     PWM_Set(&motors[i], res);
        // }

        // PWM_Set(&motor1, ADC_Read(&pot) >> 2);
    }
}