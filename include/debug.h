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

#include <typeinfo>   // necesario para typeid
#include <cxxabi.h>   // necesario para abi::__cxa_demangle
#include <cstdlib>    // necesario para free
#include <cstring>    // necesario para strncpy

//**Para ver los nombres de los datos*/
template <typename T>
const char* mostrarTipo(const T& var) {
    static char buffer[256];
    int status;
    const char* mangled = typeid(var).name();
    char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);

    if (status == 0 && demangled) {
        strncpy(buffer, demangled, sizeof(buffer)-1);
        buffer[sizeof(buffer)-1] = '\0';
        free(demangled);
    } else {
        strncpy(buffer, mangled, sizeof(buffer)-1);
        buffer[sizeof(buffer)-1] = '\0';
    }
    return buffer;
}
template <typename T>
const char* estadoPuntero(T* ptr) {
    if (ptr == nullptr) {
        return "NULL";
    } else {
        return mostrarTipo(ptr);
    }
}

void debuf(const char* funcion,const char* fmt, ...);

#endif
