#ifndef DEBUG_H
#define DEBUG_H

#include "logger.h"


void debug_init(void);

void debug_log(const enum LOG_LEVEL level, const char* str);

#endif
