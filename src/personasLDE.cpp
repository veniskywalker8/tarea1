#include "../include/personasLDE.h"

//+ AUXILIARES
void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact);
TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant);


struct rep_personasLDE {
    TPersona nodo;
    TPersonasLDE sig;
    TPersonasLDE ant;
};

TPersonasLDE crearTPersonasLDE(){
    return auxCrear(nullptr, nullptr, nullptr);
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
        liberarTPersona(actual->nodo);
        delete actual;
    }
    personasLDE = nullptr;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    while (personas != nullptr) {
        imprimirTPersona(personas->nodo);
        personas = personas->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    if (personas == nullptr) return 0;
    return 1 + cantidadTPersonasLDE(personas->sig);
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas == nullptr) return;

    TPersonasLDE viejo = personas;        /// Nodo a eliminar
    TPersonasLDE nuevoInicio = personas->sig; /// Segundo nodo

    liberarTPersona(viejo->nodo);         /// Liberar contenido
    delete viejo;                         /// Liberar nodo

    personas = nuevoInicio;               /// Actualizar cabeza
    if (personas != nullptr) {            /// Por si el nuevo es nulo
        personas->ant = nullptr;          /// Nuevo inicio no tiene anterior
    }
}


void eliminarFinalTPersonasLDE(TPersonasLDE &personas){

}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    return false;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    return NULL;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    return NULL;
}

//+ AUXILIARES
void auxInsertar(TPersonasLDE &personas, TPersona persona, nat pos, nat posact) {
    if (posact == pos) {
        //- Caso: insertar en la posición exacta (incluye inicio si pos==1)
        TPersonasLDE nuevo = auxCrear(
            persona, /// La persona a colocar
            personas, /// Como es el último, debe apuntar a null
            /// Si no existe, el anterior es nulo
            (personas ? personas->ant : nullptr)
        );


        /// [actual <-anterior- personas]
        if (personas->nodo != nullptr) {
            if (personas->ant != nullptr) {
                /// si hay existen los nodos A,B,C (b es el nuevo)
                /// c->a->sig = b
                personas->ant->sig = nuevo;
            }
            /// c->ant = b
            personas->ant = nuevo;
        }
        personas = nuevo;
    }else if (personas->sig == nullptr) {
        //- Caso: llegamos al final y pos es mayor al largo
        TPersonasLDE nuevo = auxCrear(
            persona,   /// La persona a colocar
            nullptr,   /// Como es el último, debe apuntar a null
            personas); /// El anterior debe ser toda la lista
        personas->sig = nuevo; /// El sig de toda la lista de ser el nuevo.
    }else {
        //- Caso general: avanzar en la lista
        auxInsertar(personas->sig, persona, pos, posact+1);
    }
}

TPersonasLDE auxCrear(TPersona nodo, TPersonasLDE sig, TPersonasLDE ant){
    TPersonasLDE nuevo = new rep_personasLDE;
    nuevo->nodo = nodo; 
    nuevo->sig = sig; 
    nuevo->ant = ant; 
    return nuevo;
}