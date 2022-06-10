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




void left_forward(char s)
{
	pwm_left=s-5;
	MOTOR_L_PORT |= _BV(MOTOR_L_1);
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
}

void left_reverse(char s)
{
	pwm_left=s-5;
	MOTOR_L_PORT |= _BV(MOTOR_L_2);
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
}

void left_break()
{
	pwm_left=255;
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));
}



void right_forward(char s)
{
	pwm_right=s-5;
	MOTOR_R_PORT |= _BV(MOTOR_R_1);
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
}

void right_reverse(char s)
{
	pwm_right=s-5;
	MOTOR_R_PORT |= _BV(MOTOR_R_2);
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
}

void right_break()
{
	pwm_right=255;
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));
}
