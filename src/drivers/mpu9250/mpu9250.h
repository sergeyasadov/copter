#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>


void MPU9250_Init(void);

void MPU9250_WriteReg(const uint8_t reg, const uint8_t value);

uint8_t MPU9250_ReadReg(const uint8_t reg);



#endif /* MPU9250_H */
