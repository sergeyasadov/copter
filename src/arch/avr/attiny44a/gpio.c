#include "gpio.h"


#define sbi(r, b) ((r) |= _BV(b))
#define cbi(r, b) ((r) &= ~_BV(b))

/// EXTERNAL

const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_1 = PB2;
const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_2 = PA7;
const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_3 = PA6;
const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_4 = PA5;

const GPIO_Port_t GPIO_PORT_PWM_MOTOR_1 = GPIO_PORT_B;
const GPIO_Port_t GPIO_PORT_PWM_MOTOR_2 = GPIO_PORT_A;
const GPIO_Port_t GPIO_PORT_PWM_MOTOR_3 = GPIO_PORT_A;
const GPIO_Port_t GPIO_PORT_PWM_MOTOR_4 = GPIO_PORT_A;


void GPIO_Init(GPIO_t* gpio) {
    GPIO_SetDir(gpio, gpio->dir);
    GPIO_Write(gpio, GPIO_LEVEL_LOW);
}


void GPIO_SetDir(GPIO_t* gpio, GPIO_Dir ndir) {
    gpio->dir = ndir;
    volatile uint8_t* reg = gpio->port == GPIO_PORT_A ? &DDRA : &DDRB;
    switch (gpio->dir) {
        case GPIO_DIR_OUTPUT : {
            sbi(*reg, gpio->pin);
            break;
        }

        case GPIO_DIR_INPUT_PULLUP : {
            GPIO_SetHigh(gpio);
        }

        case GPIO_DIR_INPUT : {
            cbi(*reg, gpio->pin);
            break;
        }

        default: break;
    }
}


void GPIO_Write(GPIO_t* gpio, GPIO_Level level) {
    volatile uint8_t* reg = gpio->port == GPIO_PORT_A ? &PORTA : &PORTB;
    switch (level) {
        case GPIO_LEVEL_HIGH : {
            sbi(*reg, gpio->pin);
            break;
        }
        case GPIO_LEVEL_LOW : {
            cbi(*reg, gpio->pin);
            break;
        }  
        default:
            break;
    }
}


GPIO_Level GPIO_Read(const GPIO_t* gpio) {
    return ((gpio->port == GPIO_PORT_A ? PINA : PINB) & _BV(gpio->pin)) ? GPIO_LEVEL_LOW : GPIO_LEVEL_HIGH;
}

void GPIO_SetHigh(GPIO_t* gpio) {
    GPIO_Write(gpio, GPIO_LEVEL_HIGH);
}


void GPIO_SetLow(GPIO_t* gpio) {
    GPIO_Write(gpio, GPIO_LEVEL_LOW);
}


void GPIO_SetToggle(GPIO_t* gpio) {
    GPIO_Write(gpio, GPIO_Read(gpio) == GPIO_LEVEL_LOW);
}