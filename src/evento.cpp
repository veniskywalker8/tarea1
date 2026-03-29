#include "../include/evento.h"

struct rep_evento {
    /************ Parte 4.1 ************/
    /*Escriba el código a continuación */
    int id;
    TFecha fecha;
    char descripcion[MAX_DESCRIPCION];
    /****** Fin de parte Parte 4.1 *****/
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;
    /************ Parte 4.2 ************/
    /*Escriba el código a continuación */
    //- Pedir memoria
    nuevoEvento = new rep_evento;
    //- Copiar la cadena de forma segura
    strncpy(nuevoEvento->descripcion, descripcion, MAX_DESCRIPCION - 1);
    nuevoEvento->descripcion[MAX_DESCRIPCION - 1] = '\0'; // asegurar terminación
    //- asignar fecha e id
    nuevoEvento->fecha = fecha;
    nuevoEvento->id = id;
    /****** Fin de parte Parte 4.2 *****/
    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
    if (evento == nullptr) return;
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    printf("Evento %d: %s\nFecha: ", evento->id, evento->descripcion);
    imprimirTFecha(evento->fecha);
    /****** Fin de parte Parte 4.3 *****/
}

void liberarTEvento(TEvento &evento) {
    if (evento == nullptr) return;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    liberarTFecha(evento->fecha);
    delete evento;
    evento = nullptr;
    /****** Fin de parte Parte 4.4 *****/
}

int idTEvento(TEvento evento) {
    if (evento == nullptr) return -1;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    int res = evento->id;
    /****** Fin de parte Parte 4.4 *****/
    return res;
}

TFecha fechaTEvento(TEvento evento) {
    if (evento == nullptr) return nullptr;
    TFecha fecha = NULL;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    fecha = evento->fecha;
    /****** Fin de parte Parte 4.4 *****/
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    if (evento == nullptr) return;
    /************ Parte 4.5 ************/
    /*Escriba el código a continuación */
    aumentarTFecha(evento->fecha, dias);
    /****** Fin de parte Parte 4.5 *****/
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento) {
    return NULL;
}
