#define		F_CPU		16000000UL

#include	<avr/io.h>
#include	<util/delay.h>
#include	<avr/interrupt.h>

#include	"LCD.h"
#include	"keypad.h"
#include	"EXT_interrupt.h"
#include	"servo.h"
#include	"buzzer.h"
#include	"LED.h"

static		unsigned	char	key;
static		unsigned	char	password[6] = {'1','2','3','4','5','6'};
static		unsigned	char	pass_check[6] = {};
static		unsigned	char	size_pass = 0;


int main(void)
{
	LCD_voidInit();
	Keypad_voidInit();
	INT_voidInit();
	Servo_voidInit();
	Buzzer_voidInit();
	LEDs_voidInit();
	
	/*	Turn LEDs On and Off	*/
	LEDs_voidTurnOn(LED_R);
	
	/*	Display message		*/
	LCD_voidNewScreen("Enter Password");
	LCD_voidSetXY(5,1);
	
	/*	Waits for input, enables INT2	*/
	INT_voidEnable(INT2);
	
	while (1);
}

char	check_password(){
	
	unsigned char flag = 1;
	
	for(unsigned char i = 0; i<6; i++)
	{
		if(password[i] != pass_check[i])
		{
			flag = 0;
			break;
		}
	}
	return flag;
}


ISR(INT0_vect)
{
	/*	When Button is pressed, close door	*/
	LEDs_voidTurnOn(LED_R);
	LEDs_voidTurnOff(LED_G);
	
	/*	Closes door			*/
	Servo_voidSetPosition(300);
	
	/*	Display message		*/
	LCD_voidNewScreen("Door Closed");
	
	/*	Delay 1.5 seconds	*/
	_delay_ms(1500);
	
	/*	Enable interrupt of keypad and closes interrupt of door	*/
	INT_voidEnable(INT2);
	INT_voidDisable(INT0);
	
	/*	Display initial message	*/
	LCD_voidNewScreen("Enter Password");
	
	/*	Waits for input			*/
	LCD_voidSetXY(5,1);
	
	/*	Reset index of password	for overwrite	*/
	size_pass = 0;
}

ISR(INT2_vect)
{
	key = Keypad_charGetKey();
	
	if(key >= '0' && key <= '9')
	{
		pass_check[size_pass] = key;
		size_pass++;
		LCD_voidSendData('*');
		
		LEDs_voidTurnOn(LED_Y);
		Buzzer_voidToggle(100);
		LEDs_voidTurnOff(LED_Y);
	}
	else if(key == 'D')
	{
		/*	Auto Decrement Counter	*/
		LCD_voidSendCmd(0x04);
		_delay_ms(1);
		
		/*	Write blank space twice	*/
		LCD_voidSendData(' ');
		LCD_voidSendData(' ');
		
		/*	Buzzer signal			*/
		LEDs_voidTurnOn(LED_Y);
		Buzzer_voidToggle(100);
		LEDs_voidTurnOff(LED_Y);
		
		/*	Decrement size_pass		*/
		if(size_pass > 0)
			size_pass--;
		
		/*	Auto Increment counter again	*/
		LCD_voidSendCmd(0x06);
		_delay_ms(1);
		
		/*	Sets LCD at same position		*/
		LCD_voidSetXY(5+size_pass, 1);
	}
	
	if(size_pass == 6)
	{
		if(check_password())
		{
			/*	Enable INT0 to close the door and disable INT2 for keypad	*/
			INT_voidEnable(INT0);
			INT_voidDisable(INT2);
			
			/*	Turn green led ON, turn red led OFF	*/
			LEDs_voidTurnOn(LED_G);
			LEDs_voidTurnOff(LED_R);
			
			/*	Turn buzzer ON for 1 second			*/
			Buzzer_voidToggle(1000);
			
			/*	Turns servo motor	*/
			Servo_voidSetPosition(150);	//Equivalent to +90 degrees
			
			/*	Display message		*/
			LCD_voidNewScreen("Door Open");
		}
		else
		{	
			/*	Display message		*/
			LCD_voidNewScreen("Error");
			
			/*	Buzzer rings 3 short times	*/
			for(char i = 0; i<3; i++)
			{
				LEDs_voidTurnOn(LED_Y);
				Buzzer_voidToggle(100);
				_delay_ms(10);
				LEDs_voidTurnOff(LED_Y);
			}
			
			/*	Wait for 1 second before allowing next attempt	*/
			_delay_ms(500);
			
			/*	Display initial message	*/
			LCD_voidNewScreen("Enter Password");
			
			/*	Turn Led Red On			*/
			LEDs_voidTurnOn(LED_R);
			
			/*	Waits for input			*/
			LCD_voidSetXY(5,1);
			
			/*	Reset index of password	for overwrite	*/
			size_pass = 0;
		}
	}
}

