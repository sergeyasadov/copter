#include "debug.h"

#include "_debug_led_power.c"
#include "_debug_led_signal.c"
#include "_debug_led_exception.c"

void debug_init(void) {
    _dl_power_init();
    _dl_power_on();

    _dl_signal_init();

    _dl_exception_init();
}

void debug_set_state(enum DEBUG_STATE state) {
    switch(state) {
        case DEBUG_STATE_OK:
            _dl_signal_on();
            _dl_exception_off();
            break;
        case DEBUG_STATE_ERROR:
            _dl_signal_off();
            _dl_exception_off();
            break;
        case DEBUG_STATE_EXCEPTION:
            _dl_signal_off();
            _dl_exception_on();
            break;
        default:
            _dl_signal_off();
            _dl_exception_off();
            _dl_power_off();
            break;
    }
}
