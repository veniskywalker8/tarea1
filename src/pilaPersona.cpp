#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct rep_pilaPersona {
  TPersonasLDE lista;
};

TPilaPersona crearTPilaPersona() {
  TPilaPersona nuevo = new rep_pilaPersona;
  nuevo->lista = crearTPersonasLDE();
  return nuevo;
}

void liberarTPilaPersona(TPilaPersona &p) {
  liberarTPersonasLDE(p->lista);
  delete p;
  p=NULL;
}

nat cantidadEnTPilaPersona(TPilaPersona p) { 
  return cantidadTPersonasLDE(p->lista);
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona) {
  //TPersona copia = copiarTPersona(persona);
  
}

TPersona cimaDeTPilaPersona(TPilaPersona p) { 
  return NULL;
}

void desapilarDeTPilaPersona(TPilaPersona &p) {

}
