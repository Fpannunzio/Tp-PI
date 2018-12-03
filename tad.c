//Def
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include "tad.h"
	#include "funcionesauxiliares.h"

	#define BLOQUEVEC 10
	
	typedef struct node{
		int cantMov;
		char oaci[DIM_OACI];
		char * desc;
	}node;

	typedef struct vectorCDT{
		int dim;
		node * vec;
	}vectorCDT;

static int compNumAlf(const node * e1, const  node * e2 );

static node completaVec( char * vecLinea[]);

static int compAlfabetico(const node * e1, const  node * e2 );

vectorADT newVec(char const * file){
	
	FILE * f = fopen(file, "r");
	int flag=1, k=0;
	
	vectorADT resp = calloc(1,sizeof(vectorCDT));

	//obtenerLinea 
	char lineaAux[MAX_TEXTO];
	char ** vecLinea;

	//Calcular cantidad elementos aeropuertos.csv
	int cantParam=calcularLinea(lineaAux,&vecLinea,f);

	while(! feof(f) && flag){
		
		flag = obtenerLineaTokens(lineaAux,vecLinea,cantParam,f);
		
		if( flag && validarOACI(vecLinea[POS_OACI]) ){
			
			if(k%BLOQUEVEC == 0)
				resp->vec=realloc(resp->vec, (k + BLOQUEVEC) * sizeof(node));

			resp->vec[k++]=completaVec(vecLinea);
		}
	}
	
	resp->vec = realloc(resp->vec, k * sizeof(node));
	resp->dim=k;
	free(vecLinea);
	fclose(f);
	ordenaVec(resp,1);
	return resp;
}

void freeVec(vectorADT resp){

	free(resp);
}

void ordenaVec(vectorADT resp, int crit){

	int (* criterio)(const void * , const void * );
	if(crit == 1)
		criterio = (int (*)(const void * , const void * ) ) compAlfabetico;
	else
		criterio = (int (*)(const void * , const void * ) ) compNumAlf;

	qsort(resp->vec, resp->dim, sizeof(node), criterio );
}

void agregarItem(vectorADT resp, char * item){

	if(!validarOACI(item))
		return;
	node aux;
	strcpy(aux.oaci,item);
	node * elem = bsearch(&aux, resp->vec, resp->dim, sizeof(node), (int (*)(const void * , const void * ) )compAlfabetico);
	if(elem != NULL)
		elem->cantMov++;
	else
		printf("No se encontro el OACI %s en la planilla Aeropuertos.\n",item);
}

void imprimirEnArchivo(vectorADT resp, FILE * archivo){

	fprintf(archivo, "%-10s;%-60s;%-20s\n","OACI","DESCRIPCION","CANT MOVIMIENTOS");
	for (int i = 0; i < resp->dim; ++i)
	{
		fprintf(archivo, "%-10s;%-60s;%-20d\n",resp->vec[i].oaci,resp->vec[i].desc,resp->vec[i].cantMov );
		free(resp->vec[i].desc);
	}
	free(resp->vec);
}

static node completaVec( char * vecLinea[]){
	node aux;
	aux.cantMov=0;
	strcpy(aux.oaci,vecLinea[POS_OACI]);
	aux.desc = malloc(strlen(vecLinea[POS_DESC]) + 1);
	strcpy(aux.desc,vecLinea[POS_DESC]);
	return aux;	
}

static int compAlfabetico(const node * e1, const  node * e2 ){

	return strcmp(e1->oaci,e2->oaci);
}

static int compNumAlf(const node * e1, const  node * e2 ){

	int c= e1->cantMov - e2->cantMov;
	if( c != 0 )
		return c*-1;
	else
		return strcmp(e1->oaci,e2->oaci);
}


