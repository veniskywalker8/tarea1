#include "../include/personasABB.h"

//- Definición del nodo del ABB
struct rep_personasAbb {
    TPersona persona;              // dato principal (persona)
    struct rep_personasAbb* izq;   // subárbol izquierdo
    struct rep_personasAbb* der;   // subárbol derecho
};

//- Crear un ABB vacío
TPersonasABB crearTPersonasABB() {
    return NULL;
}

//- Verificar si el ABB está vacío
bool esVacioTPersonasABB(TPersonasABB personasABB) {
    return personasABB == NULL;
}

//- Insertar una persona en el ABB según su id
void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p) {
    if (personasABB == NULL) {
        // Crear nuevo nodo
        personasABB = new rep_personasAbb;
        personasABB->persona = p;
        personasABB->izq = NULL;
        personasABB->der = NULL;
    } else {
        nat idNodo = idTPersona(personasABB->persona);
        nat idNuevo = idTPersona(p);
        if (idNuevo < idNodo) {
            insertarTPersonasABB(personasABB->izq, p);
        } else if (idNuevo > idNodo) {
            insertarTPersonasABB(personasABB->der, p);
        } else {
            // Si el id ya existe, se puede decidir reemplazar o ignorar
            liberarTPersona(personasABB->persona);
            personasABB->persona = p;
        }
    }
}

//- Liberar todo el ABB
void liberarTPersonasABB(TPersonasABB &personasABB) {
    if (personasABB != NULL) {
        liberarTPersonasABB(personasABB->izq);
        liberarTPersonasABB(personasABB->der);
        liberarTPersona(personasABB->persona);
        delete personasABB;
        personasABB = NULL;
    }
}

//- Imprimir el ABB en orden (in-order traversal)
void imprimirTPersonasABB(TPersonasABB personasABB) {
    if (personasABB != NULL) {
        imprimirTPersonasABB(personasABB->izq);
        imprimirTPersona(personasABB->persona);
        imprimirTPersonasABB(personasABB->der);
    }
}

//- Contar la cantidad de nodos en el ABB
nat cantidadTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL) return 0;
    return 1 + cantidadTPersonasABB(personasABB->izq) + cantidadTPersonasABB(personasABB->der);
}

//- Obtener la persona con el máximo id
TPersona maxIdPersona(TPersonasABB personasABB) {
    if (personasABB == NULL) return NULL;
    if (personasABB->der == NULL) return personasABB->persona;
    return maxIdPersona(personasABB->der);
}

//- Remover una persona por id
void removerTPersonasABB(TPersonasABB &personasABB, nat id) {
    if (personasABB == NULL) return;
    nat idNodo = idTPersona(personasABB->persona);
    if (id < idNodo) {
        removerTPersonasABB(personasABB->izq, id);
    } else if (id > idNodo) {
        removerTPersonasABB(personasABB->der, id);
    } else {
        // Caso encontrado
        if (personasABB->izq == NULL && personasABB->der == NULL) {
            liberarTPersona(personasABB->persona);
            delete personasABB;
            personasABB = NULL;
        } else if (personasABB->izq == NULL) {
            TPersonasABB temp = personasABB->der;
            liberarTPersona(personasABB->persona);
            delete personasABB;
            personasABB = temp;
        } else if (personasABB->der == NULL) {
            TPersonasABB temp = personasABB->izq;
            liberarTPersona(personasABB->persona);
            delete personasABB;
            personasABB = temp;
        } else {
            // Reemplazar por el mínimo del subárbol derecho
            TPersonasABB minDer = personasABB->der;
            while (minDer->izq != NULL) minDer = minDer->izq;
            liberarTPersona(personasABB->persona);
            personasABB->persona = copiarTPersona(minDer->persona);
            removerTPersonasABB(personasABB->der, idTPersona(minDer->persona));
        }
    }
}

//- Verificar si un id está en el ABB
bool estaTPersonasABB(TPersonasABB personasABB, nat id) {
    if (personasABB == NULL) return false;
    nat idNodo = idTPersona(personasABB->persona);
    if (id == idNodo) return true;
    if (id < idNodo) return estaTPersonasABB(personasABB->izq, id);
    return estaTPersonasABB(personasABB->der, id);
}

//- Obtener la persona por id
TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id) {
    if (personasABB == NULL) return NULL;
    nat idNodo = idTPersona(personasABB->persona);
    if (id == idNodo) return personasABB->persona;
    if (id < idNodo) return obtenerDeTPersonasABB(personasABB->izq, id);
    return obtenerDeTPersonasABB(personasABB->der, id);
}

//- Calcular la altura del ABB
nat alturaTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL) return 0;
    nat izqAlt = alturaTPersonasABB(personasABB->izq);
    nat derAlt = alturaTPersonasABB(personasABB->der);
    return 1 + (izqAlt > derAlt ? izqAlt : derAlt);
}

//- Verificar si el ABB es perfecto (todos los niveles completos)
bool esPerfectoTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL) return true;
    nat izqAlt = alturaTPersonasABB(personasABB->izq);
    nat derAlt = alturaTPersonasABB(personasABB->der);
    if (izqAlt != derAlt) return false;
    return esPerfectoTPersonasABB(personasABB->izq) && esPerfectoTPersonasABB(personasABB->der);
}

//- Crear un ABB con personas mayores a cierta edad
TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad) {
    if (personasABB == NULL) return NULL;

    TPersonasABB nuevo = NULL;
    if (edadTPersona(personasABB->persona) > edad) {
        insertarTPersonasABB(nuevo, copiarTPersona(personasABB->persona));
    }
    TPersonasABB izq = mayoresTPersonasABB(personasABB->izq, edad);
    TPersonasABB der = mayoresTPersonasABB(personasABB->der, edad);

    // Insertar recursivamente los subárboles
    if (izq != NULL) {
        insertarTPersonasABB(nuevo, copiarTPersona(izq->persona));
        // seguir recorriendo izq->izq y izq->der
    }
    if (der != NULL) {
        insertarTPersonasABB(nuevo, copiarTPersona(der->persona));
        // seguir recorriendo der->izq y der->der
    }
    return nuevo;
}

//- Convertir el ABB a una lista doblemente enlazada (in-order)
TPersonasLDE aTPersonasLDE(TPersonasABB personasABB) {
    if (personasABB == NULL) return crearTPersonasLDE();

    // Primero convertir el subárbol izquierdo
    TPersonasLDE lista = aTPersonasLDE(personasABB->izq);

    // Insertar la persona actual al final de la lista
    nat pos = cantidadTPersonasLDE(lista) + 1;
    insertarTPersonasLDE(lista, copiarTPersona(personasABB->persona), pos);

    // Convertir el subárbol derecho y concatenar
    TPersonasLDE listaDer = aTPersonasLDE(personasABB->der);
    lista = concatenarTPersonasLDE(lista, listaDer);

    return lista;
}

