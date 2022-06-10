#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "timer.h"
#include "steering.h"




void out_x(char s)
{
	pwm_x=s;
	MOTOR_X_PORT |= _BV(MOTOR_X_1);
	MOTOR_X_PORT &= ~(_BV(MOTOR_X_2));
}

void in_x(char s)
{
	pwm_x=s;
	MOTOR_X_PORT |= _BV(MOTOR_X_2);
	MOTOR_X_PORT &= ~(_BV(MOTOR_X_1));
}

void down_token(char s)
{
	pwm_token=s;
	MOTOR_TOKEN_PORT |= _BV(MOTOR_TOKEN_1);
	MOTOR_TOKEN_PORT &= ~(_BV(MOTOR_TOKEN_2));
}

void up_token(char s)
{
	pwm_token=s;
	MOTOR_TOKEN_PORT |= _BV(MOTOR_TOKEN_2);
	MOTOR_TOKEN_PORT &= ~(_BV(MOTOR_TOKEN_1));
}

void break_x()
{
	pwm_x= 255;
	MOTOR_X_PORT |= _BV(MOTOR_X_2);
	MOTOR_X_PORT |= (_BV(MOTOR_X_1));

}

void break_token()
{
	pwm_token=255;
	MOTOR_TOKEN_PORT |= _BV(MOTOR_TOKEN_2);
	MOTOR_TOKEN_PORT |= (_BV(MOTOR_TOKEN_1));
}

void in_servo(char s)
{
	pwm_servo=s;
	SERVO_PORT |= _BV(SERVO_1);
	SERVO_PORT &= ~(_BV(SERVO_2));
}

void out_servo(char s)
{
	pwm_servo=s;
	SERVO_PORT |= _BV(SERVO_2);
	SERVO_PORT &= ~(_BV(SERVO_1));
}

void break_servo()
{	
	pwm_servo=255;
	SERVO_PORT &= ~(_BV(SERVO_2));
	SERVO_PORT &= ~(_BV(SERVO_1));

}
