#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "ADC.h"
#include "hardware.h"
#include "LCD.h"

int main()
{
	sei();
	initialize();

	while(1)
	{
		if(ADC_channel != 0)
		{
			if(ADC_channel<5)
				display_num(4*ADCH,3,1,((ADC_channel-1)*4)+1);
			else 
				display_num(4*ADCH,3,2,((ADC_channel-5)*4)+1);
		}
		else
		{
			display_num(4*ADCH,3,2,14);
		}
	}

	while(1)
	{
//		read_sensor();
		display_num(final_counter,4,2,1);
		display_num(ADC_result,4,1,1);
//		display_num(last_ADC_result,4,1,6);

//		_delay_ms(500);
	}



/*		if(ADC_result==9)
		{
			COM_PORT |= _BV(OUT_MAIN);
		}
		else
		{
			COM_PORT &= ~(_BV(OUT_MAIN));
		}
*/
	
}
