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
    TAgendaLS p = agenda;
    while (idTEvento(p->evento) != id){
        p=p->sig;
    }
    return p->evento;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    TAgendaLS p = agenda;
    TAgendaLS q;
    if(idTEvento(p->evento) == id){
        q = p;
        agenda=p->sig;
    }else{
        while (idTEvento(p->sig->evento) != id){
            p=p->sig;
        }
        q = p->sig;
        p->sig = p->sig->sig;
        
    }
    posponerTEvento(q->evento, n);
    agregarEnAgendaLS(agenda, q->evento);
    delete q;
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS p = agenda;
    if (hayEventosFechaLS(agenda, fecha)){
        while(p!=NULL){
            if (compararTFechas(fechaTEvento(p->evento), fecha) == 0){
                imprimirTEvento(p->evento);
            }
            p = p->sig;
        }
    }
    p=NULL;
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS p = agenda;
    while(p!=NULL && (compararTFechas(fechaTEvento(p->evento), fecha) != 0)){
            p=p->sig;
    }
    return p!=NULL;;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    TAgendaLS p = agenda;
    TAgendaLS q;
    if(idTEvento(p->evento) == id){
        q = p;
        agenda=p->sig;
    }else{
        while (idTEvento(p->sig->evento) != id){
            p=p->sig;
        }
        q = p->sig;
        p->sig = p->sig->sig;
    }
    liberarTEvento(q->evento);
    delete q;
}