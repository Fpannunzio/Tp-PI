#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct listaCDT{
	struct listaCDT * prox;
	struct listaCDT * ant;
	char * oaci;
	char * denom;
	int cantMov;
}listaCDT;
/*typedef Nodo * Tnodo;
typedef struct listaCDT{
	Tnodo Prim;

}*/

listaADT nuevaLista (){

	return calloc(1,sizeof(listaCDT));
}

listaADT addList(listaADT l, char *oaci){

	if (l!= NULL && strcmp(l->oaci, oaci)==0){
		l->cantMov++;
		listaADT aux=l->prox;
		aux->ant=reordenaRecur(l, l->ant,);
		aux->ant->prox=aux;

	}
}

listaADT reordenaRecur(listaADT nodo, listaADT l){
	
	int c, d;
	if((l==NULL|| (c= nodo->cantMov - l->cantMov)<0)||(c==0 && (d=strcmp(nodo->oaci, l->oaci))>0)){
		nodo->ant=l;
		if(l!=NULL)
			l->prox=nodo;

		return nodo;
	}
	nodo->prox=l;
	l->ant=reordenaRecur(nodo, l->ant);

	return l;
}










