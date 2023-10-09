#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include "juego.h"
int main (void) {
struct juego_S *p = NULL, *o = NULL;
int barcos[] = {1, 3};
int propioF=0, propioC=0, oponenteF=0, oponenteC=0, rsp=0;
srand(time(NULL));
	p = juegoInicializar (TABLERO_FILA_CANT, TABLERO_COLUMNA_CANT, barcos, sizeof (barcos) / sizeof (barcos[0]));
	if (p == NULL) {
 		printf ("Error en juegoInicializar propio\r\n");
		return (-1);
	}
	printf ("Propio\r\n");
	juegoImprimir (p);
	
	o = juegoInicializar (TABLERO_FILA_CANT, TABLERO_COLUMNA_CANT, barcos, sizeof (barcos) / sizeof (barcos[0]));
	if (o == NULL) {
 		printf ("Error en juegoInicializar propio\r\n");
		return (-1);
	}
	printf ("Oponente\r\n");
	juegoImprimir (o);

	do {
		
		//-- Mi disparo --
		juegoIA_Disparar (p, &propioF, &propioC);
		printf ("Disparo propio %d %d\r\n", propioF, propioC);
		rsp = juegoIA_RecibirDisparo (o, propioF, propioC);	//-- Le digo al oponente donde le dispare, espero la respuesta --
		juegoIA_DisparoRespuesta (p, propioF, propioC, rsp);  //-- Marco la respuesta del oponente --
		
		printf ("\r\n\r\n-- Propio --\r\n\r\n");
		juegoImprimir (p);
		
		//-- Mi disparo --
		juegoIA_Disparar (o, &oponenteF, &oponenteC);
		printf ("Disparo Oponente %d %d\r\n", oponenteF, oponenteC);
		rsp = juegoIA_RecibirDisparo (p, oponenteF, oponenteC);	//-- Le digo al oponente donde le dispare, espero la respuesta --
		juegoIA_DisparoRespuesta (o, oponenteF, oponenteC, rsp);  //-- Marco la respuesta del oponente --
		
		printf ("\r\n\r\n-- Oponente --\r\n\r\n");
		juegoImprimir (o);
		
		rsp = juegoGuardarJugada (p, propioF, propioC, oponenteF, oponenteC);
		printf ("rsp %d\r\n", rsp);

		
	} while ( juegoRevisar (p) == EN_LA_BATALLA); 
	
	
	printf ("%d\r\n", juegoRevisar (p));
	juegoGuardar (p, "jugada.txt") ;
	
	
	return (0);
}