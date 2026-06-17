#include "../include/tablaPersonas.h"

struct TNodoTabla {
    TPersona persona;
    TNodoTabla* siguiente;
};

struct rep_tablaPersonas {
    int tamanio;
    TNodoTabla** listas;
};

static bool stringsIguales(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i++;
    }
    return s1[i] == '\0' && s2[i] == '\0';
}

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
    rep_tablaPersonas* tabla = new rep_tablaPersonas;
    tabla->tamanio = max;
    tabla->listas = new TNodoTabla*[max];
    for (int i = 0; i < max; i++) {
        tabla->listas[i] = NULL;
    }
    return tabla;
}

void insertarPersonaEnTTablaPersonas(TTablaPersonas &tabla, TPersona persona){
    char* nombre = nombreTPersona(persona);
    nat pos = funcionDeDispersion(nombre) % tabla->tamanio;
    TNodoTabla* nuevo = new TNodoTabla;
    nuevo->persona = persona;
    nuevo->siguiente = tabla->listas[pos];
    tabla->listas[pos] = nuevo;
}

void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->tamanio;
    TNodoTabla* actual = tabla->listas[pos];
    TNodoTabla* anterior = NULL;
    while (actual != NULL) {
        if (stringsIguales(nombreTPersona(actual->persona), nombre)) {
            if (anterior == NULL) {
                tabla->listas[pos] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            liberarTPersona(actual->persona);
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->tamanio;
    TNodoTabla* actual = tabla->listas[pos];
    while (actual != NULL) {
        if (stringsIguales(nombreTPersona(actual->persona), nombre)) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat pos = funcionDeDispersion(nombre) % tabla->tamanio;
    TNodoTabla* actual = tabla->listas[pos];
    while (actual != NULL) {
        if (stringsIguales(nombreTPersona(actual->persona), nombre)) {
            return actual->persona;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void liberarTTablaPersonas(TTablaPersonas &tabla){
    for (int i = 0; i < tabla->tamanio; i++) {
        TNodoTabla* actual = tabla->listas[i];
        while (actual != NULL) {
            TNodoTabla* sig = actual->siguiente;
            liberarTPersona(actual->persona);
            delete actual;
            actual = sig;
        }
    }
    delete[] tabla->listas;
    delete tabla;
    tabla = NULL;
}

void imprimirTTablaPersonas(TTablaPersonas tabla){
    for (int i = 0; i < tabla->tamanio; i++) {
        TNodoTabla* actual = tabla->listas[i];
        while (actual != NULL) {
            imprimirTPersona(actual->persona);
            actual = actual->siguiente;
        }
    }
}