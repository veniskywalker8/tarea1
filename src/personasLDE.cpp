#include "../include/personasLDE.h"

//+ AUXILIARES
void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact);
TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);
TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);
void auxListar(TPersonasLDE personas);

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
    // TPersonasLDE aux = personas;
    auxInsertar(personas, persona, pos, posact);
    // personas = aux;
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
    if (personas == nullptr) {
        // debuf("\nLista inexistente: []");
        return;
    }

    if (personas->nodo == nullptr) {
        // debuf("\nLista vacía: [(null, null, null)]");
        return;
    }

    // Avanzar hasta el último nodo con datos (antes del centinela)
    TPersonasLDE it = personas;
    while (it->sig && it->sig->nodo) {
        it = it->sig;
    }

    // debuf("\nEstado antes de eliminar:");
    // auxListar(personas);

    // debuf("\nLiberando persona: %s", nombreTPersona(it->nodo));
    liberarTPersona(it->nodo);

    if (it->ant) {
        it->ant->sig = it->sig; // enlaza con el centinela
        it->sig->ant = it->ant; // actualizar también el ant del centinela
    } else {
        // era el único nodo con datos, ahora la cabeza es el centinela
        personas = it->sig;
        if (personas) personas->ant = nullptr;
    }

    delete it;

    // // debuf("\nEstado después de eliminar:");
    // if (personas == nullptr) {
    //     // debuf("[]");
    // } else if (personas->nodo == nullptr) {
    //     // debuf("[(null, null, null)]");
    // } else {
    //     // auxListar(personas);
    // }
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
    // debuf("\n%sauxInsertar %sen %s%d/%d\n%s%s\n%sPRS: %s \n%sTIP:%s %s%s=%s%s\n%sSIG:%s %s"
    //     ,AZUL,NC, AMARILLO,posact, pos
    //     ,ROJO, nombreTPersona(persona), NC
    //     ,nombreTPersona(personas->nodo?personas->nodo:nullptr), NC
    //     ,AMARILLO, mostrarTipo(personas->nodo), NC
    //     ,MAGENTA, estadoPuntero(personas->nodo), NC
    //     ,VERDE, estadoPuntero(personas->sig)
    // );
    if (posact == pos or !personas->nodo) {
        TPersonasLDE nuevo = auxEnlazar(persona, personas, personas->ant);
        personas = nuevo;
        // debuf("\n%sPOS:%s %d/%d"
        //     "\n%sPERSONA:%s %s"
        //     "\n%sLISTA nodo:%s %s"
        //     "\n%sNUEVO nodo:%s %s"
        //     "\n%sNUEVO sig:%s %s"
        //     "\n%sNUEVO ant:%s %s",
        //     MAGENTA, NC, posact, pos,
        //     ROJO, NC, nombreTPersona(persona),
        //     AMARILLO, NC, nombreTPersona(personas->nodo),
        //     AZUL, NC, nombreTPersona(nuevo->nodo),
        //     CIAN, NC, estadoPuntero(nuevo->sig ? nuevo->sig->nodo : nullptr),
        //     VERDE, NC, estadoPuntero(nuevo->ant ? nuevo->ant->nodo : nullptr)
        // );
    }
    else {
        auxInsertar(personas->sig, persona, pos, posact + 1);
    }
}

TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant){
    TPersonasLDE nuevo = new rep_personasLDE;
    nuevo->nodo = nodo;
    nuevo->ant = ant;
    nuevo->sig = sig;
    return nuevo;
}

TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant){
    TPersonasLDE nuevo = auxCrear(nodo, sig, ant);
    //- Enlazar A con nuevo (si A existe)
    if (ant != nullptr) ant->sig = nuevo;
    //- Enlazar C con nuevo (si C existe)
    if (sig != nullptr) sig->ant = nuevo;
    return nuevo;
}

void auxEnlazrABC(TPersonasLDE &A, TPersonasLDE &B, TPersonasLDE &C);

void auxListar(TPersonasLDE personas){
    for (TPersonasLDE aux = personas; aux != nullptr; aux = aux->sig) {
        debuf("%s(%s, %s, %s)", CIAN,
            nombreTPersona(aux->nodo),
            nombreTPersona(aux->sig ? aux->sig->nodo : nullptr),
            nombreTPersona(aux->ant ? aux->ant->nodo : nullptr)
        );
    }
}

