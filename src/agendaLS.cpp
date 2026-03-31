#include "../include/agendaLS.h"

struct rep_agendaLS {
    TEvento evento;
    TAgendaLS sig;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS nuevo = NULL;
    return nuevo;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    TAgendaLS nuevo = new rep_agendaLS;
    nuevo->evento=evento;
    nuevo->sig = NULL;
    if (agenda == NULL){
        agenda = nuevo;
        nuevo = NULL;
    }else{
        TAgendaLS p = agenda;
        if(compararTFechas(fechaTEvento(p->evento), fechaTEvento(evento)) != -1 ){
            agenda = nuevo;
            nuevo->sig = p;
            p=NULL;
        }else{        
            while ((p->sig != NULL) && (compararTFechas(fechaTEvento(p->sig->evento), fechaTEvento(evento)) == -1)){
                p=p->sig;
            }
            if (p->sig == NULL){
                p->sig = nuevo;
            }
            else{
                TAgendaLS q = p->sig;
                p->sig = nuevo;
                nuevo->sig = q;
                p = NULL;
                q = NULL;
            }
        }
    }
    
}


void imprimirAgendaLS(TAgendaLS agenda) {
    TAgendaLS p = agenda;
    while (p!=NULL){
        imprimirTEvento(p->evento);
        p=p->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda) {
    TAgendaLS p = agenda;
    TAgendaLS q;
    while (p!=NULL){
        liberarTEvento(p->evento);
        q=p;
        p=p->sig;
        delete q;
        q=NULL;
    }
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return agenda == NULL;
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    TAgendaLS copia = crearAgendaLS();
    TAgendaLS p = agenda;
    while(p != NULL){
        agregarEnAgendaLS(copia, copiarTEvento(p->evento));
        p=p->sig;
    }
    p = NULL;
    return copia;
}


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    TAgendaLS p = agenda;
    while(p != NULL && idTEvento(p->evento) != id){
        p = p->sig;
    }
    return p != NULL;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    return NULL;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    return false;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    
}