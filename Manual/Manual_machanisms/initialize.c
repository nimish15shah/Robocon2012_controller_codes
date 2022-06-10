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






void initialize()
{
	final_auto=0;
	normal=0;
	once=0;
	speed_y=255;
	speed_z=255;
	buzzer_start=0;
	enable_buzzer_y=1;
	enable_buzzer_x=1;
	LCD=0;
	init_ports();
	init_ADC();
	init_timer();
	r_break=0;
	l_break=0;
}

void init_ports()
{
	MOTOR_Z_DDR |= _BV(MOTOR_Z_1) | _BV(MOTOR_Z_2);
	MOTOR_Y_DDR |= _BV(MOTOR_Y_1) | _BV(MOTOR_Y_2);
	MOTOR_PWM_DDR |= _BV(MOTOR_PWM_Z) | _BV(MOTOR_PWM_Y);

	REMOTE_DDR= 0x00;
	REMOTE_PORT= 0xFF;

	BREAK_DDR &= ~(_BV(Y_BREAK_RIGHT)) & ~(_BV(Y_BREAK_LEFT))
				& ~(_BV(X_BREAK));
	BREAK_PORT |= (_BV(Y_BREAK_RIGHT)) | (_BV(Y_BREAK_LEFT))
					| _BV(X_BREAK);
	SIGNAL_DDR |= _BV(SIGNAL_1) | _BV(SIGNAL_2);
	SIGNAL_PORT &= ~(_BV(SIGNAL_2)) & ~(_BV(SIGNAL_1));
	
	DDRD &= ~(_BV(PD2)) & ~(_BV(PD0));
	PORTD |= (_BV(PD2)) | (_BV(PD0));

	BUZZER_DDR |= _BV(BUZZER_SIGNAL);
	BUZZER_PORT |= (_BV(BUZZER_SIGNAL));

	Z_FINAL_DDR &= ~(_BV(Z_FINAL));
	Z_FINAL_PORT |= _BV(Z_FINAL);

//	DDRD &= ~(_BV(Z_UP)) & ~(_BV(Y_LEFT));
//	PORTD |= _BV(Z_UP) | _BV(Y_LEFT);
}
