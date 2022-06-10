#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "hardware.h"
#include "LCD.h"
#include "timer.h"
#include "steering.h"
#include "remote.h"



int ADC_value[]={700,700,250,275,350,150,350,325};

void init_ADC()
{
	counter=0;
	ADC_channel=0;
	ADMUX= 0b01100000;	// reference AVcc=5v, ADLAR high, ADC0 selected
	ADCSRA= 0b11000111;	//ADC enable, ADC first conversion start,
						//interrupt disabled, prescale 128
	while((ADCSRA & (1<<ADIF)) == 0x00)
		;
	ADCSRA |= (1<<ADIF);	// clear interrupt

//	ADMUX |= 0b00000001;
	ADC_threshold =380;	//extra
	ADCSRA |= 0b01101000;
	last_ADC_result=31;
	temp_result=0;
	ADC_result= 31;
//	ADC_value[]={0,0,0,0,0,0};
	_delay_us(50);
	ADMUX |= 0b00000001;
}

ISR(ADC_vect)
{
//	ADC_result= 4*ADCH;
//	ADC_value[ADC_channel]= 4*ADCH;
	if((4*ADCH) > ADC_value[ADC_channel])
	{
		temp_result	|= (1<<(7-ADC_channel));		
		if(ADC_channel>1)
		{
			counter++;
		}
	}

/*
	if( (4*ADCH) > ADC_threshold )
	{
		if(ADC_channel>1)
		{
			temp_result |=  (1<<(9-ADC_channel)) ;	//7-ADC_channel+2   //there may be problem for (1<<0)
		}
		
		else if(ADC_channel==0)
		{
			temp_result |= (1<<1);
		}
	
		else if(ADC_channel==1)
		{
			temp_result |= 1;
		}
	}
*/	
	 _delay_us(25);


	if(ADC_channel==7)
	{
		if( (temp_result & 0b10000000)== 0b10000000)
		{
			slider_gap=1;
		}
		else
		{
			slider_gap=0;
		}
/*
		if( (temp_result & 0b00000001)== 0b00000001)
		{
			balance=1;
		}
		else
		{
			green_sense=0;
		}
*/
		line_reading= temp_result & 0b00111111;
		switch(line_reading)
		{
			case 0b00100000 : ADC_result=1;
	 					 	  break;		
			
			case 0b00110000 : ADC_result=2;
	 					 	  break;		

			case 0b00010000 : ADC_result=3;
	 					 	  break;		

			case 0b00011000 : ADC_result=4;
	 					 	  break;		

			case 0b00001000 : ADC_result=5;
	 					 	  break;		

			case 0b00001100 : ADC_result=6;
	 					 	  break;		

			case 0b00000100 : ADC_result=7;
	 					 	  break;		

			case 0b00000110 : ADC_result=8;
	 					 	  break;		

			case 0b00000010 : ADC_result=9;
	 					 	  break;		

			case 0b00000011 : ADC_result=10;
	 					 	  break;		

			case 0b00000001 : ADC_result=11;
	 					 	  break;		


			case 0b00111000 : ADC_result=12;
	 					 	  break;		
			case 0b00111100 : ADC_result=13;
	 					 	  break;		
			case 0b00111110 : ADC_result=14;
	 					 	  break;		
			case 0b00111111 : ADC_result=15;
	 					 	  break;		
			case 0b00011111 : ADC_result=16;
	 					 	  break;		

			case 0b00001111 : ADC_result=17;
	 					 	  break;		
			case 0b00000111 : ADC_result=18;
	 					 	  break;		
	 					 	  break;		
			case 0b00000000 : ADC_result=19;
							  break;

		}


		ADC_channel=0;
		ADMUX++;
//		ADMUX &= 0b11100000;
//		ADMUX |= 0b00000001;
		temp_result=0;
		if(counter>3 || (ADC_result>12 && ADC_result<18))
		{
			COM_PORT &= ~(_BV(OUT_SENSOR));
			_delay_us(15);
			intersection=1;
		}
		else
		{
			COM_PORT |= _BV(OUT_SENSOR);
			intersection=0;
		}
		counter=0;
	}

	else if(ADC_channel==6)
	{
		ADC_channel++;
		ADMUX &= 0b11100000;
	}

	else if(ADC_channel<6)
	{
		ADC_channel++;
		ADMUX++;
	}

}

