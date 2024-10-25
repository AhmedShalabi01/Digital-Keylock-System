#define		LCD_DATA_DDR		DDRA
#define		LCD_DATA_PORT		PORTA

#define		LCD_CONTROL_DDR		DDRC
#define		LCD_CONTROL_PORT	PORTC

#define		EN		7
#define		RW		6
#define		RS		5

void 	LCD_voidSendCmd(char);
void	LCD_voidSendData(char);

void	LCD_voidInit();

void	LCD_voidNewScreen(char*);
void	LCD_voidClear();
void 	LCD_voidWriteStr (char*);
void	LCD_voidWriteNum(int);
void	LCD_voidSetXY(char, char);