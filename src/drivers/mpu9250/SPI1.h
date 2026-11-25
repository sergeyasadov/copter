#ifndef SPI1_H
#define SPI1_H

#include "../../defines.h"
#include "../../iodefs.h"
#include "../../debug/debug.h"


enum SPI1_BaudRate {
    SPI1_BR_2,
    SPI1_BR_4,
    SPI1_BR_8,
    SPI1_BR_16,
    SPI1_BR_32,
    SPI1_BR_64,
    SPI1_BR_128,
    SPI1_BR_256
};


__STATIC_INLINE void SPI1_CS_Set(const uint_fast32_t state) {
    switch(state) {
        case 0: {
            GPIOA->BRR = GPIO_MPU_NSS;
            return;
        }
        case 1: {
            GPIOA->BSRR = GPIO_MPU_NSS;
            return;
        }
        default: return;
    }
}




__STATIC_INLINE void SPI1_GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;

    SPI1_CS_Set(1);

    GPIOA->CRL = (GPIOA->CRL & ~(
        (GPIO_CRL_MODE4 | GPIO_CRL_CNF4) |      // CS
        (GPIO_CRL_MODE0 | GPIO_CRL_CNF0) |      // SCK
        (GPIO_CRL_MODE6 | GPIO_CRL_CNF6) |      // MISO
        (GPIO_CRL_MODE7 | GPIO_CRL_CNF7) |      // MOSI
        (GPIO_CRL_MODE5 | GPIO_CRL_CNF5)        // INT
    )) | (
        (GPIO_CRL_MODE4) |                      // PA4 CS:   output push-pull
        (GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5) |    // PA5 SCK:  AF push-pull
        (GPIO_CRL_CNF6_0) |                     // PA6 MISO: floating input
        (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7) |    // PA7 MOSI: AF push-pull
        (GPIO_CRL_CNF0_0)                       // PA0 INT:  floating input
    );

    DebugLog(STATUS_OK, "SPI1 GPIO Init");
}


__STATIC_INLINE void SPI1_Init(void) {
    SPI1->CR2 = 0x0000;
    SPI1->CR1 = 0x0000;

    SPI1->CR1 |= SPI_CR1_MSTR
               | SPI_CR1_SSI  | SPI_CR1_SSM
               | SPI_CR1_CPOL | SPI_CR1_CPHA // mode 3
               | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2; // low frq

    SPI1->CR1 |= SPI_CR1_SPE;
    DebugLog(STATUS_OK, "SPI1 Init");
}


__STATIC_INLINE void SPI1_SetSpeed(const enum SPI1_BaudRate br) {
    while(SPI1->SR & SPI_SR_BSY);
    SPI1->CR1 = (SPI1->CR1 & ~SPI_CR1_BR) | ((uint32_t)(br) << SPI_CR1_BR_Pos);
}

__STATIC_INLINE uint8_t SPI1_Transfer(const uint8_t data) {
    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;

    while(!(SPI1->SR & SPI_SR_RXNE));
    return (uint8_t)(SPI1->DR);
}



#endif // SPI1_H
