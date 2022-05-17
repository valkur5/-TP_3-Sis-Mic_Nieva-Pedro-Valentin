/*=============================================================================
 * Author: Pedro Valentin Nieva <valentin9702@gmail.com>
 * Date: 2022/05/07
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP_3.h"
#include "sapi.h"
#include "RITimer.h"
#include "GPIO.h"

/*=====[Definición de funciones]==============================*/

void Encendido();
void Apagado();

/*=====[Definición de variables globales]==============================*/

int Led=0;

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void ){
   // ----- Setup -----------------------------------
   boardInit();
   Init_LED('1');
   Init_LED('2');
   Init_LED('3');
   Init_LED('B');

   RIT_init();
   RIT_set(200);
   // ----- Repeat for ever -------------------------
   while( true ) {
	   if(Led!=0){
		   Encendido();
	   }else{
		   Apagado();
	   }
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not calLed by any Operating System, as in the
   // case of a PC program.
   return 0;
}

void RIT_IRQHandler(void){
        Led++;
        if (Led>4){
                Led=0;
        }

        RIT_clean();
}

void Encendido(){
	switch(Led){
	case 1:
		Apagar('3');
		Encender('B');
		break;
	case 2:
		Apagar('B');
		Encender('1');
		break;
	case 3:
		Apagar('1');
		Encender('2');
		break;
	case 4:
		Apagar('2');
		Encender('3');
		break;
	}
}

void Apagado(){
	Apagar('B');
	Apagar('1');
	Apagar('2');
	Apagar('3');
}
