/*
  Módulo principal de la Tarea 2.

Intérprete de comandos para probar los módulos implementados.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

El comando 'Fin' termina el programa

El comando '# comentario' imprime comentario.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#define cmd_es(nom_comando, cmd) (0 == strcmp(nom_comando, cmd))

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/agendaLS.h"
#include "include/personasABB.h"


#define MAX_PALABRA 32
#define MAX_LINEA 256

// Lee una fecha de la entrada en formato "dd/mm/aaaa" y la escribe la variable fecha
void leerFecha(TFecha &fecha);

/* La implementación de las funciones de testeo se realiza al final del archivo*/
// Funciones para testear fecha
void main_crearFecha(TFecha &fecha); 
void main_liberarFecha(TFecha &fecha);
void main_imprimirFecha(TFecha fecha);
void main_aumentarDias(TFecha &fecha);
void main_compararFechas(); 
void main_copiarFecha(TFecha fecha);
// Funciones para testear evento
void main_crearEvento(TEvento &evento, TFecha &fecha);
void main_liberarEvento(TEvento &evento);
void main_imprimirIdEvento(TEvento evento);
void main_imprimirFechaEvento(TEvento evento);
void main_imprimirEvento(TEvento evento);
void main_posponerEvento(TEvento &evento);
void main_copiarEvento(TEvento evento);
// Funciones para testear agenda
void main_crearAgenda(TAgendaLS &agenda);
void main_agregarEnAgenda(TAgendaLS &agenda, TEvento &evento);
void main_liberarAgenda(TAgendaLS &agenda);
void main_imprimirAgenda(TAgendaLS agenda);
void main_estaEnAgenda(TAgendaLS agenda);
void main_removerDeAgenda(TAgendaLS &agenda);
void main_posponerEnAgenda(TAgendaLS &agenda);
void main_hayEventosFechaAgenda(TAgendaLS agenda);
void main_imprimirEventosFechaAgenda(TAgendaLS agenda);
void main_imprimirCopiaAgenda(TAgendaLS agenda);
// Funciones para testear persona
void main_crearPersona(TPersona &persona, TAgendaLS &agenda);
void main_imprimirIdPersona(TPersona persona);
void main_imprimirEdadPersona(TPersona persona);
void main_imprimirNombrePersona(TPersona persona);
void main_imprimirAgendaPersona(TPersona persona);
void main_imprimirPersona(TPersona persona);
void main_liberarPersona(TPersona &persona);
void main_agregarEventoPersona(TPersona &persona, TEvento &evento);
void main_removerEventoPersona(TPersona &persona);
void main_estaEnAgendaPersona(TPersona persona);
void main_posponerEventoPersona(TPersona &persona);
void main_imprimirEventosFechaPersona(TPersona persona);
void main_imprimirEventoPersona(TPersona persona);
void main_imprimirCopiaPersona(TPersona persona);
//Funciones para testear personasLDE
void main_crearListaPersonas(TPersonasLDE &listaPersonas);
void main_liberarListaPersonas(TPersonasLDE &listaPersonas);
void main_imprimirListaPersonas(TPersonasLDE &listaPersonas);
void main_insertarPersonaListaPersonas(TPersonasLDE &listaPersonas, TPersona &persona);
void main_imprimirPersonaListaPersonas(TPersonasLDE &listaPersonas);
void main_eliminarInicioListaPersonas(TPersonasLDE &listaPersonas);
void main_eliminarFinalListaPersonas(TPersonasLDE &listaPersonas);
void main_imprimirCantidadListaPersonas(TPersonasLDE &listaPersonas);
void main_estaEnListaPersonas(TPersonasLDE &listaPersonas);
void main_concatenarConVacioListaPersonas(TPersonasLDE &listaPersonas);
void main_crearYConcatenarListaPersonas(TPersonasLDE &listaPersonas);
void main_concatenarListaPersonasTiempo(TPersonasLDE &listaPersonas);
//Funciones para testear personasABB
void main_crearArbolPersonas(TPersonasABB &arbolPersonas);
void main_esVacioArbolPersonas(TPersonasABB arbolPersonas);
void main_liberarArbolPersonas(TPersonasABB &arbolPersonas);
void main_insertarArbolPersonas(TPersonasABB &arbolPersonas, TPersona &persona);
void main_estaEnArbolPersonas(TPersonasABB arbolPersonas);
void main_removerArbolPersonas(TPersonasABB &arbolPersonas);
void main_imprimirArbolPersonas(TPersonasABB arbolPersonas);
void main_imprimirCantidadArbolPersonas(TPersonasABB arbolPersonas);
void main_imprimirPersonaArbolPersonas(TPersonasABB arbolPersonas);
void main_alturaArbolPersonas(TPersonasABB arbolPersonas);
void main_esPerfectoArbolPersonas(TPersonasABB arbolPersonas);
void main_maxIdPersonaArbolPersonas(TPersonasABB arbolPersonas);
void main_mayoresEdadArbolPersonas(TPersonasABB arbolPersonas);
void main_aplanarArbolPersonas(TPersonasABB &arbolPersonas);
void main_esPerfectoArbolPersonasTiempo(TPersonasABB &arbolPersonas);
void main_esPerfectoArbolPersonasTiempo2(TPersonasABB &arbolPersonas);
void main_mayoresEdadArbolPersonasTiempo(TPersonasABB &arbolPersonas);

