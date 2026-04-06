#include "../include/personasLDE.h"

//+ AUXILIARES
void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact);
TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);
TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);
void auxEnlazarABC(TPersonasLDE &A, TPersonasLDE &B, TPersonasLDE &C);

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
    while (personasLDE) {
        TPersonasLDE actual = personasLDE;
        personasLDE = personasLDE->sig;
        if (actual->nodo) liberarTPersona(actual->nodo);
        delete actual;
    }
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
    for (;it->nodo && it->sig->nodo;it=it->sig);
  
    if (it->nodo) liberarTPersona(it->nodo);
    if (it->ant) it->ant->sig = it->sig;
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
        TPersonasLDE nuevo = auxEnlazar(persona, personas, personas->ant);
        personas = nuevo;
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
    // printf("Tipo de personas: %s\n", estadoPuntero(nodo));
    // printf("Tipo de sig: %s\n", estadoPuntero(sig));
    // printf("Tipo de ant: %s\n", estadoPuntero(ant));
    return nuevo;
}

TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant){
    TPersonasLDE nuevo = auxCrear(nodo, sig, ant);
    auxEnlazarABC(ant, nuevo, sig);
    return nuevo;
}

void auxEnlazarABC(TPersonasLDE &A, TPersonasLDE &B, TPersonasLDE &C) {
    //- Enlazar B con sus vecinos
    B->ant = A;
    B->sig = C;
    //- Enlazar A con B (si A existe)
    if (A != nullptr) A->sig = B;
    //- Enlazar C con B (si C existe)
    if (C != nullptr) C->ant = B;
}
