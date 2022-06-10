#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "initialize.h"
#include "hardware.h"
#include "ADC.h"
#include "LCD.h"


int main(void)
{
	sei();
	initialize();
	while(1)
	{
//  Display All ADC channels
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


/*	
	while(1)
	{
		display_num(ADC_result,4,1,1);
	}
*/	
	
	}
}
