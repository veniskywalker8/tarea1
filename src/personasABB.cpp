#include "../include/personasABB.h"

//+AUXILIAR
void auxLiberar(TPersonasABB &personasABB, TPersonasABB reemplazo);
static void recolectarMayores(TPersonasABB arb, nat edad, TPersonasABB &destino);

//- Definición del nodo del ABB
struct rep_personasAbb {
    TPersona persona;              // dato principal (persona)
    struct rep_personasAbb* izq;   // subárbol izquierdo
    struct rep_personasAbb* der;   // subárbol derecho
};

//- Crear un ABB vacío
TPersonasABB crearTPersonasABB() {
    return nullptr;
}

//- Verificar si el ABB está vacío
bool esVacioTPersonasABB(TPersonasABB personasABB) {
    return personasABB == nullptr;
}

//- Insertar una persona en el ABB según su id
void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p) {
    if (personasABB == nullptr) {
        personasABB = new rep_personasAbb;
        personasABB->persona = p;
        personasABB->izq = nullptr;
        personasABB->der = nullptr;
    } else {
        nat idNodo = idTPersona(personasABB->persona);
        nat idNuevo = idTPersona(p);
        if (idNuevo < idNodo) {
            insertarTPersonasABB(personasABB->izq, p);
        } else if (idNuevo > idNodo) {
            insertarTPersonasABB(personasABB->der, p);
        } else {
            liberarTPersona(personasABB->persona);
            personasABB->persona = p;
        }
    }
}

//- Liberar todo el ABB
void liberarTPersonasABB(TPersonasABB &personasABB) {
    if (personasABB == nullptr) return;
    liberarTPersonasABB(personasABB->izq);
    liberarTPersonasABB(personasABB->der);
    auxLiberar(personasABB, nullptr);
}

//- Imprimir el ABB en orden (in-order traversal)
void imprimirTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == nullptr) return;
    imprimirTPersonasABB(personasABB->izq);
    imprimirTPersona(personasABB->persona);
    imprimirTPersonasABB(personasABB->der);
}

//- Contar la cantidad de nodos en el ABB
nat cantidadTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == nullptr) return 0;
    return 1 + cantidadTPersonasABB(personasABB->izq) + cantidadTPersonasABB(personasABB->der);
}

//- Obtener la persona con el máximo id
TPersona maxIdPersona(TPersonasABB personasABB) {
    if (personasABB == nullptr) return nullptr;
    if (personasABB->der == nullptr) return personasABB->persona;
    return maxIdPersona(personasABB->der);
}

//- Remover una persona por id
void removerTPersonasABB(TPersonasABB &personasABB, nat id) {
    if (personasABB == nullptr) return;
    nat idNodo = idTPersona(personasABB->persona);
    if (id < idNodo) {
        removerTPersonasABB(personasABB->izq, id);
    } else if (id > idNodo) {
        removerTPersonasABB(personasABB->der, id);
    } else {
        if (personasABB->izq == nullptr && personasABB->der == nullptr) {
            auxLiberar(personasABB, nullptr);
        } else if (personasABB->izq == nullptr) {
            TPersonasABB temp = personasABB->der;
            auxLiberar(personasABB, temp);
        } else if (personasABB->der == nullptr) {
            TPersonasABB temp = personasABB->izq;
            auxLiberar(personasABB, temp);
        } else {
            // Usar el máximo del subárbol izquierdo (como exige el enunciado)
            TPersonasABB maxIzq = personasABB->izq;
            while (maxIzq->der != nullptr) {
                maxIzq = maxIzq->der;
            }
            liberarTPersona(personasABB->persona);
            personasABB->persona = copiarTPersona(maxIzq->persona);
            removerTPersonasABB(personasABB->izq, idTPersona(maxIzq->persona));
        }
    }
}

//- Verificar si un id está en el ABB
bool estaTPersonasABB(TPersonasABB personasABB, nat id) {
    if (personasABB == nullptr) return false;
    nat idNodo = idTPersona(personasABB->persona);
    if (id == idNodo) return true;
    if (id < idNodo) return estaTPersonasABB(personasABB->izq, id);
    return estaTPersonasABB(personasABB->der, id);
}

//- Obtener la persona por id
TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id) {
    if (personasABB == nullptr) return nullptr;
    nat idNodo = idTPersona(personasABB->persona);
    if (id == idNodo) return personasABB->persona;
    if (id < idNodo) return obtenerDeTPersonasABB(personasABB->izq, id);
    return obtenerDeTPersonasABB(personasABB->der, id);
}

//- Calcular la altura del ABB
nat alturaTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == nullptr) return 0;
    nat izqAlt = alturaTPersonasABB(personasABB->izq);
    nat derAlt = alturaTPersonasABB(personasABB->der);
    nat altura = 1 + (izqAlt > derAlt ? izqAlt : derAlt);
    return altura;
}

//- Verificar si el ABB es perfecto (todos los niveles completos)
bool esPerfectoTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == nullptr) return true;
    nat izqAlt = alturaTPersonasABB(personasABB->izq);
    nat derAlt = alturaTPersonasABB(personasABB->der);
    if (izqAlt != derAlt) return false;
    return esPerfectoTPersonasABB(personasABB->izq) && esPerfectoTPersonasABB(personasABB->der);
}

//- Crear un ABB con personas mayores a cierta edad
TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad) {
    if (personasABB == nullptr) return nullptr;
    TPersonasABB nuevo = crearTPersonasABB();
    recolectarMayores(personasABB, edad, nuevo);
    return nuevo;
}

//- Convertir el ABB a una lista doblemente enlazada (in-order)
TPersonasLDE aTPersonasLDE(TPersonasABB personasABB) {
    if (personasABB == nullptr) return crearTPersonasLDE();

    TPersonasLDE lista = aTPersonasLDE(personasABB->izq);

    nat pos = cantidadTPersonasLDE(lista) + 1;
    insertarTPersonasLDE(lista, copiarTPersona(personasABB->persona), pos);

    TPersonasLDE listaDer = aTPersonasLDE(personasABB->der);
    lista = concatenarTPersonasLDE(lista, listaDer);

    return lista;
}

//+AUXILIAR
void auxLiberar(TPersonasABB &personasABB, TPersonasABB reemplazo) {
    if (personasABB != nullptr) {
        liberarTPersona(personasABB->persona);
        delete personasABB;
        personasABB = reemplazo;
    }
}
static void recolectarMayores(TPersonasABB arb, nat edad, TPersonasABB &destino) {
    if (arb == nullptr) return;
    recolectarMayores(arb->izq, edad, destino);
    if (edadTPersona(arb->persona) > edad) {
        TPersona copia = copiarTPersona(arb->persona);
        insertarTPersonasABB(destino, copia);
    }
    recolectarMayores(arb->der, edad, destino);
}