#include "../include/debug.h"
#include <cstdarg>
#include <cstdio>

void debuf(const char* funcion,const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char newFmt[1024];
    std::snprintf(newFmt, sizeof(newFmt), "%s", fmt);

    std::printf("\n--------[DEBUG: %s%s%s]--------\n", AZUL, funcion, NC);
    std::vprintf(newFmt, args);

    va_end(args);
    std::printf("%s\n", NC);
}
