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

void stair_climb_move()
{
		stair_climb(200);							
		breaks('0');
		_delay_ms(100);

		COM_PORT |= (_BV(OUT_BACK_SENSOR));
			_delay_ms(100);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
			
		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
			;
		}
	
	// take sliders up
			up_back(100);
			_delay_ms(800);
			
			initialize_intersection();	
			while(back_black_intersection!=3 || front_white_intersection!=2)
			{
				calculate_intersection();
				if(back_black_intersection!=3)
				{
					up_back(255);
				}
				else
				{
					breaks('b');
				}
				
				if(front_white_intersection!=2)
				{
					up_front(255);
				}
				else
				{
					breaks('f');
				}
			
			}
	
			breaks('0');
			_delay_ms(500);

			COM_PORT |= _BV(OUT_MAIN);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_MAIN));

}


