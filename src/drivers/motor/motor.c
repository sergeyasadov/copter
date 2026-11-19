#include "motor.h"
#include "TIM1.h"


void Motor_Init(struct Motor_TypeDef* m) {
    TIM1_GPIO_Init();
    TIM1_Init();

    Motor_Reset(m);
}

void Motor_Set(const struct Motor_TypeDef* m) {
    TIM1_CH1_Set(m->value[0]);
    TIM1_CH2_Set(m->value[1]);
    TIM1_CH3_Set(m->value[2]);
    TIM1_CH4_Set(m->value[3]);
}

void Motor_Write(struct Motor_TypeDef* m, const uint8_t* __RESTRICT val) {
    for(uint_fast8_t i = 0; i < 4; i++) {
        m->value[i] = val[i];
    }
}


void Motor_Reset(struct Motor_TypeDef* m) {
    *m = (struct Motor_TypeDef){0};
    Motor_Set(m);
}
