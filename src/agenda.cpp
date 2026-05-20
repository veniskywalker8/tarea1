#include "../include/agenda.h"
//+AUXILIAR
TEvento remover_de_lista(TAgenda &agenda, int id);

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
    agenda = nullptr;
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
    TEvento res = nullptr;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    nat i;
    nat tope =agenda->tope;
    for (i = 0; i < tope 
        && idTEvento(agenda->eventos[i]) != id; i++);
    res = (i< tope) ? agenda->eventos[i] : nullptr;
    /****** Fin de parte Parte 5.5 *****/
    return res;
}

void posponerEnAgenda(TAgenda &agenda, int id, nat n) {
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    if (agenda == NULL) return;
    //- Encuentra el evento
    TEvento evento = obtenerDeAgenda(agenda, id);
    //- Compuerta de control
    if (evento == NULL) return;
    //- Remover
    remover_de_lista(agenda, id);
    //- Sumar n
    posponerTEvento(evento, n);/// usa la función del módulo evento
    //- Agregar evento+n
    agregarEnAgenda(agenda, evento);
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
    if (fecha == nullptr) return false;
    bool res = false;
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    int izq = 0, der = agenda->tope - 1, mid;
    do {
        mid = (izq + der) / 2;
        TFecha mid_fecha = fechaTEvento(agenda->eventos[mid]);
        int cmp = compararTFechas(mid_fecha,fecha);
        if (cmp == 0) {
            res = true;
        } else if (cmp < 0) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }while (izq <= der && !res);
    /****** Fin de parte Parte 5.7 *****/
    return res;
}

void removerDeAgenda(TAgenda &agenda, int id) {
    /************ Parte 5.8 ************/
    /*Escriba el código a continuación */
    //- Remover sin eliminar de memoria
    TEvento evento = remover_de_lista(agenda, id);
    //- Eliminar de memoria
    liberarTEvento(evento);
    /****** Fin de parte Parte 5.8 *****/
}
//+AUXILIAR
TEvento remover_de_lista(TAgenda &agenda, int id){
    nat tope = agenda->tope;
    nat pos = 0;
    //- Buscar la posición del evento
    for (pos = 0; pos < tope &&
         idTEvento(agenda->eventos[pos]) != id; pos++);

    //- Si lo encontró
    if (pos > tope-1) return nullptr;
    //- Guardar return
    TEvento retorno = agenda->eventos[pos];
    //- Corrimiento de los elementos siguientes
    tope--; /// Ajustar el tope
    for (nat p=pos; p < tope; p++) {
        agenda->eventos[p] = agenda->eventos[p + 1];
    }
    //- Ajustar el tope
    agenda->tope--;
    return retorno;
}