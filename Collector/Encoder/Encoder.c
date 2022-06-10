#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "ADC.h"
#include "Encoder.h"
#include "hardware.h"
#include "initialize.h"
#include "timer.h"
#include "steering.h"
#include "stair_climb.h"
#include "remote.h"
#include "LCD.h"

int main()
{

	sei();

	initialize();
	_delay_ms(10);
	while(1)
	{
		if(bit_is_clear(PATH_SELECT_PIN,START))
		{
			path=1;
			break;
		}
	
		if(bit_is_clear(PATH_SELECT_PIN,RESTART))
		{
			path=2;
			break;
		}
	
		if(bit_is_clear(PATH_SELECT_PIN,PENG_ON_DEI_GATE))
		{
			path=4;
			break;
		}
	
		if(bit_is_set(COM_PIN,IN_BACK_SENSOR))
		{
			path=3;
			_delay_ms(500);
			break;
		}
	
	}

	if(path==1)
	{
		while(autonomous_signal==0)
		{
			_delay_us(10);
		}
	// Take sliders down before slope Climb
		COM_PORT |= _BV(OUT_MAIN);
		_delay_ms(100);
		COM_PORT &= ~(_BV(OUT_MAIN));
		_delay_ms(800);
		initialize_intersection();
		down_back(200);
		while(back_white_intersection<2)
		{
			calculate_intersection();
		}	
		_delay_ms(20);
		initialize_intersection();
		while(back_black_intersection<1)
		{
			calculate_intersection();
		}
		_delay_ms(300);
		breaks('b');
		breaks('f');
		breaks('0');

		initialize_intersection();
		down_front(200);

		while(front_white_intersection<3)
		{
			calculate_intersection();
		}
		breaks('b');
		breaks('f');
		breaks('0');
		_delay_ms(200);
		up_front(200);
		_delay_ms(600);
		breaks('b');
		breaks('f');
		breaks('0');	

	// Take slider up after slope climb
	}

	if(path==2 || path==1)
	{
	// Wait to unload from Autonomous
		while(autonomous_signal==0)
		{
			_delay_ms(1);	
		}

		COM_PORT |= _BV(OUT_MAIN);
		_delay_ms(100);
		COM_PORT &= ~(_BV(OUT_MAIN));
		_delay_ms(700);
		while(gap_back==0)
		{
			up_back(100);
		}
		initialize_intersection();
		_delay_ms(50);
		up_back(150);
		while(back_white_intersection<2)
		{
			calculate_intersection();
		}
		_delay_ms(200);
		initialize_intersection();
		while(gap_back==1)
		{
			;
		}
//		_delay_ms(400);
		breaks('b');
		breaks('f');
		breaks('0');

	_delay_ms(400);
		COM_PORT |= _BV(OUT_MAIN);
		_delay_ms(100);
		COM_PORT &= ~(_BV(OUT_MAIN));




/*		up_front(255);
		initialize_intersection();
		while(front_white_intersection<2)
		{
			calculate_intersection();
		}
		breaks('0');
		breaks('f');
		_delay_ms(200);	
		initialize_intersection();
		while(front_black_intersection<2)
		{
			calculate_intersection();
		}
		breaks('f');
		breaks('0');
		_delay_ms(100);
		while(gap_front==0)
		{
			down_front(255);
		}
		_delay_ms(50);
		breaks('0');
		breaks('f');
*/	}







/*

		while(bit_is_clear(COM_PIN,IN_MAIN));
	
			stair_climb(90);							
			breaks('0');
			_delay_ms(100);
	
		COM_PORT |= (1<<3);
			_delay_ms(100);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
			
			while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
			{
				_delay_ms(2);
			}
		
	// take sliders up
			up_back(100);
			_delay_ms(500);
			
			initialize_intersection();	
			while(back_black_intersection!=2 || front_white_intersection!=2)
			{
				calculate_intersection();
				if(back_black_intersection!=2)
				{
					up_back(150);
				}
				else
				{
					breaks('b');
				}
				
				if(front_white_intersection!=2)
				{
					up_front(100);
				}
				else
				{
					breaks('f');
				}
			
			}
	
			breaks('0');
			_delay_ms(100);
			
			COM_PORT |= _BV(OUT_MAIN);
			_delay_ms(100);
			COM_PORT &= ~(_BV(OUT_MAIN));
*/			

		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			_delay_ms(1);
		}	
		stair_climb_move();
	// Wait for signal from main
//		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
//			_delay_us(40);
		}
//

	//	Take Sliders up For Safety From green bun
			_delay_ms(1000);

			COM_PORT |= _BV(OUT_BACK_SENSOR);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_BACK_SENSOR));

			initialize_intersection();
			up_front(255);
			_delay_ms(50);
			while(front_black_intersection<3)
			{
				calculate_intersection();
			}
			_delay_ms(100);
			initialize_intersection();
			up_front(200);	
			while(front_white_intersection<1)
			{
				calculate_intersection();
			}
			breaks('0');
			breaks('f');
			breaks('b');
