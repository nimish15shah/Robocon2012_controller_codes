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






int main()
{
	sei();
	initialize();
//  Display All ADC channels

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
		read_sensor();
		display_num(sensor_read,4,2,1);
		display_num(ADC_result,4,1,1);
		display_num(last_ADC_result,4,1,6);

//		_delay_ms(500);
	}
*/
/*	while(1)
	{
		if(bit_is_clear(COM_PIN,IN_SENSOR))
		{
			display_num(1,1,1,1);
		}
		else
		{
			display_num(0,1,1,1);
		}	
	
		if(bit_is_clear(COM_PIN,IN_BASKET))
		{
			display_num(1,1,2,1);
		}
		else 
		{	
			display_num(0,1,2,1);
		}


		COM_PORT |= _BV(OUT_BASKET);
		_delay_ms(500);
		COM_PORT &= ~(_BV(OUT_BASKET));
		_delay_ms(500);
	}
*/

//	forward(150);
	
	while(1)
	{
		blue_arena=0;
		red_arena=0;
		while(1)
		{
			if(bit_is_clear(REMOTE_PIN,BLUE) || bit_is_clear(RED_PIN,RED))
			{
				if(bit_is_clear(RED_PIN,RED))
				{
					red_arena=1;
				}
			
				if(bit_is_clear(REMOTE_PIN,BLUE))
				{
					blue_arena=1;
				}
				break;
			}
		}

		while(1)
		{
			red_arena=1;
			if(bit_is_clear(REMOTE_PIN,BASKET_2))
			{
				path=2;
				forward_move();
				path_basket_2();
				break;
			}
					
			else if(bit_is_clear(REMOTE_PIN,BASKET_1))
			{
				path=1;
				forward_move();	
				path_basket_1();
				break;
			}
					
			else if(bit_is_clear(PIND,BASKET_CHECK))
			{
				path=3;
				forward_move();
				path_basket_1();
				break;
			}
			
			else if(bit_is_clear(REMOTE_PIN,COLLECTOR))
			{
				path=4;
				_delay_ms(500);
				forward_move();
				while(intersection<6)
				{
					front_line_follow(70,1);
				}
				breaks('b');
	//			_delay_ms(300);
				path_basket_2();
				break;
			}
		
			else if(bit_is_clear(REMOTE_PIN,RESTART))
			{
				path=5;
				restart_move();
				break;
			}
		}
		
		while(1);
	}
}
		// Moving towards Basket
/*		if(red_arena==1 && blue_arena==0)
		{
			if(path<5)
			{
				while(intersection<5)
				{
					front_line_follow(255,1);	
				}
			

				while(intersection<6)
				{
					front_line_follow(100,1);	
				}

			}
		}
		
		
		
			if(path==1 || path==3)
			{
				while(intersection<7)
				{
					front_line_follow(80,1);
				}

				while(1)
				{
					read_sensor();
					if(bit_is_clear(COM_PIN,IN_SENSOR));
					{
						break;
					}

					front_line_follow(80,1);
				}
			}

			else if(path==2 || path==4)
			{
				while(1)
				{
					read_sensor();

					if(sensor_read>18 && sensor_read<24)
					{
						break;
					}
			
					front_line_follow(80,1);
				}			
			}
			breaks('b');
			_delay_ms(500);
			
			if(path==1 || )

				COM_PORT &= ~(_BV(OUT_BASKET));
				_delay_ms(100);
				COM_PORT |= _BV(OUT_BASKET);

			while(bit_is_set(COM_PIN,IN_BASKET))
			{
				;
			}
		
		//Move to drop the basket 
			intersection=0;
			temp_intersection=0;
			enable_intersection=1;
			reverse(150);
			_delay_ms(100);
			while(sensor_read>16)
			{
				reverse_double_line_follow(100);
			}
		
			intersection=0;
			temp_intersection=0;
			enable_intersection=1;
	
			while(intersection<4)
			{
				reverse_double_line_follow(200);
			}
				breaks('b');
				_delay_ms(500);
	
*/	/*	// new method
			reverse(100);
			_delay_ms(300);

			while(ADC_result!=27)
			{
				spin_right(100,100);
			}

			while((ADC_result>10 && ADC_result<16) || ADC_result==27)
			{
				spin_right(100,100);
			}

			while(ADC_result!=27)
			{
				spin_right(100,100);
			}

			while((ADC_result>10 && ADC_result<16) || ADC_result==27)
			{
				spin_right(100,100);
			}
			breaks('b');	
			_delay_ms(200);
				debounce=0;
			while(debounce<6000)
			{
				front_line_follow(100,1);
				debounce++;
			}


		
			intersection=0;
			temp_intersection=0;
			enable_intersection=1;

			while(intersection<3)
			{
				front_line_follow(100,1);
			}
			_delay_ms(200);
			reverse(100);
			_delay_ms(400);

			while(ADC_result!=27)
				spin_right(100,100);	
		
	//			_delay_ms(100);
		
			while( (ADC_result>10 && ADC_result<16) || ADC_result==27  )
			{
				spin_left(100,100);	
			}
	
		//180 turn
	

			breaks('b');
			_delay_ms(300);		
	*/

	/*			read_sensor();
				reverse(90);	
				debounce=0;
			while(sensor_read<16 && debounce<1000)
			{
				read_sensor();
				debounce++;
			}
				_delay_ms(100);
				breaks('b');
				_delay_ms(100);		
	*/
