#include "../include/personasLDE.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact);
TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);
TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);

struct rep_personasLDE {
    TPersona     nodo;
    TPersonasLDE sig;
    TPersonasLDE ant;
    TPersonasLDE inicio;
    TPersonasLDE fin;
};

///////////////////////////////////////////////////////////////////////////
/////////////  FUNCIONES PRINCIPALES  /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TPersonasLDE crearTPersonasLDE() {
    TPersonasLDE cabezal = new rep_personasLDE;
    cabezal->nodo   = nullptr;
    cabezal->sig    = nullptr;
    cabezal->ant    = nullptr;
    cabezal->inicio = nullptr;
    cabezal->fin    = nullptr;
    return cabezal;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos) {
    if (pos < 1) return;
    auxInsertar(personas, persona, pos, 1);
}

void liberarTPersonasLDE(TPersonasLDE &personas) {
    if (!personas) return;
    TPersonasLDE actual = personas->inicio;
    while (actual) {
        TPersonasLDE siguiente = actual->sig;
        liberarTPersona(actual->nodo);
        delete actual;
        actual = siguiente;
    }
    delete personas;
    personas = nullptr;
}

void imprimirTPersonasLDE(TPersonasLDE personas) {
    if (!personas) return;
    for (TPersonasLDE it = personas->inicio; it; it = it->sig)
        imprimirTPersona(it->nodo);
}

nat cantidadTPersonasLDE(TPersonasLDE personas) {
    if (!personas) return 0;
    nat c = 0;
    for (TPersonasLDE it = personas->inicio; it; it = it->sig) c++;
    return c;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas) {
    if (!personas || !personas->inicio) return;

    TPersonasLDE viejo = personas->inicio;
    personas->inicio   = viejo->sig;
    if (personas->inicio)
        personas->inicio->ant = nullptr;
    else
        personas->fin = nullptr;

    liberarTPersona(viejo->nodo);
    delete viejo;
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas) {
    if (!personas || !personas->fin) return;

    TPersonasLDE viejo = personas->fin;
    personas->fin      = viejo->ant;
    if (personas->fin)
        personas->fin->sig = nullptr;
    else
        personas->inicio = nullptr;

    liberarTPersona(viejo->nodo);
    delete viejo;
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id) {
    if (!personas) return false;
    for (TPersonasLDE it = personas->inicio; it; it = it->sig)
        if (idTPersona(it->nodo) == id) return true;
    return false;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id) {
    if (!personas) return nullptr;
    for (TPersonasLDE it = personas->inicio; it; it = it->sig)
        if (idTPersona(it->nodo) == id) return it->nodo;
    return nullptr;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2) {
    if (!personas1) return personas2;
    if (!personas2) return personas1;
    if (!personas2->inicio) {
        // personas2 vacía: no hay nada que concatenar
        delete personas2;
        return personas1;
    }
    if (!personas1->fin) {
        personas1->inicio = personas2->inicio;
        personas1->fin    = personas2->fin;
    } else {
        personas1->fin->sig = personas2->inicio;
        personas2->inicio->ant = personas1->fin;
        personas1->fin = personas2->fin;
    }
    delete personas2;
    return personas1;
}

///////////////////////////////////////////////////////////////////////////
/////////////  AUXILIARES  ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact) {
    // Avanzar hasta el nodo en posición pos (it será el desplazado)
    TPersonasLDE it = personas->inicio;
    for (nat i = 1; i < pos && it; i++, it = it->sig);

    TPersonasLDE ant   = it ? it->ant : personas->fin;
    TPersonasLDE nuevo = auxEnlazar(persona, it, ant);

    if (it == personas->inicio) personas->inicio = nuevo; // frente o lista vacía
    if (!it)                    personas->fin    = nuevo; // final
}

TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant) {
    TPersonasLDE nuevo = new rep_personasLDE;
    nuevo->nodo   = nodo;
    nuevo->sig    = sig;
    nuevo->ant    = ant;
    nuevo->inicio = nullptr;
    nuevo->fin    = nullptr;
    return nuevo;
}

TPersonasLDE auxEnlazar(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant) {
    TPersonasLDE nuevo = auxCrear(nodo, sig, ant);
    if (ant) ant->sig = nuevo;
    if (sig) sig->ant = nuevo;
    return nuevo;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona) {
    insertarTPersonasLDE(personas, persona, 1);
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona) {
    if (!personas) return;
    TPersonasLDE nuevo = auxCrear(persona, nullptr, personas->fin);
    if (personas->fin) personas->fin->sig = nuevo;
    else               personas->inicio   = nuevo;
    personas->fin = nuevo;
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas) {
    if (!personas || !personas->inicio) return nullptr;
    return personas->inicio->nodo;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas) {
    if (!personas || !personas->fin) return nullptr;
    return personas->fin->nodo;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100]){
    TPersonasLDE p=personas;
    while (nombreTPersona(p->nodo) != nombre) p=p->sig;
    TPersonasLDE d = p;
    if (d == p->inicio) p->inicio = p->inicio->sig;
    if (d == p->fin) p->fin = p->fin->ant;
    if (d->ant != NULL) d->ant->sig = d->sig;
    if (d->sig != NULL) d->sig->ant = d->ant;
    liberarTPersona(p->nodo);
    p=NULL;
    d=NULL;
}

bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    TPersonasLDE p = personas;
    while ((p!=NULL) && (nombreTPersona(p->nodo) != nombre)) p=p->sig;
    return p!=NULL;
}

TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    TPersonasLDE p = personas;
    while (nombreTPersona(p->nodo) != nombre) p=p->sig;
    return p->nodo;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

