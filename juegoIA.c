#include"juegoIA.h"
#include"juego.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
/**
	\fn int juegoIA_Barcos (struct juego_S *p)
	\brief funcion que acomoda los barcos
	\author federico gonzalez
	\date 2017.11.4
	\return 1 si acomoda los barcos,-1 si no pudo o no hay barcos para acomodar,-2 si p es NULL,-3 si tablero propio NULL,-4 si tablero oponente es NULL,-5 si lista de barcos es NULL
*/
int juegoIA_Barcos (struct juego_S *p){
    if(p==NULL){                                 return(-2);         }
    if (p->tableroPropio==NULL){                 return(-3);         }
    if(p->tableroOponente==NULL){                return(-4);         }
    if(p->barcos==NULL){                         return(-5);         }
char *A=p->tableroPropio;
int No_Pudo=0;
int a,b,ejec,filas,columnas;
for (ejec=0;ejec<(p->barcosCant);){     filas= NumAlea();               columnas= NumAlea(); 
    if((ejec%2)==0){                                                                         
                                    //-Barco verticales--//
    if(Verif(filas,columnas,*(p->barcos+ejec),A)==0){ 
    for (b=0,a=columnas;b<*(p->barcos+ejec);b++){          *(A+(filas*TABLERO_COLUMNA_CANT)+a)=BARCO;             a+=TABLERO_COLUMNA_CANT;   }
                                ejec++;             } 
else    {                       No_Pudo++;          }}

            else if((ejec%2)>0){                      

                //--Barcos horizontal--//
    if(Verif_2(filas,columnas,*(p->barcos+ejec),A)==0){
    a=columnas;       for (b=0;b<*(p->barcos+ejec);b++,a++){          *(A+(filas*TABLERO_COLUMNA_CANT)+a)=BARCO; }     ejec++;             }
else    {                       No_Pudo++;          }}


if (No_Pudo==900){              return(-1);         }
}                               return(1);          }
/**
	\fn int NumAlea(void)
	\brief funcion de numeros aleatorios
	\author federico gonzalez
	\date 2017.11.15
	\return un numero aleatorio dentro de un rango donde pueda ser introducido el barco
*/
int NumAlea(void){          int a,b=(TABLERO_COLUMNA_CANT);             a=rand() % b;              return (a);     }
/**
	\fn int Verif(int filas,int columnas,int barco,char *A)
	\brief funcion que verifica si es posible introducir el barco en las cordenadas especificadas
	\author federico gonzalez
	\date 2017.11.15
	\return -1 si no puede poner los barcos ,0 si es posible ponerlos
*/
                    int Verif(int filas,int columnas,int barco,char *A){
                        //--Poner barcos verticales--//
int a,b,c,d;
b=columnas;
b-=1;
c=columnas;
c+=1;
d=filas;
d-=1;
if (*(A+(((d)*TABLERO_COLUMNA_CANT)+columnas))==BARCO) {           return(-1);  }
for (a=0;a<=barco;a++,filas++){
    if (*(A+((filas*TABLERO_COLUMNA_CANT)+columnas))==BARCO) {     return(-1);  }
    if (*(A+((filas*TABLERO_COLUMNA_CANT)+b))==BARCO)        {     return(-1);  }
    if (*(A+((filas*TABLERO_COLUMNA_CANT)+c))==BARCO        ){     return(-1);  }
}
return(0);}

