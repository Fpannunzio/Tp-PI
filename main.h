// movimientos y aeropuertos
/* se fija si la cantidad de parametros declarada en el main fue la pasada */
void validarEntrada(int argc);

/* Crea el archivo movimientos_aeropuerto.csv, en caso de que no exista, sino lo reescribe, y 
** imprime en él los datos obtenidos en Q1Ans, ordenandolos principalmente por cantidad de movimientos 
** y en segundo lugar alfabeticamente, en caso que la cantidad sea igual 
*/
void query1front(vectorADT Q1Ans);
/* Crea el archivo dia_semana.csv, en caso de que no exista, sino lo reescribe, imprime en él los
** datos obtenidos en Q2Ans, en una tabla que imprime la cantidad de movimientos por dia, diferenciando 
** segun si son de cabotaje o internacional, y por ultimo la suma de ambos 
*/

void query2Front(int Q2Ans[][CANT_CARACTERISTICA_VUELO]);
/* Crea el archivo composicion.csv, en caso de que no exista, sino lo reescribe, imprime en él los
** datos obtenidos en Q3Ans, en una tabla que imprime una tabla diferenciando entre cabotaje e 
** internacional, y segun si son regulares, no regulares, o vuelos privados, imprimiendo cuantos hay
** de cada uno
*/

void query3Front(int Q3Ans[][CANT_CLASE_VUELO], char * vecCarac[], char * vecClase[]);
/*chequea si la linea si el parametro POS_TIPO_MOV de vecMov es un aterrizaje o un despegue y usa 
** agregarItem para cargar el dato de la linea de vecCarac en Q1Ans
*/

void query1back(vectorADT Q1Ans, char * vecMov[],char *vecTipoMov[]);
/* Calcula a que dia corresponde vecMov[POS_FECHA] de lunes a domingo, y se fija de que tipo y aumenta
** el elemento de la matriz Q2Ans correspondiente
*/

void query2back(char *vecMov[], int Q2Ans[][CANT_CARACTERISTICA_VUELO], char * carac[]);
/* Se fija si el parametro vecMov[POS_CARACTERISTICA_VUELO] es de cabotaje o internacional, despues se
** compara si es regular, no regular o privado y lo carga al elemento de la matriz Q3Ans correspondiente
*/

void query3Back ( char *vecMov[], char * vecCarac[], char * vecClase[], int Q3Ans[][CANT_CLASE_VUELO]);

