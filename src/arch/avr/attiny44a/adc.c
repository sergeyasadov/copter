#include "adc.h"


void ADC_Init(ADC_t* adc) {
    if(adc->gpio.port != GPIO_PORT_A) return;

    switch(adc->ref) {
        case ADC_REF_EXTERNAL: {
            ADMUX |= _BV(REFS0);
            break;
        }

        case ADC_REF_INTERNAL: {
            ADMUX |= _BV(REFS1);
            break;
        }
        
        case ADC_REF_VCC:
        default: {
            break;
        }
    }

    ADMUX |= adc->gpio.pin;

    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(adc->presc);
}


uint16_t ADC_Read(ADC_t* adc) {
    return (uint16_t)(ADC);
}