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

void right_move(char speed_l,char speed_r)
{
/*
	while(ADC_result!=31)
	{
		spin_right(speed_l,speed_r);
	}
	while( ((ADC_result==31) || (ADC_result>11 && ADC_result<22)) && final_counter<4 )
	{
//		if(ADC_result==31)
		{
			spin_right(speed_l,speed_r);
		}
//		else
		{
//			spin_right(speed_l/2,speed_r/2);
		}
	}
	breaks('b');
	_delay_ms(500);
*/
//		spin_right(100,100);
		while( (((final_temp_result & 0b10000000) != 0b10000000)
			&& ((final_temp_result & 0b01000000) != 0b01000000)) || (final_counter>3) )
		{
			 spin_right(speed_l,speed_r);
		}
		
		while((final_temp_result & 0b00011000) != 0b00011000)
		{
			spin_right(speed_l,speed_r);
		}

		breaks('b');
		_delay_ms(500);

}

void left_move(char speed_l,char speed_r)
{
/*	while(ADC_result!=31)
	{
		spin_left(speed_l,speed_r);
	}
	while( ((ADC_result==31) || (ADC_result<10)) && final_counter<4 )
	{
//		if(ADC_result==27)
		{
			spin_left(speed_l,speed_r);
		}
//		else
		{
//			spin_left(speed_l/2,speed_r/2);
		}


	}
	breaks('b');
	_delay_ms(500);
*/
		while( (((final_temp_result & 0b00000001) != 0b00000001)
			&& ((final_temp_result & 0b00000010) != 0b00000010)) || (final_counter>3) )
		{
			 spin_left(speed_l,speed_r);
		}
		
		while((final_temp_result & 0b00011000) != 0b00011000)
		{
			spin_left(speed_l,speed_r);
		}
		breaks('b');
		_delay_ms(500);

}










void bun_picking()
{
	// Bun picking 

	while(bit_is_clear(COM_PIN,IN_ENCODER)) //extra
	{
		_delay_ms(2);
	}
	while(final_counter<4)
	{
		reverse(100);
	}
	breaks('b');
	_delay_ms(500);

// Indicate to Move sliders down
	COM_PORT |= _BV(OUT_ENCODER);
	_delay_ms(10);
	COM_PORT &= ~(_BV(OUT_ENCODER));

	while(bit_is_clear(COM_PIN,IN_ENCODER))	 //extra
	{	
		;
	}
// Move to pick green Bun
	while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
	{
		front_line_follow(100,1);
	}
	while(bit_is_set(COM_PIN,IN_BACK_SENSOR))
	{
		front_line_follow(100,1);
	}
	breaks('b');
	_delay_ms(500);	

/*	while(bit_is_clear(COM_PIN,IN_FINAL_SENSOR_1)) // Original on 
													29/02
	{
		reverse(80);
	}
	breaks('b');
	_delay_ms(100);
*/
	// Indicate Encoder to pick Green BUN

	COM_PORT |= _BV(OUT_ENCODER);
	_delay_ms(10);
	COM_PORT &= ~(_BV(OUT_ENCODER));

	// Wait to move Towards basket
		while(bit_is_clear(COM_PIN,IN_ENCODER)) //extra
		{
			_delay_ms(2);
		}	

		while(final_counter<4)
		{
			reverse(90);
		}

		breaks('b');
		_delay_ms(500);
	// move towards basket 
// For flat surface

/*		while(final_counter>3)
		{
			front_line_follow(80,1);
		}
		breaks('b');
//		_delay_ms(4000);
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
		drop_move();
		
/*		while(ADC_result<16)
		{
			reverse(100);
		}
		breaks('b');
		_delay_ms(500);
*/
/*		while(final_counter>3)
		{
			front_line_follow(100,1);
		}

		debounce=0;
		while(debounce<8000)
		{
			front_line_follow(100,1);
			debounce++;
		}
*/
		while(bit_is_clear(COM_PIN,IN_FINAL_SENSOR_1))
		{
			reverse(100);
		}

		breaks('b');
		_delay_ms(500);

	// Move for peng on dei gate
		if(red_arena==1)
		{
			right_move(100,100);
		}
		else if(blue_arena==1)
		{
			left_move(100,100);
		}

		breaks('b');
		_delay_ms(500);

		clear_intersection();

	// Indicate encoder to move down
	 	COM_PORT |= _BV(OUT_ENCODER);
		_delay_ms(50);
		COM_PORT &= ~(_BV(OUT_ENCODER));
	

		while(intersection<1)
		{
			front_line_follow(100,1);
		}

/*		while(final_counter>3)
		{
			front_line_follow(100,1);
		}	
		debounce=0;
		while(debounce<8000)
		{
			front_line_follow(100,1);
		}
*/
		while(bit_is_clear(COM_PIN,IN_FINAL_SENSOR_1))
		{
			front_line_follow(100,1);
		}
		breaks('b');
		_delay_ms(600);

	// Turn towards Bun Tower

		if(red_arena==1)
		{
			right_move(80,80);
		}
		if(blue_arena==1)
		{
			left_move(80,80);
		}

		breaks('b');
	// Set Bot for peng on dei gate
		while(ADC_result<16)
		{
			turn_reverse(60,70);
		}	
		breaks('b');
		_delay_ms(500);

		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
			front_line_follow(80,1);
		}
		breaks('b');
		_delay_ms(500);

		while(ADC_result<16)
		{
			turn_reverse(60,70);
		}	
		breaks('b');
		_delay_ms(500);

	// indicate Encoder for peng on dei gate
	
		COM_PORT |= _BV(OUT_ENCODER);
		_delay_ms(50);
		COM_PORT &= ~(_BV(OUT_ENCODER));	
	
	// Wait till Purple Bun pick
	
		while(bit_is_clear(COM_PIN,IN_ENCODER))	//extra
		{
			_delay_ms(2);
		}	
	//
		final_fall=1;
		drop_move();
		while(1)
		{
			;
		}
}









