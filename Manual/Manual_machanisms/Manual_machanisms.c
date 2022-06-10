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



int main(void)
{
	sei();
	initialize();

	while(1)
	{
			if(bit_is_clear(REMOTE_PIN,Z_UP))
			{
				normal=1;
				auto_z_up=0;
				auto_z_down=0;
				up_z(speed_z);
			}

			else if(bit_is_clear(REMOTE_PIN,Z_DOWN))
			{
				normal=1;
				auto_z_up=0;
				auto_z_down=0;
				down_z(30);
				enable_profile=1;
				speed_z_i=10;
			}
			
			else if(bit_is_clear(REMOTE_PIN,Z_AUTO_BREAK))
			{
				break_z();
				auto_z_up=0;
				auto_z_down=0;
			}
			
			else if((bit_is_clear(REMOTE_PIN,Z_AUTO_UP) || auto_z_up==1) &&
					bit_is_set(REMOTE_PIN,Z_AUTO_BREAK) && normal==0)
			{
				normal=0;
				auto_z_up=1;
				if(gap_sensor==1)
				{
					up_z(255);
				}
				else
				{
					auto_z_up=0;
					break_z();
				}
			}

			else if((bit_is_clear(PIND,Z_AUTO_DOWN) || auto_z_down==1) &&
					bit_is_set(REMOTE_PIN,Z_AUTO_BREAK) && normal==0 && bit_is_set(Z_FINAL_PIN,Z_FINAL))
			{
				normal=0;
				auto_z_down=1;
				if(gap_sensor==1)
				{
					down_z(255);
				}
				else
				{
					auto_z_down=0;
					break_z();
				}
			}

			else if(final_auto==0)
			{
				normal=0;
				break_z();
				enable_profile=1;
				speed_z_i=10;
				auto_z_up=0;
				auto_z_down=0;
			}
		

			if(bit_is_clear(REMOTE_PIN,Y_RIGHT) && r_break==0)
			{
				right_y(speed_y);
			}

			else if(bit_is_clear(REMOTE_PIN,Y_LEFT) && l_break==0)
			{
				left_y(speed_y);
			}
			else
			{
				break_y();
			}

		// change speed
			if(bit_is_clear(SPEED_PIN,HIGH_SPEED))
			{
				speed_z=255;
				speed_y=255;
			}
			if(bit_is_clear(SPEED_PIN,LOW_SPEED))
			{
//				speed_z=150;
//				speed_y=150;
			}

		// Switch Break

			if(bit_is_clear(BREAK_PIN,Y_BREAK_LEFT))
			{
				if(l_break==0)
				{
					break_y();
				}
				l_break=1;
				if(enable_buzzer_y==1)
				{
					enable_buzzer_y=0;
					buzzer_start=1;
				}
			}
			else
			{
				l_break=0;
			}

			if(bit_is_clear(BREAK_PIN,Y_BREAK_RIGHT))
			{
				if(r_break==0)
				{	
					break_y();
				}

				r_break=1;
				if(enable_buzzer_y==1)
				{
					enable_buzzer_y=0;
					buzzer_start=1;
				}

			}
			else
			{
				r_break=0;
			}
		
			if(bit_is_set(BREAK_PIN,Y_BREAK_RIGHT)
			 && bit_is_set(BREAK_PIN,Y_BREAK_LEFT) )
			{
				enable_buzzer_y=1;
			}
			if(bit_is_set(BREAK_PIN,X_BREAK))
			{
				enable_buzzer_x=1;
			}
			else
			{
				if(enable_buzzer_x==1)
				{
					enable_buzzer_x=0;
					buzzer_start=1;
				}
			}


		// signalling
		
			if(bit_is_clear(REMOTE_PIN,ARM_AHEAD))
			{
				SIGNAL_PORT |= _BV(SIGNAL_1);		
				SIGNAL_PORT &= ~(_BV(SIGNAL_2));
			}	
			else if(bit_is_clear(REMOTE_PIN,ARM_BACK))
			{
				SIGNAL_PORT |= _BV(SIGNAL_2);		
				SIGNAL_PORT &= ~(_BV(SIGNAL_1));
			}
			else if(bit_is_clear(PIND,BUN_CLUTCH))
			{
				SIGNAL_PORT |= _BV(SIGNAL_2);		
				SIGNAL_PORT |= (_BV(SIGNAL_1));
			}
			else
			{
				SIGNAL_PORT &= ~(_BV(SIGNAL_2));		
				SIGNAL_PORT &= ~(_BV(SIGNAL_1));
			}
	// buzzering

		if(buzzer_start==1)
		{
			debounce++;
			BUZZER_PORT &= ~(_BV(BUZZER_SIGNAL));
			if(debounce==50)
			{
				debounce=0;
				buzzer_start=0;
				BUZZER_PORT |= _BV(BUZZER_SIGNAL);
			}
		}
	
	// auto after token
		
		if( (bit_is_clear(PIND,BUN_CLUTCH) && once==0) || final_auto==1)
		{
			if(bit_is_set(Z_FINAL_PIN,Z_FINAL))
			{
				down_z(30);
				final_auto=1;
			}
			else
			{
				break_z();
				once=1;
				final_auto=0;
			}
			if(bit_is_clear(REMOTE_PIN,Z_AUTO_BREAK))
			{
				final_auto=0;;
			}
	
		}
		else
		{
			final_auto=0;
		}

	}
}
