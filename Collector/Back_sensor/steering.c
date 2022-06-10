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

void yellow_forward(char s)
{
	pwm_yellow= s;
	YELLOW_PORT |= _BV(YELLOW_1);
	YELLOW_PORT &= ~(_BV(YELLOW_2));
}

void yellow_reverse(char s)
{
	pwm_yellow= s;
	YELLOW_PORT |= _BV(YELLOW_2);
	YELLOW_PORT &= ~(_BV(YELLOW_1));
}

void green_right(char s)
{
	pwm_green= s;
	if(LCD!=1)
	{
		GREEN_PORT |= _BV(GREEN_2);
		GREEN_PORT &= ~(_BV(GREEN_1));
	}
}

void green_left(char s)
{
	pwm_green= s;
	if(LCD!=1)
	{
		GREEN_PORT |= _BV(GREEN_1);
		GREEN_PORT &= ~(_BV(GREEN_2));
	}
}

void breaks(char t)
{
	if(t=='y')
	{
		pwm_yellow=255;
		YELLOW_PORT &= ~(_BV(YELLOW_2));
		YELLOW_PORT &= ~(_BV(YELLOW_1));
	}
	else if(t=='g')
	{
		pwm_green=255;
		if(LCD!=1)
		{
			GREEN_PORT &= ~(_BV(GREEN_1));
			GREEN_PORT &= ~(_BV(GREEN_2));
		}
	}
	else if(t=='b')
	{
		pwm_green=255;
		pwm_yellow=255;
		if(LCD!=1)
		{	
			GREEN_PORT &= ~(_BV(GREEN_1));
			GREEN_PORT &= ~(_BV(GREEN_2));
		}
		YELLOW_PORT &= ~(_BV(YELLOW_2));
		YELLOW_PORT &= ~(_BV(YELLOW_1));
	}
	
}
