#ifndef __tad_h
#define __tad_h

#include <stdio.h>

typedef struct vectorCDT * vectorADT;


void agregarItem(vectorADT resp, char * item);


vectorADT newVec(char const * file);
/* ordena el vector en base a una funcion criterio que puede ser, alfabeticamente por OACI
** o numericamente por cantidad de movimientos y en caso de igualdad por orden alfabetico de OACI
*/
void ordenaVec(vectorADT resp, int crit);

/* Se asume que si desea imprimir el archivo es porque se termino de usar el TAD, es por eso que se realizan los free 
** de los elementos contenidos por el vector dentro de esta funcion.
*/
void imprimirEnArchivo(vectorADT resp, FILE * archivo);

/* Free del tad
*/
void freeVec(vectorADT resp);
#endif //__tad_h
