/**	
	\file juego.c
	\brief Funciones para el manejo del tablero
	\author Jerónimo F. Atencio (jerome5416@gmail.com)
	\date 2015.10.14
	\todo 
*/
#include <stdio.h>
#include<stdlib.h>
#include "juego.h"
/**
	\fn struct juego_S *juegoInicializar (int filasCant, in columnasCant, int *barcos, int barcosCant)
	\brief funcion que incializa los tableros el del usuario y contricante
	\author federico gonzalez
	\date 2017.10.30
	\return la direccion de la structura base , en caso de falla retorna NULL
*/
                            struct juego_S *juegoInicializar (int filasCant, int columnasCant, int *barcos, int barcosCant)
{
    struct juego_S *A;
    int a;
    A =(struct juego_S *)malloc(sizeof(struct juego_S));                        if (A==NULL){                       return(NULL);       }
    A->partida=NULL;
    A->tableroPropio=(char *) malloc (sizeof(char)*filasCant*columnasCant);     if (A->tableroPropio==NULL){        return(NULL);       }
    A->tableroOponente=(char *) malloc (sizeof(char)*filasCant*columnasCant);   if (A->tableroOponente==NULL){      return(NULL);       }
    A->barcos=barcos;
    A->filasCant=filasCant;
    A->columnasCant=columnasCant;
    A->barcosCant=barcosCant;
          for(a=0;a<(TABLERO_COLUMNA_CANT*TABLERO_FILA_CANT);a++){
           A->tableroPropio[a]=AGUA;
           A->tableroOponente[a]=AGUA;
    }
    juegoIA_Barcos(A);
                    return (A);                 }
/**
	\fn void juegoImprimir (struct juego_S *p)
	\brief  muestra por pantalla los tableros 
	\author federico gonzalez
	\date 2017.10.30
	\return void
*/
                                                void juegoImprimir (struct juego_S *p){
int filas,columnas;
if(p==NULL){
    printf("error ");
}
printf("\ttablero del oponente\n\r");
    for(filas=0;filas<TABLERO_FILA_CANT;filas++){
        for (columnas=0;columnas<TABLERO_COLUMNA_CANT;columnas++){	
            printf("%c",*(p->tableroOponente+(filas*TABLERO_COLUMNA_CANT)+columnas));                    
        }
        printf("\n");           
    }
        printf("\ttablero propio\n\r");
for(filas=0;filas<TABLERO_FILA_CANT;filas++){
for (columnas=0;columnas<TABLERO_COLUMNA_CANT;columnas++){	
printf("%c",*(p->tableroPropio+(filas*TABLERO_COLUMNA_CANT)+columnas));
}           printf("\n");       }
}


/**
	\fn int juegoRevisar (struct juego_S *p)
	\brief  compureba el estado del tablero,si sigo jugando o perdi
	\author Federico Gonzalez
	\date 2/11/2017
	\return Estado del juego /-1 si ubo un error
*/
                                                int juegoRevisar (struct juego_S *p)
{
    int b,c,d,e;
    for(b=0,c=0,d=0;b<(TABLERO_COLUMNA_CANT*TABLERO_FILA_CANT);b++){
        if (*(p->tableroPropio + b) == BARCO) {                                                             c++; /*cantidad de mis barcos */      }      
        if(*(p->tableroOponente+b)==BARCO_TOCADO){d++;}
    }
    for(b=0,e=0;b<(p->barcosCant);b++){                             e+=*(p->barcos+b);          }
    
    if (d==e && c==0){         return(EMPATE);            }        
    
    else if(d==e && c!=0){          return(GANE);              }
    else if(c==0 ){               return(PERDI);             } 
    else if(c<=e && d<e){          return(EN_LA_BATALLA);     }

return(EN_LA_BATALLA);}
/**
	\fn int juegoGuardarJugada (struct juego_S *p, int filaPropio, int columnaPropio, int filaOponente, int columnaOponente)
	\brief guarda dentro de una lista doble enlazada las partidas
	\author Federico Gonzalez
	\date 2/11/2017
	\return 1 en caso de guardar correctamente ,un numero negativo en caso de error
*/
                        int juegoGuardarJugada (struct juego_S *p, int filaPropio, int columnaPropio, int filaOponente, int columnaOponente)
{
    struct partida_S *A,*N,*B,*C;
    A=(struct partida_S *)malloc (sizeof(struct partida_S));
                N=p->partida;
                A->propio[0] = filaPropio;
                A->propio[1]=columnaPropio;
                A->oponente[0]=filaOponente;
                A->oponente[1]=columnaOponente;
                A->sig=NULL;
                if (N==NULL)       {
                A->sig=NULL;
                A->ant=NULL;
                p->partida=A;
    }
if(N!=NULL) {
		for (C=N; C!= NULL; C =C->sig) {              B=C;        }
                A->ant=B;
                B->sig=A;	
}
    	return (0);
}

/**
	\fn int juegoGuardar (struct juego_S *p, char nombre) 
	\brief guardar la lista doble enlazada dentro de un archivo
	\author Federico Gonzalez
	\date 3/11/2017
	\return cantidad de byts escritos o en caso de error un numero negativo
*/
                int juegoGuardar (struct juego_S *p, char *nombre) 
{
    FILE *f=fopen(nombre,"w");
    if (f==NULL){
        return(-1);}
struct partida_S *C,*N;
int a=0;
N=p->partida;
    for (C=N; C!= NULL; C =C->sig) {
        fprintf(f,"mi jugada Fila : ");
         a+=fprintf(f,"%d",C->propio[0]);
         fprintf(f,"\t Columna : ");
         a+=fprintf(f,"%d",C->propio[1]);
         fprintf(f,"\n\r\n\r");
         fprintf(f,"Jugada oponente Fila : ");
         a+=fprintf(f,"%d",C->oponente[0]);
         fprintf(f,"\t Columna : ");
         a+=fprintf(f,"%d",C->oponente[1]);
         fprintf(f,"\n\r\n\r");
    }
	return (a);
}
