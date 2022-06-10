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


ISR(INT0_vect)
{
//	code_select=1;
	GICR &= ~(_BV(INT0));
	SREG |= (1<<7);
	breaks('b');
	call_remote();
	GICR |= _BV(INT0);
}


void call_remote()
{
	while(bit_is_set(REMOTE_PIN,END_REMOTE))
	{
		while(bit_is_clear(REMOTE_PIN,YELLOW_HIGH))
		{
			yellow_forward(remote_speed);
		
		}
	
		while(bit_is_clear(REMOTE_PIN,YELLOW_LOW))
		{
			yellow_reverse(remote_speed);

		}

//		else if(bit_is_set(REMOTE_PIN,YELLOW_HIGH) && bit_is_set(REMOTE_PIN,YELLOW_LOW))
		{
			breaks('y');
		}

		while(bit_is_clear(REMOTE_PIN,GREEN_LEFT_1))
		{
			green_left(remote_speed);
		}
		while(bit_is_clear(REMOTE_PIN,GREEN_RIGHT_1))
		{
			green_right(remote_speed);
		}

	
		{
			breaks('g');
		}
	}
	breaks('b');
}

