#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "timer.h"
#include "steering.h"



int main()
{
	sei();
	initialize();

	while(1)
	{
		if(bit_is_clear(REMOTE_PIN,X_IN) && break_x_in==0)
		{
			in_x(255);
		}
		else if(bit_is_clear(REMOTE_PIN,X_OUT))
		{
			out_x(255);
		}
		else
		{
			break_x();
		}

		if(bit_is_clear(REMOTE_PIN,TOKEN_UP))
		{
			up_token(255);
		}
		else if(bit_is_clear(REMOTE_PIN,TOKEN_DOWN))
		{
			down_token(255);
		}
		else
		{
			break_token();
		}
		
		if(bit_is_clear(REMOTE_PIN,SERVO_IN))
		{
			in_servo(100);
		}
		else if(bit_is_clear(REMOTE_PIN,SERVO_OUT))
		{
			out_servo(100);
		}
		else
		{
			break_servo();
		}
	
	// Check Break Switch
		if(bit_is_clear(BREAK_PIN,X_BREAK))
		{
			if(break_x_in==0)
			{
				break_x();
			}
			break_x_in=1;
		}
		else
		{
			break_x_in=0;
		}

	//.Auto token
		if(bit_is_clear(AUTO_TOKEN_PIN,AUTO_TOKEN) && once==0)
		{
			down_token(255);
			_delay_ms(3000);
			break_token();
			once=1;
		}
	
	}
}