// programa principal que lee comandos de la entrada estándar e invoca a la función de test correspondiente
int main() {
    TFecha fecha = NULL;
    TEvento evento = NULL;
    TAgendaLS agenda = NULL;
    TPersona persona = NULL;
    TPersonasLDE listaPersonas = NULL;
    TPersonasABB arbolPersonas = NULL;

    char restoLinea[MAX_LINEA + 1];
    char cmd[MAX_PALABRA];

    int cont_comandos = 0;
    bool seguir = true;
    while (seguir) {
        // mostrar el prompt
        cont_comandos++;
        printf("%u>", cont_comandos);

        // leer el comando en la variable cmd
        leerChars(cmd);

        // procesar el comando
        if (cmd_es("Fin", cmd)) {  // Termina el programa
            seguir = false;
            printf("Fin.\n");

        } else if (cmd_es("#", cmd)) {  // Imprime el comentario luego del #
            leerRestoLinea(restoLinea);
            printf("# %s.\n", restoLinea);

            ///////////////////////////////////
            /* Funciones para testear fecha */
            ///////////////////////////////////

        } else if (cmd_es("crearFecha", cmd)) {  // Crea una fecha y la almacena en la variable fecha
            main_crearFecha(fecha);

        } else if (cmd_es("imprimirFecha", cmd)) {  // Imprime la fecha almacenada en la variable fecha
            main_imprimirFecha(fecha);

        } else if (cmd_es("liberarFecha", cmd)) {  // Libera la memoria de la variable fecha
            main_liberarFecha(fecha);

        } else if (cmd_es("aumentarDias", cmd)) {  // Aumenta la fecha almacenada en la variable fecha en la cantidad de días indicada
            main_aumentarDias(fecha);

        } else if (cmd_es("compararFechas", cmd)) {  // Compara dos fechas leidas de la entrada
            main_compararFechas();

        } else if (cmd_es("copiarFecha", cmd)) {  // Copia la fecha almacenada en la variable fecha en otra variable fecha
            main_copiarFecha(fecha);

        }

            ///////////////////////////////////
            /* Funciones para testear evento */
            ///////////////////////////////////

          else if (cmd_es("crearEvento", cmd)) {  // Crea un evento y lo almacena en la variable evento
            main_crearEvento(evento, fecha);

        } else if (cmd_es("imprimirIdEvento", cmd)) {  // Imprime el id del evento almacenado en la variable evento
            main_imprimirIdEvento(evento);

        } else if (cmd_es("imprimirFechaEvento", cmd)) {  // Imprime la fecha del evento almacenado en la variable evento
            main_imprimirFechaEvento(evento);

        } else if (cmd_es("imprimirEvento", cmd)) {  // Imprime toda la infromación del evento almacenado en la variable evento
            main_imprimirEvento(evento);

        } else if (cmd_es("liberarEvento", cmd)) {  // Libera la memoria del evento almacenado en la variable evento
            main_liberarEvento(evento);

        } else if (cmd_es("posponerEvento", cmd)) {  // Pospone el evento almacenado en la variable evento una cantidad de días indicada
            main_posponerEvento(evento);

        } else if (cmd_es("copiarEvento", cmd)) {  // Copia el evento almacenado en la variable evento en otra variable evento
            main_copiarEvento(evento);

        }

            ///////////////////////////////////
            /* Funciones para testear agenda */
            ///////////////////////////////////

          else if (cmd_es("crearAgenda", cmd)) {  // Crea una agenda y la almacena en la variable agenda
            main_crearAgenda(agenda);

        } else if (cmd_es("agregarEnAgenda", cmd)) {  // Agrega el evento almacenado en la variable evento a la agenda almacenada en la variable agenda
            main_agregarEnAgenda(agenda, evento);

        } else if (cmd_es("imprimirAgenda", cmd)) {  // Imprime toda la información de la agenda almacenada en la variable agenda
            main_imprimirAgenda(agenda);

        } else if (cmd_es("liberarAgenda", cmd)) {  // Libera la memoria de la agenda almacenada en la variable agenda
            main_liberarAgenda(agenda);

        } else if (cmd_es("estaEnAgenda", cmd)) {  // Indica si el evento almacenado en la variable evento está en la agenda almacenada en la variable agenda
            main_estaEnAgenda(agenda);

        } else if (cmd_es("posponerEnAgenda", cmd)) {  // Pospone el evento almacenado en la variable evento una cantidad de días indicada en la agenda almacenada en la variable agenda
            main_posponerEnAgenda(agenda);

        } else if (cmd_es("removerDeAgenda", cmd)) {  // Remueve el evento almacenado en la variable evento de la agenda almacenada en la variable agenda
            main_removerDeAgenda(agenda);

        } else if (cmd_es("hayEventosFechaAgenda", cmd)) {  // Indica si hay eventos en la agenda en una fecha indicada
            main_hayEventosFechaAgenda(agenda);

        } else if (cmd_es("imprimirEventosFechaAgenda", cmd)) {  // Imprime todos los eventos de la agenda con fecha igual a la indicada
            main_imprimirEventosFechaAgenda(agenda);

        } else if (cmd_es("imprimirCopiaAgenda", cmd)) {  // Imprime una copia de la agenda almacenada en la variable agenda"))
            main_imprimirCopiaAgenda(agenda);
        }

            ///////////////////////////////////
            /* Funciones para testear persona */
            ///////////////////////////////////

        else if (cmd_es("crearPersona", cmd)) {  
            main_crearPersona(persona, agenda);
        
        } else if (cmd_es("liberarPersona", cmd)){ // Libera la memoria de la persona almacenado en la variable persona
            main_liberarPersona(persona);

        }else if (cmd_es("imprimirIdPersona", cmd)) {  // Imprime el id de la persona almacenado en la variable persona
            main_imprimirIdPersona(persona);

        } else if (cmd_es("imprimirEdadPersona", cmd)) {  // Imprime la edad de la persona almacenado en la variable persona
            main_imprimirEdadPersona(persona);
                
        } else if (cmd_es("imprimirNombrePersona", cmd)) {  // Imprime el nombre de la persona almacenado en la variable persona
            main_imprimirNombrePersona(persona);

        } else if (cmd_es("imprimirAgendaPersona", cmd)) {  // Imprime la agenda de la persona almacenado en la variable persona
            main_imprimirAgendaPersona(persona);

        } else if (cmd_es("imprimirPersona", cmd)) {  // Imprime todos los datos de la persona almacenado en la variable persona
            main_imprimirPersona(persona);

        } else if (cmd_es("agregarEventoPersona", cmd)){ // Agrega el evento almacenado en la variable evento a la agenda de la persona almacenado en la variable persona
            main_agregarEventoPersona(persona, evento);

        } else if (cmd_es("posponerEventoPersona", cmd)){ // Pospone el evento con Id pasado por parametro una cantidad de días indicada en la agenda de la persona almacenado en la variable persona
            main_posponerEventoPersona(persona);

        } else if (cmd_es("removerEventoPersona", cmd)){ // Remueve el evento con Id pasado por parametro de la agenda de la persona almacenado en la variable persona
            main_removerEventoPersona(persona);

        } else if (cmd_es("estaEnAgendaPersona", cmd)){
            main_estaEnAgendaPersona(persona);

        } else if (cmd_es("imprimirEventoPersona", cmd)){ // Imprime el evento con Id pasado por parametro de la agenda de la persona almacenado en la variable persona
            main_imprimirEventoPersona(persona);

        } else if (cmd_es("imprimirCopiaPersona", cmd)){ // Imprime una copia de la persona almacenado en la variable persona
            main_imprimirCopiaPersona(persona);

        }

            ///////////////////////////////////
            /* Funciones para testear lista de personas */
            ///////////////////////////////////

        else if (cmd_es("crearListaPersonas", cmd)) {  // Crea una lista de personas y la almacena en la variable listaPersonas
            main_crearListaPersonas(listaPersonas);

        } else if (cmd_es("liberarListaPersonas", cmd)) {  // Libera la memoria de la lista de personas almacenada en la variable listaPersonas
            main_liberarListaPersonas(listaPersonas);

        } else if (cmd_es("imprimirListaPersonas", cmd)) {  // Imprime toda la información de la lista de personas almacenada en la variable listaPersonas
            main_imprimirListaPersonas(listaPersonas);

        } else if (cmd_es("insertarPersonaListaPersonas", cmd)) {  // Agrega la persona almacenada en la variable persona a la lista de personas almacenada en la variable listaPersonas
            main_insertarPersonaListaPersonas(listaPersonas, persona);

        } else if (cmd_es("imprimirPersonaListaPersonas", cmd)) {  // Imprime la persona con Id pasado por parametro de la lista de personas almacenada en la variable listaPersonas
            main_imprimirPersonaListaPersonas(listaPersonas);

        } else if (cmd_es("imprimirCantidadListaPersonas", cmd)) {
            main_imprimirCantidadListaPersonas(listaPersonas);

        } else if (cmd_es("eliminarInicioListaPersonas", cmd)) {
            main_eliminarInicioListaPersonas(listaPersonas);

        } else if (cmd_es("eliminarFinalListaPersonas", cmd)) {
            main_eliminarFinalListaPersonas(listaPersonas);

        } else if (cmd_es("estaEnListaPersonas", cmd)) {
            main_estaEnListaPersonas(listaPersonas);
            
        } else if (cmd_es("concatenarConVacioListaPersonas", cmd)) {
            main_concatenarConVacioListaPersonas(listaPersonas);
            
        } else if (cmd_es("crearYConcatenarListaPersonas", cmd)) {
            main_crearYConcatenarListaPersonas(listaPersonas);
            
        } else if (cmd_es("concatenarListaPersonasTiempo", cmd)) {
            main_concatenarListaPersonasTiempo(listaPersonas);
            
        }

            ///////////////////////////////////
            /* Funciones para testear arbol de personas */
            ///////////////////////////////////

        else if (cmd_es("crearArbolPersonas", cmd)) {
            main_crearArbolPersonas(arbolPersonas);

        } else if (cmd_es("esVacioArobolPersonas", cmd)) {
            main_esVacioArbolPersonas(arbolPersonas);

        } else if (cmd_es("liberarArbolPersonas", cmd)) {
            main_liberarArbolPersonas(arbolPersonas);

        } else if (cmd_es("insertarPersonaArbolPersonas", cmd)) {
            main_insertarArbolPersonas(arbolPersonas, persona);

        } else if (cmd_es("imprimirCantidadArbolPersonas", cmd)) {
            main_imprimirCantidadArbolPersonas(arbolPersonas);

        } else if (cmd_es("imprimirArbolPersonas", cmd)) {
            main_imprimirArbolPersonas(arbolPersonas);

        } else if (cmd_es("estaEnArbolPersonas", cmd)) {
            main_estaEnArbolPersonas(arbolPersonas);

        } else if (cmd_es("removerArbolPersonas", cmd)) {
            main_removerArbolPersonas(arbolPersonas);

        } else if (cmd_es("imprimirPersonaArbolPersonas", cmd)) {
            main_imprimirPersonaArbolPersonas(arbolPersonas);

        } else if (cmd_es("alturaArbolPersonas", cmd)) {
            main_alturaArbolPersonas(arbolPersonas);

        } else if (cmd_es("esPerfectoArbolPersonas", cmd)) {
            main_esPerfectoArbolPersonas(arbolPersonas);

        } else if (cmd_es("maxIdPersonaArbolPersonas", cmd)) {
            main_maxIdPersonaArbolPersonas(arbolPersonas);

        } else if (cmd_es("mayoresEdadArbolPersonas", cmd)) {
            main_mayoresEdadArbolPersonas(arbolPersonas);

        } else if (cmd_es("aplanarArbolPersonas", cmd)) {
            main_aplanarArbolPersonas(arbolPersonas);

        } else if (cmd_es("esPerfectoArbolPersonasTiempo", cmd)) {
            main_esPerfectoArbolPersonasTiempo(arbolPersonas);

        } else if (cmd_es("esPerfectoArbolPersonasTiempo2", cmd)) {
            main_esPerfectoArbolPersonasTiempo2(arbolPersonas);

        } else if (cmd_es("mayoresEdadArbolPersonasTiempo", cmd)) {
            main_mayoresEdadArbolPersonasTiempo(arbolPersonas);

        } else {
            printf("Comando no reconocido.\n");  // Comando no reconocido

        }  // if
        fgets(restoLinea, MAX_LINEA + 1, stdin);
    }  // while

    return 0;
}  // main

