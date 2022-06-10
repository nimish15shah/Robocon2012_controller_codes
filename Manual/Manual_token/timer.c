#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "timer.h"
#include "steering.h"



void init_timer()
{
//	TCCR1A= 0b10100010; // for both compare match, 
						//ICR1 fast PWM
	TCCR1A= 0b10100001; // for both compare match, 
						//8-bit fast PWM


	pwm_x=0;
	pwm_servo=15;
	
	ICR1H= 0x01;
	ICR1L= 0xFF;

	OCR1AH=0x00;
	OCR1AL=0x00;

	OCR1BH=0x00;
	OCR1BL=0x00;
	
	TCNT1H= 0x00;
	TCNT1L= 0x00;

//	TCCR1B |= 0b00011100; // ICR1 top value fast PWM, prescale 64
	TCCR1B |= 0b00001011; // 8-bit fast PWM, prescale 64
	TIMSK |= (1<<TOIE1);
//	TIMSK |= (1<<OCIE1A);
//	TIMSK |= (1<<OCIE1B);
//	forward(0);


	TIMSK |= (1<<TOIE0); // interrupt enable
	pwm_token=0;
	OCR0= 0;
	TCNT0= 0;
	TCCR0= 0b01101100;	// Prescale 64, fast PWM, clear on compare
}

ISR(TIMER1_OVF_vect)
{
	OCR1AH= 0;//(pwm_servo*2 & 0xFF00)>>8 ;
	OCR1AL=	pwm_servo;//(pwm_servo*2 & 0x00FF);
	OCR1BH= 0;	//(pwm_x*2 & 0xFF00)>>8 ;
	OCR1BL= pwm_x;//	(pwm_x*2 & 0x00FF);
}

ISR(TIMER0_OVF_vect)
{
	OCR0= pwm_token;
}


	
