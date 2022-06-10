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

ISR(INT0_vect)
{
	_delay_ms(500);
//	code_select=1;
	GICR &= ~(_BV(INT0));
	SREG |= (1<<7);
	DDRD &= ~(_BV(END_REMOTE));
	PORTD |= _BV(END_REMOTE);
	breaks('0');
	_delay_ms(15);
	call_remote();
	_delay_ms(500);
	GICR |= _BV(INT0);
	code_select=0;
}



void call_remote()
{
	remote_speed=100;
	front_continue_1=0;
	front_continue_2=0;
	back_continue_1=0;
	back_continue_2=0;
/*	while(code_select==0)
	{
	// PB0
		if(bit_is_clear(REMOTE_PIN,MECHANISM_LOW_CONT))
		{
			while(gap_front==0)
			{
				down_front(remote_speed);
				if(bit_is_clear(PIND,END_REMOTE))
					break;
		//		_delay_ms(200);			

			}
			breaks('f');
		}
	
	// PB1 
		if(bit_is_clear(REMOTE_PIN,MECHANISM_HIGH_CONT))
		{
			while(gap_front==0)
			{
				up_front(remote_speed);
				if(bit_is_clear(PIND,END_REMOTE))
					break;
		//		_delay_ms(200);			

			}
			breaks('f');
		}	
	
	// PB2 	
		if(bit_is_clear(REMOTE_PIN,MECHANISM_LOW))
		{
			_delay_ms(20);
			while(bit_is_clear(REMOTE_PIN,MECHANISM_LOW))
			{
				down_front(remote_speed);
			}
			breaks('f');
		}	

	// PB3 	
		if(bit_is_clear(REMOTE_PIN,MECHANISM_HIGH))
		{
			_delay_ms(20);
			while(bit_is_clear(REMOTE_PIN,MECHANISM_HIGH))
			{
				up_front(remote_speed);
			}
			breaks('f');
		}	

	// PB5 	
		if(bit_is_clear(REMOTE_PIN,REAR_LOW))
		{
			_delay_ms(20);
			while(bit_is_clear(REMOTE_PIN,REAR_LOW))
			{
				down_back(remote_speed);
			}
			breaks('b');
		}	

	// PB6 	
		if(bit_is_clear(REMOTE_PIN,REAR_LOW_CONT))
		{
			while(gap_back==0)
			{
				down_back(remote_speed);
				if(bit_is_clear(PIND,END_REMOTE))
					break;
//				_delay_ms(200);			
			}
			breaks('b');
		}	

	// PB7 	
		if(bit_is_clear(REMOTE_PIN,REAR_HIGH))
		{
			_delay_ms(50);
			while(bit_is_clear(REMOTE_PIN,REAR_HIGH))
			{
				up_back(remote_speed);
			}
			breaks('b');
		}	

	// PD0 	
		if(bit_is_clear(PIND,REAR_HIGH_CONT))
		{
			while(gap_back==0)
			{
				up_back(remote_speed);
				if(bit_is_clear(PIND,END_REMOTE))
					break;
//				_delay_ms(200);			
			}
			breaks('b');
		}	
//		display_num(gap_front,1,1,1);
//		display_num(gap_back,1,2,1);

	// PD1 	
		while(bit_is_clear(PIND,PD2))
		{
			_delay_ms(50);
			code_select=1;
		}	

	}

*/
	while(code_select==0)
	{
	// PB0
		if( (bit_is_clear(REMOTE_PIN,MECHANISM_LOW_CONT)) || front_continue_1==1)
		{
			front_continue_1=1;
//			_delay_ms(20);
			if(gap_front==0)
			{
				down_front(remote_speed/2);
			}
			else
			{
				breaks('f');
				front_continue_1=0;
			}
		}
	
	// PB1 
		else if( (bit_is_clear(PIND,MECHANISM_HIGH_CONT)) || front_continue_2==1)
		{
			front_continue_2=1;
			if(gap_front==0)
			{
				up_front(remote_speed);
		//		_delay_ms(200);			
			}
			else
			{
				breaks('f');
				front_continue_2=0;
			}
		}	
	
	// PB2 	
		else if(bit_is_clear(REMOTE_PIN,MECHANISM_LOW))
		{
//			_delay_ms(20);
//			while(bit_is_clear(REMOTE_PIN,MECHANISM_LOW))
//			{
				down_front(remote_speed);
//			}
//			breaks('f');
		}

	// PB3 	
		else if(bit_is_clear(REMOTE_PIN,MECHANISM_HIGH))
		{
//			_delay_ms(20);
//			while(bit_is_clear(REMOTE_PIN,MECHANISM_HIGH))
//			{
				up_front(remote_speed);
//			}
//			breaks('f');
		}	

		else
		{
			breaks('f');
		}


	// PB5 	

		if( (bit_is_clear(REMOTE_PIN,REAR_HIGH_CONT)) || (back_continue_1==1))
		{
			back_continue_1=1;
			if(gap_back==0)
			{
				up_back(remote_speed/2);
			}
			else
			{
				breaks('b');
				back_continue_1=0;
			}
		}	

		else if( (bit_is_clear(REMOTE_PIN,REAR_LOW_CONT)) || (back_continue_2==1))
		{
			back_continue_2=1;
			if(gap_back==0)
			{
				down_back(remote_speed);
			}
			else
			{
				breaks('b');
				back_continue_2=0;
			}
		}	

		else if(bit_is_clear(REMOTE_PIN,REAR_LOW))
		{
//			_delay_ms(20);
//			while(bit_is_clear(REMOTE_PIN,REAR_LOW))
//			{
				down_back(remote_speed);
//			}
//			breaks('b');
		}	

	// PB6 	


	// PB7 	
		else if(bit_is_clear(REMOTE_PIN,REAR_HIGH))
		{
//			_delay_ms(50);
//			while(bit_is_clear(REMOTE_PIN,REAR_HIGH))
//			{
				up_back(remote_speed);
//			}
//			breaks('b');
		}	

	// PD0 	
		else
		{
			breaks('b');
		}



	// PD1 	
		while(bit_is_clear(PIND,PD2))
		{
			_delay_ms(100);
			code_select=1;
		}	

	}
	breaks('0');
	breaks('f');
	breaks('b');


}