///////////////////////////////
/* Funciones main para Fecha */
///////////////////////////////

void leerFecha(TFecha &fecha) {
    nat *componentes = new nat[3];
    scanf("%u/%u/%u", &componentes[0], &componentes[1], &componentes[2]);
    fecha = crearTFecha(componentes[0], componentes[1], componentes[2]);
    delete[] componentes;
}

void main_crearFecha(TFecha &fecha) {
    assert(fecha == NULL);
    leerFecha(fecha);
}

void main_liberarFecha(TFecha &fecha) {
    assert(fecha != NULL);
    liberarTFecha(fecha);
}

void main_imprimirFecha(TFecha fecha) {
    assert(fecha != NULL);
    imprimirTFecha(fecha);
}

void main_aumentarDias(TFecha &fecha) {
    assert(fecha != NULL);
    nat cantDias = leerNat();
    aumentarTFecha(fecha, cantDias);
    printf("La nueva fecha aplazada %d dias es: ", cantDias);
    imprimirTFecha(fecha);
}

void main_compararFechas() {
    TFecha fecha1 = NULL, fecha2 = NULL;
    leerFecha(fecha1);
    leerFecha(fecha2);
    int comp = compararTFechas(fecha1, fecha2);
    if (comp == 0) {
        printf("Las fechas son iguales. \n");
    } else if (comp == 1) {
        printf("La primera fecha es posterior a la segunda. \n");
    } else
        printf("La primera fecha es anterior a la segunda. \n");
    liberarTFecha(fecha1);
    liberarTFecha(fecha2);
}

