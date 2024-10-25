#define		F_CPU	16000000UL

#include	<avr/io.h>
#include	<util/delay.h>

#include	"buzzer.h"


void Buzzer_voidInit(){
	BUZDDR |= (1<<BPIN);
	BUZPORT &= ~(1<<BPIN); 
}

void Buzzer_voidToggle(int delay){
	BUZPORT |= (1<<BPIN);
	
	for(int i = 0; i<delay; i++)
		_delay_ms(1);
	
	BUZPORT &= ~(1<<BPIN);
}