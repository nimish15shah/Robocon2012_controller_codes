void init_LCD();		// for lcd
void command(unsigned char c);
void data(unsigned char d);
void display_char(char a[20],char x,char letters,char line,char position);
void display_num(int num,char digit,char line,char positon);
void display_binary(int bin,char line, char position);

char show;
void delay(int s);
char num_i,char_i;
int LCD_i;
int delay_j;
int delay_g;
char LCD;

#define LCD_DDR			 DDRB
#define LCD_PORT		 PORTB
#define CONTROL_DDR		 DDRD
#define CONTROL_PORT	 PORTD
#define E				 PD2
#define RS				 PD0
