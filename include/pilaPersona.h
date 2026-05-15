/*
  Módulo de definición de 'TPilaPersona'.

  Los elementos de tipo TPilaPersona son pilas de elementos de tipo TPersona.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "persona.h"

// Representación de 'TPilaPersona'.
// Se debe definir en pila.cpp.
// struct rep_pilaPersona;
// Declaración del tipo 'TPilaPersona'
typedef struct rep_pilaPersona *TPilaPersona;

// Devuelve una TPilaPersona vacía (sin elementos).
// La funcion es Theta(1) peor caso.
TPilaPersona crearTPilaPersona();

// Libera la memoria asignada a la pila 'p' y la de todos sus elementos.
// La funcion es O(n*m) peor caso, siendo n la cantidad de elementos en 'p' y m la cantidad de eventos de la agenda con mas eventos entre todas las personas de 'p'.
void liberarTPilaPersona(TPilaPersona &p);

// Devuelve la cantidad de elementos de la pila 'p'.
// La funcion es Theta(1) peor caso.
nat cantidadEnTPilaPersona(TPilaPersona p);

// Apila la persona 'persona' en la pila 'p'.
// La TPilaPersona resultado no comparte memoria con 'persona'.
// La funcion es Theta(m) peor caso, donde m es la cantidad de eventos de la agenda de 'persona'.
void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona);

// Devuelve el elemento más nuevo (el último insertado) en 'p'.
// Precondición: cantidadEnPila(p) > 0.
// La funcion es Theta(1) peor caso.
TPersona cimaDeTPilaPersona(TPilaPersona p);

// Remueve de 'p' su elemento más nuevo (el último insertado).
// Se libera la memoria asignada al mismo.
// La funcion es Theta(m) peor caso, donde m es la cantidad de eventos de la agenda de la persona que se desapila.
void desapilarDeTPilaPersona(TPilaPersona &p);

#endif
