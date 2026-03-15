#include "../include/fecha.h"
nat largoMes[13] = {
    0,  /// índice 0 no se usa
    31, /// 1 - Enero
    28, /// 2 - Febrero (ajustar si es bisiesto)
    31, /// 3 - Marzo
    30, /// 4 - Abril
    31, /// 5 - Mayo
    30, /// 6 - Junio
    31, /// 7 - Julio
    31, /// 8 - Agosto
    30, /// 9 - Septiembre
    31, /// 10 - Octubre
    30, /// 11 - Noviembre
    31  /// 12 - Diciembre
};

//+AUXILIAR
bool esBisiesto(int anio);
nat convertirFecha(TFecha fecha);

struct rep_fecha {
    /************ Parte 2.1 ************/
    /*Escriba el código a continuación */
	nat dia, mes, anio;

    /****** Fin de parte Parte 2.1 *****/
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    /************ Parte 3.1 ************/
    /*Escriba el código a continuación */
	nuevaFecha = new rep_fecha;
	nuevaFecha->dia = dia;
	nuevaFecha->mes = mes;
	nuevaFecha->anio = anio;

    /****** Fin de parte Parte 3.1 *****/
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    /************ Parte 3.3 ************/
    /*Escriba el código a continuación */
    delete fecha;
    fecha = nullptr;
    /****** Fin de parte Parte 3.3 *****/
}

void imprimirTFecha(TFecha fecha) {
    /************ Parte 3.5 ************/
    /*Escriba el código a continuación */
	printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);

    /****** Fin de parte Parte 3.5 *****/
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    /************ Parte 3.9 ************/
    /*Escriba el código a continuación */
    /*Recuerde que las funciones auxiliares
      deben declararse antes de ser utilizadas*/
    
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
    //? END
    /****** Fin de parte Parte 3.9 *****/
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */
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
    /****** Fin de parte Parte 3.10 *****/
    return res;
}

//+AUXILIARES
bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
nat convertirFecha(TFecha fecha) {
    return fecha->anio * 10000 + fecha->mes * 100 + fecha->dia;
}
