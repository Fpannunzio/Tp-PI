#ifndef __tad_h
#define __tad_h

#include <stdio.h>

typedef struct vectorCDT * vectorADT;
/* Valida que el string item coincida con un oaci valido. Luego en caso que lo sea, busca en el 
** vector resp, donde estan todos los oacis ordenados alfabeticamente, usando bsearch, el
** oaci que coincide con item y cuando llegue al nodo que corresponde con el oaci y si no es null, 
** agrega uno a cantidad de movimientos (Una vez usada la funcion imprimirEnArchivo, deja de funcionar 
** ya que el vector deja de estar ordenado alfabeticamente segun el oaci)
** Ejemplo: agregarItem recibe el vector resp ordenado y el string SAAC, el cual es un oaci valido
** lo busca con bsearch y agrega uno al nodo de dicho oaci.
** agregarItem recibe el mismo vector resp y el string SAAB, el cual es un oaci valido, pero al buscarlo
** con bsearch no lo encuentra en resp, por lo que no suma nada.
*/

void agregarItem(vectorADT resp, char * item);


vectorADT newVec(char const * file);
/* ordena el vector en base a una funcion criterio que puede ser, alfabeticamente por OACI
** o numericamente por cantidad de movimientos y en caso de igualdad por orden alfabetico de OACI
*/
void ordenaVec(vectorADT resp, int crit);

/*
**Se asume que si desea imprimir el archivo es porque se termino de usar el TAD, es por eso que se realizan los free 
**de los elementos contenidos por el vecotr dentro de esta funcion.
*/
void imprimirEnArchivo(vectorADT resp, FILE * archivo);

/* Free del tad
*/
void freeVec(vectorADT resp);

#endif
