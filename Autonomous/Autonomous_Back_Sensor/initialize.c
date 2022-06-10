#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "ADC.h"
#include "LCD.h"

void initialize()
{
	LCD=1;
	init_port();
	init_ADC();
	if(LCD==1)
	{
		init_LCD();
	}

}

void init_port(void)
{
	ADC_DDR= 0x00;
	ADC_PORT= 0x00;
	SENSOR_DDR= 0b11111000;
	SENSOR_PORT= 0b11111111;

}
