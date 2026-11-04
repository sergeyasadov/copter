#include "debug.h"
#include "debug_led.h"
#include "logger/logger.h"

#include <stdarg.h>
#include <stdio.h>

//========================================================================================
#define DEBUG_BUF_LOGF_SIZE 128
//========================================================================================
void DebugInit(void) {
    DebugLogger_Init();
    DEBUG_LOGGER_OK("Debug logger init");

    DebugLed_Init(DL_TYPE_POWER);
    DEBUG_LOGGER_OK("Debug POWER led init");

    DebugLed_SetState(DL_TYPE_POWER, 1);
    DEBUG_LOGGER_OK("Debug POWER led ON");

    DebugLed_Init(DL_TYPE_SIGNAL);
    DEBUG_LOGGER_OK("Debug signal-led init");

    DebugLed_Init(DL_TYPE_EXCEPTION);
    DEBUG_LOGGER_OK("Debug exception-led init");

    DebugLed_SetState(DL_TYPE_EXCEPTION, 0);
    DebugLed_SetState(DL_TYPE_SIGNAL, 0);
}
//----------------------------------------------------------------------------------------
void DebugLog(const enum Status status, const char* str) {
    DebugLogger_Print(status, str);
    DebugLed_SetStatus(status);
}
//----------------------------------------------------------------------------------------
void DebugLogf(const enum Status status, const char* fmt, ...) {
    char buffer[DEBUG_BUF_LOGF_SIZE];

    va_list args;
    va_start(args, fmt);
    int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    if(n < 0) {
        DebugLog(STATUS_EXCEPTION, "Debug log format");
        return;
    }

    if((uint32_t)(n) >= sizeof(buffer)) {
        buffer[sizeof(buffer) - 2] = '~';
        buffer[sizeof(buffer) - 1] = '\0';
    }

    DebugLog(status, buffer);
}
//========================================================================================