void main_copiarFecha(TFecha fecha) {
    assert(fecha != NULL);
    TFecha fechaCopia = copiarTFecha(fecha);
    printf("La fecha copiada es: ");
    imprimirTFecha(fechaCopia);
    liberarTFecha(fechaCopia);
}

/////////////////////////////////
/* Funciones main para Eventos */
/////////////////////////////////

void main_crearEvento(TEvento &evento, TFecha &fecha) {
    assert(evento == NULL && fecha != NULL);
    int id = leerNat();
    char desc[100];
    leerRestoLinea(desc);
    evento = crearTEvento(id, desc, fecha);
    fecha = NULL;    
}

void main_imprimirIdEvento(TEvento evento) {
    assert(evento != NULL);
    printf("El id del evento es: %d\n", idTEvento(evento));
}

void main_imprimirFechaEvento(TEvento evento) {
    assert(evento != NULL);
    TFecha fechaEvento = fechaTEvento(evento);
    assert(fechaEvento != NULL);
    printf("La fecha del evento es: ");
    imprimirTFecha(fechaEvento);
}

void main_imprimirEvento(TEvento evento) {
    assert(evento != NULL);
    imprimirTEvento(evento);
}

void main_posponerEvento(TEvento &evento) {
    assert(evento != NULL);
    nat cantDias = leerNat();
    posponerTEvento(evento, cantDias);
}

