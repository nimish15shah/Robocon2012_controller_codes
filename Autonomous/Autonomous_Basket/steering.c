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

void up_slider(char s)
{
	pwm_slider= s;
	MOTOR_PORT |= _BV(SLIDER_MOTOR_UP);
	MOTOR_PORT &= ~(_BV(SLIDER_MOTOR_DOWN));
}

void down_slider(char s)
{
	pwm_slider= s;
	MOTOR_PORT |= _BV(SLIDER_MOTOR_DOWN);
	MOTOR_PORT &= ~(_BV(SLIDER_MOTOR_UP));
}

void in_balance(char s)
{
	pwm_balance= s;
	MOTOR_PORT |= _BV(BALANCE_MOTOR_IN);
	MOTOR_PORT &= ~(_BV(BALANCE_MOTOR_OUT));
}

void out_balance(char s)
{
	pwm_balance= s;
	MOTOR_PORT |= _BV(BALANCE_MOTOR_OUT);
	MOTOR_PORT &= ~(_BV(BALANCE_MOTOR_IN));
}

void break_slider()
{
	pwm_slider= 255;
	MOTOR_PORT &= ~(_BV(SLIDER_MOTOR_DOWN));
	MOTOR_PORT &= ~(_BV(SLIDER_MOTOR_UP));
	
}

void break_balance()
{
	pwm_balance= 255;
	MOTOR_PORT &= ~(_BV(BALANCE_MOTOR_OUT));
	MOTOR_PORT &= ~(_BV(BALANCE_MOTOR_IN));
}
