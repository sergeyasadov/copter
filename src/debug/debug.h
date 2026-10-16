#ifndef DEBUG_H
#define DEBUG_H

#include "../status.h"


void debug_init(void);

void debug_log(const enum Status, const char* str);

void debug_logf(const enum Status, const char* fmt, ...) __attribute__((format(printf, 2, 3)));


#endif
