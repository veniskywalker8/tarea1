#include "../include/fecha.h"

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


      
    /****** Fin de parte Parte 3.9 *****/
}



int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */
    if (fecha1->anio > fecha2->anio || (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) || (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia)){
        res = 1;
    }
    else if (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia == fecha2->dia) {
        res = 0;
    }
    else{
        res = -1;
    }

    /****** Fin de parte Parte 3.10 *****/
    return res;
}