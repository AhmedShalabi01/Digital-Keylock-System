#include	<avr/io.h>
#include	<avr/interrupt.h>

#include	"EXT_interrupt.h"


void	INT_voidInit()
{
	sei();							// Enables SREG interrupts
	GICR = 0x00;					// All interrupts initial disabled
	
	MCUCR = 1<<ISC00 | 1<<ISC01;	// Trigger INT0 on rising edge
	MCUCSR = 1<<ISC2;				// Trigger INT2 on rising edge
	
	INT0_DDR &= ~(1<<INT0P);
	INT2_DDR &= ~(1<<INT2P);
}


void	INT_voidEnable(char i)
{
	GICR |= (1<<i);
}

void	INT_voidDisable(char i)
{
	GICR &= ~(1<<i);
}