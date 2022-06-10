#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "hardware.h"
#include "LCD.h"

void initialize()
{
	init_ports();
	init_ADC();
	init_LCD();
}

void init_ports()
{
	ADC_DDR= 0x00;
	ADC_PORT= 0x00;

	COM_DDR= 0x00;
	COM_DDR |= _BV(OUT_MAIN_1) | _BV(OUT_MAIN_2);
	COM_PORT &= ~(_BV(OUT_MAIN_1)) & ~(_BV(OUT_MAIN_2));
}
