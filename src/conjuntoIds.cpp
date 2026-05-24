#include "conjuntoIds.h"
#include <cstdio>

// Representación del conjunto acotado: bitmap + contador
struct rep_conjuntoIds {
    bool* presentes;  // presentes[id] = true ⇔ id ∈ conjunto (1 ≤ id ≤ cantMax)
    nat cantMax;      // límite superior del rango de ids válidos
    nat cardinal;     // cantidad actual de elementos (para Θ(1) en cardinal)
};

//- Crear conjunto vacío de capacidad cantMax
TConjuntoIds crearTConjuntoIds(nat cantMax) {
    TConjuntoIds c = new rep_conjuntoIds;
    c->cantMax = cantMax;
    c->cardinal = 0;
    // +1 para indexar desde 1; () inicializa en false
    c->presentes = new bool[cantMax + 1]();
    return c;
}

//- Verificar si el conjunto está vacío
bool esVacioTConjuntoIds(TConjuntoIds c) {
    return c->cardinal == 0;
}

//- Insertar id si está en rango y no pertenece ya
void insertarTConjuntoIds(nat id, TConjuntoIds &c) {
    if (id > 0 && id <= c->cantMax && !c->presentes[id]) {
        c->presentes[id] = true;
        c->cardinal++;
    }
}

//- Borrar id si está en rango y pertenece
void borrarTConjuntoIds(nat id, TConjuntoIds &c) {
    if (id > 0 && id <= c->cantMax && c->presentes[id]) {
        c->presentes[id] = false;
        c->cardinal--;
    }
}

//- Pertenece: consulta directa al bitmap
bool perteneceTConjuntoIds(nat id, TConjuntoIds c) {
    if (id <= 0 || id > c->cantMax) return false;
    return c->presentes[id];
}

//- Cardinal: retorno del contador mantenido
nat cardinalTConjuntoIds(TConjuntoIds c) {
    return c->cardinal;
}

//- Cantidad máxima: retorno del límite del rango
nat cantMaxTConjuntoIds(TConjuntoIds c) {
    return c->cantMax;
}

//- Imprimir ids en orden ascendente, separados por espacio, con salto final
void imprimirTConjuntoIds(TConjuntoIds c) {
    for (nat id = 1; id <= c->cantMax; id++) {
        if (c->presentes[id]) {
            printf("%u ", id);
        }
    }
    printf("\n");
}

//- Liberar memoria del bitmap y del struct
void liberarTConjuntoIds(TConjuntoIds &c) {
    if (c != nullptr) {
        delete[] c->presentes;
        delete c;
        c = nullptr;
    }
}

//- Unión: id ∈ resultado ⇔ id ∈ c1 ∨ id ∈ c2
TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2) {
    // PRE: c1->cantMax == c2->cantMax
    TConjuntoIds resultado = crearTConjuntoIds(c1->cantMax);
    for (nat id = 1; id <= c1->cantMax; id++) {
        if (c1->presentes[id] || c2->presentes[id]) {
            resultado->presentes[id] = true;
            resultado->cardinal++;
        }
    }
    return resultado;
}

//- Intersección: id ∈ resultado ⇔ id ∈ c1 ∧ id ∈ c2
TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2) {
    // PRE: c1->cantMax == c2->cantMax
    TConjuntoIds resultado = crearTConjuntoIds(c1->cantMax);
    for (nat id = 1; id <= c1->cantMax; id++) {
        if (c1->presentes[id] && c2->presentes[id]) {
            resultado->presentes[id] = true;
            resultado->cardinal++;
        }
    }
    return resultado;
}

//- Diferencia: id ∈ resultado ⇔ id ∈ c1 ∧ id ∉ c2
TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2) {
    // PRE: c1->cantMax == c2->cantMax
    TConjuntoIds resultado = crearTConjuntoIds(c1->cantMax);
    for (nat id = 1; id <= c1->cantMax; id++) {
        if (c1->presentes[id] && !c2->presentes[id]) {
            resultado->presentes[id] = true;
            resultado->cardinal++;
        }
    }
    return resultado;
}