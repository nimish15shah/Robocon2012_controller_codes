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





void up_z(char s)
{
	pwm_z=s;
	MOTOR_Z_PORT |= _BV(MOTOR_Z_1);
	MOTOR_Z_PORT &= ~(_BV(MOTOR_Z_2));
}

void down_z(char s)
{
	pwm_z=s;
	MOTOR_Z_PORT |= _BV(MOTOR_Z_2);
	MOTOR_Z_PORT &= ~(_BV(MOTOR_Z_1));
}

void right_y(char s)
{
	pwm_y=s;
	MOTOR_Y_PORT |= _BV(MOTOR_Y_1);
	MOTOR_Y_PORT &= ~(_BV(MOTOR_Y_2));
}

void left_y(char s)
{
	pwm_y=s;
	MOTOR_Y_PORT |= _BV(MOTOR_Y_2);
	MOTOR_Y_PORT &= ~(_BV(MOTOR_Y_1));
}

void break_z()
{
	pwm_z=255;
	MOTOR_Z_PORT &= ~(_BV(MOTOR_Z_1));
	MOTOR_Z_PORT &= ~(_BV(MOTOR_Z_2));
}

void break_y()
{
	pwm_y=255;
	MOTOR_Y_PORT &= ~(_BV(MOTOR_Y_1));
	MOTOR_Y_PORT &= ~(_BV(MOTOR_Y_2));

}
