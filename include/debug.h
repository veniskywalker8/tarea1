#ifndef DEBUG_H
#define DEBUG_H
//*/* Colores ANSI para C++ */
constexpr const char* ROJO    = "\033[31m";
constexpr const char* VERDE   = "\033[32m";
constexpr const char* AMARILLO= "\033[33m";
constexpr const char* AZUL    = "\033[34m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* CIAN    = "\033[36m";
constexpr const char* NC      = "\033[0m";   // Reset (No Color)

void debuf(const char* funcion,const char* fmt, ...);

#endif