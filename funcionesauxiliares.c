#include "funcionesauxiliares.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <ctype.h>

int calcularDia(char * fecha){
	// formula sacada de https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto's_methods

	int d,m,y;
	d = (fecha[0] - '0') * 10 + fecha[1] - '0';
	m = (fecha[3] - '0') * 10 + fecha[4] - '0';
	y = (fecha[6] - '0') * 1000 + (fecha[7] - '0') * 100 + (fecha[8] - '0') * 10 + fecha[9] - '0';

	return ( (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400) - 1) % 7;

}

int calcularLinea(char * lineaAux, char *** vector ,FILE * archivo){

	int k=0;
	lineaAux=fgets(lineaAux, MAX_TEXTO, archivo);
	
	char ** aux = malloc(BLOQUE * sizeof(char *));
	
	aux[k++] = strtok(lineaAux, ";");
	
	do{
		if(k % BLOQUE == 0)
			aux = realloc( aux, (k + BLOQUE) * sizeof(char *) );
		aux[k]=strtok(NULL,";");
	
	}while( aux[k++] !=  NULL);
	
	aux = realloc(aux, --k * sizeof(char*));
	
	*vector=aux;

	return k;
}

int obtenerLineaTokens(char * linea, char * vec[], int dim, FILE * archivo ){ 

	
	linea=fgets(linea, MAX_TEXTO, archivo);

	vec[0] = strtok(linea, ";");



	for (int i = 1; i < dim; ++i){
		vec[i]=strtok( NULL, ";" );	
	}

	if ( vec[dim-1]  == NULL )
		return 0;

	return 1;
}

int validarOACI(char *oaci){
	
	if (isalpha (oaci[0]) && isalpha(oaci[1]) && isalpha(oaci[2]) && isalpha(oaci[3]))
		return 1;
	else 
		return 0;
}
