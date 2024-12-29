#ifndef _DEBUG_H

#include "sokol_log.h"
#include <stdio.h>

static void log_impl(const int level, const int line, const char* filename, const char* msg, ...)
{
    char str[256];
    int length = -1;
    va_list argList;
    va_start(argList, msg);
    length = vsnprintf(str, sizeof(str), msg, argList);
    va_end(argList);
    if (length > 0)
        slog_func((char*)"app", level, 0, str, line, filename, nullptr);
}

#define LOG_INFO(...) log_impl(3, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_WARNING(...) log_impl(2, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_ERROR(...) log_impl(1, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_PANIC(...) log_impl(0, __LINE__, __FILE__, __VA_ARGS__)

#endif
