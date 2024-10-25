#define		INT0_DDR	DDRD
#define		INT0_PORT	PORTD
#define		INT0P		2

#define		INT1_DDR	DDRD
#define		INT1_PORT	PORTD
#define		INT1P		3

#define		INT2_DDR	DDRB
#define		INT2_PORT	PORTB
#define		INT2P		2

void	INT_voidInit();

/*		Takes INT0 or INT2	*/
void	INT_voidEnable(char);
void	INT_voidDisable(char);