void main_liberarEvento(TEvento &evento) {
    assert(evento != NULL);
    liberarTEvento(evento);
}

void main_copiarEvento(TEvento evento) {
    assert(evento != NULL);
    TEvento eventoCopia = copiarTEvento(evento);
    printf("El evento copiado es: ");
    imprimirTEvento(eventoCopia);
    liberarTEvento(eventoCopia);
}

////////////////////////////////
/* Funciones main para Agenda */
////////////////////////////////

void main_crearAgenda(TAgendaLS &agenda) {
    assert(agenda == NULL);
    agenda = crearAgendaLS();
}

void main_liberarAgenda(TAgendaLS &agenda) {
    liberarAgendaLS(agenda);
}

void main_estaEnAgenda(TAgendaLS agenda) {
    nat id = leerNat();
    if (estaEnAgendaLS(agenda, id))
        printf("El evento con id %d está en la agenda.\n", id);
    else
        printf("El evento con id %d NO está en la agenda.\n", id);
}

void main_removerDeAgenda(TAgendaLS &agenda) {
    nat id = leerNat();
    if (estaEnAgendaLS(agenda, id)) {
        removerDeAgendaLS(agenda, id);
        printf("El evento con id %d se removió de la agenda.\n", id);
    } else
        printf("El evento con id %d NO está en la agenda.\n", id);
}

void main_agregarEnAgenda(TAgendaLS &agenda, TEvento &evento) {
    assert(evento != NULL);
    agregarEnAgendaLS(agenda, evento);
    evento = NULL;
}

void main_posponerEnAgenda(TAgendaLS &agenda) {
    assert(agenda != NULL);
    nat id = leerNat();
    nat cantDias = leerNat();
    if (estaEnAgendaLS(agenda, id)) {
        posponerEnAgendaLS(agenda, id, cantDias);
        TEvento eventoPos = obtenerDeAgendaLS(agenda, id);
        TFecha fechaEvento = fechaTEvento(eventoPos);
        printf("La nueva fecha del evento %d pospuesto %d dias es: ", idTEvento(eventoPos), cantDias);
        imprimirTFecha(fechaEvento);
    } else
        printf("El evento con id %d no existe en la agenda y no puede ser pospuesto.\n", id);
}

