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

int main()
{
	sei();
	initialize();
/*
	while(1)
	{
		if(ADC_channel != 0)
		{
			if(ADC_channel<5)
				display_num(4*ADCH,3,1,((ADC_channel-1)*4)+1);
			else 
				display_num(4*ADCH,3,2,((ADC_channel-5)*4)+1);
		}
		else
		{
			display_num(4*ADCH,3,2,14);
		}
	}

*/
/*	
	while(1)
	{
//		read_sensor();
//		display_num(sensor_read,4,2,1);
		display_num(ADC_result,4,1,1);
//		display_num(last_ADC_result,4,1,6);

//		_delay_ms(500);
	}
*/




//	while(bit_is_set(REMOTE_PIN,SLIDER_UP))
//	{
/*		COM_PORT |= _BV(OUT_MAIN);
		display_num(ADC_result,2,1,1);
		display_num(slider_gap,2,2,1);
		_delay_ms(500);

		COM_PORT &= ~(_BV(OUT_MAIN));
		_delay_ms(500);
*/
/*		if(bit_is_clear(COM_PIN,IN_MAIN))
		{
			display_num(1,1,1,1);
		}
		else
		{
			display_num(0,1,1,1);
		}
	}

	while(1)
	{
		if(bit_is_set(SWITCH_PIN,BALANCE_SWITCH))
		{
//			out_balance(70);
		}
		else
		{
//			break_balance();
		}
	}

*/
		_delay_ms(500);

		while(bit_is_set(COM_PIN,IN_MAIN))
		{
			;
		}


//	while(bit_is_clear(SWITCH_PIN,BALANCE_SWITCH))
		{
//			out_balance(255);
		}
//		_delay_ms(100);
	


		out_balance(255);
		while(bit_is_set(SWITCH_PIN,BALANCE_SWITCH))
		{
			out_balance(255);
		}
		while(1)
		{
			if(bit_is_clear(SWITCH_PIN,BALANCE_SWITCH))
			{
				break_balance();
				break;
			}
		}


	while(1)
	{
		while(bit_is_set(COM_PIN,IN_MAIN))
		{
			;
		}
		if(gap_yes==1)
		{
			while(slider_gap==1)
			{
				up_slider(200);
			}
		}
		// Pick up Basket
		debounce=0;	
		while(slider_gap==0)
		{	
			if(debounce<100)
			{
				_delay_ms(5);
				up_slider(255);
				debounce++;
			}
			if(debounce>100)
			{
				_delay_ms(5);
				up_slider(255);
				debounce++;
				if(debounce==200)
				{
					debounce=0;
				}
			}
				
		}
		break_slider();
	
		while(bit_is_clear(SWITCH_PIN,BALANCE_SWITCH))
		{
			in_balance(255);
			
		}

		debounce=0;
		while(bit_is_set(SWITCH_PIN,BALANCE_SWITCH))
		{
			in_balance(255);
			debounce++;
			_delay_ms(5);
			if(debounce==150)
			{
				break;
			}
		}


		COM_PORT &= ~(_BV(OUT_MAIN));
		_delay_ms(30);
		COM_PORT |= _BV(OUT_MAIN);


		while(bit_is_set(SWITCH_PIN,BALANCE_SWITCH))
		{
			in_balance(255);
		}
		_delay_ms(10);
		while(1)
		{
			if(bit_is_clear(SWITCH_PIN,BALANCE_SWITCH))
			{
				_delay_ms(10);
				break_balance();
				break;
			}
		}


		COM_PORT &= ~(_BV(OUT_MAIN));
		_delay_ms(5);
		COM_PORT |= _BV(OUT_MAIN);


//		_delay_ms(500);

		// Keep down Basket

		while(bit_is_set(COM_PIN,IN_MAIN))
		{
			;
		}

		while(bit_is_clear(SWITCH_PIN,BALANCE_SWITCH))
		{
			out_balance(250);
		}
		_delay_ms(100);
	
		while(bit_is_set(SWITCH_PIN,BALANCE_SWITCH))
		{
			out_balance(250);
		}
		while(1)
		{
			if(bit_is_clear(SWITCH_PIN,BALANCE_SWITCH))
			{
				break_balance();
				break;
			}
		}

		while(slider_gap==1)
		{
			down_slider(250);
		}
		debounce=0;
		down_slider(100);
		while(debounce<37 && slider_gap==0)
		{
			_delay_ms(100);
			debounce++;
		}
		if(slider_gap==1)
		{
			gap_yes=1;
		}
		break_slider();
	
		COM_PORT &= ~(_BV(OUT_MAIN));
		_delay_ms(100);
		COM_PORT |= _BV(OUT_MAIN);
	}
}
