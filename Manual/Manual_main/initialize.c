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




void initialize()
{
	enable_debounce=0;
	debounce_level=0;
	enable_level=1;
	LCD=0;
	constant=0;
	l_break=0;
	r_break=0;
	division_factor=level_0;
	init_ports();
	init_ADC();
	init_timer();
	if(LCD==1)
	{
		init_LCD();
	}
}

void init_ports()
{
	ADC_DDR=0x00;
	ADC_PORT=0x00;

	MOTOR_L_DDR |= _BV(MOTOR_L_1) | _BV(MOTOR_L_2);
	MOTOR_R_DDR |= _BV(MOTOR_R_1) | _BV(MOTOR_R_2);
	MOTOR_PWM_DDR |= _BV(MOTOR_PWM_R) | _BV(MOTOR_PWM_L);

	BREAK_DDR &= ~(_BV(BREAK_RIGHT)) & ~(_BV(BREAK_LEFT));
	BREAK_PORT |= _BV(BREAK_RIGHT) | _BV(BREAK_LEFT);
	SPEED_DDR =0x00;
	SPEED_PORT= 0xFF;

//	SPEED_DDR &= ~(_BV(HIGH_SPEED))& ~(_BV(LOW_SPEED));
//	SPEED_PORT |=  _BV(HIGH_SPEED) | _BV((LOW_SPEED));

	CONSTANT_DDR &= ~(_BV(CONSTANT_FRONT)) & ~(_BV(CONSTANT_BACK));
	CONSTANT_PORT |= _BV(CONSTANT_FRONT) | _BV(CONSTANT_BACK);
}

