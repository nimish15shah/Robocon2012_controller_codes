#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "hardware.h"
#include "LCD.h"
#include "line_follow.h"
#include "sensor.h"
#include "timer.h"
#include "steering.h"
//#include "breaking.c"



void initialize()
{
	break_check=0;
	final_fall=0;
	division_factor=30;
	LCD=0;
	init_ports();
	init_ADC();
	init_timer();
	init_line_follow();
	if(LCD==1)
	{
		init_LCD();
	}
}

void init_ports()
{
	ADC_DDR= 0x00;
	SENSOR_DDR= 0x00;
	MOTOR_L_DDR |= _BV(MOTOR_L_1) | _BV(MOTOR_L_2);
	MOTOR_R_DDR |= _BV(MOTOR_R_1) | _BV(MOTOR_R_2);
	MOTOR_PWM_DDR |= _BV(MOTOR_PWM_R) | _BV(MOTOR_PWM_L);

//	COM_DDR= 0x00;
	COM_DDR &= ~(_BV(IN_BACK_SENSOR)) & ~(_BV(IN_ENCODER)) &
				~(_BV(IN_SERVO)) & ~(_BV(IN_FINAL_SENSOR_1))
				& ~(_BV(IN_FINAL_SENSOR_2));
	COM_DDR |= _BV(OUT_ENCODER);
	COM_PORT= 0x00;

	if(LCD!=1)
	{
		PATH_SELECT_DDR &= ~(_BV(RED)) & ~(_BV(BLUE))
							& ~(_BV(START)) & ~(_BV(RESTART))
							& ~(_BV(MAIN)) & ~(_BV(PENG_ON_DEI_GATE))
							& ~(_BV(EXTRA));

		PATH_SELECT_PORT |= (_BV(RED)) | (_BV(BLUE))
							| (_BV(START)) | (_BV(RESTART))
							| (_BV(MAIN)) | (_BV(PENG_ON_DEI_GATE))
							| (_BV(EXTRA));
		
		DDRD |= _BV(LED);
		PORTD |= _BV(LED);
	}
	BASKET_SENSE_DDR &= ~(_BV(BASKET_SENSE));
	BASKET_SENSE_PORT |= _BV(BASKET_SENSE);


}
