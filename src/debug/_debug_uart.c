#include "../defines.h"

__STATIC_INLINE void _debug_uart_init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    GPIOA->CRL &= ~((0b1111u << (4 * UART_DEBUG_TX)));
    GPIOA->CRL |= (0b1011 << (4 * UART_DEBUG_TX));

    GPIOA->CRL &= ~((0b1111u << (4 * UART_DEBUG_RX)));
    GPIOA->CRL |= (0b0100u << (4 * UART_DEBUG_RX));

    USART2->BRR = 0x341;
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}
