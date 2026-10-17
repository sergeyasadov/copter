#ifndef DEBUG_USART2_H
#define DEBUG_USART2_H

#include "../../defines.h"


__STATIC_INLINE
void USART2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    GPIOA->CRL &= ~((0b1111u << (4 * UART_DEBUG_TX)));
    GPIOA->CRL |= (0b1011u << (4 * UART_DEBUG_TX));

    GPIOA->CRL &= ~((0b1111u << (4 * UART_DEBUG_RX)));
    GPIOA->CRL |= (0b0100u << (4 * UART_DEBUG_RX));

    USART2->BRR = 0x139; // 115200 baud

    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}


__STATIC_INLINE
void USART2_SendByte(const uint_fast8_t ch) {
    while(!(USART2->SR & USART_SR_TXE));
    USART2->DR = ch;
}


__STATIC_INLINE
void USART2_SendString(const char* str) {
    while(*str)
        USART2_SendByte(*str++);
}


#endif // DEBUG_USART2_H
