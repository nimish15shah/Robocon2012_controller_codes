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


void init_timer(void)
{
	TCCR1A= 0b10100001; // for both compare match, 
						//8-bit fast PWM
	pwm_slider=0;
	pwm_balance=0;

	OCR1AH=0x00;
	OCR1AL=0x00;

	OCR1BH=0x00;
	OCR1BL=0x00;

	TCNT1H= 0x00;
	TCNT1L= 0x00;

	TCCR1B |= 0b00001011; // 8-bit fast PWM, prescale 64
	TIMSK |= (1<<TOIE1);

}

ISR(TIMER1_OVF_vect)
{
	OCR1AH=0x00;
	OCR1AL=pwm_slider;
	OCR1BH=0x00;
	OCR1BL=pwm_balance;
}
