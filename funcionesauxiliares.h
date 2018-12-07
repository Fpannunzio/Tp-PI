#ifndef _funcionesauxiliares_h
#define _funcionesauxiliares_h
//Defs
	#define DIM_OACI 5
	#define MAX_TEXTO 2000
	#define POS_OACI 1
	#define POS_DESC 4
	#define BLOQUE 5

	#include <stdio.h>

/* Utiliza la primer linea del archivo para calcular la cantidad de columnas que tiene el archivo
*/
int calcularLinea(char * lineaAux, char *** vector ,FILE * archivo);

/* La funcion se encarga de recibir el archivo y un vector, y rellena a este con la informacion correspondiente
** a una linea de informacion. en cada celda del vector se encuentra un puntero hacia una seccion de esta
** ya que cuando finaliza el ciclo de strtok() la linea queda de esta forma:
** "Fecha/0Hora Movimiento HHMM/0Clase de Vuelo/0Clasificaci?n Vuelo/0Tipo de Movimiento/0...."
** Recibe los vectores para no tener que generar y borrar espacio muchas veces ya que se conoce la dimension necesaria.
*/
int obtenerLineaTokens(char * linea, char * vec[], int dim, FILE * archivo );

/* La funcion se encarga de validar si la cadena de caracteres representa un oaci valido, 
** siendo asi aquel que empieza con S
** y su tercer caracter es una letra.
*/

int validarOACI(char *oaci);

/* Formula para calcular que dia de la semana fue una fecha en particular 
** recibiendo un string de la forma dd/mm/aaaa.
*/
int calcularDia(char * fecha);


#endif
