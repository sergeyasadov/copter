#include "debug.h"

#include "_debug_led_power.c"
#include "_debug_led_signal.c"
#include "_debug_led_exception.c"
#include "_debug_logger.c"
#include "_debug_usart.c"
#include "logger.h"


void debug_init(void) {
    USART2_Init();
    _debug_logger(LOG_LEVEL_OK, "Debug UART init");

    _dl_power_init();
    _debug_logger(LOG_LEVEL_OK, "Debug POWER led init");

    _dl_power_on();
    _debug_logger(LOG_LEVEL_OK, "Debug POWER led ON");

    _dl_signal_init();
    _debug_logger(LOG_LEVEL_OK, "Debug signal-led init");

    _dl_exception_init();
    _debug_logger(LOG_LEVEL_OK, "Debig exception-led init");
}

void debug_log(const enum LOG_LEVEL level, const char* str) {
    _debug_logger(level, str);
    switch(level) {
        case LOG_LEVEL_OK: {
            _dl_signal_on();
            _dl_exception_off();
            return;
        }
        case LOG_LEVEL_ERROR: {
            _dl_signal_off();
            _dl_exception_off();
            return;
        }
        case LOG_LEVEL_EXCEPTION: {
            _dl_signal_off();
            _dl_exception_on();
            return;
        }
    }
}
