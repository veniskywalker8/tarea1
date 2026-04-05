#include "../include/personasLDE.h"

//+ AUXILIARES
void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact);
TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);
TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);

struct rep_personasLDE {
    TPersona nodo;
    TPersonasLDE sig;
    TPersonasLDE ant;
};

TPersonasLDE crearTPersonasLDE(){
    return auxCrear(nullptr, nullptr, nullptr); // lista vacía
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    if (pos < 1) return;
    nat posact = 1;
    auxInsertar(personas, persona, pos, posact);
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE){
    while (personasLDE != nullptr) {
        TPersonasLDE actual = personasLDE;
        personasLDE = personasLDE->sig;
        if (actual->nodo != nullptr) liberarTPersona(actual->nodo);
        delete actual;
    }
    personasLDE = nullptr;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    if (personas == nullptr) return;
    if (personas->nodo != nullptr) imprimirTPersona(personas->nodo);
    imprimirTPersonasLDE(personas->sig);
}

nat cantidadTPersonasLDE(TPersonasLDE personas) {
    if (personas == nullptr) return 0;
    return (personas->nodo != nullptr ? 1 : 0) + cantidadTPersonasLDE(personas->sig);
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas == nullptr) return;
    if (personas->nodo == nullptr) return;

    TPersonasLDE viejo = personas;
    TPersonasLDE nuevoInicio = personas->sig;

    liberarTPersona(viejo->nodo);
    delete viejo;

    personas = nuevoInicio;
    if (personas != nullptr) {
        personas->ant = nullptr;
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if (personas == nullptr) return;
    TPersonasLDE it = personas;
    while (it->sig != nullptr) {
        it = it->sig;
    }
    if (it->nodo != nullptr) liberarTPersona(it->nodo);
    if (it->ant != nullptr) it->ant->sig = nullptr;
    delete it;
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    for (TPersonasLDE it = personas; it != nullptr; it = it->sig) {
        if (it->nodo != nullptr && idTPersona(it->nodo) == id) return true;
    }
    return false;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    for (TPersonasLDE it = personas; it != nullptr; it = it->sig) {
        if (it->nodo != nullptr && idTPersona(it->nodo) == id) return it->nodo;
    }
    return nullptr;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    if (personas1 == nullptr) return personas2;
    TPersonasLDE it = personas1;
    while (it->sig != nullptr) {
        it = it->sig;
    }
    it->sig = personas2;
    if (personas2 != nullptr) personas2->ant = it;
    return personas1;
}

//+ AUXILIARES

void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact) {
    if (posact == pos) {
        if (personas->nodo == nullptr){
            personas->nodo = persona;
        } else {
            TPersonasLDE nuevo = auxEnlazar(persona, personas, personas->ant);
            personas = nuevo;
        }
    }
    else if (personas->sig == nullptr) {
        auxEnlazar(persona, nullptr, personas);
    }
    else {
        auxInsertar(personas->sig, persona, pos, posact + 1);
    }
}

TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant){
    TPersonasLDE nuevo = new rep_personasLDE;
    nuevo->nodo = nodo;
    nuevo->sig = sig;
    nuevo->ant = ant;
    return nuevo;
}

TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant){
    TPersonasLDE nuevo = auxCrear(nodo, sig, ant);
    if (sig != nullptr) sig->ant = nuevo;
    if (ant != nullptr) ant->sig = nuevo;
    return nuevo;
}
