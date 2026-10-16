#include "debug.h"

#include "_debug_led_power.c"
#include "_debug_led_signal.c"
#include "_debug_led_exception.c"
#include "_debug_logger.c"
#include "_debug_usart.c"

#include <stdarg.h>
#include <stdio.h>

//========================================================================================
#define DEBUG_BUF_LOGF_SIZE 128
//========================================================================================
__STATIC_INLINE void __log_level_switch(const enum Status status) {
    STATUS_SWITCH(
        status,
        {
            _dl_signal_on();
            _dl_exception_off();
        },
        {
            _dl_signal_off();
            _dl_exception_off();
        },
        {
            _dl_signal_off();
            _dl_exception_on();
        }
    );
}
//========================================================================================
void debug_init(void) {
    USART2_Init();
    DEBUG_LOGGER_OK("Debug UART init");

    _dl_power_init();
    DEBUG_LOGGER_OK("Debug POWER led init");

    _dl_power_on();
    DEBUG_LOGGER_OK("Debug POWER led ON");

    _dl_signal_init();
    DEBUG_LOGGER_OK("Debug signal-led init");

    _dl_exception_init();
    DEBUG_LOGGER_OK("Debug exception-led init");

    _dl_exception_off();
    _dl_signal_off();
}
//----------------------------------------------------------------------------------------
void debug_log(const enum Status status, const char* str) {
    _debug_logger(status, str);

    __log_level_switch(status);
}
//----------------------------------------------------------------------------------------
void debug_logf(const enum Status status, const char* fmt, ...) {
    char buffer[DEBUG_BUF_LOGF_SIZE];

    va_list args;
    va_start(args, fmt);
    int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    if(n < 0) {
        debug_log(STATUS_EXCEPTION, "Debug log format");
        return;
    }

    if((size_t)(n) >= sizeof(buffer)) {
        buffer[sizeof(buffer) - 2] = '~';
        buffer[sizeof(buffer) - 1] = '\0';
    }

    __log_level_switch(status);
}
//========================================================================================
