#ifndef __COPTER_DEFINES_H__
#define __COPTER_DEFINES_H__


#define D_FREQ_MCU ((unsigned long)4e6)


/// AVR ///
#ifdef __AVR_ARCH__

#ifndef __AVR_ATtiny44A__
#define __AVR_ATtiny44A__
#endif

#ifndef F_CPU
#   define F_CPU D_FREQ_MCU
#endif // F_CPU

#include <avr/io.h>
#include <util/delay.h>

typedef uint8_t __gpio_value_t;
typedef uint8_t __gpio_pin_t;
typedef uint8_t __gpio_port_t; 
typedef uint8_t __pwm_value_t;
typedef uint8_t __pwm_duty_t;
typedef uint8_t __pwm_freq_t;

#define GPIO_PIN_PWM_MOTOR_1 PB2 
#define GPIO_PIN_PWM_MOTOR_2 PA7 
#define GPIO_PIN_PWM_MOTOR_3 PA6
#define GPIO_PIN_PWM_MOTOR_4 PA5

#define GPIO_PORT_PWM_MOTOR_1 PORTB
#define GPIO_PORT_PWM_MOTOR_2 PORTA
#define GPIO_PORT_PWM_MOTOR_3 PORTA
#define GPIO_PORT_PWM_MOTOR_4 PORTA

#ifndef delayMs
#   define delayMs _delay_ms
#endif

#ifndef delayUs
#   define delayUs _delay_us
#endif

#endif //__AVR_ARCH__
/// AVR ///

#endif // __COPTER_DEFINES_H__