/*				while(ADC_result!=27)
				spin_right(100,100);	
		
	//			_delay_ms(100);
		
			while( (ADC_result>10) )
			{
				spin_right(75,75);	
			}
	
		//180 turn
	

			breaks('b');
			_delay_ms(300);		
		
				debounce=0;
			while(debounce<6000)
			{
				front_line_follow(100,1);
				debounce++;
			}

			intersection=0;
			temp_intersection=0;
			enable_intersection=1;

			read_sensor();

			while(sensor_read<17 || sensor_read>24)
			{
				read_sensor();
				front_line_follow(75,1);
			}
		
	//		while(intersection<2)
			{
	//			front_line_follow(60,1);
			}
	//


				breaks('b');
	//			_delay_ms(2000);
			COM_PORT &= ~(_BV(OUT_BASKET));
			_delay_ms(100);
			COM_PORT |= _BV(OUT_BASKET);

			while(bit_is_set(COM_PIN,IN_BASKET))
			{
				;
			}

			intersection=0;
			temp_intersection=0;
			enable_intersection=1;
		
	//		debounce=0;
	//		while(debounce<1000)
	//		{
	//			reverse_line_follow(100);
	//			debounce++;
	//		}
	//		while(intersection<2)
	//		{
	//			reverse_line_follow(75);
	//		}	
	//
			read_sensor();
			while(sensor_read>15)
			{
				reverse(100);
				read_sensor();
			}
				debounce=0;
			while(debounce<600)
			{
				reverse_double_line_follow(150);
				debounce++;
			}
	
	//		reverse(75);
	//		_delay_ms(100);
	
	//		while(ADC_result>15)
	//		reverse(75);

			intersection=0;
			temp_intersection=0;
			enable_intersection=1;

			while(intersection<1)
			{
				reverse_double_line_follow(100);
			}	
				breaks('b');
				_delay_ms(300);
				while(ADC_result!=27)
					spin_right(75,75);	
	//			_delay_ms(100);

			while( (ADC_result<6) || (ADC_result>10) )
			{
				spin_right(75,75);	
			}
			breaks('b');
			_delay_ms(500);		

	//		reverse(100);
	//		_delay_ms(100);
			debounce=0;
			while(debounce<6000)
			{
				front_line_follow(150,1);
				debounce++;
			}

			intersection=0;
			temp_intersection=0;
			enable_intersection=1;
			while(intersection<1)
			{
				front_line_follow(150,1);
			}
		
			while(intersection<2)
			{
				front_line_follow(55,1);
			}

				breaks('b');
				_delay_ms(4000);
			intersection=0;
			temp_intersection=0;
			enable_intersection=1;

	
			while(intersection<5)
			{
	//			forward(255);
				front_line_follow(255,1);	
	//			display_num(ADC_result,4,1,1);
	//			display_num(sensor_read,4,2,1);
			}
			while(intersection<6)
			{
	//			forward(255);
				front_line_follow(100,1);	
	//			display_num(ADC_result,4,1,1);
	//			display_num(sensor_read,4,2,1);
			}

			while(1)
			{
				read_sensor();
				if(sensor_read>15)
				{
					break;
				}
				front_line_follow(55,1);
			}
			breaks('b');
			_delay_ms(500);

				while(ADC_result<16)
				spin_right(100,100);	
		
	//			_delay_ms(100);
		
			while( (ADC_result<6) || (ADC_result>10) )
			{
				spin_right(75,75);	
			}
			breaks('b');
			_delay_ms(300);		
		
				debounce=0;
			while(debounce<8000)
			{
				front_line_follow(100,1);
				debounce++;
			}

			intersection=0;
			temp_intersection=0;
			enable_intersection=1;

			while(intersection<13)
			{
	//			forward(255);
				front_line_follow(255,1);	
	//			display_num(ADC_result,4,1,1);
	//			display_num(sensor_read,4,2,1);
			}
			breaks('b');
			_delay_ms(100);

			while(ADC_result!=27)
			{
				spin_left(75,75);

			}			
		
			while(ADC_result<5 && ADC_result>10)
			{
				spin_left(75,75);
			}			
		
			while(ADC_result!=27)
			{
				spin_left(75,75);

			}			
					while(ADC_result<5 && ADC_result>10)
			{
				spin_left(75,75);

			}			
			breaks('b');
			_delay_ms(200);




			while(1);

				spin_left(100,100);	
				_delay_ms(800);

			while( (ADC_result<6) || (ADC_result>10) )
			{
				spin_left(75,75);	
			}
			breaks('b');
			_delay_ms(500);		

				debounce=0;
			while(debounce<5000)
			{
				front_line_follow(150,1);
				debounce++;
			}


			intersection=0;
			temp_intersection=0;
			enable_intersection=1;
			while(intersection<3)
			{
				front_line_follow(100,1);
			}	

			while(intersection<4)
			{
				reverse_double_line_follow(75);
			}	
				breaks('b');
				_delay_ms(5000);
		
				intersection=0;
			temp_intersection=0;
			enable_intersection=1;

	
			while(intersection<5)
			{
	//			forward(255);
				front_line_follow(255,1);	
	//			display_num(ADC_result,4,1,1);
	//			display_num(sensor_read,4,2,1);
			}
			while(intersection<6)
			{
	//			forward(255);
				front_line_follow(100,1);	
	//			display_num(ADC_result,4,1,1);
	//			display_num(sensor_read,4,2,1);
			}

		


		}

	*/
	/*	while(1)
		{
	////
		
			while(sensor_read==21)
			{
				front_line_follow();
			}
		
			while(ADC_result>4 && ADC_result<12)
			{
				spin_right(30,30);
			}
			intersection=0;
			enable_intersection=1;
			temp_intersection=0;
			while(intersection!=3)
			{
				double_line_follow();
			}
			while(1)
			{
				forward(0);
			}
	*/
	//	forward(255);	
	/*		SENSOR_PORT=0x00;
			read_sensor();
			display_num( sensor_read,4,1,4);
		while(ADC_channel==0)
			_delay_ms(1000);
		;
	*/
	//	}
	/*	while(1)
		{
			if(ADC_result==13)
				spin_left(50,50);
			else
				forward(0);


		single_line_follow();
	//	display_num(single_diff,4,1,4);
	//	_delay_ms(1000);
		}
	*/
	/*	while(ADC_result<11 || ADC_result>13 )
		{
			double_line_follow();
	//	display_num(ADC_result,4,1,4);
	
		}
	*///	while(sensor_read<11 /*|| sensor_read>13*/)
	/*	{
			read_sensor();
			turn(20,30);
		}


		while(ADC_result<3 || ADC_result>6)
		{

			spin_left(50,50);
	//		display_num(ADC_result,4,1,4);

		}
		while(ADC_result!=13)
		{	
			double_line_follow();
	//		display_num(ADC_result,4,1,4);
		}
			forward(50);
			_delay_ms(200);
			spin_right(50,50);
			_delay_ms(200);
		while(ADC_result<3 || ADC_result>6)
		{
			spin_right(50,50);
		}
		while(ADC_result<13 || ADC_result>15 )
	
		{
			front_line_follow();
		}
	
		forward(50);
		_delay_ms(200);

		while( (ADC_result<2) || (ADC_result>7) )
		{	
			spin_right(50,50);
		}	

		while(1)
		{
			front_line_follow();
		}
	*/
//}
 

