#include "../include/debug.h"
#include <iostream>
#include <cstdarg>
#include <cstdio>

void debuf(const char* funcion,const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // Construimos un nuevo formato que añade "%s\n" al final
    char newFmt[1024];
    std::snprintf(newFmt, sizeof(newFmt), "%s", fmt);

    // Prefijo de depuración
    std::printf("\n--------[DEBUG: %s%s%s]--------\n", AZUL,funcion, NC);

    // Imprimimos los argumentos originales
    std::vprintf(newFmt, args);

    va_end(args);          

    // Añadimos siempre "NC" al final
    std::printf("%s\n", NC);
}