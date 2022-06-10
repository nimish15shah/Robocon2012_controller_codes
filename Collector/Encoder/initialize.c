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
#include "remote.h"



void initialize()
{
	init_ports();
	init_ADC();
	init_timer();
}

void init_ports()
{
	ADC_DDR= 0x00;
	ADC_PORT= 0x00;

	MOTOR_DDR= 0xFF;
	MOTOR_PORT=0x00;

	REMOTE_DDR= 0x00;
	REMOTE_DDR |= (1<<PB4);	// for providing GND to REMOTE
	REMOTE_PORT= 0xFF;	// pull-up
	REMOTE_PORT &= ~(1<<PB4);
/*
	DDRD &= ~(_BV(END_REMOTE)) & ~(_BV(REAR_HIGH_CONT));
	PORTD |= (_BV(END_REMOTE)) | (_BV(REAR_HIGH_CONT));
*/

	DDRD &= ~(_BV(END_REMOTE)) & ~(_BV(MECHANISM_HIGH_CONT));
	PORTD |= (_BV(END_REMOTE)) | (_BV(MECHANISM_HIGH_CONT));


//	DDR_REAR_MOTOR |= _BV(REAR_MOTOR_PWM) | _BV(REAR_MOTOR_1) | _BV(REAR_MOTOR_2);
	
	COM_DDR= 0x00;
	COM_DDR |= _BV(OUT_MAIN) | _BV(OUT_BACK_SENSOR) | _BV(OUT_SERVO);
	COM_DDR &= ~(_BV(IN_MAIN)) & ~(_BV(IN_BACK_SENSOR));
	COM_PORT &= ~(_BV(OUT_MAIN)) & ~(_BV(OUT_BACK_SENSOR)) & ~(_BV(OUT_SERVO)); 

	PATH_SELECT_DDR &= ~(_BV(PENG_ON_DEI_GATE)) & ~(_BV(RESTART))
					   & ~(_BV(START));
	PATH_SELECT_PORT |= (_BV(PENG_ON_DEI_GATE)) | (_BV(RESTART))
					   | (_BV(START));

	MCUCR |= (_BV(ISC01));
	MCUCR &= ~(_BV(ISC00));
	GICR |= (_BV(INT0));


}

