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

void path_basket_1()
{
// Move towards Basket
//	forward_move();

	while(intersection<7)
	{
		front_line_follow(80,1);	//100
	}
/*	while(1)
	{
		read_sensor();
		if(bit_is_clear(COM_PIN,IN_SENSOR))
		{
			break;
		}
		front_line_follow(60,1);	//80
	}
*/	breaks('b');
	_delay_ms(600);

// Pick Basket
	COM_PORT &= ~(_BV(OUT_BASKET));
	_delay_ms(5);
	COM_PORT |= _BV(OUT_BASKET);


	while(bit_is_set(COM_PIN,IN_BASKET))
	{
//		_delay_ms(10);
		;
	}
// Go back to Droping point
	
	_delay_ms(500);
	init_line_follow();
	while(ADC_result>16)
	{
		reverse(100);
	}
	_delay_ms(100);
	read_sensor();
	while(sensor_read<16)
	{
		read_sensor();
		reverse_double_line_follow(150);	//80
	}
	
	if(path==3)
	{
		if(bit_is_set(BASKET_SENSE_PIN,BASKET_SENSE))
		{
//			_delay_ms(500);

			read_sensor();
/*			while(sensor_read>16)
			{
				read_sensor();
				reverse(100);
			}
*/			_delay_ms(50);
			init_line_follow();
			while(intersection<1)
			{
				reverse_double_line_follow(80);
			}
			read_sensor();
			while(sensor_read<16)
			{
				reverse_double_line_follow(80);
			}
//			_delay_ms(100);
			breaks('b');
//			COM_PORT &= ~(_BV(OUT_BASKET));
			_delay_ms(500);
//			COM_PORT |= (_BV(OUT_BASKET));
			path_basket_2();
		}
	}

	// Move in reverse to drop Basket

/*	while(ADC_result>16)
	{
		reverse(80);
	}
	_delay_ms(200);
*/
	init_line_follow();
	while(intersection<3)
	{
		reverse_double_line_follow(100);	//80
	}

	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		reverse_double_line_follow(70);
	}

	breaks('b');
	_delay_ms(500);


/*
	if(red_arena==1)
	{
//		right_move(150,150);
		right_move(150,150);	//100
//		while(ADC_result!=27)
//		{
//			spin_right(150,150);
//		}
//		while(ADC_result==27 && final_counter<2)
		{
//			spin_right(150,150);
		}

		breaks('b');
		_delay_ms(500);
		forward(100);
		while(ADC_result>16 || final_counter>3);
		debounce=0;
		while(debounce<2500)
		{
			front_line_follow(80,1);
			debounce++;
		}
		breaks('b');
		_delay_ms(500);
		while(ADC_result>16)
		{
			reverse(100);
		}
		breaks('b');
		_delay_ms(100);

		while(bit_is_set(COM_PIN,IN_SENSOR))
		{
			reverse_double_line_follow(80);
		}
		breaks('b');
		_delay_ms(500);

//		while(1)
//		{
//			read_sensor();
//			if(sensor_read>18 && sensor_read<24)
			{
//				break;
			}
//			front_line_follow(80,1);

//		}
		breaks('b');	
		_delay_ms(500);
	
	// Again Move for 180 turn
//		while(ADC_result!=27)
		{
//			spin_right(150,150);
		}
//		while(ADC_result==27 && final_counter<2)
		{
//			spin_right(150,150);
		}

		right_move(150,150);	//100

		breaks('b');
		_delay_ms(500);
		forward(100);
		while(ADC_result>16 || final_counter>3);

	}
	if(blue_arena==1)
	{
//		left_move(150,150);
//		left_move(150,150);
		while(ADC_result!=27)
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
		while(final_counter>3);
		debounce=0;
		while(debounce<1000)
		{
			front_line_follow(80,1);
			debounce++;
		}
		breaks('b');


		breaks('b');

//		while(1)
		{
//			read_sensor();
//			if(sensor_read>18 && sensor_read<24)
			{
//				break;
			}
//			front_line_follow(80,1);

		}
//		breaks('b');	
//		_delay_ms(500);
	
	// Again Move for 180 turn
		while(ADC_result!=27)
		{
			spin_left(150,150);
		}
		while(ADC_result==27 && final_counter<2)
		{
			spin_left(150,150);
		}
		forward(150);
		while(ADC_result>16 || final_counter>3);
		breaks('b');


	}
*/
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
	init_line_follow();
	division_factor=1;
	while(bit_is_set(COM_PIN,IN_SENSOR))
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
		point_line_follow(100);	//80
	}
	read_sensor();
	while(sensor_read>16)
	{
		read_sensor();
		front_line_follow(100,1);
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
		left_move(80,80);	//150
	}

	else if(blue_arena==1)
	{
		right_move(80,80);
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
}