/*	// signal for signalling back_sensor
	
		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			;
		}
		COM_PORT |= _BV(OUT_BACK_SENSOR);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
		_delay_ms(200);

*/
	// wait for signal before picking yellow bun
		
		while(bit_is_clear(COM_PIN,IN_MAIN))	//original
		{
			_delay_ms(2);
		}
		_delay_ms(500);
		COM_PORT |= _BV(OUT_BACK_SENSOR);	// Extra on 28/02
		_delay_ms(15);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
	
		if(path==4)
		{
			initialize_intersection();
			up_front(200);
			while(front_black_intersection<2)
			{
				calculate_intersection();
			}
			breaks('0');
			breaks('f');
			breaks('b');
			goto COMMUNICATION;
		}

	// Give signal for picking Yellow Bun
		
/*		_delay_ms(500);		// Original till 28/02

		COM_PORT |= _BV(OUT_BACK_SENSOR);	// Original till 28/02
		_delay_ms(15);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));

		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR)) // Original till 28/02
		{
			_delay_us(40);
		}
*/		
		get_s_main=0;
		get_s_back_sensor=0;
		while(get_s_main==0 || get_s_back_sensor==0)
		{
			if(bit_is_set(COM_PIN,IN_MAIN))
			{
				get_s_main=1;
			}
		
			if(bit_is_set(COM_PIN,IN_BACK_SENSOR))
			{
				get_s_back_sensor=1;
			}
		}		

		_delay_ms(500);
		COM_PORT |= _BV(OUT_SERVO);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_SERVO));

		_delay_ms(2000);

	// Move slider after holding yellow BUn to take it out
		initialize_intersection();
		up_front(255);
		_delay_ms(50);
		while(front_black_intersection<1)
		{
			calculate_intersection();
		}
		initialize_intersection();
		while(front_white_intersection<1)
		{
			calculate_intersection();
		}

		breaks('0');
		_delay_ms(1000);
		
		COM_PORT |= _BV(OUT_BACK_SENSOR);
		_delay_ms(10); // remaining from here
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
		
		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
			;
		}	

	
	// Give signal to Move Back
		
		_delay_ms(1000);
		
		COM_PORT |= _BV(OUT_MAIN);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_MAIN));
		
		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			;
		}

	// Take sliders down for Green bun Picking

		down_front(255);
		while(gap_front==0)
		{
			;
		}
		_delay_ms(100);
		initialize_intersection();
		while(front_black_intersection<4)
		{
			calculate_intersection();
		}
		initialize_intersection();
		_delay_ms(5);
		while(front_white_intersection<1)
		{
			calculate_intersection();
		}

		breaks('0');
		breaks('f');
		breaks('b');


	// Give signal to main to move towards Green Bun

		COM_PORT |= _BV(OUT_MAIN);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_MAIN));	

		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			;
		}
		
	//	Pick Green Bun
		_delay_ms(100);
		COM_PORT |= _BV(OUT_SERVO);
		_delay_ms(50);
		COM_PORT &= ~(_BV(OUT_SERVO));

		_delay_ms(2500);
	// After cluthing Green Bun
				
			initialize_intersection();
			up_front(255);
			_delay_ms(10);
			while(front_black_intersection<2)
			{
				calculate_intersection();
			}
//				_delay_ms(50);
			initialize_intersection();
			up_front(150);
			while(front_white_intersection<1)
			{
				calculate_intersection();
			}
			
			breaks('0');
			breaks('f');
			breaks('b');
	
	//	Indicate Bot to move Towards Bun Tower
			COM_PORT |= _BV(OUT_MAIN);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_MAIN));
	// Indicate to take green hand in
			
			COM_PORT |= _BV(OUT_BACK_SENSOR);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_BACK_SENSOR));

			while(bit_is_clear(COM_PIN,IN_MAIN))
			{
				;
			}

	// Take Sliders Up to drop Buns

			initialize_intersection();
			up_front(255);
			_delay_ms(50);
			while(front_black_intersection<2)
			{
				calculate_intersection();
			}
			_delay_ms(100);
	// Continue with taking slider up
			COM_PORT |= _BV(OUT_BACK_SENSOR);
			_delay_ms(5);
			COM_PORT &= ~(_BV(OUT_BACK_SENSOR));

			initialize_intersection();
			up_front(200);	
			while(front_white_intersection<1)
			{
				calculate_intersection();
			}
			
			breaks('0');
			breaks('f');
			breaks('b');
			
	// Wait for Signal From main to release Bun
		while(bit_is_clear(COM_PIN,IN_MAIN))
		{	
			;
		}
		// Release Green BUN
			COM_PORT |= _BV(OUT_SERVO);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_SERVO));			
			_delay_ms(500);

		// Release Yellow Bun

		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			;
		}

			_delay_ms(1000);

			COM_PORT |= _BV(OUT_SERVO);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_SERVO));
		
			_delay_ms(200);

		COM_PORT |= _BV(OUT_BACK_SENSOR);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));

