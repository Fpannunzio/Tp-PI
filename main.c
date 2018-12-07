//Definiciones
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <math.h>
	#include "tad.h"
	#include "funcionesauxiliares.h"

	// Las constantes llamadas POS_*** son utilizadas dentro del vector vecMov para elegir que informacion se utilizará
	
	#define POS_FECHA 0
	#define POS_CLASE_VUELO 2
	#define POS_CARACTERISTICA_VUELO 3
	#define POS_TIPO_MOV 4
	#define POS_OACI_ORGIGEN 5
	#define POS_OACI_DESTINO 6	

	#define CANT_PARAMETROS 3
	#define CANT_CARACTERISTICA_VUELO 2
	#define CANT_CLASE_VUELO 3
	#define CANT_DIAS 7

void validarEntrada(int argc){

	if (argc != CANT_PARAMETROS){
		printf("Cantidad de Parametros Incorrecta \n");
		exit (1);
	}
}

void query1front(vectorADT Q1Ans){

	FILE * arch=fopen("./movimientos_aeropuerto.csv","w+");
	ordenaVec(Q1Ans,2);
	imprimirEnArchivo(Q1Ans,arch);
	fclose(arch);
	freeVec(Q1Ans);
}

void query2Front(int Q2Ans[][CANT_CARACTERISTICA_VUELO]){
	
	int i;

	FILE * aux=fopen("./dia_semana.csv","w+");

	char * dias[CANT_DIAS] = {"lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"};

	fprintf(aux,"%-15s;%-15s;%-15s;%-15s\n","dias","cabotaje","internacional","total");
	for (i = 0; i < CANT_DIAS; ++i)
		fprintf(aux,"%-15s;%-15d;%-15d;%-15d\n", dias[i], Q2Ans[i][0], Q2Ans[i][1], Q2Ans[i][0] + Q2Ans[i][1]);

	fclose(aux);
}

void query3Front(int Q3Ans[][CANT_CLASE_VUELO], char * vecCarac[], char * vecClase[]){
	
	FILE * aux=fopen("./composicion.csv","w+");
	int i,j;

	fprintf(aux, "%-25s;%-20s;%-10s\n","Clasificacion de Vuelo", "Clase de vuelo", "Movimientos");

	for (i = 0; i < CANT_CARACTERISTICA_VUELO; ++i)
		for(j=0; j<CANT_CLASE_VUELO;j++)
			fprintf(aux,"%-25s;%-20s;%-10d\n", vecCarac[i], vecClase[j], Q3Ans[i][j]);	
	
	fclose(aux);
}

void query1back(vectorADT Q1Ans, char * vecMov[],char *vecTipoMov[]){
	
	int k;
	
	if(vecMov[POS_TIPO_MOV][0] == vecTipoMov[1][0]) // Compara la primer letra para ver si es un Despegue 
		k=POS_OACI_ORGIGEN;								// y tomar el OACI de Destino
	else												// Caso contrario es un aterrizaje entonces 
		k=POS_OACI_DESTINO;								// toma el OACI de Destino

	agregarItem(Q1Ans, vecMov[k]);
}

void query2back(char *vecMov[], int Q2Ans[][CANT_CARACTERISTICA_VUELO], char * carac[]){
	
	int i=0;
	int dia=calcularDia(vecMov[POS_FECHA]);
	if(toupper(vecMov[POS_CARACTERISTICA_VUELO][0]) == 'N')
		return;

	// Solo compara la primer letra de "cabotaje" o "internacional"
	if(vecMov[POS_CARACTERISTICA_VUELO][0] != carac[0][0])
		i++;

	Q2Ans[dia][i]++;
}

void query3Back ( char *vecMov[], char * vecCarac[], char * vecClase[], int Q3Ans[][CANT_CLASE_VUELO]){

	int x,y,i;
 	// Si es N el vuelo es N/A no se carga entonces tengo que salir
	if(toupper(vecMov[POS_CARACTERISTICA_VUELO][0]) == 'N')
		return;

	// Comparamos solo la primer letra ya que es informacion suficiente.
	// Si es verdadero entonces x = 1, por lo tanto es un vuelo internacional, caso contrario es de cabotaje.
	x = vecMov[POS_CARACTERISTICA_VUELO][0] ==  vecCarac[1][0]; 


	//Comparamos la primer letra para ver que clase de vuelo es.
	for (i = 0; i < CANT_CLASE_VUELO; ++i)
		if(vecMov[POS_CLASE_VUELO][0] == vecClase[i][0])
			y = i;

	Q3Ans[x][y]++;
}

int main(int argc, char const *argv[]){
		
	validarEntrada(argc);
	
	FILE * archMov = fopen(argv[1], "r");

	int c, flag = 1;

	char lineaAux[MAX_TEXTO];
	// vecMov contiene la informacion de un movimiento (linea de texto dentro del archivo)
	char ** vecMov; 
	
	vectorADT Q1Ans=newVec(argv[2]);
	int Q3Ans[CANT_CARACTERISTICA_VUELO][CANT_CLASE_VUELO]={{0,0,0},{0,0,0}};
	int Q2Ans[CANT_DIAS][CANT_CARACTERISTICA_VUELO]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

	char * vecTipoMov[]={"Aterrizaje","Despegue"};
	char * vecCarac[]={"Cabotaje", "Internacional"};
	char * vecClase[]={"Regular", "No Regular", "Vuelo Privado"}; 

	//Leer primero la linea que tiene la Informacion de los campos y que no se usara para el calculo de los movmientos.
	
	int cantParametros=calcularLinea(lineaAux,&vecMov,archMov);
	
	while( ! (c = feof(archMov) ) && flag){
		flag= obtenerLineaTokens(lineaAux,vecMov,cantParametros,archMov);
		
		if(flag){
			query3Back(vecMov,vecCarac,vecClase,Q3Ans);
			query2back(vecMov, Q2Ans, vecCarac);
			query1back(Q1Ans,vecMov,vecTipoMov);
		}
	}
	
	query3Front(Q3Ans,vecCarac,vecClase);
	query2Front(Q2Ans);
	query1front(Q1Ans);
	free(vecMov);
	fclose(archMov);

	return 0;
}
