#include "../include/persona.h"

struct rep_persona {
    nat id;
    nat edad;
    char nombre[MAX_NOMBRE];
    TAgendaLS agenda;
};

TPersona crearTPersona(nat id, nat edad, const char nombre[MAX_NOMBRE], TAgendaLS agenda) {
    TPersona nuevo = new rep_persona;
    nuevo->id = id;
    nuevo->edad = edad;
    for (int i=0; i<MAX_NOMBRE; i++){
        nuevo->nombre[i]=nombre[i];
    } 
    nuevo->agenda=copiarAgendaLS(agenda);
    liberarAgendaLS(agenda);
    return nuevo;
}

void liberarTPersona(TPersona &persona) {
    if (persona == nullptr) return;
    
    liberarAgendaLS(persona->agenda);
    delete persona;
    persona = nullptr;
}

//Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona) {
    if (persona == nullptr) return;
    printf("Persona %d: %s, %d años\n", persona->id, persona->nombre, persona->edad);

    imprimirAgendaLS(persona->agenda);
}

nat idTPersona(TPersona persona) {
    return persona->id;
}

nat edadTPersona(TPersona persona) {
    return persona->edad;
}

char* nombreTPersona(TPersona persona) {
    if (!persona) {
        static char retorno[] = "NULL"; // buffer modificable
        return retorno;
    }
    return persona->nombre;
}

TAgendaLS agendaTPersona(TPersona persona) {
    return persona->agenda;
}

void agregarEventoATPersona(TPersona &persona, TEvento evento) {
    agregarEnAgendaLS(persona->agenda, evento);
}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n) {
    posponerEnAgendaLS(persona->agenda, id, n);
}

void removerEventoDeTPersona(TPersona &persona, int id) {
    removerDeAgendaLS(persona->agenda, id);
}

bool estaEnAgendaDeTPersona(TPersona persona, int id) {
    return estaEnAgendaLS(persona->agenda, id);
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id) {
    return obtenerDeAgendaLS(persona->agenda, id);
}

TPersona copiarTPersona(TPersona persona) {
    TPersona nuevo = new rep_persona;
    nuevo->id = persona->id;
    nuevo->edad = persona->edad;
    for (int i=0; i<MAX_NOMBRE; i++){
        nuevo->nombre[i]=persona->nombre[i];
    }
    nuevo->agenda = copiarAgendaLS(persona->agenda);
    return nuevo;
}