void main_hayEventosFechaAgenda(TAgendaLS agenda) {
    TFecha fecha = NULL;
    leerFecha(fecha);

    if (hayEventosFechaLS(agenda, fecha))
        imprimirEventosFechaLS(agenda, fecha);
    else
        printf("No se encontraron eventos en la fecha determinada.\n");

    liberarTFecha(fecha);
}

void main_imprimirAgenda(TAgendaLS agenda) {
    imprimirAgendaLS(agenda);
}

void main_imprimirEventosFechaAgenda(TAgendaLS agenda) {
    TFecha fecha = NULL;
    leerFecha(fecha);

    imprimirEventosFechaLS(agenda, fecha);

    liberarTFecha(fecha);
}

void main_imprimirCopiaAgenda (TAgendaLS agenda) {
    if (esVaciaAgendaLS(agenda)) {
        printf("La agenda está vacía.\n");
    }
    TAgendaLS copia = copiarAgendaLS(agenda);
    if (esVaciaAgendaLS(copia))
        printf("La copia está vacía.\n");
    else
        imprimirAgendaLS(copia);

    liberarAgendaLS(copia);
}

void main_crearPersona(TPersona &persona, TAgendaLS &agenda){
    assert (persona == NULL);
    nat id = leerNat();
    nat edad = leerNat();
    char nombre[100];
    leerRestoLinea(nombre);
    persona = crearTPersona(id, edad, nombre, agenda);
    agenda = NULL;
}

void main_liberarPersona(TPersona &persona){
    assert (persona != NULL);
    liberarTPersona(persona);
}

void main_imprimirIdPersona(TPersona persona){
    assert (persona != NULL);
    printf("El id de la persona es: %d\n", idTPersona(persona));
}

void main_imprimirEdadPersona(TPersona persona){
    assert (persona != NULL);
    printf("La edad de la persona es: %d\n", edadTPersona(persona));
}   

void main_imprimirNombrePersona(TPersona persona){
    assert (persona != NULL);
    printf("El nombre de la persona es: %s\n", nombreTPersona(persona));
}

void main_imprimirAgendaPersona(TPersona persona){
    assert (persona != NULL);
    imprimirAgendaLS(agendaTPersona(persona));
}

void main_imprimirPersona(TPersona persona){
    assert (persona != NULL);
    imprimirTPersona(persona);   
}

void main_agregarEventoPersona(TPersona &persona, TEvento &evento){
    assert (persona != NULL && evento != NULL);
    agregarEventoATPersona(persona, evento);
    evento = NULL;
}

void main_removerEventoPersona(TPersona &persona){
    assert (persona != NULL);
    nat id = leerNat();
    removerEventoDeTPersona(persona, id);
}

void main_posponerEventoPersona(TPersona &persona){
    assert (persona != NULL);
    nat id = leerNat();
    nat cantDias = leerNat();
    posponerEventoEnTPersona(persona, id, cantDias);
}

void main_estaEnAgendaPersona(TPersona persona){
    assert (persona != NULL);
    nat id = leerNat();
    if (estaEnAgendaDeTPersona(persona, id))
        printf("El evento con id %d está en la agenda de la persona.\n", id);
    else
        printf("El evento con id %d NO está en la agenda de la persona.\n", id);
}

void main_imprimirEventoPersona(TPersona persona){
    assert (persona != NULL);
    nat id = leerNat();
    TEvento evento = obtenerDeAgendaDeTPersona(persona, id);
    imprimirTEvento(evento);
}

void main_imprimirCopiaPersona(TPersona persona){
    assert (persona != NULL);
    TPersona copia = copiarTPersona(persona);
    imprimirTPersona(copia);
    liberarTPersona(copia);
}

void main_crearListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas == NULL);
    listaPersonas = crearTPersonasLDE();
}

void main_liberarListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    liberarTPersonasLDE(listaPersonas);
}

void main_insertarPersonaListaPersonas(TPersonasLDE &listaPersonas, TPersona &persona){
    assert (listaPersonas != NULL && persona != NULL);
    int pos = leerNat();
    assert (pos >= 1);
    insertarTPersonasLDE(listaPersonas, persona, pos);
    persona = NULL;
}

void main_eliminarInicioListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    eliminarInicioTPersonasLDE(listaPersonas);
}

void main_eliminarFinalListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    eliminarFinalTPersonasLDE(listaPersonas);
}

void main_imprimirListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    imprimirTPersonasLDE(listaPersonas);
}

void main_imprimirCantidadListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    printf("La cantidad de personas en la lista es: %d.\n", cantidadTPersonasLDE(listaPersonas));
}

