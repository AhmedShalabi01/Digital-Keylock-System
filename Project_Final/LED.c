#define		F_CPU	16000000UL

#include	<avr/io.h>
#include	<util/delay.h>

#include	"LED.h"


void LEDs_voidInit(){
	LEDDDR |= 0x07;
	LEDPORT &= 0xF8; 
}

void LEDs_voidTurnOn(char LED){
	LEDPORT |= (1<<LED);
}

void LEDs_voidTurnOff(char LED){
	LEDPORT &= ~(1<<LED);	//0b1111 1000
}