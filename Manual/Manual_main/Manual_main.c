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




int main(void)
{
	sei();
	initialize();

/*	
	if(final_value[LEFT_JOYSTICK_1]>100 && final_value[RIGHT_JOYSTICK_1]>100
		&& l_break==0 && r_)
	{
		if( (final_value[LEFT_JOYSTICK_1]-final_value[RIGHT_JOYSTICK_1]<30)
		 || (final_value[RIGHT_JOYSTICK_1]-final_value[LEFT_JOYSTICK_1]<30)
		  )
		{
			forward( final_value[RIGHT_JOYSTICK_1]/2 );
		}
		
		else
		{
			
		}
	
		else if(final_value[LEFT_JOYSTICK_1]>100 && 
			final_value[RIGHT_JOYSTICK_1]>100 && direction==0)
		{
			if( (final_value[LEFT_JOYSTICK_1]-final_value[RIGHT_JOYSTICK_1]<30)
			 || (final_value[RIGHT_JOYSTICK_1]-final_value[LEFT_JOYSTICK_1]<30)
			  )
			{
				reverse( final_value[RIGHT_JOYSTICK_1]/2 );
			}
		}
	}

	else if

	else
	{
		pwm
	}
*/
	while(1)
	{
	
/*		for(debounce=0;debounce<2;debounce++)
		{
			display_num(ADC_value[debounce],4,1,(5*debounce)+1);
			display_num(pwm_right,4,2,1);
			display_num(pwm_left,4,2,6);

//			display_num(final_value[debounce],4,2,(5*debounce)+1);
			display_num(l_break,1,1,12);
			display_num(r_break,1,1,14);
		}
	
*/


//		_delay_ms(500);
	
	// Left Joystick
		if(constant==0 && l_break==0)
		{
			if(final_value[LEFT_JOYSTICK_1]>100 && l_break==0)
			{
				if(direction[LEFT_JOYSTICK_1]==1)
				{
					left_forward(final_value[LEFT_JOYSTICK_1]/division_factor);
				}
				else if(direction[LEFT_JOYSTICK_1]==0)
				{
					left_reverse(final_value[LEFT_JOYSTICK_1]/division_factor);
				}
	
				debounce_i=0;
				debounce_j=0;
			}

			else if(final_value[LEFT_JOYSTICK_2]>100 && l_break==0)
			{
				if(direction[LEFT_JOYSTICK_2]==1)
				{
					left_forward(final_value[LEFT_JOYSTICK_2]/division_factor);
				}
				else if(direction[LEFT_JOYSTICK_2]==0)
				{
					left_reverse(final_value[LEFT_JOYSTICK_2]/division_factor);
				}
				debounce_i=0;
				debounce_j=0;
			}

			else if( final_value[LEFT_JOYSTICK_2]<100 && final_value[LEFT_JOYSTICK_1]<60
					 && l_break==0 )
			{
				pwm_left=0;
				_delay_ms(10);
				MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
				MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));

			}
		}
		else if(l_break==1)
		{
			left_break();
		}

	// Right joystick
		if(r_break==0 && constant==0)
		{
			if(final_value[RIGHT_JOYSTICK_1]>100 && r_break==0)
			{

				if(direction[RIGHT_JOYSTICK_1]==1)
				{
					if((direction[RIGHT_JOYSTICK_1]==direction[LEFT_JOYSTICK_1])
					&& ( (final_value[LEFT_JOYSTICK_1]-final_value[RIGHT_JOYSTICK_1]<60)
		   	  	 	|| (final_value[RIGHT_JOYSTICK_1]-final_value[LEFT_JOYSTICK_1]<60) ) )
					{
						right_forward(final_value[RIGHT_JOYSTICK_1]/division_factor);
					}

					else
					{
						right_forward(final_value[RIGHT_JOYSTICK_1]/division_factor);
					}
				}
				else if(direction[RIGHT_JOYSTICK_1]==0)
				{

					if((direction[RIGHT_JOYSTICK_1]==direction[LEFT_JOYSTICK_1])
					&& ( (final_value[LEFT_JOYSTICK_1]-final_value[RIGHT_JOYSTICK_1]<60)
		   		    || (final_value[RIGHT_JOYSTICK_1]-final_value[LEFT_JOYSTICK_1]<60) ) )
					{
						right_reverse(final_value[RIGHT_JOYSTICK_1]/division_factor);
					}
					else
					{
						right_reverse(final_value[RIGHT_JOYSTICK_1]/division_factor);
					}
				}
				debounce_i=0;
				debounce_j=0;
			}

			else if(final_value[RIGHT_JOYSTICK_2]>100 && r_break==0)
			{
		
				if(direction[RIGHT_JOYSTICK_2]==1)
				{
					if((direction[RIGHT_JOYSTICK_2]==direction[LEFT_JOYSTICK_2])
					&& ( (final_value[LEFT_JOYSTICK_2]-final_value[RIGHT_JOYSTICK_2]<60)
		   	  	 	|| (final_value[RIGHT_JOYSTICK_2]-final_value[LEFT_JOYSTICK_2]<60) ) )
					{
						right_forward(final_value[RIGHT_JOYSTICK_2]/division_factor);
					}

					else
					{
						right_forward(final_value[RIGHT_JOYSTICK_2]/division_factor);
					}
				}
				else if(direction[RIGHT_JOYSTICK_2]==0)
				{
					if((direction[RIGHT_JOYSTICK_2]==direction[LEFT_JOYSTICK_2])
					&& ( (final_value[LEFT_JOYSTICK_2]-final_value[RIGHT_JOYSTICK_2]<60)
		   		    || (final_value[RIGHT_JOYSTICK_2]-final_value[LEFT_JOYSTICK_2]<60) ) )
					{
						right_reverse(final_value[RIGHT_JOYSTICK_2]/division_factor);
					}
					else
					{
						right_reverse(final_value[RIGHT_JOYSTICK_2]/division_factor);
					}		
				}
				debounce_i=0;
				debounce_j=0;
			}

			else if(final_value[RIGHT_JOYSTICK_2]<100 && final_value[RIGHT_JOYSTICK_1]<100
					 && r_break==0 )
			{
				pwm_right=0;
				_delay_ms(10);
				MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
				MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
			}
		}
		else if(r_break==1)
		{
			right_break();
		}


	// Break Pins
		if(bit_is_clear(BREAK_PIN,BREAK_LEFT))
		{
			l_break=1;
		}
		else
		{
			l_break=0;	
		}
		if(bit_is_clear(BREAK_PIN,BREAK_RIGHT))
		{
			r_break=1;
		}
		else
		{
			r_break=0;
		}

	// Difffrent Speed levels
		if(bit_is_clear(SPEED_PIN,LOW_SPEED))
		{
			if(enable_level==1)
			{			
				_delay_ms(100);
				enable_debounce=1;
				enable_level=0;
				if(division_factor==level_1)
				{
					division_factor=level_0;
				}
				else if(division_factor==level_2)
				{
					division_factor=level_1;
				}
			}	
		}
		else if(bit_is_clear(SPEED_PIN,HIGH_SPEED))
		{
			if(enable_level==1)
			{
				_delay_ms(100);
				enable_debounce=1;
				enable_level=0;
				if(division_factor==level_1)
				{
					division_factor=level_2;
				}
				if(division_factor==level_0)
				{
					division_factor=level_1;
				}
			}
		}	

		else
		{
/*			if(enable_debounce==1)
			{
				debounce_level++;
				if(debounce_level==1)
				{
					enable_debounce=0;
					debounce_level=0;
				}
			}
			else
*/			{
				enable_level=1;
				enable_debounce=0;
				debounce_level=0;
			}
		}
	// Constant Speed Buttons
		if(bit_is_clear(CONSTANT_PIN,CONSTANT_FRONT))
		{
			if(r_break==0)
			{
				right_forward(512/17);
			}
			if(l_break==0)
			{
				left_forward(512/17);
			}
			constant=1;
			debounce_i=0;
			debounce_j=0;

		}
		else if(bit_is_clear(CONSTANT_PIN,CONSTANT_BACK))
		{
			if(r_break==0)
			{
				right_reverse(512/16);
			}
			if(l_break==0)
			{
				left_reverse(512/16);
			}
			constant=1;
			debounce_i=0;
			debounce_j=0;
		}
		else
		{
			constant=0;
		}

	// Change speed level to lower level
/*		if( (pwm_right==0 && pwm_left==0) || (l_break==1 && r_break==1))
		{
			if(l_break==1 && r_break==1)
			{
				division_factor= level_0;
			}
			else
			{
				debounce_i++;
				if(debounce_i==1)
				{
					debounce_j++;
					debounce_i=0;
				}
				if(debounce_j==1)
				{
					division_factor= level_0;
				}
			}
		
		}
*/

	}
}

