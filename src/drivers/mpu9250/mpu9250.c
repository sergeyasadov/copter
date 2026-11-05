#include "mpu9250.h"
#include "SPI1.h"

#include "../../defines.h"
#include "../../debug/debug.h"

#define MPU_REG_USER_CTRL   0x6A
#define MPU_REG_PWR_MGMT_1  0x6B
#define MPU_REG_WHO_AM_I    0x75

#define MPU_REG_CLOCK_SEL_PLL 0x01


#define MPU_BIT_I2C_IF_DIS  (1UL << 4)
#define MPU_BIT_FIFO_EN     (1UL << 6)

#define MPU_BIT_H_RESET     (1UL << 7)


void MPU9250_WriteReg(const uint8_t reg, const uint8_t value) {
    SPI1_CS_Set(0);
    SPI1_Transfer(reg & 0x7F);
    SPI1_Transfer(value);
    while(SPI1->SR & SPI_SR_BSY);
    SPI1_CS_Set(1);
}

uint8_t MPU9250_ReadReg(const uint8_t reg) {
    SPI1_CS_Set(0);
    SPI1_Transfer(reg | 0x80);
    const uint8_t data = SPI1_Transfer(0);
    while(SPI1->SR & SPI_SR_BSY);
    SPI1_CS_Set(1);
    return data;
}


void MPU9250_Init(void) {
    SPI1_GPIO_Init();
    SPI1_Init();
    for(volatile uint32_t i = 0; i < 5000; i++);
}
