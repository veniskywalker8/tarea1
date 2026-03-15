#include "../include/agenda.h"

struct rep_agenda {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TEvento eventos [MAX_EVENTOS];
    nat tope;
    /****** Fin de parte Parte 5.1 *****/
};

TAgenda crearTAgenda() {
    TAgenda nuevaAgenda = new rep_agenda;
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    nuevaAgenda->tope = 0;
    /****** Fin de parte Parte 5.2 *****/
    return nuevaAgenda;
}

void agregarEnAgenda(TAgenda &agenda, TEvento evento) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    
    //- Insertar ordenado por fecha
    int i = agenda->tope;
    //? ¿Hay espacio?
    if (i == MAX_EVENTOS) return;
    //-Buscar ubicación
    for (i= i; 
        i > 0 && compararTFechas(
            fechaTEvento(evento)
            , fechaTEvento(agenda->eventos[i-1])) < 1;
        i--) 
    {agenda->eventos[i] = agenda->eventos[i-1];}

    //- Asignar nueva ubicación
    agenda->eventos[i] = evento;
    agenda->tope++;
    /****** Fin de parte Parte 5.2 *****/
}

void liberarTAgenda(TAgenda &agenda) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++) 
    {liberarTEvento(agenda->eventos[i]);}
    
    delete agenda;
    agenda = NULL;
    /****** Fin de parte Parte 5.2 *****/
}

void imprimirTAgenda(TAgenda agenda) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++) {
        imprimirTEvento(agenda->eventos[i]);
    }
    /****** Fin de parte Parte 5.2 *****/
}

bool estaEnAgenda(TAgenda agenda, int id) {
    bool res = false;
    /************ Parte 5.4 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope && !res; i++) {
        if (idTEvento(agenda->eventos[i]) == id) {
            res = true;
        }
    }
    /****** Fin de parte Parte 5.4 *****/
    return res;
}

TEvento obtenerDeAgenda(TAgenda agenda, int id) {
    TEvento res = NULL;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope && res == NULL; i++) {
        if (idTEvento(agenda->eventos[i]) == id) {
            res = agenda->eventos[i];
        }
    }
    /****** Fin de parte Parte 5.5 *****/
    return res;
}

void posponerEnAgenda(TAgenda &agenda, int id, nat n) {
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    
    /****** Fin de parte Parte 5.5 *****/
}

void imprimirEventosFecha(TAgenda agenda, TFecha fecha) {
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++) {
        if (compararTFechas(fechaTEvento(agenda->eventos[i]), fecha) == 0) {
            imprimirTEvento(agenda->eventos[i]);
        }
    }
    /****** Fin de parte Parte 5.7 *****/
}

bool hayEventosFecha(TAgenda agenda, TFecha fecha) {
    bool res = false;
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    int izq = 0, der = agenda->tope - 1;
    while (izq <= der && !res) {
        int mid = (izq + der) / 2;
        int cmp = compararTFechas(fechaTEvento(agenda->eventos[mid]), fecha);
        if (cmp == 0) {
            res = true;
        } else if (cmp < 0) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }
    /****** Fin de parte Parte 5.7 *****/
    return res;
}

void removerDeAgenda(TAgenda &agenda, int id) {
    /************ Parte 5.8 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++) {
        if (idTEvento(agenda->eventos[i]) == id) {
            liberarTEvento(agenda->eventos[i]);
            for (nat j = i; j < agenda->tope-1; j++) {
                agenda->eventos[j] = agenda->eventos[j+1];
            }
            agenda->tope--;
            break;
        }
    }
    /****** Fin de parte Parte 5.8 *****/
}