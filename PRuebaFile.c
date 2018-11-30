//Definiciones
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <math.h>

	// Las constantes llamadas POS_*** son utilizadas dentro del vector vecMov para elegir que informacion se utilizará
	
	#define POS_FECHA 0
	#define POS_CLASE_VUELO 2
	#define POS_CARACTERISTICA_VUELO 3
	#define POS_TIPO_MOV 4
	#define POS_OACI_ORGIGEN 5

	#define CANT_PARAMETROS 3
	#define CANT_CARACTERISTICA_VUELO 2
	#define CANT_CLASE_VUELO 3
	#define CANT_DIAS 7

	#define MAX_TEXTO 1000
	#define PARAMETROS_MOV 10

void validarImput(int argc){

	if (argc != CANT_PARAMETROS){
		printf("Cantidad de Parametros Incorrecta \n");
		exit (1);
	}
}

// Formula para calcular que dia de la semana fue una fecha en particular recibiendo un string de la forma dd/mm/aaaa.
int calcularDia(char * fecha){

	int k,d,c,m,f;


	//http://mathforum.org/dr.math/faq/faq.calendar.html

	k= (fecha[0] - '0') * 10 + fecha[1] - '0';
	d= (fecha[8] - '0') * 10 + fecha[9] - '0';
	c= (fecha[6] - '0') * 10 + fecha[7] - '0';
	m= (fecha[3] - '0') * 10 + fecha[4] - '0';
	if( m <= 2 )
		m+=10;
	else 
		m-=2;

	f = k +  (int) ( (13 * m - 1) / 5) + d + (int) d/4 + (int)c/4 - 2*c;
	f=abs(f)%7;

	//para cambiar domingo que es 0 y queremos que sea el 6
	if( f == 0)
		f+=6;
	else
		f-=1;

	return f ;
}
/* La funcion se encarga de recibir el archivo y un vector, y rellena a este con la informacion correspondiente
** a una linea de informacion. en cada celda del vector se encuentra un puntero hacia una seccion de esta
** ya que cuando finaliza el ciclo de strtok() la linea queda de esta forma:
** "Fecha/0Hora Movimiento HHMM/0Clase de Vuelo/0Clasificaci?n Vuelo/0Tipo de Movimiento/0...."
** Recibe los vectores para no tener que generar y borrar espacio muchas veces ya que se conoce la dimension necesaria.
*/
int obtenerLineaTokens(char * linea, char * vec[], int dim, FILE * archivo ){ 

	
	linea=fgets(linea, MAX_TEXTO, archivo);

	// Este if es para validar que la linea tenga informacion y no se haya llegado al final del archivo, se puede sacar siempre y cuando el archivo de entrada no termine con una linea vacia.	
	//if(isspace(linea[0]))
	//	return 0;

	vec[0] = strtok(linea, ";");

	// SI LA LINEA ESTA VACIA VEC0 DEBERIA SER NULL

	for (int i = 1; i < dim; ++i)
		vec[i]=strtok( NULL, ";" );	

	if ( vec[dim-1]  == NULL )
		return 0;

	return 1;
}

/* Funcion encargada de procesar la informacion necesaria para el Query 2, carga las respuestas en
** la matriz Q2Ans,  
*/
void query2back(char *vecMov[], int Q2Ans[][CANT_CARACTERISTICA_VUELO], char * carac[]){
	
	int i=0;
	int dia=calcularDia(vecMov[0]);
	
	// Solo compara la primer letra de "cabotaje" o "internacional"
	if(vecMov[POS_CARACTERISTICA_VUELO][0] != carac[0][0])
		i++;

	Q2Ans[dia][i]++;
}
/* La funcion se encarga de crear el archivo de salida dia_semana.csv
*/
void query2Front(int Q2Ans[][CANT_CARACTERISTICA_VUELO]){
	
	int i;
	
	FILE * aux=fopen("./Salida/dia_semana.csv","w+");

	char * dias[CANT_DIAS] = {"lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"};

	fprintf(aux,"%-15s;%-15s;%-15s;%-15s\n","dias","cabotaje","internacional","total");
	for (i = 0; i < CANT_DIAS; ++i)
		fprintf(aux,"%-15s;%-15d;%-15d;%-15d\n", dias[i], Q2Ans[i][0], Q2Ans[i][1], Q2Ans[i][0] + Q2Ans[i][1]);

	fclose(aux);
}

