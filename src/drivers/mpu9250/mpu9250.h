#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>

void MPU9250_Init(void);

void MPU9250_SetSpeed(const uint32_t);

void MPU9250_Write(const uint8_t reg, const uint8_t val);

uint8_t MPU9250_Read(const uint8_t reg);

void MPU9250_ReadBurst(const uint8_t reg, uint8_t* buf, uint_fast8_t len);




#endif // MPU9250_H
