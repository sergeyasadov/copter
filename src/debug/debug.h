#ifndef DEBUG_H
#define DEBUG_H

#include "../status.h"


void Debug_Init(void);

void DebugLog(const enum Status, const char* str);

void DebugLogf(const enum Status, const char* fmt, ...) __attribute__((format(printf, 2, 3)));


#endif