/*	// Indicate to Take out yellow bun
		COM_PORT |= _BV(OUT_BACK_SENSOR);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
		
		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
			;
		}

	// Indicate Main to move Robot ahead
			COM_PORT |= _BV(OUT_MAIN);
			_delay_ms(10);
			COM_PORT &= ~(_BV(OUT_MAIN));
	
	// Indicate to Take green Bun in		
//			COM_PORT |= _BV(OUT_BACK_SENSOR);
//			_delay_ms(20);
//			COM_PORT &= ~(_BV(OUT_BACK_SENSOR));


	// Wait For main to Move ahead

	// Move for PENG_ON_DEI_GAT
			COM_PORT |= _BV(OUT_MAIN);
			_delay_ms(50);
			COM_PORT &= ~(_BV(OUT_MAIN));
*/		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			_delay_us(50);
		}
	//Move hand in to be safe from Bun tower
		down_front(255);
		initialize_intersection();
		while(front_white_intersection<2)
		{
			calculate_intersection();
		}
		breaks('f');
		breaks('0');
	// Wait till bot reaches Bun tower
			while(bit_is_clear(COM_PIN,IN_MAIN))
			{
				_delay_ms(2);
			}
	//Peng On dei gate
COMMUNICATION:

		PATH_SELECT_DDR |= _BV(START) | _BV(RESTART);		
		PATH_SELECT_PORT |= _BV(START) | _BV(RESTART);
		end=0;
		while(end==0)
		{
			if(manual_signal_1==1
			 && manual_signal_2==0 && back==0) //to move hand ahead
			{
				COM_PORT |= _BV(OUT_BACK_SENSOR);
				ahead=1;
			}
			else
			{
				COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
				ahead=0;
			}
			if(manual_signal_1==0 
			&& manual_signal_2==1 && ahead==0) // To move Hand back
			{
				PATH_SELECT_PORT &= ~(_BV(START));
				back=1;
			}		
			else 
			{
				PATH_SELECT_PORT |= _BV(START);
				back=0;
			}
		
			if(manual_signal_1==1 
			&& manual_signal_2==1) // for Bun clutch
			{
				COM_PORT |= _BV(OUT_SERVO);
				end=1;
				_delay_ms(2000);
			}
			else
			{
				COM_PORT &= ~(_BV(OUT_SERVO));
			}
		}			
	// After First Bun clutch 	
		end=0;
		while(end==0)
		{
			if(manual_signal_1==1 
			&& manual_signal_2==0) //to take Bun back Auto matically
			{
				PATH_SELECT_PORT &= ~(_BV(RESTART));
				_delay_ms(10);
				PATH_SELECT_PORT |= _BV(RESTART);
				end=1;
			}
			else
			{
				COM_PORT &= ~(_BV(OUT_BACK_SENSOR));
			}
			if(manual_signal_1==0
			 && manual_signal_2==1) // To take Bun back Manuually
			{
				PATH_SELECT_PORT &= ~(_BV(START));
			}		
			else
			{
				PATH_SELECT_PORT |= _BV(START);
			}
		
			if(manual_signal_1==1
			 && manual_signal_2==1) // To again open Servos Arm
			{
				COM_PORT |= _BV(OUT_SERVO);
				_delay_ms(500);
			}
			else
			{
				COM_PORT &= ~(_BV(OUT_SERVO));
			}
			
		}
	// After final Bun clutch ready to move towards basket
		end=0;
		while(end==0)
		{
			if(manual_signal_1==0 
			&& manual_signal_2==1) // to take hand in mannualy
			{
				PATH_SELECT_PORT &= ~(_BV(START));
			}		
			else
			{
				PATH_SELECT_PORT |= _BV(START);
			}

			if(manual_signal_1==1 
			&& manual_signal_2==1) // End of bun clutching
			{
				end=1;
			}
		}
		PATH_SELECT_PORT &= ~(_BV(START));
		PATH_SELECT_PORT &= ~(_BV(RESTART));
		COM_PORT |= (_BV(OUT_BACK_SENSOR));
		_delay_ms(1000);
		
	// Wait for final signal to move towards basket
		while(manual_signal_1==0 && manual_signal_2==0)
		{
			;
		}
		_delay_ms(2000);
	
	// Indicate main to maove towards basket
		COM_PORT |= _BV(OUT_MAIN);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_MAIN));
	// Wait for final Bun drop
		while(bit_is_clear(COM_PIN,IN_MAIN))
		{
			_delay_us(40);
		}
		COM_PORT |= _BV(OUT_BACK_SENSOR);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_BACK_SENSOR));	
		
		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
			_delay_us(50);
		}
		_delay_ms(1500);
		COM_PIN |= _BV(OUT_SERVO);
		_delay_ms(400);

		while(1)
		{
			COM_PIN &= _BV(OUT_SERVO);
			_delay_ms(1100);
			COM_PIN |= _BV(OUT_SERVO);
			_delay_ms(1100);
		}

}
