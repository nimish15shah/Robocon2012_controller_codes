#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "timer.h"
#include "steering.h"



void initialize()
{
	once=0;
	init_ports();
	init_timer();
}

void init_ports()
{
	MOTOR_X_DDR |= _BV(MOTOR_X_1) | _BV(MOTOR_X_2);
	MOTOR_PWM_DDR_X |= _BV(MOTOR_PWM_X);
	
	MOTOR_TOKEN_DDR |= _BV(MOTOR_TOKEN_1) | _BV(MOTOR_TOKEN_2);
	MOTOR_PWM_DDR_TOKEN |= _BV(MOTOR_PWM_TOKEN);
	
	REMOTE_DDR &= ~(_BV(X_IN)) & ~(_BV(X_OUT))
				& ~(_BV(TOKEN_UP)) & ~(_BV(TOKEN_DOWN))
				& ~(_BV(SERVO_OUT)) & ~(_BV(SERVO_IN));
	
	REMOTE_PORT |= (_BV(X_IN)) | (_BV(X_OUT))
				| (_BV(TOKEN_UP)) | (_BV(TOKEN_DOWN))
				| (_BV(SERVO_OUT)) | (_BV(SERVO_IN));

	REMOTE_DDR= 0x00;
	REMOTE_PORT= 0xFF;
	SERVO_DDR |= _BV(SERVO_PWM) | _BV(SERVO_1) | _BV(SERVO_2);
	
	BREAK_DDR &= ~(_BV(X_BREAK));
	BREAK_PORT |= _BV(X_BREAK);

	AUTO_TOKEN_DDR &= ~(_BV(AUTO_TOKEN));
	AUTO_TOKEN_PORT |= _BV(AUTO_TOKEN);
}
