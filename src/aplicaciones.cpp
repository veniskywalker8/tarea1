#include "../include/aplicaciones.h"

TPilaPersona menoresQueElResto(TPersonasLDE lista) {
    TPilaPersona pila = crearTPilaPersona();
    nat n = cantidadTPersonasLDE(lista);
    if (n == 0) return pila;

    // Lectura segura sin mutar la lista (evita puntero colgante en main)
    TPersona* buffer = new TPersona[n];
    for (nat i = 0; i < n; i++) {
        buffer[i] = copiarTPersona(obtenerDeTPersonasLDE(lista, i + 1));
    }

    // Filtrado de derecha a izquierda
    nat min_suffix = edadTPersona(buffer[n - 1]) + 1;
    TPersona* calificados = new TPersona[n];
    nat k = 0;

    for (int i = n - 1; i >= 0; i--) {
        nat edad = edadTPersona(buffer[i]);
        if (edad < min_suffix) {
            calificados[k++] = buffer[i];
            min_suffix = edad;
        } else {
            liberarTPersona(buffer[i]);
        }
    }

    // Apilado en orden reverso (cima = mayor edad)
    for (int i = k - 1; i >= 0; i--) {
        apilarEnTPilaPersona(pila, calificados[i]);
        liberarTPersona(calificados[i]); // Pila ya hizo copia interna
    }

    delete[] buffer;
    delete[] calificados;
    return pila; // Lista intacta: liberarTPersonasLDE en main será segura
}

bool sumaPares(nat k, TConjuntoIds c) {
    nat n = cantMaxTConjuntoIds(c);
    for (nat id = 1; id <= n; id++) {
        if (perteneceTConjuntoIds(id, c)) {
            nat comp = k - id;
            if (comp > 0 && comp <= n && comp != id && perteneceTConjuntoIds(comp, c)) {
                return true;
            }
        }
    }
    return false;
}