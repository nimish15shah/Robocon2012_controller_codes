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



void init_ADC()
{
	counter=0;
	ADC_channel=3;
	ADMUX= 0b01100100;	// reference AVcc=5v, ADLAR high, ADC0 selected
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
	ADMUX++;
}

ISR(ADC_vect)
{
	if((4*ADCH)<512)	
	{
		final_value[ADC_channel]= 512-(4*ADCH);
		direction[ADC_channel]=1;
		ADC_value[ADC_channel]= 4*ADCH;
	}
	else if((4*ADCH)>=512)
	{
		final_value[ADC_channel]= (4*ADCH)-512;
		direction[ADC_channel]=0;
		ADC_value[ADC_channel]= 4*ADCH;
	}
	_delay_us(10);

	if(ADC_channel==0)
	{
		ADC_channel=3;
		ADMUX++;
	}

	else if(ADC_channel>1)
	{
		ADC_channel--;
		ADMUX++;	
	}
	
	else if(ADC_channel==1)
	{
		ADMUX= 0b01100100;
		ADC_channel--;
	}

}
