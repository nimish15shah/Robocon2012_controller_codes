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
#include "collector.h"
//#include "breaking.c"

int main(void)
{
	sei();
	initialize();

	/* display of ADC_results */


/*	while(1)
	{
//		read_sensor();
//		display_num(sensor_read,4,2,1);
		display_num(ADC_result,2,1,1);
//		_delay_ms(500);
	}
*/





	/* Display of each ADCH */

/*	while(1)
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
*/
/*	
	while(1)
	{
		if(bit_is_set(COM_PIN,IN_BACK_SENSOR))
		{
			display_num(1,2,1,1);
		}
		else
			display_num(0,2,1,1);


		if(bit_is_set(COM_PIN,IN_SERVO))
		{
			display_num(1,2,2,1);

		}
		else
		{
			display_num(0,2,2,1);
		}
	
		display_num(ADC_result,2,1,4);

	}

*/

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

		if(bit_is_clear(PATH_SELECT_PIN,MAIN))
		{
			path=3;
//			COM_PORT |= _BV(OUT_ENCODER);
			_delay_ms(5);
//			COM_PORT &= ~(_BV(OUT_ENCODER));
			break;
		}

		if(bit_is_clear(PATH_SELECT_PIN,PENG_ON_DEI_GATE))
		{
			path=4;
			final_fall=1;
			break;
		}


		if(bit_is_clear(PATH_SELECT_PIN,EXTRA))
		{
			path=5;
			break;
		}
	
	}


	while(1)
	{
		if(bit_is_clear(PATH_SELECT_PIN,RED))
		{
			red_arena=1;
			break;
		}
	
		if(bit_is_clear(PATH_SELECT_PIN,BLUE))
		{
			blue_arena=1;
			break;
		}
	
	}


/*	_delay_ms(5000);
	init_LCD();	

	while(1)
	{
		display_num(path,1,1,1);
	}

*/



// Jump from Autonomous
//	_delay_ms(100);
	if(path==1)
	{
		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			_delay_us(50);
			breaks('b');
		}
		reverse(70);
		_delay_ms(800);
		breaks('b');
		_delay_ms(500);

//		_delay_ms(500);
	}
	if(path==1 || path==2)
	{

		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			_delay_us(50);
			breaks('b');
		}
		reverse(70);
		_delay_ms(800);
		breaks('b');
		_delay_ms(10);
		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			_delay_us(50);
			breaks('b');
		}

//		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		clear_intersection();
		while(intersection<1)
		{
			front_line_follow(150,1);
		}	
		while(intersection<2)
		{
			front_line_follow(250,1);
		}
	
		while(1)
		{
			front_line_follow(150,1);
			if(bit_is_set(COM_PIN,IN_SERVO))
			{
				break;
			}
		}
		forward(60);
		_delay_ms(700);

		breaks('b');
		_delay_ms(20);
		
	}




//	 before stair climb
	


	COM_PORT |= _BV(OUT_ENCODER);
	_delay_ms(600);
	COM_PORT &= ~(_BV(OUT_ENCODER));

	clear_intersection();
	
	// Wait for Stair climb

	while(bit_is_clear(COM_PIN,IN_ENCODER))
	{
		;
	}




	// after stair climb 
/*	forward(80);
	_delay_ms(100);
	breaks('b');
	_delay_ms(400);
	spin_threshold= (PINB>>3);
	_delay_ms(10000);
	init_LCD();
	display_num(spin_threshold,4,1,1);
*/
/*	if(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
	{
		spin_threshold=10;
	}
	else if(bit_is_set(COM_PIN,IN_BACK_SENSOR))
	{
		spin_threshold=12;
	}
*/
//	allign(100);
//	COM_PORT &= ~(_BV(OUT_ENCODER));
	division_factor=5;
	init_line_follow();
	while(intersection<1)
	{
		front_line_follow(250,1); // initally 100
	}
	breaks('b');
	_delay_ms(500);

	if(red_arena==1)
	{
		while(final_counter!=0)
		{
			point_left_reverse(200);
		}
	}
	else if(blue_arena==1)
	{
		while(final_counter!=0)
		{
			point_right_reverse(200);
		}
	}

	_delay_ms(100);
	breaks('b');