void path_basket_2()
{
	if(path==2 || path==4)
	{
		while(1)
		{
			read_sensor();
			if(sensor_read>18 && sensor_read<24)
			{
				break;
			}
			if(path==2)
			{
				front_line_follow(10,1);
			}
			else if(path==4)
			{
				front_line_follow(60,1);
			}
		}
	}
	breaks('b');
	_delay_ms(500);

	if(path==2 || path==4)
	{
		read_sensor();
		while(sensor_read<16)
		{
			read_sensor();
			reverse(70);
		}
		read_sensor();
		while(sensor_read>16)
		{
			read_sensor();
			reverse(70);
		}
		breaks('b');
		
	}

// Turn to move towards second Basket
	if(red_arena==1)
	{
		right_move(80,80);
	}

	else if(blue_arena==1)
	{
		left_move(80,80);
	}
	breaks('b');
	_delay_ms(500);

// Move forward
/*	debounce=0;
	while(debounce<4000)
	{
		front_line_follow(100,1);
		debounce++;
	}
*/
// for droping collecotr
	if(path==4)
	{
		drop_collector();		
	}

// to follow basket_2 path
	init_line_follow();
	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		point_line_follow(70);
	}

	if(path==3)
	{
		COM_PORT &= ~(_BV(OUT_BASKET));
		_delay_ms(20);
		COM_PORT |= _BV(OUT_BASKET);
	}
	init_line_follow();
	while(intersection<1)
	{
		point_line_follow(60);
	}

	while(1)
	{
		read_sensor();
		if(sensor_read>16 && sensor_read<24)
		{
			break;
		}
		front_line_follow(50,1);

	}

	breaks('b');
	_delay_ms(500);

	read_sensor();
	while(sensor_read<16)
	{
		read_sensor();
		reverse(70);
	}
	read_sensor();
	while(sensor_read>16)
	{
		read_sensor();
		reverse(70);
	}
	breaks('b');


	if(path==3)
	{
		_delay_ms(5000);
	}

// Turn towards 2nd Basket
	if(red_arena==1)
	{
		left_move(70,70);
	}

	else if(blue_arena==1)
	{
		right_move(60,60);
	}
	breaks('b');
	_delay_ms(500);
/*	
	read_sensor();
	while(final_counter<3)
	{
		read_sensor();
		reverse(80);
	}

//	while(final_counter<3)
	{
//		reverse_double_line_follow(80);
	}
	breaks('b');
	_delay_ms(400);
	while(final_counter>3)
	{
		forward(80);
	}
	_delay_ms(500);
*/



// Move finally for 2nd Basket

/*	debounce=0;
	while(debounce<6000)
	{
		front_line_follow(80,1);
	}
*/
	division_factor=1;

	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		point_line_follow(60);
	}
	init_line_follow();
	while(intersection<1)
	{
		point_line_follow(60);
	}


/*
	while(1)
	{
		read_sensor();
		if(bit_is_clear(COM_PIN,IN_SENSOR))
		{
			break;
		}
		front_line_follow(60,1);
	}
*/
	breaks('b');
	_delay_ms(200);
	 
// Indicate to pick Basket
	COM_PORT &= ~(_BV(OUT_BASKET));
	_delay_ms(20);
	COM_PORT |= _BV(OUT_BASKET);
	
	while(bit_is_set(COM_PIN,IN_BASKET))
	{
		;
	}
	
// Move back
	read_sensor();
	while(ADC_result>16)
	{
		read_sensor();
		reverse(100);
	}
	init_line_follow();
	read_sensor();
	while(sensor_read<16)
	{
		read_sensor();
		reverse_double_line_follow(80);
	}
	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		reverse_double_line_follow(80);
	}



	breaks('b');
	_delay_ms(500);

	if(red_arena==1)
	{
		left_move(80,80);
//		while(ADC_result!=27)
		{
//			spin_left(100,100);
		}

	}
	else if(blue_arena==1)
	{
		right_move(80,80);
//		while(ADC_result!=27)
		{
//			spin_right(100,100);
		}

	}
	
	breaks('b');
	_delay_ms(500);

	read_sensor();	