//Q3-Ans es una matriz con las 6 posibles combinaciones
void query3Back ( char *vecMov[], char * vecCarac[], char * vecClase[], int Q3Ans[][CANT_CLASE_VUELO]){

	int x,y,i;

	// Comparamos solo la primer letra ya que es informacion suficiente
	x = vecMov[POS_CARACTERISTICA_VUELO][0] ==  vecCarac[1][0]; // Si es verdadero entonces x = 1, por lo tanto es un vuelo internacional, caso contrario es de cabotaje

	for (i = 0; i < CANT_CLASE_VUELO; ++i)
		if(vecMov[POS_CLASE_VUELO][0] == vecClase[i][0])
			y = i;

	Q3Ans[x][y]++;
}

void query3Front(int Q3Ans[][CANT_CLASE_VUELO], char * vecCarac[], char * vecClase[]){
	
	FILE * aux=fopen("./Salida/composicion.csv","w+");
	int i,j;
	fprintf(aux, "%-25s;%-20s;%-10s\n","Clasificacion de Vuelo", "Clase de vuelo", "Movimientos");
	for (i = 0; i < CANT_CARACTERISTICA_VUELO; ++i)
	{
		for(j=0; j<CANT_CLASE_VUELO;j++)
			fprintf(aux,"%-25s;%-20s;%-10d\n", vecCarac[i], vecClase[j], Q3Ans[i][j]);	
	}

	fclose(aux);
}

/*void filePrinting( char * filePath, char * vecTitulos[], int ** vecRespuesta,  ){

	FILE * auxFile = fopen(filePath, "w+");
}*/

//TAD
	typedef struct nodeCDT * nodeADT;

	typedef struct nodeCDT{
		int cantMov;
		char *oaci;
		char *descripcion;
		struct nodeCDT * next;
	}nodeCDT;


	nodeADT newList(){
		return NULL;
	}

	nodeADT addItem(nodeADT l, char *oaci){
		int c;
		if ( l == NULL || ( c = strcmp( l->oaci, oaci ) ) > 0 ){

			nodeADT aux = malloc(sizeof(nodeCDT));
			aux->next=l;
			aux->cantMov=1;
			aux->descripcion="hola";//obtenerDesc(oaci);
			aux->oaci=malloc(5);
			strcpy(aux->oaci,oaci);
			return aux;
		}

		if (c == 0)
			l->cantMov++;
		else 
			l->next=addItem(l->next,oaci);

		return l;
	}	


int validarOACI(char *oaci){
	if (oaci[0]=='S' && isalpha(oaci[2]))
		return 1;
	else 
		return 0;
}

void query1back( char *vecMov[], char *vecTipoMov[], nodeADT * nodeRespuesta){

	int pos=0;
	if( vecMov[POS_TIPO_MOV][0] == vecTipoMov[0][0] )
		pos++;		//Aterrizaje
	char *aux=vecMov[POS_OACI_ORGIGEN + pos];
	if (validarOACI(aux))
		*nodeRespuesta=addItem(*nodeRespuesta,aux);
}

void query1front(nodeADT nodeRespuesta){
	if(nodeRespuesta!=NULL){
		printf("OACI: %s y numero : %d \n",nodeRespuesta->oaci, nodeRespuesta->cantMov );
		query1front(nodeRespuesta->next);
	}
}



int main(int argc, char const *argv[]){
	
	validarImput(argc);
	FILE * archMov = fopen(argv[1], "r");

	int c,flag = 1;
	char * vecMov[PARAMETROS_MOV]; // vecMov contiene la informacion de un movimiento (linea de texto dentro del archivo)
	char * lineaAux = malloc(MAX_TEXTO);
	
	int Q3Ans[CANT_CARACTERISTICA_VUELO][CANT_CLASE_VUELO]={{0,0,0},{0,0,0}};
	int Q2Ans[CANT_DIAS][CANT_CARACTERISTICA_VUELO]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

	char * vecTipoMov[]={"Aterrizaje","Despegue"};
	char * vecCarac[]={"Cabotaje", "Internacional"};
	char * vecClase[]={"Regular", "No Regular", "Vuelo Privado"}; 

	//Leer primero la linea que tiene la Informacion de los campos y que no se usara para el calculo de los movmientos.
	obtenerLineaTokens(lineaAux,vecMov,PARAMETROS_MOV,archMov);
	nodeADT Q1=newList();
	
	while( ! (c = feof(archMov) ) && flag){
		flag= obtenerLineaTokens(lineaAux,vecMov,PARAMETROS_MOV,archMov);
		//printf("ORIGEN %s DESTINO %s \n",vecMov[POS_OACI_ORGIGEN], vecMov[POS_OACI_ORGIGEN + 1] );
		if(flag){
			query3Back(vecMov,vecCarac,vecClase,Q3Ans);
			query2back(vecMov, Q2Ans, vecCarac);
			query1back(vecMov,vecTipoMov, &Q1);
		}
	}
	query3Front(Q3Ans,vecCarac,vecClase);
	query2Front(Q2Ans);
	query1front(Q1);
	fclose(archMov);

	return 0;
}




