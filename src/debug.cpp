#include "../include/debug.h"
#include <cstdarg>
#include <cstdio>

void debuf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // Imprimir los argumentos según el formato
    std::vprintf(fmt, args);

    va_end(args);

    // Añadir siempre "NC" al final
    std::printf("%s\n", NC);
}
