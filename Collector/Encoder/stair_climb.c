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


void stair_climb_down(char s)
{
	/* initial debounce in gap */
		while(gap_front==0 || gap_back==0)
		{
			if(gap_back==0)
			{
				down_back(s);
			}
			else if(gap_back==1)
			{
				breaks('b');
			}
		
			if(gap_front==0)
			{
				down_front(s);
			}
		
			else if(gap_front==1)
			{
				breaks('f');
			}
		}
		breaks('b');
//		down_front(s);
//		down_back(s);
		_delay_ms(50);

	/* initial gap */


	/* long run */
		back=0;
		front=0;

		while(back==0 || front==0)
		{
			if(gap_back==0 && back==0)
			{
				down_back(s);
			}
			else if(gap_back==1)
			{
				breaks('b');
				back=1;
			}
		
			if(gap_front==0 && front==0)
			{
				down_front(s);
			}
		
			else if(gap_front==1)
			{
				breaks('f');
				front=1;
			}
		}

	/* end */
		breaks('0');
		_delay_ms(2000);
	
	/* move_aheah */
		PORT_REAR_MOTOR |= _BV(REAR_MOTOR_PWM) | _BV(REAR_MOTOR_1);
		PORT_REAR_MOTOR &= ~(1<<(REAR_MOTOR_2));
		_delay_ms(400);
		
		PORT_REAR_MOTOR |= _BV(REAR_MOTOR_PWM) | _BV(REAR_MOTOR_1) | _BV(REAR_MOTOR_2);
		breaks('0');
		while(1);
}

void calculate_intersection(void)
{
	if(e_front_white && gap_front==1)
	{
		front_white_intersection++;
		e_front_white=0;
		e_front_black=1;
	}
	
	if(e_front_black==1 && gap_front==0)
	{
		front_black_intersection++;
		e_front_black=0;
		e_front_white=1;
	}
	
	if(e_back_white==1 && gap_back==1)
	{
		back_white_intersection++;
		e_back_white=0;
		e_back_black=1;
	}

	if(e_back_black==1 && gap_back==0)
	{
		back_black_intersection++;
		e_back_black=0;
		e_back_white=1;
	}
}

void initialize_intersection(void)
{
	e_front_white=1;
	e_front_black=1;
	e_back_white=1;
	e_back_black=1;
	
	front_black_intersection=0;
	front_white_intersection=0;

	back_black_intersection=0;
	back_white_intersection=0;

}

void initial_debounce(char t,char z)
{
	while(gap_back==t || gap_front==t)
	{
		if(gap_back==t)
		{
			if(z=='d')
			{
				down_back(75);
			}
			if(z=='u')
			{
				up_back(75);	
			}
		}
		else
		{
			breaks('b');
		}

		if(gap_front==t)
		{
			if(z== 'd')
			{
				down_front(75);
			}
			if(z== 'u')
			{
				up_front(75);
			}
		}
		else
		{
			breaks('f');
		}
	}
	breaks('0');
	_delay_ms(20);
}

void stair_climb(char s)
{
	/* initial debounce */
//	initial_debounce(0,'d');
	breaks('0');
	while(gap_front==1)
	{
		down_front(100);
	}
	_delay_ms(50);

	initialize_intersection();
	
	while(front_white_intersection!=2 || back_white_intersection!=3)
	{
		calculate_intersection();
		if(front_white_intersection!=2)
		{
			down_front(180);
		}
		else
		{
			breaks('f');
		}
	
		if(back_white_intersection!=3)
		{
			down_back(255);
		}	
		else
		{
			breaks('b');
		}

	}

	breaks('0');
	_delay_ms(50);
//	while(gap_back==1)
//		down_back(75);
	breaks('0');
//	while(1);
}

