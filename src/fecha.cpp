#include "../include/fecha.h"


nat largoMes[13] = {
    0,  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31  
};

//+AUXILIAR
bool esBisiesto(int anio);
nat convertirFecha(TFecha fecha);

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 1 //////
///////////////////////////////////

struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
	nuevaFecha = new rep_fecha;
	nuevaFecha->dia = dia;
	nuevaFecha->mes = mes;
	nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    if (fecha == nullptr) return;
    delete fecha;
    fecha = nullptr;
}

void imprimirTFecha(TFecha fecha) {
    if (fecha == nullptr) return;
	printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
}


void aumentarTFecha(TFecha &fecha, nat dias) {
    if (fecha == nullptr) return;
    //- sumar días
    fecha->dia+=dias;
    //? - WHILE
    nat corte = (fecha->mes == 2 && esBisiesto(fecha->anio))
    ? largoMes[fecha->mes] + 1/// febrero bisiesto → 29
    : largoMes[fecha->mes];   /// resto de los casos
    do {
        //- si días > CORTE => cambio mes
        if (fecha->dia>corte){
            fecha->dia -= corte;
            fecha->mes++;
        }
        //- si M>12 ANIO++
        if (fecha->mes>12){
            fecha->mes = 1;
            fecha->anio++;
        }
        //- elegir CORTE en base al mes [M=2 => 28]
        corte = largoMes[fecha->mes];
        //- comprobar bisiestos
        if (fecha->mes == 2 && esBisiesto(fecha->anio)) 
            corte++;
    }while(fecha->dia>corte);

}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
     int res = 0;
    nat f1 = convertirFecha(fecha1);
    nat f2 = convertirFecha(fecha2);

    if (f1 > f2) {
        res = 1;
    }
    else if (f1 == f2) {
        res = 0;
    }
    else {
        res = -1;
    }
    return res;
}

//+AUXILIARES
bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
nat convertirFecha(TFecha fecha) {
    return fecha->anio * 10000 + fecha->mes * 100 + fecha->dia;
}

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
    TFecha copia = crearTFecha(fecha->dia, fecha->mes, fecha->anio);
    return copia;
}

