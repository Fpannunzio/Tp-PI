#include "funcionesauxiliares.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <ctype.h>

int calcularDia(char * fecha){

	int d,m,a;
	d = (fecha[0] - '0') * 10 + fecha[1] - '0';
	m = (fecha[3] - '0') * 10 + fecha[4] - '0';
	a = (fecha[6] - '0') * 1000 + (fecha[7] - '0') * 100 + (fecha[8] - '0') * 10 + fecha[9] - '0';

	return ((d += m < 3 ? a-- : a - 2, 23*m/9 + d + 4 + a/4- a/100 + a/400) - 1) % 7;

	// int k,d,c,m,f;


	// //http://mathforum.org/dr.math/faq/faq.calendar.html

	// k= (fecha[0] - '0') * 10 + fecha[1] - '0';
	// d= (fecha[8] - '0') * 10 + fecha[9] - '0';
	// c= (fecha[6] - '0') * 10 + fecha[7] - '0';
	// m= (fecha[3] - '0') * 10 + fecha[4] - '0';
	
	// if( m <= 2 ){
	// 	d--;
	// 	m+=10;
	// }
	// else 
	// 	m-=2;

	// f = k +  (int) ( (13 * m - 1) / 5) + d + (int) d/4 + (int)c/4 - 2*c;
	
	// f = abs(f) % 7;

	// //para cambiar domingo que es 0 y queremos que sea el 6
	// if( f == 0)
	// 	f+=6;
	// else
	// 	f-=1;

	// return f ;
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

	// SI LA LINEA ESTA VACIA VEC0 DEBERIA SER NULL

	for (int i = 1; i < dim; ++i){
		vec[i]=strtok( NULL, ";" );	
	}

	if ( vec[dim-1]  == NULL )
		return 0;

	return 1;
}

int validarOACI(char *oaci){
	
	if (isalpha (oaci[0]) && isalpha(oaci[3]) && isalpha(oaci[2]))
		return 1;
	else 
		return 0;
}
