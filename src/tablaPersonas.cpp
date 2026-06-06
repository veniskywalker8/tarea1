#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    return NULL;
}

void insertarPersonaEnTTablaPersonas(TTablaPersonas &tabla, TPersona persona){
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    return false;
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    return NULL;
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
}