/*=============================================================================
 * Author: Pedro Valentin Nieva <valentin9702@gmail.com>
 * Date: 2022/05/07
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP_3_EJ2b.h"
#include "sapi.h"
#include "GPIO.h"
#include "RITimer.h"

/*=====[Definición de variables globales]=============================*/

int Opcion;
bool_t estado=false;
int aux, Led;
uint32_t ms=100;

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();
   RIT_init();
   RIT_set(ms);

   Init_LED('B');
   Init_LED('1');
   Init_LED('2');
   Init_LED('3');

   Init_TEC(1);
   Init_TEC(2);
   Init_TEC(3);
   Init_TEC(4);
   // ----- Repeat for ever -------------------------
   while( true ) {

	   if(Leer_TEC(1)!=true && Opcion>0){
		   while(Leer_TEC(1)!=true);
		   Opcion--;
	   }
	   if(Leer_TEC(2)!=true && Opcion<3){
		   while(Leer_TEC(2)!=true);
		   Opcion++;
   	   }
   	   if(Leer_TEC(3)!=true && ms>=200){
   		while(Leer_TEC(3)!=true);
   		   ms=ms-100;
   	   }
   	   if(Leer_TEC(4)!=true){
   		while(Leer_TEC(4)!=true);
   		   ms=ms+100;
   	   }
   	switch(Opcion){
   		case 0:
   			Led='B';
   			break;
   		case 1:
   			Led='1';
   			break;
   		case 2:
   			Led='2';
   			break;
   		case 3:
   			Led='3';
   			break;
   	}


   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}

void RIT_IRQHandler(void){
	RIT_set(ms);
	if(aux!=Led){
		Apagar('1');
		Apagar('2');
		Apagar('3');
		Apagar('B');
		estado=false;
	}
	if(estado==false){
		Encender(Led);
		estado=true;
	} else {
		Apagar(Led);
		estado=false;
	}
	aux=Led;
	RIT_clean();
}
