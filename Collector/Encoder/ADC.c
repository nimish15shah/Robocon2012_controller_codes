#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "ADC.h"
#include "Encoder.h"
#include "hardware.h"
#include "initialize.h"
#include "timer.h"
#include "steering.h"
#include "stair_climb.h"
#include "remote.h"




int ADC_value[]={600,600,700,725,725,700,700,650};

void init_ADC()
{
	gap_front=0;
	gap_back=0;
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
//	last_ADC_result=31;
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
//		counter++;
	}
		 _delay_us(25);

	if(ADC_channel==7)
	{
		if((temp_result & 0b10000000) == 0b10000000)
		{
			gap_back=1;
		}
		else
		{
			gap_back=0;
		}

		if((temp_result & 0b01000000) == 0b01000000)
		{
			gap_front=1;
		}
		else
		{
			gap_front=0;
		}

		if((temp_result & 0b00000010) == 0b00000010)
		{
			autonomous_signal=1;
		}
		else
		{
			autonomous_signal=0;
		}

		if((temp_result & 0b00000100) == 0b000000100)
		{
			manual_signal_1=1;
		}
		else
		{
			manual_signal_1=0;
		}


		if((temp_result & 0b00000001) == 0b000000001)
		{
			manual_signal_2=1;
		}
		else
		{
			manual_signal_2=0;
		}

		ADC_channel=0;
		ADMUX++;
		temp_result=0;

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


























/*
void init_ADC()
{
	gap_front=0;
	gap_back=0;
	ADC_channel=0;
	ADC_threshold=0;
	ADMUX= 0b01100000;	// reference AVcc=5v, ADLAR high, ADC0 selected
	ADCSRA= 0b11000111;	//ADC enable, ADC first conversion start,
						//interrupt disabled, prescale 128
	while((ADCSRA & (1<<ADIF)) == 0x00)
		;
	ADCSRA |= (1<<ADIF);	// clear interrupt

	ADMUX &= 0b11110000;
//	ADMUX |= 0b00000001;
	ADC_threshold =700;	//extra
	ADCSRA |= 0b01101000;
//	last_ADC_result=31;
	temp_result=0;
//	ADC_result= 31;
	begin=1;
}


ISR(ADC_vect)
{
	if(begin==0)
	{
		if((4*ADCH) > ADC_threshold)
		{
			if(ADC_channel==0)
				gap_back=1;

			else if(ADC_channel==1)
				gap_front=1;
//			COM_PORT |= _BV(OUT_MAIN); //extra		

		}
		else
		{
			if(ADC_channel==0)
				gap_back=0;

			else if(ADC_channel==1)
				gap_front=0;
			
//			COM_PORT &= ~(_BV(OUT_MAIN));	//extra
		}

		if(ADC_channel==0)
		{
			ADC_channel=1;
			ADMUX &= 0b11110000;
		}
		else if(ADC_channel==1)
		{
			ADC_channel=0;
			ADMUX |= 0b00000001;
		}
	
	}

	else
	{
		begin=0;
		_delay_us(50);
		ADMUX |= 0b00000001;
	}


}
*/
