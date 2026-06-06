#include "../include/aplicaciones.h"

<<<<<<< HEAD
TPilaPersona menoresQueElResto(TPersonasLDE lista) {
    TPilaPersona pila = crearTPilaPersona();
    nat n = cantidadTPersonasLDE(lista);
    if (n == 0) return pila;

    TPersona* buffer = new TPersona[n];
    for (nat i = 0; i < n; i++) {
        buffer[i] = copiarTPersona(obtenerInicioDeTPersonasLDE(lista));
        eliminarInicioTPersonasLDE(lista);
    }

    nat min_suffix = edadTPersona(buffer[n - 1]) + 1;
    TPersona* calificados = new TPersona[n];
    nat k = 0;

    for (int i = n - 1; i >= 0; i--) {
        nat edad = edadTPersona(buffer[i]);
        if (edad < min_suffix) { calificados[k++] = buffer[i]; min_suffix = edad; }
        else liberarTPersona(buffer[i]);
    }

    for (int i = k - 1; i >= 0; i--) {
        apilarEnTPilaPersona(pila, calificados[i]);
        liberarTPersona(calificados[i]);
    }

    delete[] buffer;
    delete[] calificados;
    return pila;
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
=======
void listarEnOrden(TTablaPersonas t, char** nombres, nat n){

>>>>>>> Veni
}