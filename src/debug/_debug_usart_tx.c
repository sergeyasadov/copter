#include "../defines.h"

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
