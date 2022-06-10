#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "hardware.h"
#include "initialize.h"
#include "timer.h"
#include "LCD.h"



void init_timer()
{
	/* TIMER1 for SERV0_1 and SERV0_2 */
	
	TCCR1A= 0b10100001; // for both compare match, 
							//8-bit fast PWM
	SERVO_1_PWM= SERVO_1_OUT;
	SERVO_2_PWM= SERVO_2_OUT;

	OCR1AH=0x00;
	OCR1AL=0x00;

	OCR1BH=0x00;
	OCR1BL=0x00;

	TCNT1H= 0x00;
	TCNT1L= 0x00;

	TCCR1B |= 0b00001100; // 8-bit fast PWM, prescale 64
	TIMSK |= (1<<TOIE1);

	/* TIMER0 for SERVO_4 */
	if(LCD!=1)
	{
		TIMSK |= (1<<TOIE0); // interrupt enable
		SERVO_4_PWM= SERVO_4_OUT;
		OCR0= 0;
		TCNT0= 0;
		TCCR0= 0b01101100;	// Prescale 64, fast PWM, clear on compare
	}
	/* TIMER2 for SERVO_3 */
	TIMSK |= (1<<TOIE2);
	SERVO_3_PWM= SERVO_3_OUT;
	OCR2= 0;
	TCNT2= 0;
	TCCR2= 0b01101110; // Prescale 64, fast PWM, clear on compare

}


ISR(TIMER1_OVF_vect)
{
	OCR1AH=0x00;
	OCR1AL= SERVO_1_PWM;
	OCR1BH=0x00;
	OCR1BL=	SERVO_2_PWM;
//	display_num(pwm_right,4,1,12);
//	display_num(pwm_left,4,1,6);
}

ISR(TIMER2_OVF_vect)
{
	OCR2= SERVO_3_PWM;
}

ISR(TIMER0_OVF_vect)
{
	OCR0= SERVO_4_PWM;
}
