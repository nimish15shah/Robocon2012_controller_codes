
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "define.h"
#include "hardware.h"
#include "LCD.h"
#include "line_follow.h"
#include "sensor.h"
#include "timer.h"
#include "steering.h"






void init_timer(void)
{
	TCCR1A= 0b10100001; // for both compare match, 
						//8-bit fast PWM
	pwm_left=0;
	pwm_right=0;

	OCR1AH=0x00;
	OCR1AL=0x00;

	OCR1BH=0x00;
	OCR1BL=0x00;

	TCNT1H= 0x00;
	TCNT1L= 0x00;

	TCCR1B |= 0b00001011; // 8-bit fast PWM, prescale 64
	TIMSK |= (1<<TOIE1);
//	TIMSK |= (1<<OCIE1A);
//	TIMSK |= (1<<OCIE1B);
	forward(0);
}

ISR(TIMER1_OVF_vect)
{
	OCR1AH=0x00;
	OCR1AL=pwm_right;
	OCR1BH=0x00;
	OCR1BL=pwm_left;
//	display_num(pwm_right,4,1,12);
//	display_num(pwm_left,4,1,6);
}
/*
ISR(TIMER1_COMPA_vect)
{
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_1));
	MOTOR_R_PORT &= ~(_BV(MOTOR_R_2));

}

ISR(TIMER1_COMPB_vect)
{
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_1));
	MOTOR_L_PORT &= ~(_BV(MOTOR_L_2));

}
*/
