/*=============================================================================
 * Author: Pedro Valentin Nieva <valentin9702@gmail.com>
 * Date: 2022/05/07
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP_3_EJ2.h"
#include "sapi.h"
#include "GPIO.h"
#include "RITimer.h"

/*=====[Definición de variables globales]=============================*/

char Led;
bool_t estado=false;
char aux;

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();
   RIT_init();
   RIT_set(100);

   Init_LED('B');
   Init_LED('1');
   Init_LED('2');
   Init_LED('3');

   Init_TEC(1);
   Init_TEC(2);
   Init_TEC(3);
   Init_TEC(4);

   Led='0';//Nuestro estado inicial es nulo, todos los leds apagados
   // ----- Repeat for ever -------------------------
   while( true ) {

	   if(Leer_TEC(1)!=true){
		   Led='B';
	   }
	   if(Leer_TEC(2)!=true){
		   Led='1';
	   }
	   if(Leer_TEC(3)!=true){
		   Led='2';
	   }
	   if(Leer_TEC(4)!=true){
		   Led='3';
	   }

   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}

void RIT_IRQHandler(void){

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
