#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){
    TColaDePrioridadPersona cp = crearCP(MAX_ID);
    
    for (nat i = 0; i < n; i++) {
        if (perteneceATTablaPersonas(t, nombres[i])) {
            TPersona persona = obtenerPersonaDeTTablaPersonas(t, nombres[i]);
            TPersona copia = copiarTPersona(persona);  // ← Insertar copia
            insertarEnCP(copia, cp);
        }
    }
    
    while (!estaVaciaCP(cp)) {
        TPersona p = prioritaria(cp);
        imprimirTPersona(p);
        eliminarPrioritaria(cp);  // Ahora libera la copia, no la original
    }
    
    liberarCP(cp);
}