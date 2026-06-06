#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_agendaLS {
    TEvento evento;
    TAgendaLS sig;
};

// Crear agenda vacía
TAgendaLS crearAgendaLS() {
    return nullptr;
}

// Insertar evento en orden por fecha
void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    TAgendaLS nuevo = new rep_agendaLS{evento, nullptr};

    // Caso: lista vacía o insertar al inicio
    if (agenda == nullptr || compararTFechas(fechaTEvento(agenda->evento), fechaTEvento(evento)) != -1) {
        nuevo->sig = agenda;
        agenda = nuevo;
        return;
    }

    // Caso general: buscar posición
    TAgendaLS actual = agenda;
    while (actual->sig != nullptr &&
           compararTFechas(fechaTEvento(actual->sig->evento), fechaTEvento(evento)) == -1) {
        actual = actual->sig;
    }
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
}

// Imprimir todos los eventos
void imprimirAgendaLS(TAgendaLS agenda) {
    for (TAgendaLS actual = agenda; actual != nullptr; actual = actual->sig) {
        imprimirTEvento(actual->evento);
    }
}

// Liberar toda la agenda
void liberarAgendaLS(TAgendaLS &agenda) {
    while (agenda != nullptr) {
        TAgendaLS actual = agenda;
        agenda = agenda->sig;
        liberarTEvento(actual->evento);
        delete actual;
    }
}

// Verificar si está vacía
bool esVaciaAgendaLS(TAgendaLS agenda) {
    return agenda == nullptr;
}

// Copiar agenda completa
TAgendaLS copiarAgendaLS(TAgendaLS agenda) {
    TAgendaLS copia = crearAgendaLS();
    for (TAgendaLS actual = agenda; actual != nullptr; actual = actual->sig) {
        agregarEnAgendaLS(copia, copiarTEvento(actual->evento));
    }
    return copia;
}

// Verificar si un evento está en la agenda
bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    for (TAgendaLS actual = agenda; actual != nullptr; actual = actual->sig) {
        if (idTEvento(actual->evento) == id) return true;
    }
    return false;
}

// Obtener un evento por id (precondición: existe)
TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    while (agenda != nullptr && idTEvento(agenda->evento) != id) {
        agenda = agenda->sig;
    }
    return agenda->evento;
}

// Posponer un evento y reinsertarlo
void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    if (agenda == nullptr) return;

    TAgendaLS actual = agenda;
    TAgendaLS extraido = nullptr;

    // Caso: el primero es el que buscamos
    if (idTEvento(actual->evento) == id) {
        extraido = actual;
        agenda = actual->sig;
    } else {
        while (actual->sig != nullptr && idTEvento(actual->sig->evento) != id) {
            actual = actual->sig;
        }
        extraido = actual->sig;
        actual->sig = extraido->sig;
    }

    posponerTEvento(extraido->evento, n);
    agregarEnAgendaLS(agenda, extraido->evento);
    delete extraido;
}

// Imprimir eventos de una fecha
void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    for (TAgendaLS actual = agenda; actual != nullptr; actual = actual->sig) {
        if (compararTFechas(fechaTEvento(actual->evento), fecha) == 0) {
            imprimirTEvento(actual->evento);
        }
    }
}

// Verificar si hay eventos en una fecha
bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    for (TAgendaLS actual = agenda; actual != nullptr; actual = actual->sig) {
        if (compararTFechas(fechaTEvento(actual->evento), fecha) == 0) return true;
    }
    return false;
}

// Remover un evento por id
void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    if (agenda == nullptr) return;

    TAgendaLS actual = agenda;
    TAgendaLS extraido = nullptr;

    if (idTEvento(actual->evento) == id) {
        extraido = actual;
        agenda = actual->sig;
    } else {
        while (actual->sig != nullptr && idTEvento(actual->sig->evento) != id) {
            actual = actual->sig;
        }
        extraido = actual->sig;
        actual->sig = extraido->sig;
    }

    liberarTEvento(extraido->evento);
    delete extraido;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////