#ifndef DEBUG_LOG_SEND_H
#define DEBUG_LOG_SEND_H

#include "USART2.h"


#define DEBUG_PRINT_INIT()      USART2_Init();
#define DEBUG_USART_TX(__s)     USART2_SendString(__s)

#define DEBUG_PRINT_MODULE(__prefix, __module) do { \
    DEBUG_USART_TX(__prefix);\
    DEBUG_USART_TX(__module);\
    DEBUG_USART_TX("\r\n");\
} while(0)

#endif // DEBUG_LOG_SEND_H
