#ifndef __COPTER_ADC_H__
#define __COPTER_ADC_H__

#include "defines.h"
#include "gpio.h"

typedef enum : uint_fast8_t {
    ADC_REF_VCC,
    ADC_REF_EXTERNAL,
    ADC_REF_INTERNAL
} ADC_Ref;

typedef enum : uint_fast8_t {
    ADC_PRESCALER_2 = 2,
    ADC_PRESCALER_4 = 4,
    ADC_PRESCALER_8 = 8,
    ADC_PRESCALER_16 = 16,
    ADC_PRESCALER_32 = 32,
    ADC_PRESCALER_64 = 64,
    ADC_PRESCALER_128 = 128
} ADC_Prescaler;

typedef struct {
    GPIO_t gpio;
    ADC_Ref ref;
    ADC_Prescaler presc;
} ADC_t;


void ADC_Init(ADC_t*);

uint16_t ADC_Read(ADC_t*);


#endif // __COPTER_ADC_H__