void main_estaEnListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    nat id = leerNat();
    if (estaEnTPersonasLDE(listaPersonas, id))
        printf("La persona con id %d está en la lista.\n", id);
    else
        printf("La persona con id %d NO está en la lista.\n", id);
}

void main_imprimirPersonaListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    nat id = leerNat();
    TPersona persona = obtenerDeTPersonasLDE(listaPersonas, id);
    imprimirTPersona(persona);
}

void main_concatenarConVacioListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    TPersonasLDE listaPersonas2 = crearTPersonasLDE();
    TPersonasLDE personasConcat = concatenarTPersonasLDE(listaPersonas, listaPersonas2);
    listaPersonas = personasConcat;
}
void main_crearYConcatenarListaPersonas(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    TAgendaLS agenda = crearAgendaLS();
    TPersona persona = crearTPersona(1, 20, "Juan", agenda);
    TAgendaLS agenda2 = crearAgendaLS();
    TPersona persona2 = crearTPersona(2, 21, "Pedro", agenda2);
    TAgendaLS agenda3 = crearAgendaLS();
    TPersona persona3 = crearTPersona(3, 22, "Maria", agenda3);
    TPersonasLDE listaPersonas2 = crearTPersonasLDE();
    insertarTPersonasLDE(listaPersonas2, persona, 1);
    insertarTPersonasLDE(listaPersonas2, persona2, 2);
    insertarTPersonasLDE(listaPersonas2, persona3, 3);
    TPersonasLDE personasConcat = concatenarTPersonasLDE(listaPersonas, listaPersonas2);
    listaPersonas = personasConcat;
}

void main_concatenarListaPersonasTiempo(TPersonasLDE &listaPersonas){
    assert (listaPersonas != NULL);
    nat tamanio = leerNat();
    nat timeout = leerNat();
    clock_t tm = clock();
    for (nat i = 0; i < tamanio; i++){
        TAgendaLS agenda = crearAgendaLS();
        TPersona persona = crearTPersona(i, 20, "Juan", agenda);
        insertarTPersonasLDE(listaPersonas, persona, 1);
    }
    TPersonasLDE listaPersonas2 = crearTPersonasLDE();
    for (nat i = 0; i < tamanio; i++){
        TAgendaLS agenda = crearAgendaLS();
        TPersona persona = crearTPersona(i, 20, "Juan", agenda);
        insertarTPersonasLDE(listaPersonas2, persona, 1);
    }
    
    TPersonasLDE personasConcat = concatenarTPersonasLDE(listaPersonas, listaPersonas2);
    listaPersonas = personasConcat;
    
    tm = clock() - tm;
    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    //printf("%f \n", tiempo);
    if (tiempo > timeout)
    printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
    else
    printf("Bien.\n");
}

void main_crearArbolPersonas(TPersonasABB &arbolPersonas){
    assert (arbolPersonas == NULL);
    arbolPersonas = crearTPersonasABB();
}

void main_esVacioArbolPersonas(TPersonasABB arbolPersonas){
    if (esVacioTPersonasABB(arbolPersonas))
        printf("El árbol de personas está vacío.\n");
    else
        printf("El árbol de personas NO está vacío.\n");
}

void main_liberarArbolPersonas(TPersonasABB &arbolPersonas){
    liberarTPersonasABB(arbolPersonas);
}

void main_insertarArbolPersonas(TPersonasABB &arbolPersonas, TPersona &persona){
    assert (persona != NULL);
    insertarTPersonasABB(arbolPersonas, persona);
    persona = NULL;
}

void main_estaEnArbolPersonas(TPersonasABB arbolPersonas){
    nat id = leerNat();
    if (estaTPersonasABB(arbolPersonas, id))
        printf("La persona con id %d está en el árbol de personas.\n", id);
    else
        printf("La persona con id %d NO está en el árbol de personas.\n", id);
}

void main_removerArbolPersonas(TPersonasABB &arbolPersonas){
    nat id = leerNat();
    removerTPersonasABB(arbolPersonas, id);
}

void main_imprimirArbolPersonas(TPersonasABB arbolPersonas){
    imprimirTPersonasABB(arbolPersonas);
}

void main_imprimirCantidadArbolPersonas(TPersonasABB arbolPersonas){
    printf("La cantidad de personas en el árbol es: %d.\n", cantidadTPersonasABB(arbolPersonas));
}

void main_imprimirPersonaArbolPersonas(TPersonasABB arbolPersonas){
    assert(!esVacioTPersonasABB(arbolPersonas));
    nat id = leerNat();
    if (!estaTPersonasABB(arbolPersonas, id))
        printf("La persona con id %d NO está en el árbol de personas.\n", id);
    else{
        TPersona persona = obtenerDeTPersonasABB(arbolPersonas, id);
        imprimirTPersona(persona);
    }
}

