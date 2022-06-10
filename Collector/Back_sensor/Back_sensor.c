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

int main(void)
{
	sei();
	initialize();
/*	while(1)
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
	while(1)
	{
		if(bit_is_clear(PATH_SELECT_PIN,START))
		{
			path=1;
			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,RESTART))
		{
			path=1;
			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,MAIN))
		{
			path=1;
			COM_PORT |= _BV(OUT_ENCODER);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_ENCODER));
			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,PENG_ON_DEI_GATE))
		{
			path=2;
			break;
		}


		if(bit_is_clear(PATH_SELECT_PIN,EXTRA))
		{
			path=3;
			break;
		}
	
	}
/*
	PATH_SELECT_DDR |=(_BV(START)) | (_BV(RESTART))
					| (_BV(MAIN)) | (_BV(PENG_ON_DEI_GATE))
					| (_BV(EXTRA));

	PATH_SELECT_PORT |=(_BV(START)) | (_BV(RESTART))
					 | (_BV(MAIN)) | (_BV(PENG_ON_DEI_GATE))
					 | (_BV(EXTRA));
	full_sense=0;
*/

	//	Wait till get signal from Encoder

	while(bit_is_clear(COM_PIN,IN_ENCODER))
	{
		;
	}

	// Move Rear Motor
		REAR_MOTOR_PORT |= _BV(REAR_MOTOR_1);
 		_delay_ms(2000);
		while(no_intersection==1)
		{
			;
		}
		_delay_ms(1000);
		REAR_MOTOR_PORT &= ~(_BV(REAR_MOTOR_1));
		COM_PORT |= _BV(OUT_ENCODER);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_ENCODER));
	// change Sensing pattern
	
	// Wait to change Sensing pattern

		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			;
		}
		if(path==2)
		{
			goto COMMUNICATION;	
		}


	// Move green arm towards side
//		full_sense=0;
		green_right(80);
		_delay_ms(400);
//		while(green_sense==1)
		{
//			green_right(80);
		}

		while(green_sense==0)
		{
			green_right(200);
		}

		breaks('g');
		breaks('b');
		_delay_ms(100);

	// Wait for signal to change Sensing
/*		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			;
		}
		full_sense=1;
		_delay_ms(2000);

*/	// Wait till Bot reach Bun tower
	
		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			;
		}
	
	// Move forward to pick up Yellow BUN
			while(yellow_sense==1)
			{
				yellow_forward(255);
			}
	
			while(yellow_sense==0)
			{
				yellow_forward(255);
			}	
	
			
			if(path==1)
			{
				breaks('y');
				COM_PORT |= _BV(OUT_ENCODER);
				_delay_ms(10);
				COM_PORT &= ~(_BV(OUT_ENCODER));
			}
			if(path==2)
			{
				while(yellow_sense==1)
				{
					yellow_forward(255);
				}

				while(yellow_sense==0)
				{
					yellow_forward(255);
				}	
				breaks('y');
			}		
	// Take yellow Bun In
			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{	
				;
			}
			yellow_reverse(200);
			_delay_ms(700);
			while(yellow_sense==1)
			{
				yellow_reverse(255);
			}

			while(yellow_sense==0)
			{
				yellow_reverse(255);
			}	
			breaks('y');
		
			COM_PORT |= _BV(OUT_ENCODER);
			_delay_ms(50);
			COM_PORT &= ~(_BV(OUT_ENCODER));
		// Wait to take green bun in
			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}
		// Take green bun in
			while(green_sense==1)
			{
				green_left(255);
			}

			while(green_sense==0)
			{
				green_left(255);
			}
			breaks('g');
			breaks('b');

		// Wait till bot reach Basket


			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}

		// Move Yellow Bun Out

			while(yellow_sense==1)
			{
				yellow_forward(200);
			}
			_delay_ms(200);
			while(yellow_sense==0)
			{
				yellow_forward(200);
			}	
			breaks('y');
			COM_PORT |= _BV(OUT_ENCODER);
			_delay_ms(100);
			COM_PORT &= ~(_BV(OUT_ENCODER));
	

		// Move green bun in
/*		if(path==1)
		{

			while(green_sense==1)
			{
				green_left(255);
			}

			while(green_sense==0)
			{
				green_left(255);
			}
			breaks('g');
			breaks('b');
	
			COM_PORT |= _BV(OUT_ENCODER);
			_delay_ms(100);
			COM_PORT &= ~(_BV(OUT_ENCODER));
		}
*/		
		// Take yellow arm in while bot moves for peng on dei gate
			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}
			yellow_reverse(255);
			_delay_ms(1000);
			while(yellow_sense==1)
			{
				yellow_reverse(255);
			}
			while(yellow_sense==0)
			{
				yellow_reverse(255);
			}
			breaks('y');
			_delay_ms(100);

		// Set arrangement for Mannual Communication
COMMUNICATION:
			
			PATH_SELECT_DDR &= ~(_BV(START)) & ~(_BV(RESTART));
			end=0;
			while(end==0)
			{
			// For COM_PIN
				while(bit_is_set(COM_PIN,IN_ENCODER) && 
				bit_is_set(PATH_SELECT_PIN,START) &&
				bit_is_set(PATH_SELECT_PIN,RESTART) )
				{
					yellow_forward(200);
				}
			// For START
				while(bit_is_clear(COM_PIN,IN_ENCODER) && 
				bit_is_clear(PATH_SELECT_PIN,START) &&
				bit_is_set(PATH_SELECT_PIN,RESTART) )
				{
					yellow_reverse(200);
				}
			// FOR RESTART
				while(bit_is_clear(COM_PIN,IN_ENCODER) && 
				bit_is_set(PATH_SELECT_PIN,START) &&
				bit_is_clear(PATH_SELECT_PIN,RESTART) )
				{

				}
			// FOR END
				while(bit_is_set(COM_PIN,IN_ENCODER) && 
				bit_is_clear(PATH_SELECT_PIN,START) &&
				bit_is_clear(PATH_SELECT_PIN,RESTART) )
				{
					end=1;
				}
				breaks('b');
			}

		_delay_ms(4000);
		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			_delay_us(50);
		}
	// Take Hand out for Peng on dei Gate
		
			yellow_forward(255);
			_delay_ms(800);
			while(yellow_sense==1)
			{
				yellow_forward(200);
			}
	
			while(yellow_sense==0)
			{
				yellow_forward(200);
			}	
			breaks('y');
			COM_PORT |= _BV(OUT_ENCODER);
			_delay_ms(100);
			COM_PORT &= ~(_BV(OUT_ENCODER));
	
			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}
	// End of peng on dei gate

}