/*	debounce=0;
	reverse(200);
	_delay_ms(500);
	while(debounce<1000)
	{
		reverse_double_line_follow(200);
		debounce++;
	}
*/
/*	read_sensor();
	while(sensor_read>16 || ADC_result>16)
	{
		read_sensor();
		reverse(100);
	}

	debounce=0;
	while(debounce<10000)
	{
		reverse_double_line_follow(100);
		debounce++;
	}
*/

	init_line_follow();
	while(intersection<1)
	{
		point_line_follow(100);
	}
	read_sensor();
	while(sensor_read<16)
	{
		read_sensor();
		point_line_follow(100);
	}

	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		point_line_follow(100);
	}
	breaks('b');
	_delay_ms(500);

// turn for Drop move
	if(blue_arena==1)
	{
		right_move(100,100);
	}
	else if(red_arena==1)
	{
		left_move(100,100);
	}
	breaks('b');
	_delay_ms(500);

	drop_move();

}












void drop_collector()
{
/*	debounce=0;
	while(ADC_result<16 && debounce<10000)
	{
		reverse_double_line_follow(100);
		debounce++;
	}
*/	breaks('b');
	_delay_ms(500);
	init_line_follow();

	division_factor=1;
// till slop climb
	while(intersection<3)
	{
		point_line_follow(175);
	}
	read_sensor();
	while(sensor_read<16)
	{
		read_sensor();
		point_line_follow(150);
	}
	init_line_follow();
	intersection=3;
	while(intersection<6)
	{
		point_line_follow(150);
	}

	breaks('b');
//	_delay_ms(500);
//	Over slop
	while(intersection<8)
	{
		point_line_follow(100);
	}
	breaks('b');
// On falling Slop
	debounce=0;
	while(ADC_result<16 && debounce<6000)
	{
		point_line_follow(100);
		debounce++;
	}
	while(intersection<9)
	{
		point_line_follow(70);
	}
	while(intersection<11)
	{
		point_line_follow(40);
	}
	debounce=0;
	while(implied_intersection==1 || debounce<20000)
	{
		point_line_follow(150);
		debounce++;
	}
// Move forward
	init_line_follow();
	while(intersection<1)
	{
		point_line_follow(100);
	}	

	while(intersection<3)
	{
		front_line_follow(100,1);
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
	breaks('b');
	_delay_ms(500);

// Take 180 degree turn
	right_move(100,100);
	_delay_ms(600);

	init_line_follow();

	while(intersection<1)
	{
		point_line_follow(100);
	}
	breaks('b');
	_delay_ms(500);

	while(ADC_result>16)
	{
		reverse(80);
	}
/*	init_line_follow();
	while(intersection<1)
	{
		reverse_double_line_follow(80);
	}
*/
	read_sensor();
	while(sensor_read<16)
	{
		reverse_double_line_follow(80);
	}
	breaks('b');
	_delay_ms(300);
	right_move(100,100);
	_delay_ms(500);
	
	init_line_follow();	
	while(intersection<1)
	{
		point_line_follow(80);
	}
	breaks('b');
// Move Back

	debounce=0;
//	while(debounce<3000)
	{
//		reverse_double_line_follow(100);
		debounce++;
	}
	
	while(ADC_result>16 || final_counter>5)
	{
		reverse(100);
	}
	_delay_ms(200);
	init_line_follow();
	while(intersection<1)
	{
		reverse_double_line_follow(100);
	}

	while(bit_is_set(COM_PIN,IN_SENSOR))
	{
		reverse_double_line_follow(60);
	}
	SIGNAL_PORT |= _BV(SIGNAL_COLLECTOR);
	
	debounce=0;
	while(debounce<15000)
	{
		reverse_double_line_follow(50);
		debounce++;
	}

	breaks('b');
	_delay_ms(1000);

	SIGNAL_PORT |= _BV(SIGNAL_COLLECTOR);
	_delay_ms(1000);
//	SIGNAL_PORT &= ~(_BV(SIGNAL_COLLECTOR));
	
	while(1);

}
