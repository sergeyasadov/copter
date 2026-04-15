#ifndef __COPTER_DEFINES_H__
#define __COPTER_DEFINES_H__



// #ifndef F_CPU
#define D_FREQ_MCU ((unsigned long)4e6)
// #endif


/// AVR ///
#ifdef __AVR_ARCH__

#ifndef F_CPU
#   define F_CPU D_FREQ_MCU
#endif // F_CPU

#include <avr/io.h>
#include <util/delay.h>

typedef uint8_t __gpio_value_t;
typedef uint8_t __gpio_pin_t;
typedef uint8_t __pwm_value_t;
typedef uint8_t __pwm_duty_t;
typedef uint8_t __pwm_freq_t;

#define GPIO_PWM_MOTOR_1
#define GPIO_PWM_MOTOR_2
#define GPIO_PWM_MOTOR_3
#define GPIO_PWM_MOTOR_4

#ifndef delayMs
#   define delayMs _delay_ms
#endif

#ifndef delayUs
#   define delayUs _delay_us
#endif

#endif //__AVR_ARCH__
/// AVR ///

#endif // __COPTER_DEFINES_H__
