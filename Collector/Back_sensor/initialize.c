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


void initialize(void)
{
	no_counter=0;
	end=0;
	full_sense=1;
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
	ADC_DDR= 0x00;
	ADC_PORT=0x00;
	YELLOW_DDR |= (_BV(YELLOW_PWM)) | (_BV(YELLOW_1)) | (_BV(YELLOW_2));
	GREEN_DDR |= (_BV(GREEN_PWM)) | (_BV(GREEN_1)) | (_BV(GREEN_2));
	
	REMOTE_DDR &= ~(_BV(YELLOW_HIGH)) & ~(_BV(YELLOW_LOW)) 
					& ~(_BV(GREEN_RIGHT_1)) & ~(_BV(GREEN_LEFT_1))
					& ~(_BV(END_REMOTE)); 
	REMOTE_PORT |= (_BV(YELLOW_HIGH)) | (_BV(YELLOW_LOW)) 
					| (_BV(GREEN_RIGHT_1)) | (_BV(GREEN_LEFT_1))
					| (_BV(END_REMOTE)); 

	COM_DDR |= _BV(OUT_MAIN) | _BV(OUT_ENCODER);
	COM_DDR &= ~(_BV(IN_ENCODER));
	COM_PORT &= ~(_BV(OUT_MAIN)) & ~(_BV(OUT_ENCODER));
	if(LCD==0)
	{
		DDRD &= ~(_BV(PD2));
		PORTD |= _BV(PD2);

		MCUCR |= (_BV(ISC01));
		MCUCR &= ~(_BV(ISC00));
		GICR |= (_BV(INT0));
	
		REAR_MOTOR_DDR |= _BV(REAR_MOTOR_1);
	
		PATH_SELECT_DDR &= ~(_BV(RED)) & ~(_BV(BLUE))
						& ~(_BV(START)) & ~(_BV(RESTART))
						& ~(_BV(MAIN)) & ~(_BV(PENG_ON_DEI_GATE))
						& ~(_BV(EXTRA));

		PATH_SELECT_PORT |=(_BV(RED)) | (_BV(BLUE))
						 | (_BV(START)) | (_BV(RESTART))
						 | (_BV(MAIN)) | (_BV(PENG_ON_DEI_GATE))
						 | (_BV(EXTRA));

	
	}

	


}
