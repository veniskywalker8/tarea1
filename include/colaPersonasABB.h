/*
  Módulo de definición de 'TColaPersonasABB'.

  Los elementos de tipo TColaPersonasABB son colas de elementos de tipo TPersonasABB.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_H
#define _COLA_H

#include "personasABB.h"

// Representación de 'TColaPersonasABB'.
// Se debe definir en colaPersonasABB.cpp.
// struct rep_colaPersonasABB;
// Declaración del tipo 'TColaPersonasABB'
typedef struct rep_colaPersonasABB *TColaPersonasABB;

// Devuelve una TColaPersonasABB vacía (sin elementos).
// La función es Theta(1) peor caso.
TColaPersonasABB crearTColaPersonasABB();

// Libera la memoria asignada a la cola 'c' y la de todos sus elementos pero sin liberar la memoria de los elementos de tipo TPersonasABB incluidos.
// La función es Theta(n) peor caso, donde n es la cantidad de personas en la cola.
void liberarTColaPersonasABB(TColaPersonasABB &c);

// Devuelve la cantidad de elementos en la cola 'c'.
// La función es Theta(1) peor caso.
nat cantidadEnTColaPersonasABB(TColaPersonasABB c);

// Encola la persona 'persona' en la cola 'c'.
// La función es Theta(1) peor caso.
void encolarEnTColaPersonasABB(TPersonasABB t, TColaPersonasABB &c);

// Devuelve el elemento más antiguo (el primero ingresado) en 'c'.
// Precondición: cantidadEnCola(c) > 0.
// La función es Theta(1) peor caso.
TPersonasABB frenteDeTColaPersonasABB(TColaPersonasABB c);

// Remueve de 'c' su elemento más antiguo (el primero ingresado).
// Se libera la memoria asignada al elemento de la cola pero sin liberar la memoria del elemento de tipo TPersonasABB incluido.
// Precondición: cantidadEnCola(c) > 0.
// La función es Theta(1) peor caso.
void desencolarDeTColaPersonasABB(TColaPersonasABB &c);

#endif
