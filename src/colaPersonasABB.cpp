#include "../include/colaPersonasABB.h"
#include "../include/personasLDE.h"

struct nodoLista{
  TPersonasABB arbol;
  struct nodoLista* sig;
};
struct rep_colaPersonasABB {
  nat cant;
  nodoLista* primero;
  nodoLista* ultimo;
};


TColaPersonasABB crearTColaPersonasABB() {
  TColaPersonasABB nuevo = new rep_colaPersonasABB;
  nuevo->cant = 0;
  nuevo->primero = NULL;
  nuevo->ultimo = NULL;
  return nuevo;
}

void liberarTColaPersonasABB(TColaPersonasABB &c) {
  nodoLista* aux = c->primero;
  nodoLista* auxaux;
  while(aux != c->ultimo){
    auxaux = aux->sig;
    delete aux;
    aux=auxaux;
  }
  delete aux;
  aux = NULL;
  auxaux = NULL;
  c->primero = NULL;
  c->ultimo = NULL;
  delete c;
  c=NULL;
}

nat cantidadEnTColaPersonasABB(TColaPersonasABB c) { 
  return c->cant;
 }

void encolarEnTColaPersonasABB(TPersonasABB t, TColaPersonasABB &c) {
  nodoLista* nuevo = new nodoLista;
  nuevo->arbol = t;
  nuevo->sig = NULL;
  if(c->ultimo != NULL) c->ultimo->sig = nuevo;
  else c->primero = nuevo;
  c->ultimo = nuevo;
  c->cant++;
}

TPersonasABB frenteDeTColaPersonasABB(TColaPersonasABB c) { 
  return c->primero->arbol;
}

void desencolarDeTColaPersonasABB(TColaPersonasABB &c) {
  nodoLista* p = c->primero;
  if(p != NULL) c->primero = c->primero->sig;
  delete p;
  if (c->primero == NULL) c->ultimo = NULL;
  c->cant--;
}
