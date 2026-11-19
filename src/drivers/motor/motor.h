#ifndef MOTOR_H
#define MOTOR_H


#include <stdint.h>


enum MotorState {
    MOTOR_STATE_IDLE,
    MOTOR_STATE_OFF,
    MOTOR_STATE_ON
};

struct Motor_TypeDef {
    uint8_t value[4];
};


void Motor_Init(struct Motor_TypeDef*);

void Motor_Set(const struct Motor_TypeDef*);

void Motor_Write(struct Motor_TypeDef*, const uint8_t* __RESTRICT);

void Motor_Reset(struct Motor_TypeDef*);

#endif // MOTOR_H
