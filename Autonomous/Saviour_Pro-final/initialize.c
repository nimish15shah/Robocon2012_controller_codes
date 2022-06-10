


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



void initialize(void)
{
	division_factor=20;
	LCD=0;
	init_port();
	init_ADC();
	init_timer();
	init_line_follow();


	if(LCD==1)
	
		init_LCD();
	
}

void init_port(void)
{
	ADC_DDR= 0x00;
	ADC_PORT= 0x00;
	SENSOR_DDR= 0x00;
	SENSOR_PORT= 0x00;
//	LCD_DDR= 0xFF;
//	CONTROL_DDR |= ( (1<<E) | (1<<RS) );

	MOTOR_PWM_DDR |= ( (1<<MOTOR_PWM_R) | (1<<MOTOR_PWM_L) );
	MOTOR_R_DDR |=  ( (1<<MOTOR_R_1) | (1<<MOTOR_R_2) );
	MOTOR_L_DDR |= ( (1<<MOTOR_L_1) | (1<<MOTOR_L_2) );

//	POWER_PLAY_DDR |= _BV(POWER_PLAY_LEFT) | _BV(POWER_PLAY_RIGHT);
//	POWER_PLAY_PORT &= ~(_BV(POWER_PLAY_LEFT)) & ~(_BV(POWER_PLAY_RIGHT));

	COM_DDR |= _BV(OUT_BASKET);
	COM_DDR &= ~(_BV(IN_SENSOR)) & ~(_BV(IN_BASKET));
	COM_PORT |= _BV(IN_SENSOR) | _BV(IN_BASKET) | _BV(OUT_BASKET);
	
	if(LCD==0)
	{
		REMOTE_DDR &= ~(_BV(BLUE)) & ~(_BV(BASKET_1))
					 & ~(_BV(BASKET_2)) & ~(_BV(COLLECTOR))
					 & ~(_BV(RESTART));
		REMOTE_PORT |= (_BV(BLUE)) | (_BV(BASKET_1))
					 | (_BV(BASKET_2)) | (_BV(COLLECTOR))
					 | (_BV(RESTART));

		REMOTE_DDR |= _BV(LED);
		REMOTE_PORT |= _BV(LED);

		DDRD &= ~(_BV(RED)) & ~(_BV(BASKET_CHECK));
		PORTD |= _BV(RED) | _BV(BASKET_CHECK);

		BASKET_SENSE_DDR &= ~(_BV(BASKET_SENSE));
		BASKET_SENSE_PORT |= _BV(BASKET_SENSE);
		
		SIGNAL_DDR |= _BV(SIGNAL_COLLECTOR);
		SIGNAL_PORT &= ~(_BV(SIGNAL_COLLECTOR)); 

	}

}