// Indicate Encoder to take sliders up and again change pattern 
//	of back sensor
	_delay_ms(500);
	while(final_counter!=0)
	{
		turn(80,85);
	}
	
	if(red_arena==1)
	{
		while((ADC_result==31 || ADC_result<9))
		{
			forward(100);
		}
	}

	else if(blue_arena==1)
	{
		while((ADC_result==31) || (ADC_result>13))
		{
			forward(100);
		}

	}
	clear_intersection();
	division_factor=1;

	while(intersection<1)
	{
		front_line_follow(200,1);
	}
	breaks('b');

	// For Flat Surface

//	_delay_ms(4000);
/*	while(final_counter>3)
	{
		front_line_follow(80,1);
	}
	breaks('b');
//	_delay_ms(4000);
	debounce=0;
	while(debounce<8000)
	{
		front_line_follow(80,1);
		debounce++;
	}
*/
	while(bit_is_clear(COM_PIN,IN_FINAL_SENSOR_1))
	{
		front_line_follow(100,1);
	}
	breaks('b');
	

	_delay_ms(500);

	/* turn towards bun tower */
	//Island
/*	if(red_arena==1)
	{
		spin_left(100,100);
		left_move(100,100);
		breaks('b');
		_delay_ms(500);
	}
*/	//On flat surface
	if(red_arena==1)
	{
		left_move(150,150);
/*		spin_left(100,100);
		while( (((final_temp_result & 0b00000001) != 0b00000001)
			&& ((final_temp_result & 0b00000010) != 0b00000010)) || (final_counter>3) )
		{
			 spin_left(100,100);
		}
		
		while((final_temp_result & 0b10000000) != 0b1000000
			&& (final_temp_result & 0b01000000) != 0b01000000)
		{
			spin_left(100,100);
		}
*/
		breaks('b');
		_delay_ms(500);

	}
	
	
	else if(blue_arena==1)
	{
		right_move(150,150);
/*		spin_right(100,100);
		while( (((final_temp_result & 0b10000000) != 0b10000000)
			&& ((final_temp_result & 0b01000000) != 0b01000000)) || (final_counter>3) )
		{
			 spin_right(100,100);
		}
		
		while((final_temp_result & 0b00010000) != 0b0001000
			&& (final_temp_result & 0b00001000) != 0b00001000)
		{
			spin_right(100,100);
		}

		breaks('b');
		_delay_ms(500);
*/

	}



// Move Front and back to allign
	COM_PORT |= _BV(OUT_ENCODER);
	_delay_ms(10);
	COM_PORT &= ~(_BV(OUT_ENCODER));

	debounce=0;
	for(debounce=0;debounce<2;debounce++)
	{
		breaks('b');
		_delay_ms(500);

		while(final_counter<4)
		{
			turn_reverse(80,85);
		}
		breaks('b');
		_delay_ms(500);
		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
/*			if(ADC_result<11)
			{
				turn(0,80);
			}
			else if(ADC_result>80 && ADC_result<22)
			{
				turn(100,0);
			}

			else
			{
				forward(80);
			}
*/			front_line_follow(80,1);
		
		}
		breaks('b');
		_delay_ms(500);

	}
/*	while(bit_is_clear(COM_PIN,IN_FINAL_SENSOR_1))  original till 29/02
	{
		turn_reverse(80,85);
	}
	breaks('b');
	_delay_ms(100);
*/

	while(bit_is_set(COM_PIN,IN_BACK_SENSOR))
	{
		front_line_follow(100,1);
	}
	breaks('b');
	_delay_ms(500);
// Indicate to pick yellow Bun


	if(path<4)
	{
		COM_PORT |= _BV(OUT_ENCODER);
		_delay_ms(50);
		COM_PORT &= ~(_BV(OUT_ENCODER));

		bun_picking();
		while(1);
	}


	if(path==4)
	{
		// take bot back
/*		while(ADC_result<4)
		{
			turn_reverse(80,85);
		}
*/

		// indicate Collector
		COM_PORT |= _BV(OUT_ENCODER);
		_delay_ms(30);
		COM_PORT &= ~(_BV(OUT_ENCODER));
	
		// wait for purple bun pick
		while(bit_is_clear(COM_PIN,IN_ENCODER))
		{
			_delay_ms(2);
		}	
	//
		drop_move();
		while(1)
		{
			;
		}
	}
}


















