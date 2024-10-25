/************  Servo Motor Requirements  ************/
/*													*/
/*	Connected to OC1A on PORTD						*/
/*													*/
/*	Mode 14: Non-inverted Fast PWM	(TOP = ICR1)	*/
/*	Time Period: 20ms								*/
/*	Frequency: 1/20ms = 50Hz						*/
/*													*/
/*	To find prescaler and TOP value					*/
/*	use equation:									*/
/*	TOP = (Fcpu / Fpwm*pre) - 1						*/
/*	TOP = (16000000 / 50*64) - 1 = 4999				*/
/*													*/
/*	TOP = 4999	;	 Prescaler = 64					*/
/*													*/
/*	Equation for duty cycle:						*/
/*	OCR1 = (DutyCycle/100)*(TOP+1) - 1				*/
/*													*/
/*	For 1ms ON: OCR1 = 249							*/
/*	For 2ms ON: OCR1 = 499							*/
/*													*/
/****************************************************/


#include	<avr/io.h>
#include	"servo.h"

#define		F_CPU 16000000UL
#include	<util/delay.h>


void Timer1_voidInit()
{
	TCCR1A = 0x00;						//Initialize TCCR1A with 0
	TCCR1A |= (1<<WGM11);				//Selects Fast PWM mode 14
	
	TCCR1B = 0x00;						//Initialize TCCR1B with 0
	TCCR1B |= (1<<WGM13) | (1<<WGM12);	//Selects Fast PWM mode 14
	
	TCCR1B |= (1<<CS11) | (1<<CS10);	//Selects Prescaler 64
	
	TCNT1 = 0;
	ICR1 = 4999;						//ICR1 defines the TOP value of the counter register TCNT1
										//Counts from 0 to 4999, meaning 20ms or 50Hz
}

void Servo_voidInit()
{
	SERVODDR |= (1<<SPIN); 
	Timer1_voidInit();
	OCR1A = 300;
}

void Servo_voidSetPosition(int position)
{
	TCCR1A |= (1<<COM1A1);				//OC1A works in non-inverted mode
	OCR1A = position;
	_delay_ms(100);
	TCCR1A &= ~(1<<COM1A1);
}
