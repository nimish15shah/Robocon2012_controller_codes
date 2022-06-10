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

void right_move(char speed_l,char speed_r)
{
	while( ((final_temp_result & 0b10000000) != 0b10000000)
		 && ((final_temp_result & 0b01000000) != 0b01000000) )
	{
		spin_right(speed_l,speed_r);
	}
	_delay_ms(50);
/*	while(final_counter<1)
	{
//		if(ADC_result==27)
		{
			spin_right(speed_l,speed_r);
		}
//		else
		{
//			spin_right(speed_l/2,speed_r/2);
		}
	}
	while( (ADC_result>12 && ADC_result<16) && final_counter<4)
	{
		spin_right(speed_l-10,speed_r-10);
	}
	breaks('b');
	_delay_ms(100);
*/
	while( ((final_temp_result & 0b00010000) != 0b00010000)
		 && ((final_temp_result & 0b00001000) != 0b00001000) )
	{
		spin_right(speed_l,speed_r);
	}

}

void left_move(char speed_l,char speed_r)
{
	while( ((final_temp_result & 0b00000001) != 0b00000001)
		 && ((final_temp_result & 0b00000010) != 0b00000010) )
	{
		spin_left(speed_l,speed_r);
	}
	_delay_ms(50);
/*	while(final_counter<1)
	{
//		if(ADC_result==27)
		{
			spin_right(speed_l,speed_r);
		}
//		else
		{
//			spin_right(speed_l/2,speed_r/2);
		}
	}
	while( (ADC_result>12 && ADC_result<16) && final_counter<4)
	{
		spin_right(speed_l-10,speed_r-10);
	}
	breaks('b');
	_delay_ms(100);
*/
	while( ((final_temp_result & 0b00010000) != 0b00010000)
		 && ((final_temp_result & 0b00001000) != 0b00001000) )
	{
		spin_left(speed_l,speed_r);
	}


/*	while(final_counter!=0)
	{
		spin_left(speed_l,speed_r);
	}
	while( ADC_result==27 && final_counter<1)
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
	while( (ADC_result<3) && final_counter<4 )
	{
		spin_left(speed_l-10,speed_r-10);
	}
	breaks('b');
	_delay_ms(100);
*/
}

void forward_move()
{
	if(path<4)
	{
		COM_PORT &= ~(_BV(OUT_BASKET));
		_delay_ms(5);
		COM_PORT |= _BV(OUT_BASKET);
	}
	while(intersection<3)
			{
				front_line_follow(250,1);	
			}
		
	while(intersection<4)
			{
				front_line_follow(170,1);	
			}
	
	while(intersection<5)
			{
				front_line_follow(50,1);	
			}
}

void drop_move()
{

	debounce=0;
/*	while(debounce<1000)	//5000
	{
		front_line_follow(100,1);	//100
		debounce++;
	}
*/
	init_line_follow();
	while(intersection<3)	//initially 2
	{
		front_line_follow(100,1);	//100
	}
		
	while(1)
	{
		read_sensor();
		if(bit_is_clear(COM_PIN,IN_SENSOR))
		{
			break;
		}
		front_line_follow(80,1);	//80
	}
	
	breaks('b');
	_delay_ms(500);

// Turn to Drop basket
	if(red_arena==1)
	{
		left_move(100,100);	//100
/*		while(ADC_result!=27)
		{
			spin_left(150,150);
		}
		while(ADC_result==27 && final_counter<2)
		{
			spin_left(150,150);
		}
		breaks('b');
		_delay_ms(500);
		forward(150);
		while(ADC_result>16 || final_counter>3);
*/		
	}

	else if(blue_arena==1)
	{
		right_move(100,100);
	}
	breaks('b');
	_delay_ms(500);

/*	debounce=0;
	while(debounce<10000)
	{
		front_line_follow(150,1);
		debounce++;
	}
*/
	division_factor=1;
	init_line_follow();
	while(intersection<1)
	{
		point_line_follow(100);
	}

	while(1)
	{
		read_sensor();
		if(sensor_read>18 && sensor_read<24)
		{
			break;
		}
		point_line_follow(80);	//80
	}
	read_sensor();
	while(sensor_read>16)
	{
		read_sensor();
		front_line_follow(70,1);
	}
	breaks('b');
	_delay_ms(100);



// give signal to drop basket

	COM_PORT &= ~(_BV(OUT_BASKET));
	_delay_ms(20);
	COM_PORT |= _BV(OUT_BASKET);
	
	while(bit_is_set(COM_PIN,IN_BASKET))
	{
		;
	}

// Move Towards Starting point
/*	reverse_double_line_follow(100);	//extra
	_delay_ms(800);			//extra

	
	while(bit_is_set(COM_PIN,IN_BASKET))
	{
		;
	}


	read_sensor();
	while(sensor_read>16)
	{
		reverse_double_line_follow(100);
	}
	COM_PORT &= ~(_BV(OUT_BASKET));
	_delay_ms(20);
	COM_PORT |= _BV(OUT_BASKET);

	
	init_line_follow();
	while(intersection<1)
	{
		reverse_double_line_follow(100);	//100
	}
	breaks('b');
	_delay_ms(500);

	if(red_arena==1)
	{
		right_move(100,100);	//150
	}

	else if(blue_arena==1)
	{
		left_move(100,100);
	}
	init_line_follow();
	while(intersection<2)	//2
	{
		front_line_follow(255,1);
	}

	while(intersection<3)	//2
	{
		front_line_follow(125,1);
	}

	while(1)
	{
		read_sensor();
		if(sensor_read>18 && sensor_read<24)
		{
			break;
		}
		front_line_follow(80,1);
	}
*/
	init_line_follow();
	while(intersection<1)
	{
		reverse_double_line_follow(100);	//100
	}
	read_sensor();
	while(sensor_read<16)
	{
		read_sensor();
		reverse_double_line_follow(80);
	}
	breaks('b');
	_delay_ms(500);
// Indicate to take hands in

	COM_PORT |= _BV(OUT_BASKET);
	_delay_ms(50);
	COM_PORT &= ~(_BV(OUT_BASKET));
//

	division_factor=1;
	if(red_arena==1)
	{
		left_move(100,100);	//150
	}

	else if(blue_arena==1)
	{
		right_move(100,100);
	}
/*
	debounce=0;
	while(debounce<1000)	//5000
	{
		front_line_follow(200,1);
	}
*/	
	init_line_follow();
	while(intersection<3)	//2
	{
		reverse_double_line_follow(100);
	}


	while(intersection<4)	//2
	{
		reverse_double_line_follow(80);
	}

	breaks('b');
	while(1);

	breaks('b');
	while(1);
}




void restart_move()
{
	init_line_follow();
	while(intersection<4)
	{
		reverse_double_line_follow(100);
	}
	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		reverse_double_line_follow(60);
	}
	debounce=0;
	while(debounce<20000)
	{
		reverse_double_line_follow(100);
		debounce++;
	}

	breaks('b');

	SIGNAL_PORT |= _BV(SIGNAL_COLLECTOR);
	_delay_ms(1000);
//	SIGNAL_PORT &= ~(_BV(SIGNAL_COLLECTOR));
	
	while(1);


}

