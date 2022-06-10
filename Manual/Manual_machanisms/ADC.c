#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "LCD.h"
#include "timer.h"
#include "steering.h"
#include "ADC.h"



void init_ADC()
{
	ADMUX= 0b01100001;	// reference AVcc=5v, ADLAR high, ADC0 selected
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
	if( (4*ADCH)> 800)
	{
		gap_sensor=1;
	}
	else
	{
		gap_sensor=0;
	}
}
