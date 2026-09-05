#include "../defines.h"


__STATIC_INLINE void _debug_uart_tx(const char* str) {
    while(*str) {
        while(!(USART2->SR & USART_SR_TXE));
        USART2->DR = *str++;
    }
}
