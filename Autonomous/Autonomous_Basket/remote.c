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
	GICR &= ~(_BV(INT0));
	SREG |= (1<<7);
	break_balance();
	break_slider();
	call_remote();
	GICR |= _BV(INT0);
}

void call_remote()
{
	remote_slider_speed=200;
	remote_balance_speed=200; 
	while(bit_is_set(REMOTE_PIN,END_REMOTE))
	{
		_delay_ms(20);
		if(bit_is_clear(REMOTE_PIN,SLIDER_UP))
		{
			up_slider(remote_slider_speed);
		}
		else if(bit_is_clear(REMOTE_PIN,SLIDER_DOWN))
		{
			down_slider(remote_slider_speed);
		}
		else if(bit_is_set(REMOTE_PIN,SLIDER_DOWN) && bit_is_set(REMOTE_PIN,SLIDER_UP))
		{
			break_slider();
		}
	
		if(bit_is_clear(REMOTE_PIN,BALANCE_IN))
		{
			in_balance(remote_balance_speed);
		}
		else if(bit_is_clear(REMOTE_PIN,BALANCE_OUT))
		{
			out_balance(remote_balance_speed);
		}
		else
		{
			break_balance();
		}

/*		display_num(slider_gap,1,1,1);
		
		if((SWITCH_PIN & 0b00000001) == 0x00)
		{
			display_num(1,1,2,1);
		}
		else
		{
			display_num(0,1,2,1);
		}
*/
	}

	break_balance();
	break_slider();
}