/**
	\fn int juegoIA_RecibirDisparo(struct juego_S *p,int fila,int columna)
	\brief funcion que resibe disparos
	\author federico gonzalez
	\date 2017.11.15
	\return respuesta al disparo ,<0 en caso de error
*/
int juegoIA_RecibirDisparo(struct juego_S *p,int fila,int columna){
    char *A=p->tableroPropio;
    int N;
    if(fila>TABLERO_FILA_CANT || columna>TABLERO_COLUMNA_CANT){return(FUERA_DE_TABLERO);}
        if(*(A+(fila*TABLERO_COLUMNA_CANT)+columna)==AGUA_TOCADO){          return(REPETIDO);           }
        if(*(A+(fila*TABLERO_COLUMNA_CANT)+columna)==BARCO_TOCADO){         return(REPETIDO);           }
        if(*(A+(fila*TABLERO_COLUMNA_CANT)+columna)==AGUA){
            *(A+(fila*TABLERO_COLUMNA_CANT)+columna)=AGUA_TOCADO;           return(AGUA_TORPEDO);       }
        if(*(A+(fila*TABLERO_COLUMNA_CANT)+columna)==BARCO){
            
                                        N=contr(A,fila,columna);
                                        
        if(N==TOCADO_Y_HUNDIDO){
            *(A+(fila*TABLERO_COLUMNA_CANT)+columna)=BARCO_TOCADO;          return(TOCADO_Y_HUNDIDO);   }
        else if(N==TOCADO){
                    *(A+(fila*TABLERO_COLUMNA_CANT)+columna)=BARCO_TOCADO;  return(TOCADO);     }   
                                                                            return(TOCADO);     }
                                                                            
                                                                            return(-1); }
  /**
	\fn int contr(char *A,int fila,int columna)
	\brief funcion que revisa si se hundio mi barco o no 
	\author federico gonzalez
	\date 2017.11.15
	\return devuelve TOCADO_Y_HUNDIDO si hundieron mi barco o TOCADO si solo fue tocado
*/
                                    int contr(char *A,int fila,int columna){
int i,e,R;
                for (i = columna + 1,e=0; i <= TABLERO_COLUMNA_CANT; i++,e++) {
        if (*(A + (fila*TABLERO_COLUMNA_CANT)+i)==BARCO) {
             return (TOCADO);
        }
        if (*(A + (fila*TABLERO_COLUMNA_CANT)+i)==AGUA) {
             break;
        } //SI E >0 ENTONCES ENCONTRO E BARCOS HUNDIDOS
    }
                for (i = columna-1,R=0; i >= 0 ; i--,R++) {
    if (*(A + (fila*TABLERO_COLUMNA_CANT)+i)==BARCO) {
             return (TOCADO);
        } 
        if (*(A + (fila*TABLERO_COLUMNA_CANT)+i)==AGUA) {
             break;     }
                }       //SI R>0 ENTONCES ENCONTRO BARCOS HUNDIDOS 
    if((e!=0 &&R!=0 )||(e!=0 && R==0)|| (e==0 && R!=0)){
        return(TOCADO_Y_HUNDIDO);
    }
                for (i=fila-1,e=0 ; i>=0;i--,e++){
    if (*(A + (i*TABLERO_COLUMNA_CANT)+columna)==BARCO) {           return (TOCADO);    }
        if (*(A + (fila*TABLERO_COLUMNA_CANT)+i)==AGUA) {           break;              }
                }
                
                for(i=fila+1,R=0; i<=TABLERO_FILA_CANT ;i++,R++){
    if (*(A + (i*TABLERO_COLUMNA_CANT)+columna)==BARCO) {               return (TOCADO);    }
        if (*(A + (i*TABLERO_COLUMNA_CANT)+columna)==AGUA) {            break;              }
}
if((e!=0 &&R!=0 )||(e!=0 && R==0)|| (e==0 && R!=0)){
        return(TOCADO_Y_HUNDIDO);
    }
            return(-1);}
            /**
	\fn int juegoIA_Disparar(struct juego_S *p,int *fila,int *columna)
	\brief funcion que genera cordenadas
	\author federico gonzalez
	\date 2017.11.16
	\return devuelve 0 en caso de poder disparar o numero negativo indicando error
*/
                    int juegoIA_Disparar (struct juego_S *p, int *fila, int *columna){
        char *TableEL =p->tableroOponente;
    if(p==NULL){                            return(-1);         }
    if(TableEL==NULL){                      return(-1);         }
    if((*fila)>TABLERO_FILA_CANT){          return(-1);         }
    if((*columna)>TABLERO_COLUMNA_CANT){    return(-1);         }
    if(*fila==TABLERO_FILA_CANT && *columna==TABLERO_COLUMNA_CANT){
        *columna=0;     *fila=0;            return(0);          }
    else if((*columna)>=(TABLERO_COLUMNA_CANT)){
        (*columna)=0;   (*fila)+=1;         return(0);          }
    else if((*fila)>=TABLERO_FILA_CANT){
        *fila=0;        *columna=0;         return(0);          }
        
        *columna+=1;                        return(0);          }
/**
	\fn int juegoIA_DispararRespuesta(struct juego_S *p,int fila,int columna,int respuesta)
	\brief funcion que resibe cordenadas de un ataque y la respuesta a dicho ataque y guarda en tableroOponente
	\author federico gonzalez
	\date 2017.11.16
	\return 0 si todo salio bien ,un numero negativo indicando error
*/
                int juegoIA_DisparoRespuesta(struct juego_S *p,int fila,int columna,int respuesta){
    if(p==NULL){                                                                                                    return(-1);     }
    if(p->tableroOponente==NULL){                                                                                   return(-1);     }
    char *A=p->tableroOponente;
    
    if(respuesta==AGUA_TORPEDO){                *(A+(fila*TABLERO_COLUMNA_CANT)+columna)=AGUA_TOCADO;               return(0);      }
    if(respuesta==TOCADO){                      *(A+(fila*TABLERO_COLUMNA_CANT)+columna)=BARCO_TOCADO;              return(0);      }
    if(respuesta==TOCADO_Y_HUNDIDO){            *(A+(fila*TABLERO_COLUMNA_CANT)+columna)=BARCO_TOCADO;              return(0);      }
    if(respuesta==REPETIDO){                                                                                        return(0);      }
    if(respuesta==FUERA_DE_TABLERO){                                                                                return(0);      }
                return(0);  }
                
                int Verif_2(int filas,int columnas,int barco,char *A){
                    //--Poner barcos horizontal
int a,b,c;
b=filas;
if(filas!=0){b-=1;}
c=filas;
c+=1;
if ((columnas+barco)>TABLERO_COLUMNA_CANT)                   {     return(-1);}
if((*(A+(filas*TABLERO_COLUMNA_CANT)+(--columnas)))==BARCO){return(-1);}
for (a=0;a<=barco;a++,columnas++){
    if (*(A+((filas*TABLERO_COLUMNA_CANT)+columnas))==BARCO) {     return(-1);} //lee linealmente todo el tablero;
    if (*(A+((b*TABLERO_COLUMNA_CANT)+columnas))==BARCO)     {     return(-1);} //lee linealmente todo el tablero desde una fila anterior ;
    if (*(A+((c*TABLERO_COLUMNA_CANT)+columnas))==BARCO)     {     return(-1); } //lee linealmente todo el tablero desde una fila anterior;
}
return(0);
}