void main_alturaArbolPersonas(TPersonasABB arbolPersonas){
    printf("La altura del árbol de personas es: %d.\n", alturaTPersonasABB(arbolPersonas));
}

void main_esPerfectoArbolPersonas(TPersonasABB arbolPersonas){
    if (esPerfectoTPersonasABB(arbolPersonas))
        printf("El árbol de personas es perfecto.\n");
    else
        printf("El árbol de personas NO es perfecto.\n");
}

void main_esPerfectoArbolPersonasTiempo(TPersonasABB &arbolPersonas){
    nat tamanio = leerNat();
    nat timeout = leerNat();

    for (nat i = 0; i < tamanio; i++){
        TPersona persona = crearTPersona(i, 20, "Juan", NULL);
        insertarTPersonasABB(arbolPersonas, persona);
    }
    
    clock_t tm = clock();
    bool result = esPerfectoTPersonasABB(arbolPersonas);
    tm = clock() - tm;
    if (result)
        printf("El árbol de personas es perfecto.\n");
    else
        printf("El árbol de personas NO es perfecto.\n");
    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    //printf("%f \n", tiempo);
    if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
    else
        printf("Bien.\n");
}

void insertarEnArbolDeArreglo(TPersonasABB &arbolPersonas, TPersona *arreglo, int inicio, int final){
    if (inicio <= final){
        int mid = (inicio + final) / 2;
        insertarTPersonasABB(arbolPersonas, arreglo[mid]);
        insertarEnArbolDeArreglo(arbolPersonas, arreglo, inicio, mid - 1);
        insertarEnArbolDeArreglo(arbolPersonas, arreglo, mid + 1, final);
    }
}

void main_esPerfectoArbolPersonasTiempo2(TPersonasABB &arbolPersonas){
    nat tamanio = leerNat();
    nat timeout = leerNat();

    TPersona *arreglo = new TPersona[tamanio];
    for (nat i = 0; i < tamanio; i++) {
        arreglo[i] = crearTPersona(i, 20, "Juan", NULL);
    }

    int inicio = 0;
    int final = tamanio - 1;
    insertarEnArbolDeArreglo(arbolPersonas, arreglo, inicio, final);
    clock_t tm = clock();
    bool result = esPerfectoTPersonasABB(arbolPersonas);
    tm = clock() - tm;
    if (result)
        printf("El árbol de personas es perfecto.\n");
    else
        printf("El árbol de personas NO es perfecto.\n");
    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    //printf("%f \n", tiempo);
    if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
    else
        printf("Bien.\n");

    delete[] arreglo;
}

void main_maxIdPersonaArbolPersonas(TPersonasABB arbolPersonas){
    assert (!esVacioTPersonasABB(arbolPersonas));
    TPersona persona = maxIdPersona(arbolPersonas);
    printf("La persona con mayor id en el árbol es: \n");
    imprimirTPersona(persona);
}

void main_mayoresEdadArbolPersonas(TPersonasABB arbolPersonas){
    nat edad = leerNat();
    TPersonasABB arbolMayores = mayoresTPersonasABB(arbolPersonas, edad);
    imprimirTPersonasABB(arbolMayores);
    liberarTPersonasABB(arbolMayores);
}

void main_mayoresEdadArbolPersonasTiempo(TPersonasABB &arbolPersonas){
    nat tamanio = leerNat();
    nat timeout = leerNat();
    nat edad = leerNat();

    TPersona *arreglo = new TPersona[tamanio];
    for (nat i = 0; i < tamanio; i++) {
        arreglo[i] = crearTPersona(i, i*2, "Juan", NULL);
    }

    nat inicio = 0;
    nat final = tamanio - 1;
    insertarEnArbolDeArreglo(arbolPersonas, arreglo, inicio, final);
    clock_t tm = clock();
    TPersonasABB arbolMayores = mayoresTPersonasABB(arbolPersonas, edad);
    tm = clock() - tm;
    imprimirTPersonasABB(arbolMayores);
    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    //printf("%f \n", tiempo);
    if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
    else
        printf("Bien.\n");
    
    liberarTPersonasABB(arbolMayores);
    delete[] arreglo;
}

void main_aplanarArbolPersonas(TPersonasABB &arbolPersonas){
    TPersonasLDE listaPersonas = aTPersonasLDE(arbolPersonas);
    imprimirTPersonasLDE(listaPersonas);
    liberarTPersonasLDE(listaPersonas);
}
