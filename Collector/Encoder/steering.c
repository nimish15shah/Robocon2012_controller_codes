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



void up_back(char s)
{
	pwm_back= s;
	MOTOR_PORT |= (1<<MOTOR_BACK_1);
	MOTOR_PORT &= ~(1<<MOTOR_BACK_2);
}

void down_back(char s)
{
	pwm_back= s;
	MOTOR_PORT &= ~(1<<MOTOR_BACK_1);
	MOTOR_PORT |= (1<<MOTOR_BACK_2);

}

void up_front(char s)
{
	pwm_front=s;
	MOTOR_PORT |= (1<<MOTOR_FRONT_1);
	MOTOR_PORT &= ~(1<<MOTOR_FRONT_2);
}

void down_front(char s)
{
	pwm_front=s;
	MOTOR_PORT &= ~(1<<MOTOR_FRONT_1);
	MOTOR_PORT |= (1<<MOTOR_FRONT_2);

}


void breaks(char s)
{
	if(s == '0')
	{
		pwm_back=255;
		pwm_front=255;
		MOTOR_PORT &= ~(1<<MOTOR_FRONT_1);
		MOTOR_PORT &= ~(1<<MOTOR_FRONT_2);

		MOTOR_PORT &= ~(1<<MOTOR_BACK_2);
		MOTOR_PORT &= ~(1<<MOTOR_BACK_1);
	}

	else if(s== 'f')
	{
		pwm_front=255;
		MOTOR_PORT &= ~(1<<MOTOR_FRONT_1);
		MOTOR_PORT &= ~(1<<MOTOR_FRONT_2);
	}

	else if(s== 'b')
	{
		pwm_back=255;
		MOTOR_PORT &= ~(1<<MOTOR_BACK_2);
		MOTOR_PORT &= ~(1<<MOTOR_BACK_1);
	}
} 
