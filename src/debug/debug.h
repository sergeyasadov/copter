#ifndef DEBUG_H
#define DEBUG_H

#include "status.h"


void Debug_Init(void);

void DebugLog(const enum Status, const char* str);

void DebugLogf(const enum Status, const char* fmt, ...) __attribute__((format(printf, 2, 3)));

#define DEBUG_LOG_OK(str) DebugLog(STATUS_OK, str);
#define DEBUG_LOG_ERROR(str) DebugLog(STATUS_ERROR, str);
#define DEBUG_LOG_EXCEPTION(str) DebugLog(STATUS_EXCEPTION, str);

#endif
