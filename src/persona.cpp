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
    liberarAgendaLS(persona->agenda);
    delete persona;
    persona = NULL;
}

//Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona) {
    printf("Persona %d: %s, %d años\n", persona->id, persona->nombre, persona->edad);
    /*for(int i=0; i<MAX_NOMBRE; i++){
        printf("%c", persona->nombre[i]);
    }
    printf(", %d años", persona->edad);*/
    imprimirAgendaLS(persona->agenda);
}

nat idTPersona(TPersona persona) {
    return 0;
}

nat edadTPersona(TPersona persona) {
    return 0;
}

char* nombreTPersona(TPersona persona) {
    return NULL;
}

TAgendaLS agendaTPersona(TPersona persona) {
    return NULL;
}

void agregarEventoATPersona(TPersona &persona, TEvento evento) {

}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n) {

}

void removerEventoDeTPersona(TPersona &persona, int id) {

}

bool estaEnAgendaDeTPersona(TPersona persona, int id) {
    return false;
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id) {
    return NULL;
}

TPersona copiarTPersona(TPersona persona) {
    return NULL;
}
