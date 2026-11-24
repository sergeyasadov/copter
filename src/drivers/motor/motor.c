#include "motor.h"
#include "TIM1.h"


void Motor_Init(struct Motor_TypeDef* m) {
    TIM1_GPIO_Init();
    TIM1_Init();

    Motor_Reset(m);
}


void Motor_Set(const struct Motor_TypeDef* m) {
    for(uint_fast8_t i = 4; i; i--) {
        TIM1_CH_Set(i, m->value[i - 1]);
    }
}


void Motor_Write(const uint_fast8_t n, const uint_fast8_t val) {
    TIM1_CH_Set(n + 1, val);
}


void Motor_Reset(struct Motor_TypeDef* m) {
    *m = (struct Motor_TypeDef){0};
    Motor_Set(m);
}
