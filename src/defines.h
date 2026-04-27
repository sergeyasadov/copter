#ifndef __COPTER_DEFINES_H__
#define __COPTER_DEFINES_H__


#define D_FREQ_MCU ((unsigned long)1e6)


/// AVR ///
#ifdef __AVR_ARCH__

#ifndef __AVR_ATtiny44A__
#define __AVR_ATtiny44A__
#endif

#ifdef F_CPU
#   define F_CPU D_FREQ_MCU
#endif // F_CPU

#include <avr/io.h>
#include <util/delay.h>

typedef uint8_t GPIO_Pin_t;
typedef uint8_t GPIO_Value_t;
typedef enum GPIO_Port GPIO_Port_t;

typedef uint8_t  PWM_Duty_t;
typedef uint8_t  PWM_Freq_t;
typedef uint8_t  PWM_Value_t;

#ifndef delayMs
#   define delayMs _delay_ms
#endif

#ifndef delayUs
#   define delayUs _delay_us
#endif

#endif //__AVR_ARCH__
/// AVR ///


extern const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_1; 
extern const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_2; 
extern const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_3;
extern const GPIO_Pin_t GPIO_PIN_PWM_MOTOR_4;

extern const GPIO_Port_t GPIO_PORT_PWM_MOTOR_1; 
extern const GPIO_Port_t GPIO_PORT_PWM_MOTOR_2; 
extern const GPIO_Port_t GPIO_PORT_PWM_MOTOR_3;
extern const GPIO_Port_t GPIO_PORT_PWM_MOTOR_4;



#endif // __COPTER_DEFINES_H__
