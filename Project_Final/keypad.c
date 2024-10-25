#define		F_CPU	16000000UL

#include	<avr/io.h>
#include	<util/delay.h>
#include	<avr/interrupt.h>

#include	"keypad.h"

void	Keypad_voidInit(){
	KDDR &= 0x0F;
	KDDR &= ~(1<<DA);
	
	KPORT &= 0x0F;
}

char	Keypad_charGetKey(){
	
	unsigned char key = 0;
	switch ((KIN & 0xF0)>>4)
	{
	case 0: key = '1';
	break;
	case 1: key = '2';
	break;
	case 2: key = '3';
	break;
	case 3: key = 'A';
	break;
	case 4: key = '4';
	break;
	case 5: key = '5';
	break;
	case 6: key = '6';
	break;
	case 7: key = 'B';
	break;
	case 8: key = '7';
	break;
	case 9: key = '8';
	break;
	case 10: key = '9';
	break;
	case 11: key = 'C';
	break;
	case 12: key = '*';
	break;
	case 13: key = '0';
	break;
	case 14: key = '#';
	break;
	case 15: key = 'D';
	break;
	}
	
	return key;
}