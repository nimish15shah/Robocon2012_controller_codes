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


void initialize()
{
	gap_yes=0;
	LCD=0;
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
	MOTOR_DDR |= _BV(SLIDER_MOTOR_UP) | _BV(SLIDER_MOTOR_DOWN) | _BV(SLIDER_MOTOR_PWM) 
				| _BV(BALANCE_MOTOR_IN) | _BV(BALANCE_MOTOR_PWM);
	
		
	MOTOR_DDR  |= _BV(BALANCE_MOTOR_OUT);	

	if(LCD==0)
	{
		SWITCH_DDR &= ~(_BV(BALANCE_SWITCH));
		SWITCH_PORT |= _BV(BALANCE_SWITCH);
		DDRD &= ~(_BV(START_REMOTE));
		PORTD |= _BV(START_REMOTE);

		MCUCR |= (_BV(ISC01));
		MCUCR &= ~(_BV(ISC00));
		GICR |= (_BV(INT0));
	
/*		DDRB=0x00;
		DDRB |= _BV(PB4) | _BV(PB5);
		PORTB |= _BV(PB5);
		PORTB &= ~(_BV(PB4));
*/
	}

	ADC_DDR= 0x00;
	ADC_PORT= 0x00;

	REMOTE_DDR &= ~(_BV(SLIDER_UP)) & ~(_BV(SLIDER_DOWN))
					& ~(_BV(BALANCE_IN)) & ~(_BV(BALANCE_OUT))
					& ~(_BV(END_REMOTE));
	REMOTE_PORT |= _BV(SLIDER_UP) | (_BV(SLIDER_DOWN))
					| (_BV(BALANCE_IN)) | (_BV(BALANCE_OUT))
					| (_BV(END_REMOTE));
	REMOTE_PORT |= _BV(SLIDER_UP);


	COM_DDR &= ~(_BV(IN_MAIN));
	COM_DDR |= _BV(OUT_SENSOR) | _BV(OUT_MAIN) ;
	COM_PORT |= _BV(IN_MAIN) | _BV(OUT_SENSOR) | _BV(OUT_MAIN);
}
