#include "../defines.h"


__STATIC_INLINE char _debug_uart_rx(void) {
    while(!(USART2->SR & USART_SR_RXNE));
    return (char)(USART2->DR & 0xFF);
}
