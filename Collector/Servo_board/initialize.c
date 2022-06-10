#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "hardware.h"
#include "initialize.h"
#include "timer.h"
#include "LCD.h"
#include "ADC.h"




void initialize(void)
{
	LCD=0;
	init_ports();
	init_timer();
	init_ADC();
	if(LCD==1)
	{	
		init_LCD();
	}
	//return;
}

void init_ports()
{
	SERVO_1_DDR |= (_BV(SERVO_1_PIN)) | (_BV(SERVO_2_PIN)) | (_BV(SERVO_3_PIN));
	ADC_DDR= 0x00;
	ADC_PORT= 0x00;

	REMOTE_DDR= 0x00;
	REMOTE_PORT= 0xFF;
	DDRD &= ~(_BV(END_REMOTE));
	DDRD &= ~(1<<PD2);
	PORTD |= ((1<<END_REMOTE) | (1<<PD2));

	if(LCD!=1)
	{
		COM_DDR |= _BV(OUT_MAIN);
		COM_DDR &= ~(_BV(IN_ENCODER));
		SERVO_4_DDR |= (_BV(SERVO_4_PIN));
	}

	MCUCR |= (_BV(ISC01));
	MCUCR &= ~(_BV(ISC00));
	GICR |= (_BV(INT0));

}

