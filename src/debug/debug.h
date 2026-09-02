#ifndef DEBUG_H
#define DEBUG_H


enum DEBUG_STATE {
    DEBUG_STATE_OK = 0,
    DEBUG_STATE_ERROR,
    DEBUG_STATE_EXCEPTION,
    DEBUG_STATE_UNKNOWN,
};

void debug_init(void);

void debug_set_state(enum DEBUG_STATE state);

#endif
