#include "../defines.h"
#include "logger.h"

#include "_debug_usart_tx.c"

#include <stdarg.h>

#define DEBUG_LOG_COLOR_RED     "\x1B[31m"
#define DEBUG_LOG_COLOR_GREEN   "\x1B[32m"
#define DEBUG_LOG_COLOR_YELLOW  "\x1B[33m"
#define DEBUG_LOG_COLOR_BLUE    "\x1B[34m"
#define DEBUG_LOG_COLOR_MAGENTA "\x1B[35m"
#define DEBUG_LOG_COLOR_CYAN    "\x1B[36m"
#define DEBUG_LOG_COLOR_WHITE   "\x1B[37m"
#define DEBUG_LOG_COLOR_RESET   "\x1B[0m"
#define DEBUG_LOG_UNDERLINE     "\x1B[4m"
#define DEBUG_LOG_BOLD          "\x1B[1m"

#define DEBUG_LOG_BG_BLACK   "\x1B[40m"
#define DEBUG_LOG_BG_RED     "\x1B[41m"
#define DEBUG_LOG_BG_GREEN   "\x1B[42m"
#define DEBUG_LOG_BG_YELLOW  "\x1B[43m"
#define DEBUG_LOG_BG_BLUE    "\x1B[44m"
#define DEBUG_LOG_BG_MAGENTA "\x1B[45m"
#define DEBUG_LOG_BG_CYAN    "\x1B[46m"
#define DEBUG_LOG_BG_WHITE   "\x1B[47m"

#define DEBUG_LOG_TEMPLATE_GENERIC(__data) "[" __data DEBUG_LOG_COLOR_RESET "] "
#define DEBUG_LOG_TEMPLATE_OK            DEBUG_LOG_TEMPLATE_GENERIC(DEBUG_LOG_COLOR_GREEN DEBUG_LOG_BOLD "OK")
#define DEBUG_LOG_TEMPLATE_ERR           DEBUG_LOG_TEMPLATE_GENERIC(DEBUG_LOG_COLOR_RED DEBUG_LOG_BOLD "ER")
#define DEBUG_LOG_TEMPLATE_EXC           DEBUG_LOG_TEMPLATE_GENERIC(DEBUG_LOG_COLOR_WHITE DEBUG_LOG_BG_RED DEBUG_LOG_BOLD "EX")
#define DEBUG_LOG_TEMPLATE_MODULE  "\t"

#define DEBUG_LOG_OK_PREFIX        DEBUG_LOG_TEMPLATE_OK      DEBUG_LOG_TEMPLATE_MODULE
#define DEBUG_LOG_EXC_PREFIX       DEBUG_LOG_TEMPLATE_EXC     DEBUG_LOG_TEMPLATE_MODULE
#define DEBUG_LOG_ERR_PREFIX       DEBUG_LOG_TEMPLATE_ERR     DEBUG_LOG_TEMPLATE_MODULE

#define USART_TX(__s) USART2_SendString(__s)

#define DEBUG_PRINT_MODULE(__prefix, __module) do { \
    USART_TX(__prefix);\
    USART_TX(__module);\
    USART_TX("\r\n");\
} while(0)


__STATIC_INLINE void _debug_logger(const enum LOG_LEVEL level, const char* str) {
    switch(level) {
        case LOG_LEVEL_OK: {
            DEBUG_PRINT_MODULE(DEBUG_LOG_OK_PREFIX, str);
            return;
        }

        case LOG_LEVEL_ERROR: {
            DEBUG_PRINT_MODULE(DEBUG_LOG_ERR_PREFIX, str);
            return;
        }

        case LOG_LEVEL_EXCEPTION: {
            DEBUG_PRINT_MODULE(DEBUG_LOG_EXC_PREFIX, str);
            return;
        }
    }
}
