#include "mpu9250.h"
#include "../../debug/debug.h"
#include "../../defines.h"


__STATIC_FORCEINLINE void __SPI1_CS_HIGH(void) {
    GPIOA->BSRR = (1UL << 4UL);
}

__STATIC_FORCEINLINE void __SPI1_CS_LOW(void) {
    GPIOA->BSRR = (1UL << (4UL + 16));
}

__STATIC_INLINE void __SPI1_GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;

    __SPI1_CS_HIGH();
    GPIOA->CRL = (GPIOA->CRL & ~((0xFUL << 16) | (0xFUL << 20) | (0xFUL << 24) | (0xFUL << 28)))
                | (0x3UL << 16)    // PA4 CS:   output push-pull
                | (0xBUL << 20)    // PA5 SCK:  AF push-pull
                | (0x4UL << 24)    // PA6 MISO: floating input
                | (0xBUL << 28);   // PA7 MOSI: AF push-pull

    DebugLog(STATUS_OK, "SPI1 GPIO Init");
}

__STATIC_INLINE void __SPI1_Init(void) {
    SPI1->CR1 |= SPI_CR1_MSTR
               | SPI_CR1_SSI | SPI_CR1_SSM
               | SPI_CR1_CPOL | SPI_CR1_CPHA
               | SPI_CR1_BR_1 | SPI_CR1_BR_2;

    SPI1->CR1 |= SPI_CR1_SPE;
    DebugLog(STATUS_OK, "SPI1 Init");
}

__STATIC_INLINE void __SPI1_SetSpeed(const uint32_t br) {
    while(SPI1->SR & SPI_SR_BSY);
    SPI1->CR1 = (SPI1->CR1 & ~SPI_CR1_BR) | (br << SPI_CR1_BR_Pos);
}

__STATIC_INLINE uint8_t __SPI1_RX(void) {
    while(!(SPI1->SR & SPI_SR_RXNE));
    return (uint8_t)(SPI1->DR);
}

__STATIC_INLINE void __SPI1_TX(const uint8_t b) {
    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = b;
}

__STATIC_INLINE uint8_t __SPI1_Transfer(const uint8_t data) {
    __SPI1_TX(data);
    return __SPI1_RX();
}


void MPU9250_Init(void) {
    __SPI1_GPIO_Init();
    __SPI1_Init();
    DebugLog(STATUS_OK, "Driver MPU9250 Init");
}

void MPU9250_SetSpeed(const uint32_t br) {
    __SPI1_SetSpeed(br);
}

void MPU9250_Write(const uint8_t reg, const uint8_t val) {
    __SPI1_CS_LOW();
    __SPI1_Transfer(reg & 0x7F);
    __SPI1_Transfer(val);
    __SPI1_CS_HIGH();
}

uint8_t MPU9250_Read(const uint8_t reg) {
    __SPI1_CS_LOW();
    __SPI1_Transfer(reg | 0x80);
    const uint8_t val = __SPI1_Transfer(0xFF);
    __SPI1_CS_HIGH();
    return val;
}

void MPU9250_ReadBurst(const uint8_t reg, uint8_t* buf, uint_fast8_t len) {
    __SPI1_CS_LOW();
    __SPI1_Transfer(reg | 0x80);
    while(len--)
        *buf++ = __SPI1_Transfer(0xFF);
    __SPI1_CS_HIGH();
}
