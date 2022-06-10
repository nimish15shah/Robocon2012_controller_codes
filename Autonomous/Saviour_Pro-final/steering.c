#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "define.h"
#include "hardware.h"
#include "LCD.h"
#include "line_follow.h"
#include "sensor.h"
#include "timer.h"
#include "steering.h"


void forward(char l)
{
	pwm_right= l;
	pwm_left= l;
//	display_num(l,4,1,12);
//	display_num(l,4,1,6);

	MOTOR_R_PORT |= _BV(MOTOR_R_1);
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
	MOTOR_L_PORT |= _BV(MOTOR_L_1);
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
}

void reverse(char l)
{
	pwm_right= l;
	pwm_left= l;
//	display_num(l,4,1,12);
//	display_num(l,4,1,6);

	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
	MOTOR_R_PORT |= (_BV(MOTOR_R_2));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
	MOTOR_L_PORT |= (_BV(MOTOR_L_2));

}

void turn(char l, char r)
{
	pwm_right=r;
	pwm_left= l;
//	display_num(pwm_right,4,1,12);
//	display_num(pwm_left,4,1,6);
//	_delay_ms(500);
	MOTOR_R_PORT |= (_BV(MOTOR_R_1));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
	MOTOR_L_PORT |= (_BV(MOTOR_L_1));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
}


void turn_reverse(char l, char r)
{
	pwm_right=r;
	pwm_left= l;
//	display_num(pwm_right,4,1,12);
//	display_num(pwm_left,4,1,6);
//	_delay_ms(500);
	MOTOR_R_PORT |= (_BV(MOTOR_R_2));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
	MOTOR_L_PORT |= (_BV(MOTOR_L_2));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
}


void spin_right(char l, char r)
{
	pwm_right= r;
	pwm_left= l;
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
	MOTOR_R_PORT |= (_BV(MOTOR_R_2));
	MOTOR_L_PORT |= (_BV(MOTOR_L_1));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));

}

void spin_left(char l, char r)
{
	pwm_right= r;
	pwm_left= l;
/*	
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));

	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
	_delay_ms(100);
*/
	MOTOR_R_PORT |= (_BV(MOTOR_R_1));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
	
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
	MOTOR_L_PORT |= (_BV(MOTOR_L_2));
}

void point_left(char s)
{
	pwm_right= s;
	breaks('l');
	MOTOR_R_PORT |= (_BV(MOTOR_R_1));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
}

void point_right(char s)
{
	pwm_left= s;
	breaks('r');
	MOTOR_L_PORT |= (_BV(MOTOR_L_1));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
}

void breaks(char s)
{
	if(s== 'r')
	{
		pwm_right=255;
		MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
		MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
	}
	
	else if(s== 'l')
	{
		pwm_left=255;
		MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
		MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));

	}

	else if(s== 'b')
	{
		pwm_right= 255;
		pwm_left= 255;
		MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
		MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
		MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
		MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
	}

}

/*
void allign()
{
	if(ADC_result<7)
	{
		while(ADC_result==8)
		{
			spin_left(100);
		}
	}



}
*/

void find_theta()
{
	distance_sensor= double_diff*1.25;
//	cos_theta= distance_sensor/sqrt(distance_sensor*distance_sensor + 1600);
	cos_theta= distance_sensor/1;

}

void find_theta_single()
{
	distance_sensor= single_diff*1.25;
//	cos_theta= distance_sensor/sqrt(distance_sensor*distance_sensor + 1600);
	cos_theta= distance_sensor/division_factor;

}
