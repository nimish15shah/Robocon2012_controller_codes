#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "hardware.h"
#include "LCD.h"

void init_LCD()
{
	LCD_DDR= 0xFF;  // set data pins as output
	CONTROL_DDR |= _BV(E) | _BV(RS); // set control pins as output

	command(0x38); //various commands required 
	command(0x38);
	command(0x38);//to initiate lcd 
	command(0x0E); //and blink the cursir etc.
	command(0x0F);
	command(0x06);
	command(0x01);
	command(0x0C);
//	return;

}

void command(unsigned char c)
{
	LCD_PORT=c;
	CONTROL_PORT &= ~(_BV(RS));	//RS pin in command mode
	CONTROL_PORT |= _BV(E);
	delay(100); 
	CONTROL_PORT &= ~(_BV(E));	//for high-to-low pulse over E pin
	delay(100);
//	return;

}

void data(unsigned char d)
{
	LCD_PORT=d;
	CONTROL_PORT |= _BV(RS);		//RS pin in data mode
	CONTROL_PORT |= _BV(E);
	delay(100);
	CONTROL_PORT &= ~(_BV(E));	//for high-to-low pulse over E pin
	delay(100);

}

void delay(int s)
{

	for(delay_g=0;delay_g<s*10;delay_g++)
	{
		for(delay_j=0;delay_j<=10;delay_j++)
			;
	}

//	return;
}


void display_char(char a[20],char x,char letters,char line,char position)
{
	command(0x01);

	if(line==1)
	{
		command(0x80+position-1);
	}

	else if(line==2)
	{
		command(0xC0+position-1);
	}

	if(letters!=0)
	{
		LCD_i=0;
		while(LCD_i<letters)
		{
			data(a[LCD_i]);	
			LCD_i=LCD_i+1;
		}
	}
	else if(letters==0)
	{
		data(x);
	}

}

void display_num(int num,char digit,char line,char position)
{
//	command(0x01);

	int n=1;
	int show;	
	
	if(line==1)
	{
		show=0x80+position-1;
		command(show);
	}
	else if(line==2)
	{
		show=0xC0+position-1;
		command(show);
	}

	for(LCD_i=0;LCD_i<digit;LCD_i++)
	{
		n = n * 10;
	}

	for(LCD_i=1; LCD_i<digit;LCD_i++)
	{
		show=num%n;
		n=n/10;
		show=show/n + 48;
		data(show);
		_delay_ms(100);
	
	}
	
	show=num%10+48;
	data(show);
}

void display_binary(int bin,char line, char position)
{
	command(0x01);

	int show[16] = {0};
	int show_i=0;

	if(line==1)
	{
		show_i=0x80+position-1;
		command(show_i);
	}
	else if(line==2)
	{
		show_i=0xC0+position-1;
		command(show_i);
	}
	
	show_i= 0;

	while(bin!=0)
	{
		show[show_i] = bin % 2;
		bin = bin / 2;
		show_i++;
	}

	while(show_i>=0)
	{
		data((show[show_i]+48));
		if(show_i==0)
		{
			break;
		}
		show_i--;
	}
}

