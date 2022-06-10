#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "hardware.h"
#include "initialize.h"
#include "timer.h"
#include "LCD.h"
#include "remote.h"




ISR(INT0_vect)
{
//	code_select=1;
	GICR &= ~(_BV(INT0));
	SREG |= (1<<7);
	call_remote();
	GICR |= _BV(INT0);
}

void call_remote()
{
	while((PIND & (1<<END_REMOTE))==(1<<END_REMOTE))
	{
		_delay_ms(100);
/*		if(bit_is_clear(PIND,END_REMOTE))
		{
			SREG &= ~(1<<7);
			display_num(SERVO_1_PWM,2,1,1);
			display_num(SERVO_2_PWM,2,1,4);	
			display_num(SERVO_3_PWM,2,2,1);	
			display_num(SERVO_4_PWM,2,2,4);	
			SREG |= (1<<7);
		}
*/		
		/* SERVO_1 */
		if(bit_is_clear(REMOTE_PIN,SERVO_1_HIGH))
		{
			if(SERVO_1_PWM<UNIVERSAL_HIGH)
				SERVO_1_PWM++;
		}
	
		if(bit_is_clear(REMOTE_PIN,SERVO_1_LOW))
		{
			if(SERVO_1_PWM>UNIVERSAL_LOW)
				SERVO_1_PWM--;
		}

		/* SERVO_2 */
		
		if(bit_is_clear(REMOTE_PIN,SERVO_2_HIGH))
		{
			if(SERVO_2_PWM<UNIVERSAL_HIGH)
				SERVO_2_PWM++;
		}
	
		if(bit_is_clear(REMOTE_PIN,SERVO_2_LOW))
		{
			if(SERVO_2_PWM>UNIVERSAL_LOW)
				SERVO_2_PWM--;
		}

		/* SERVO_3 */
		
		if(bit_is_clear(REMOTE_PIN,SERVO_3_HIGH))
		{
			if(SERVO_3_PWM<UNIVERSAL_HIGH)
				SERVO_3_PWM++;
		}
	
		if(bit_is_clear(REMOTE_PIN,SERVO_3_LOW))
		{
			if(SERVO_3_PWM>UNIVERSAL_LOW)
				SERVO_3_PWM--;
		}

		/* SERVO_4 */

		if(bit_is_clear(REMOTE_PIN,SERVO_4_HIGH))
		{
			if(SERVO_4_PWM<UNIVERSAL_HIGH)
				SERVO_4_PWM++;
		}
	
		if(bit_is_clear(REMOTE_PIN,SERVO_4_LOW))
		{
			if(SERVO_4_PWM>UNIVERSAL_LOW)
				SERVO_4_PWM--;
		}
	


	}
	
}
