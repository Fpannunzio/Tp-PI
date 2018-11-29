//Definiciones
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <math.h>

	// Las constantes llamadas POS_*** son utilizadas dentro del vector vecMov para elegir que informacion se utilizará
	#define POS_CARACTERISTICA_VUELO 3
	#define POS_CLASE_VUELO 2
	#define POS_FECHA 0

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
	if(isspace(linea[0]))
		return 0;

	vec[0] = strtok(linea, ";");


	for (int i = 1; i < dim; ++i)
		vec[i]=strtok( NULL, ";" );	

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
void query3Back ( char *vecMov[], char * Q3Carac[], char * Q3Clase[], int Q3Ans[][CANT_CLASE_VUELO]){

	int x,y,i;

	// Comparamos solo la primer letra ya que es informacion suficiente
	x = vecMov[POS_CARACTERISTICA_VUELO][0] ==  Q3Carac[1][0]; // Si es verdadero entonces x = 1, por lo tanto es un vuelo internacional, caso contrario es de cabotaje

	for (i = 0; i < CANT_CLASE_VUELO; ++i)
		if(vecMov[POS_CLASE_VUELO][0] == Q3Clase[i][0])
			y = i;

	Q3Ans[x][y]++;
}

void query3Front(int Q3Ans[][CANT_CLASE_VUELO], char * Q3Carac[], char * Q3Clase[]){
	
	FILE * aux=fopen("./Salida/composicion.csv","w+");
	int i,j;
	fprintf(aux, "%-25s;%-20s;%-10s\n","Clasificacion de Vuelo", "Clase de vuelo", "Movimientos");
	for (i = 0; i < CANT_CARACTERISTICA_VUELO; ++i)
	{
		for(j=0; j<CANT_CLASE_VUELO;j++)
			fprintf(aux,"%-25s;%-20s;%-10d\n", Q3Carac[i], Q3Clase[j], Q3Ans[i][j]);	
	}

	fclose(aux);
}

int main(int argc, char const *argv[]){
	
	int flag = 1;
	validarImput(argc);
	FILE * archMov = fopen(argv[1], "r");
	char * vecMov[PARAMETROS_MOV]; // vecMov contiene la informacion de un movimiento (linea de texto dentro del archivo)
	char * lineaAux = malloc(MAX_TEXTO);
	int Q3Ans[CANT_CARACTERISTICA_VUELO][CANT_CLASE_VUELO]={{0,0,0},{0,0,0}};
	int Q2Ans[CANT_DIAS][CANT_CARACTERISTICA_VUELO]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

	char * Q3Carac[]={"Cabotaje", "Internacional"};
	char * Q3Clase[]={"Regular", "No Regular", "Vuelo Privado"}; 

	obtenerLineaTokens(lineaAux,vecMov,PARAMETROS_MOV,archMov);
	while(! feof(archMov) && flag){
		flag= obtenerLineaTokens(lineaAux,vecMov,PARAMETROS_MOV,archMov);
		if(flag){
			query3Back(vecMov,Q3Carac,Q3Clase,Q3Ans);
			query2back(vecMov, Q2Ans, Q3Carac);
		}
	}
	query3Front(Q3Ans,Q3Carac,Q3Clase);
	query2Front(Q2Ans);
	fclose(archMov);()

	return 0;
}

















