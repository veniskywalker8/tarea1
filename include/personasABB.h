/*
  Módulo de definición de 'personasABB'.

  La estructura de tipo TPersonasABB es un árbol binario de búsqueda que almacena a las personas por id.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef PERSONASABB_H
#define PERSONASABB_H

#include "personasLDE.h"
#include "pilaPersona.h"

// Definición de tipo TPersonasABB como un puntero a rep_personasAbb
typedef struct rep_personasAbb* TPersonasABB;

// Función para crear un nuevo árbol binario
// Devuelve un nuevo árbol binario vacío
// La función es Theta(1) peor caso
TPersonasABB crearTPersonasABB();

// Función para determinar si un árbol binario es vacío
// Devuelve true si el árbol binario es vacío, false en caso contrario
// La función es Theta(1) peor caso
bool esVacioTPersonasABB(TPersonasABB personasABB);

// Función para insertar una persona en el árbol binario ordenado por id
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
// PRE: la persona no está en el árbol binario
void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p);

// Función para liberar la memoria asignada a un árbol binario
// La función es O(n*m) peor caso, donde n es la cantidad de personas en el árbol y m es la cantidad de eventos de la agenda con mas eventos entre todas las personas del árbol.
void liberarTPersonasABB(TPersonasABB &personasABB);

// Función para imprimir las personas del árbol binario en orden de id
// La función es O(n*m) peor caso, donde n es la cantidad de personas en el árbol y 
// m es la cantidad de eventos de la agenda con mas eventos entre todas las personas del árbol.
void imprimirTPersonasABB(TPersonasABB personasABB);

// Función para obtener la cantidad de personas en el árbol binario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
nat cantidadTPersonasABB(TPersonasABB personasABB);

// Función para obtener la persona con el id más grande del árbol binario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
// PRE: el árbol binario no es vacío
TPersona maxIdPersona(TPersonasABB personasABB);

// Función para eliminar una persona del árbol binario
// En caso de que el nodo a remover tenga ambos subárboles no vacíos,
// se reemplaza por la Persona con el id más grande del subárbol izquierdo. 
// La función es Theta(n+m) peor caso, donde n es la cantidad de personas en 
// el árbol y m es la cantidad de eventos de la agenda de la persona a remover.
// PRE: la persona está en el árbol binario
void removerTPersonasABB(TPersonasABB &personasABB, nat id);

// Función que determina si una persona está en el árbol binario
// Devuelve true si la persona está en el árbol binario, false en caso contrario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
bool estaTPersonasABB(TPersonasABB personasABB, nat id);

// Función para obtener una persona del árbol binario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
// PRE: la persona está en el árbol binario
TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id);

// Función para obtener la altura del árbol binario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
nat alturaTPersonasABB(TPersonasABB personasABB);

// Función para determinar si el árbol binario es perfecto
// Devuelve true si el árbol binario es perfecto, false en caso contrario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
bool esPerfectoTPersonasABB(TPersonasABB personasABB);

// Función que retorna un nuevo TPersonasABB con las personas de personasABB que son mayores a cierta edad
// El árbol retornado NO comparte memoria con el árbol pasado por parámetro.
// En caso de que deba elegir un nuevo nodo como raíz seleccione el nodo con el id más grande del 
// subárbol izquierdo.
// La función es O(n*m) peor caso, donde n es la cantidad de personas en el árbol y m es la cantidad de eventos 
// de la agenda con más eventos entre todas las personas del árbol.
TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad);

// Función que retorna una lista de tipo TPersonasLDE con las personas que están en el árbol pasado por parámetro
// La lista debe estar ordenada por id.
// La lista resultado NO comparte memoria con el árbol pasado por parámetro.
// La función es O(n*m) peor caso, siendo n la cantidad de personas en el árbol binario y m la cantidad de eventos 
// de la agenda con más eventos entre todas las personas del árbol.
TPersonasLDE aTPersonasLDE(TPersonasABB personasABB);

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// Función que retorna la amplitud del árbol binario.
// La amplitud es la cantidad de nodos en el nivel con mas nodos del árbol.
// La función es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario.
nat amplitudTPersonasABB(TPersonasABB t);

// Función que transforma el árbol en una pila de personas de tipo TPersona, donde las personas están ordenadas como 
// en una recorrida por niveles del árbol.
// Es decir, en la pila primero deben estar los nodos del nivel 1 (la raiz), luego los del nivel 2, etc.
// El árbol no se debe modificar y los elementos de la pila no comparten memoria con el árbol original.
// La función es O(n*m) peor caso, siendo n la cantidad de personas en el árbol binario y m la cantidad de eventos 
// de la agenda con mas eventos entre todas las personas del árbol.
TPilaPersona serializarTPersonasABB(TPersonasABB t);

// Función que transforma una pila de personas de tipo TPersona en un árbol binario de tipo TPersonasABB.
// Las personas en la pila están ordenadas como en una recorrida por niveles del árbol.
// Es decir, en la pila primero están las personas que corresponden a los nodos del nivel 1, luego los del nivel 2, etc.
// Se asume que el árbol que generó la pila es completo.
// Las personas en el árbol resultado deben estar ordenadas de tal forma que si se serializa se obtiene la misma pila.
// Los elementos del árbol no comparten memoria con la pila original y al final de la función la pila queda vacía y se libera. 
// La funcion es O(n*m) peor caso, siendo n la cantidad de personas en la pila y m la cantidad de eventos de la agenda 
// con mas eventos entre todas las personas de la pila.
TPersonasABB deserializarTPersonasABB(TPilaPersona &t);

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

#endif  // PERSONASABB_H