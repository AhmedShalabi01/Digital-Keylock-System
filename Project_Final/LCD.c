#include	<avr/io.h>
#define		F_CPU		16000000UL
#include	<util/delay.h>

#include	"LCD.h"


void 	LCD_voidSendCmd(char cmd){

	LCD_DATA_PORT = cmd;

	LCD_CONTROL_PORT &= ~(1<<RS);	//RS = 0	--> CMD
	LCD_CONTROL_PORT &= ~(1<<RW);	//RW = 0	--> Write
	LCD_CONTROL_PORT |= (1<<EN);	//EN = 1	--> Enable
	_delay_ms(1);
	LCD_CONTROL_PORT &= ~(1<<EN);	//EN = 0	--> Disable
	_delay_ms(3);
}

void	LCD_voidSendData(char data){

	LCD_DATA_PORT = data;

	LCD_CONTROL_PORT |= (1<<RS);	//RS = 1	--> DATA
	LCD_CONTROL_PORT &= ~(1<<RW);	//RW = 0	--> Write
	LCD_CONTROL_PORT |= (1<<EN);	//EN = 1	--> Enable
	_delay_ms(1);
	LCD_CONTROL_PORT &= ~(1<<EN);	//EN = 0	--> Disable
	_delay_ms(3);
}


void	LCD_voidInit(){
	
	/*	Waits more than 30ms at start of LCD	*/
	_delay_ms(35);

	/*	Defines direction of ports	*/
	LCD_CONTROL_DDR |= 0xE0;
	LCD_DATA_DDR = 0xFF;

	/*	Waits 39us	*/
	_delay_ms(1);

	/*	Function Set	*/
	LCD_voidSendCmd(0x38);
	_delay_ms(1);

	/*	Display ON/OFF	*/
	LCD_voidSendCmd(0x0C);
	_delay_ms(1);

	/*	Auto Increment Counter	*/
	LCD_voidSendCmd(0x06);
	_delay_ms(1);

	/*	Display Clear	*/
	LCD_voidSendCmd(0x01);
	_delay_ms(1);

	/*	Cursor at first position	*/
	LCD_voidSendCmd(0x80);
	_delay_ms(1);
}

void	LCD_voidNewScreen(char* str)
{
	LCD_voidClear();
	LCD_voidSetXY(0,0);
	LCD_voidWriteStr(str);
	_delay_ms(10);
}

void LCD_voidClear(){
	LCD_voidSendCmd(0x01);
	_delay_ms(1);
}

void LCD_voidWriteStr(char *str)	//"hello" = {'h', 'e', 'l', 'l', 'o', '\0'}	
{
	for(int i=0; str[i] != '\0'; i++)  /* send each char of string till the NULL */
	{
		LCD_voidSendData(str[i]);  /* call LCD data write */
	}
}

void LCD_voidWriteNum(int num){
	unsigned l = 0;
	
	if (num >= 10000)
		l = 5;
	else if(num>=1000)
		l = 4;
	else if(num >=100)
		l = 3;
	else if(num >=10)
		l = 2;
	else if(num >=0)
		l = 1;
	
	switch (l)
	{
	case 5:		LCD_voidSendData((num/10000)%10 + 0x30);	
	case 4:		LCD_voidSendData((num/1000)%10 + 0x30);		
	case 3:		LCD_voidSendData((num/100)%10 + 0x30);		
	case 2:		LCD_voidSendData((num/10)%10 + 0x30);		
	case 1:		LCD_voidSendData((num/1)%10 + 0x30);
	}
}

void LCD_voidSetXY(char x, char y){
	if(y == 0)
		LCD_voidSendCmd(0x80 + x);
	else if(y == 1)
		LCD_voidSendCmd(0xC0 + x);
}