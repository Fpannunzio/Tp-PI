#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANT_PARAMETROS 3
#define MAX_TEXTO 1000
#define PARAMETROS_MOV 10
#define CANT_CARACTERISTICA_VUELO 2
#define CANT_CLASE_VUELO 3
#define POS_CARACTERISTICA_VUELO 3
#define POR_CLASE_VUELO 2

void validarImput(int argc){

	if (argc != CANT_PARAMETROS){
		printf("Cantidad de Parametros Incorrecta \n");
		exit (1);
	}
}


int obtenerLineaTokens(char * linea, char * vec[], int dim, FILE * archivo ){ // Recibe los vectores para no tener que generar y borrar espacio muchas veces

	linea=fgets(linea, MAX_TEXTO, archivo);
	
	if (strchr(linea,';') == NULL )
		return 0;

	vec[0] = strtok(linea, ";");

	for (int i = 1; i < dim; ++i)
		vec[i]=strtok( NULL, ";" );	

	return 1;
}

//Q3-Ans es una matriz con las 6 posibles combinaciones
void  query3Back ( char *vecMov[], char * Q3Carac[], char * Q3Clase[], int Q3Ans[][CANT_CLASE_VUELO]){

	int x,y,i;

	// Comparamos solo la primer letra ya que es informacion suficiente
	x = vecMov[POS_CARACTERISTICA_VUELO][0] ==  Q3Carac[1][0]; // Si es verdadero entonces x = 1, por lo tanto es un vuelo internacional, caso contrario es de cabotaje

	for (i = 0; i < CANT_CLASE_VUELO; ++i)
		if(vecMov[POR_CLASE_VUELO][0] == Q3Clase[i][0])
			y = i;

	Q3Ans[x][y]++;
}

void query3Front(int Q3Ans[][CANT_CLASE_VUELO], char * Q3Carac[], char * Q3Clase[]){
	int i,j;
	for (i = 0; i < CANT_CARACTERISTICA_VUELO; ++i)
	{
		for(j=0; j<CANT_CLASE_VUELO;j++)
			printf("%s;%s;%d\n", Q3Carac[i], Q3Clase[j], Q3Ans[i][j]);	
	}
}

int main(int argc, char const *argv[]){
	int flag = 1;
	validarImput(argc);
	FILE * archMov = fopen(argv[1], "r");
	char * vecMov[PARAMETROS_MOV]; // vecMov contiene cada las caracteristicas de cada movimiento
	char * lineaAux = malloc(MAX_TEXTO);
	int Q3Ans[CANT_CARACTERISTICA_VUELO][CANT_CLASE_VUELO]={{0,0,0},{0,0,0}};

	char * Q3Carac[]={"Cabotaje", "Internacional"};
	char * Q3Clase[]={"Regular", "No Regular", "Vuelo Privado"}; 

	obtenerLineaTokens(lineaAux,vecMov,PARAMETROS_MOV,archMov);
	while(! feof(archMov) && flag){
		flag = obtenerLineaTokens(lineaAux,vecMov,PARAMETROS_MOV,archMov);
		if( flag )
			query3Back(vecMov,Q3Carac,Q3Clase,Q3Ans);
	}
	query3Front(Q3Ans,Q3Carac,Q3Clase);




	return 0;
}