void drop_move()
{
	if(red_arena==1)
	{
		right_move(100,100);
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
	else if(blue_arena==1)
	{
		left_move(100,100);
/*		spin_left(100,100);
		while( (((final_temp_result & 0b00000001) != 0b00000001)
			&& ((final_temp_result & 0b00000010) != 0b00000010)) || (final_counter>3) )
		{
			 spin_left(100,100);
		}
		
		while((final_temp_result & 0b00010000) != 0b0001000
			&& (final_temp_result & 0b00001000) != 0b00001000)
		{
			spin_left(100,100);
		}

		breaks('b');
		_delay_ms(500);
*/
	}
	breaks('b');
	_delay_ms(800);

	clear_intersection();

	while(intersection<1)
	{
		front_line_follow(100,1);
	}

// For flat surfaces
/*
	while(final_counter>3)
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
			front_line_follow(80,1);
		}
	breaks('b');
	_delay_ms(500);


// Indicate Encoder to take sliders up

	COM_PORT |= _BV(OUT_ENCODER);
	_delay_ms(100);
	COM_PORT &= ~(_BV(OUT_ENCODER));

	breaks('b');
	_delay_ms(500);

	// Turn towards Basket

	if(red_arena==1)
	{
		right_move(100,100);
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

	else if(blue_arena==1)
	{
		left_move(100,100);
/*		spin_left(100,100);
		while( (((final_temp_result & 0b00000001) != 0b00000001)
			&& ((final_temp_result & 0b00000010) != 0b00000010)) || (final_counter>3) )
		{
			 spin_left(100,100);
		}
		
		while((final_temp_result & 0b00010000) != 0b0001000
			&& (final_temp_result & 0b00001000) != 0b00001000)
		{
			spin_left(100,100);
		}

		breaks('b');
		_delay_ms(500);
*/
	}

	breaks('b');
	_delay_ms(500);

// basket check
	if(final_fall==0)
	{
		while(break_check==0)		
		{
			while(bit_is_set(BASKET_SENSE_PIN,BASKET_SENSE)
			&& bit_is_clear(COM_PIN,IN_FINAL_SENSOR_2))
			{
				front_line_follow(80,1);
			}
			breaks('b');
			_delay_ms(600);

			if(bit_is_clear(BASKET_SENSE_PIN,BASKET_SENSE))
			{
				break_check=1;
			}
			else
			{
				while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
				{
					reverse(100);
				}
				breaks('b');
				_delay_ms(1000);
			}
		}
	}

//	Indicate Encoder to drop Buns
	COM_PORT |= _BV(OUT_ENCODER);
	_delay_ms(10);
	COM_PORT &= ~(_BV(OUT_ENCODER));
	_delay_ms(500);

// take robot Back To Drop Yellow Bun

		while(bit_is_clear(COM_PIN,IN_BACK_SENSOR))
		{
			reverse(100);
		}
		breaks('b');
		_delay_ms(500);

		debounce=0;
		while(debounce<10000)
		{
			reverse(80);
			debounce++;
		}
		breaks('b');
		_delay_ms(50);
// Indicate to drop yellow bun
		COM_PORT |= _BV(OUT_ENCODER);
		_delay_ms(10);
		COM_PORT &= ~(_BV(OUT_ENCODER));
		_delay_ms(2000);


/*	while(bit_is_clear(COM_PIN,IN_ENCODER)) //extra
	{
		_delay_ms(2);
	}
*/
// Take Robot Ahead to drop Green Bun
/*		while(bit_is_set(BASKET_SENSE_PIN,BASKET_SENSE))
		{
			front_line_follow(80,1);
		}
		breaks('b');
		_delay_ms(500);
//Indicate to drop Green Bun



	while(bit_is_clear(COM_PIN,IN_ENCODER)) //extra
	{
		_delay_ms(2);
	}
*/
}
