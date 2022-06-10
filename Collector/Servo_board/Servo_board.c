#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "hardware.h"
#include "initialize.h"
#include "timer.h"
#include "LCD.h"
#include "remote.h"
#include "ADC.h"

int main()
{
	sei();
//	initialize();

	PATH_SELECT_DDR= 0x00;
	PATH_SELECT_PORT= 0xFF;
//	PATH_SELECT_DDR &= ~(_BV(PENG_ON_DEI_GATE));
	
//	_delay_ms(1000);
//	while(1);

	while(1)
	{
		if(bit_is_clear(PATH_SELECT_PIN,START))
		{
			path=1;
			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,RESTART))
		{
			path=1;
			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,MAIN))
		{
			path=1;
			break;
		}


//		if(bit_is_set(COM_PIN,IN_ENCODER))
		{
//			path=1;
//			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,PENG_ON_DEI_GATE))
		{
			path=2;
			break;
		}


		if(bit_is_clear(PATH_SELECT_PIN,EXTRA))
		{
			path=3;
			break;
		}

	}
	_delay_ms(2000);

	initialize();
//	int debounce_i,debounce_j=0;
/*	while(1)
	{
//		display_num(ADC_result,4,1,1);
		if(ADC_channel<4 && ADC_channel!=0)
			display_num(4*ADCH,4,1,(((ADC_channel-1)*6)+ 1));
		else if(ADC_channel>3)
			display_num(4*ADCH,3,2, ((ADC_channel-4)*4)+ 1);
		else if(ADC_channel==0)
		{
			display_num(4*ADCH,3,2,13);
		}
	}
*/	


/*
		while(1)
		{
		SERVO_1_PWM= 11;


		_delay_ms(100);
//		for(debounce_i=0; debounce_i<1000;debounce_i++)
//			for(debounce_j=0;debounce_j<1000;debounce_j++);
		while(SERVO_1_PWM<39)
		{
			SERVO_1_PWM++;
//		for(debounce_i=0; debounce_i<1000;debounce_i++)
//			for(debounce_j=0;debounce_j<1000;debounce_j++);


			_delay_ms(100);
//			display_num(OCR1AL,4,1,1);	
		}
	
		while(SERVO_1_PWM>6)
		{
			SERVO_1_PWM--;
//		for(debounce_i=0; debounce_i<1000;debounce_i++)
//			for(debounce_j=0;debounce_j<1000;debounce_j++);

			_delay_ms(100);
//			display_num(OCR1AL,4,1,1);	
		}
	
		}
//		code_select=0;
		SERVO_1_PWM= 24;
		while(1);
*/		
/*		
		while(1)
		{
			if(bit_is_clear(PIND,END_REMOTE))
			{
				SERVO_1_PWM= SERVO_1_IN;
				SERVO_2_PWM= SERVO_2_IN;
				SERVO_3_PWM= SERVO_3_IN;
				SERVO_4_PWM= SERVO_4_IN;
			}
		
			if(bit_is_clear(REMOTE_PIN,SERVO_1_HIGH))
			{
				SERVO_1_PWM= SERVO_1_OUT;
				SERVO_2_PWM= SERVO_2_OUT;
				SERVO_3_PWM= SERVO_3_OUT;
				SERVO_4_PWM= SERVO_4_OUT;
			}
		}

*/
		SERVO_2_PWM= SERVO_2_OUT;
		SERVO_4_PWM= SERVO_4_OUT;

		SERVO_1_PWM= SERVO_1_OUT;
		SERVO_3_PWM= SERVO_3_OUT;

		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			;
		}
	
	//	Pick Green bun
			SERVO_2_PWM= SERVO_2_OUT;
			SERVO_4_PWM= SERVO_4_OUT;

			SERVO_1_PWM= SERVO_1_OUT;
			SERVO_3_PWM= SERVO_3_OUT;

		_delay_ms(100);

		if(path==1)
		{
//			SERVO_4_PWM= 6;
//			SERVO_2_PWM= 30;

//			_delay_ms(3000);

			SERVO_1_PWM= SERVO_1_IN;
			SERVO_3_PWM= SERVO_3_IN;
		

			_delay_ms(2000);

			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}

		// Pick yellow Bun
	
	//		SERVO_1_PWM= 38;
	//		SERVO_3_PWM= 6;

	//		_delay_ms(5000);

			SERVO_2_PWM= SERVO_2_IN;
			SERVO_4_PWM= SERVO_4_IN;

				_delay_ms(1000);

			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}

		// Release Bun
			SERVO_2_PWM= SERVO_2_OUT;
			SERVO_4_PWM= SERVO_4_OUT;

			_delay_ms(600);

			while(bit_is_clear(COM_PIN,IN_ENCODER))
			{
				;
			}
			SERVO_1_PWM= SERVO_1_OUT;
			SERVO_3_PWM= SERVO_3_OUT;
	
			_delay_ms(2000);		
		// for Purple Bun Clutch And Peng on dei Gate
			while(1)
			{
				_delay_ms(1000);
				while(bit_is_clear(COM_PIN,IN_ENCODER))
				{
					_delay_us(50);
				}
				SERVO_1_PWM= SERVO_1_IN;
				SERVO_3_PWM= SERVO_3_IN;
				_delay_ms(100);
				while(bit_is_clear(COM_PIN,IN_ENCODER))
				{
					_delay_us(1000);
				}
				SERVO_1_PWM= SERVO_1_OUT;
				SERVO_3_PWM= SERVO_3_OUT;
			}


			while(1);
		}
	
	if(path==2)
	{
		// Clutch Purple Bun
				SERVO_1_PWM= SERVO_1_IN;
				SERVO_3_PWM= SERVO_3_IN;
				_delay_ms(1000);
				while(bit_is_clear(COM_PIN,IN_ENCODER))
				{
					_delay_us(50);
				}
				SERVO_1_PWM= SERVO_1_OUT;
				SERVO_3_PWM= SERVO_3_OUT;
	
			while(1)
			{
				_delay_ms(1000);
				while(bit_is_clear(COM_PIN,IN_ENCODER))
				{
					_delay_us(50);
				}
				SERVO_1_PWM= SERVO_1_IN;
				SERVO_3_PWM= SERVO_3_IN;
				_delay_ms(1000);
				while(bit_is_clear(COM_PIN,IN_ENCODER))
				{
					_delay_us(50);
				}
				SERVO_1_PWM= SERVO_1_OUT;
				SERVO_3_PWM= SERVO_3_OUT;
			}


	}



}
