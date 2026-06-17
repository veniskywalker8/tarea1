#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
    nat N;
    nat cantidad;
    bool menorEsPrioritario;
    TPersona* heap;
    nat* posicion;
};

static void intercambiar(rep_colaDePrioridadPersona* cp, nat i, nat j) {
    TPersona aux = cp->heap[i];
    cp->heap[i] = cp->heap[j];
    cp->heap[j] = aux;
    
    nat id_i = idTPersona(cp->heap[i]);
    nat id_j = idTPersona(cp->heap[j]);
    cp->posicion[id_i] = i;
    cp->posicion[id_j] = j;
}

static bool esPrioritario(rep_colaDePrioridadPersona* cp, TPersona p1, TPersona p2) {
    TEvento e1 = primerEventoDeTPersona(p1);
    TEvento e2 = primerEventoDeTPersona(p2);
    TFecha f1 = fechaTEvento(e1);
    TFecha f2 = fechaTEvento(e2);
    
    if (cp->menorEsPrioritario) {
        return compararTFechas(f1, f2) < 0;
    } else {
        return compararTFechas(f1, f2) > 0;
    }
}

static void siftUp(rep_colaDePrioridadPersona* cp, nat i) {
    while (i > 1 && esPrioritario(cp, cp->heap[i], cp->heap[i/2])) {
        intercambiar(cp, i, i/2);
        i = i/2;
    }
}

static void siftDown(rep_colaDePrioridadPersona* cp, nat i) {
    while (2*i <= cp->cantidad) {
        nat hijo = 2*i;
        if (hijo + 1 <= cp->cantidad && esPrioritario(cp, cp->heap[hijo+1], cp->heap[hijo])) {
            hijo++;
        }
        if (esPrioritario(cp, cp->heap[hijo], cp->heap[i])) {
            intercambiar(cp, i, hijo);
            i = hijo;
        } else {
            break;
        }
    }
}

TColaDePrioridadPersona crearCP(nat N) {
    rep_colaDePrioridadPersona* cp = new rep_colaDePrioridadPersona;
    cp->N = N;
    cp->cantidad = 0;
    cp->menorEsPrioritario = true;
    cp->heap = new TPersona[N + 1];
    cp->posicion = new nat[N + 1];
    
    // Inicializar desde 0 hasta N (inclusive) para evitar accesos no inicializados
    for (nat i = 0; i <= N; i++) {
        cp->posicion[i] = 0;
        if (i > 0) {
            cp->heap[i] = NULL;
        }
    }
    
    return cp;
}

void liberarCP(TColaDePrioridadPersona& cp) {
    for (nat i = 1; i <= cp->cantidad; i++) {
        liberarTPersona(cp->heap[i]);
    }
    delete[] cp->heap;
    delete[] cp->posicion;
    delete cp;
    cp = NULL;
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
    return cp->cantidad == 0;
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
    return cp->posicion[id] != 0;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona& cp) {
    cp->cantidad++;
    nat id = idTPersona(persona);
    cp->heap[cp->cantidad] = persona;
    cp->posicion[id] = cp->cantidad;
    siftUp(cp, cp->cantidad);
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
    return cp->heap[1];
}

void eliminarPrioritaria(TColaDePrioridadPersona& cp) {
    if (cp->cantidad == 0) return;
    
    nat id = idTPersona(cp->heap[1]);
    cp->posicion[id] = 0;
    liberarTPersona(cp->heap[1]);
    
    if (cp->cantidad > 1) {
        cp->heap[1] = cp->heap[cp->cantidad];
        nat id_ultimo = idTPersona(cp->heap[1]);
        cp->posicion[id_ultimo] = 1;
        siftDown(cp, 1);
    }
    cp->cantidad--;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp) {
    nat indice = cp->posicion[id];
    TEvento ev = primerEventoDeTPersona(cp->heap[indice]);
    return fechaTEvento(ev);
}

void invertirPrioridad(TColaDePrioridadPersona& cp) {
    cp->menorEsPrioritario = !cp->menorEsPrioritario;
    
    for (int i = cp->cantidad / 2; i >= 1; i--) {
        siftDown(cp, i);
    }
}