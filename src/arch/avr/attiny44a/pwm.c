#include "pwm.h"
#include "utils.h"

typedef enum PWM_TimerID {
    PWM_TIMER_0,
    PWM_TIMER_1
} PWM_TimerID;

typedef enum PWM_ChannelID {
    PWM_CH_A,
    PWM_CH_B
} PWM_ChannelID;

typedef struct PWM_HwChannel_t {
    PWM_TimerID timerID;
    PWM_ChannelID chID;
} PWM_HwChannel_t;


static const PWM_HwChannel_t PWM_CHANNELS[] = {
    {PWM_TIMER_0, PWM_CH_A},
    {PWM_TIMER_0, PWM_CH_B},
    {PWM_TIMER_1, PWM_CH_A},
    {PWM_TIMER_1, PWM_CH_B}
};


static inline const PWM_HwChannel_t* PWM_FindChannel(const GPIO_t* gpio) {
    if(gpio->pin == GPIO_PIN_PWM_MOTOR_1 && gpio->port == GPIO_PORT_PWM_MOTOR_1) {
        return &PWM_CHANNELS[0];
    }
    if(gpio->pin == GPIO_PIN_PWM_MOTOR_2 && gpio->port == GPIO_PORT_PWM_MOTOR_2) {
        return &PWM_CHANNELS[1];
    }
    if(gpio->pin == GPIO_PIN_PWM_MOTOR_3 && gpio->port == GPIO_PORT_PWM_MOTOR_3) {
        return &PWM_CHANNELS[2];
    }
    if(gpio->pin == GPIO_PIN_PWM_MOTOR_4 && gpio->port == GPIO_PORT_PWM_MOTOR_4) {
        return &PWM_CHANNELS[3];
    }
}


// static uint8_t PWM_GetPrescalerBits(const PWM_HwChannel_t* channel, const PWM_t* pwm) {
//     if(channel->timerID == PWM_TIMER_0) {
//         switch(pwm->prescaler) {
//             case PWM_PRESCALER_1:    return _BV(CS00);
//             case PWM_PRESCALER_8:    return _BV(CS01);
//             case PWM_PRESCALER_64:   return _BV(CS01) | _BV(CS00);
//             case PWM_PRESCALER_256:  return _BV(CS02);
//             case PWM_PRESCALER_1024: return _BV(CS02) | _BV(CS00);
//             default:                 return 0;
//         }
//     } else {
//         switch(pwm->prescaler) {
//             case PWM_PRESCALER_1:    return _BV(CS10);
//             case PWM_PRESCALER_8:    return _BV(CS11);
//             case PWM_PRESCALER_64:   return _BV(CS11) | _BV(CS10);
//             case PWM_PRESCALER_256:  return _BV(CS12);
//             case PWM_PRESCALER_1024: return _BV(CS12) | _BV(CS10);
//             default:                 return 0;
//         }
//     }
// }


void PWM_Init(PWM_t* pwm) {
    GPIO_Init(&pwm->gpio);

    const PWM_HwChannel_t* channel = PWM_FindChannel(&pwm->gpio);

    if(channel->timerID == PWM_TIMER_0) {
        TCCR0A |= _BV(WGM00) | _BV(WGM01);

        if(channel->chID == PWM_CH_A) {
            TCCR0A |= _BV(COM0A1) | _BV(COM0A0);
        } 
        else {
            TCCR0A |= _BV(COM0B1) | _BV(COM0B0); 
        }

        TCCR0B |= pwm->prescaler;
    }
    else {
        TCCR1A |= _BV(WGM10);
        TCCR1B |= _BV(WGM12) | pwm->prescaler;

        if(channel->chID == PWM_CH_A) {
            TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
        }
        else {
            TCCR1A |= _BV(COM1B1) | _BV(COM1B0);
        }

    }

    PWM_Set(pwm, 0);
}


void PWM_Set(PWM_t* pwm, const uint8_t value) {
    const PWM_HwChannel_t* channel = PWM_FindChannel(&pwm->gpio);
    
    if(channel->timerID == PWM_TIMER_0) {
        if(channel->chID == PWM_CH_A) {
            OCR0A = 255 - value;
        }
        else {
            OCR0B = 255 - value;
        }
    }
    else {
        if(channel->chID == PWM_CH_A) {
            OCR1A = 255 - value;
        }
        else {
            OCR1B = 255 - value;
        }
    }
}
