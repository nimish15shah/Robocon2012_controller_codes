
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


void init_line_follow(void)
{
	enable_intersection=1;
	intersection=0;
	temp_intersection=0;
	debounce=0;
	single_delay_n=0;
	double_delay_n=0;

}

void front_line_follow(char speed_1,char normal)
{
	if(ADC_result==27)
	{
		ADC_result=last_ADC_result;
	}

	single_diff= ADC_result-8;
	
	if(single_diff>1 && ADC_result<16)
	{
			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
		
			turn( speed_1, ((speed_1/((3*cos_theta)+1))*normal) );
	}

	else if(single_diff<-1 && ADC_result<16)
	{
		single_diff=8-ADC_result;

			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
			turn( (speed_1/((3*cos_theta)+1))*normal, speed_1 );
	}

	else if(single_diff<2 && single_diff>-2)
	{
		if(momentum==1)
		{
			breaks('b');
			momentum=0;
		}
			
			forward(speed_1);
	}
	if(single_diff>1 && single_diff<-1)
	{
		momentum=1;
	}
	
	if((ADC_result>19 && ADC_result<23) || implied_intersection==1)
	{
		temp_intersection++;
		if(temp_intersection>10 && enable_intersection==1)
		{
			intersection++;
			enable_intersection=0;
			temp_intersection=0;
		}
		forward(speed_1);
	}
	else
	{
		temp_intersection=0;
		enable_intersection=1;
	}

	if(last_ADC_result<3)
	{
		breaks('l');
	}

	if(last_ADC_result>13 && last_ADC_result<16)
	{
		breaks('r');
	}

}



/*
void double_line_follow(char speed)
{
	read_sensor();
	if(sensor_read==27)
		sensor_read=1;
	
	if(ADC_result==27)
		ADC_result=9;		
	if(sensor_read>9 && sensor_read<16 && ADC_result<16)  // right to the centre
	{
		double_diff= sensor_read-ADC_result;

		if(double_diff>2)
		{
			if( ( (last_ADC_result==ADC_result-1 || last_ADC_result==ADC_result-2) && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				find_theta();
				turn(speed/((5*cos_theta)+1),speed);

			}
		
//		point_left(30+5*double_diff);
		}	

		else if(double_diff<2)
		{
			double_diff=ADC_result-sensor_read+2;
			
			if(sensor_read>12)
			{
			double_diff= double_diff+2;
			}

			if( ( (last_ADC_result==ADC_result+1 || last_ADC_result==ADC_result+2) && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				find_theta();
				turn( speed,speed/((5*cos_theta)+1) );
			}

			
			
			//point_right(30+((double_diff+1)*5));
		}
	
		else if(double_diff==2)
		{
			if( (last_ADC_result != ADC_result && ADC_result%2 !=0 ) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				forward(speed);
			}
		}
	}

	if(sensor_read>0 && sensor_read<7 && ADC_result<16)  // right to the centre
	{
		double_diff= ADC_result-sensor_read;

		if(double_diff>2)
		{

//			point_right(30+(double_diff*5));

			if( ( (last_ADC_result==ADC_result+1 || last_ADC_result==ADC_result+2) && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				find_theta();
				turn( speed,speed/((5*cos_theta)+1) );
			}
		}
	
		else if(double_diff<2)
		{
			double_diff=sensor_read-ADC_result+2;
//			point_left(30+ ((double_diff+1)*5) );
			if(sensor_read<4)
			{
				double_diff= double_diff+2;
			}		

			if( ( (last_ADC_result==ADC_result-1 || last_ADC_result==ADC_result-2) && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				find_theta();
				turn( speed/((5*cos_theta)+1),speed );
			}
		}
	
		else if(double_diff==2)
		{
			if( (last_ADC_result != ADC_result && ADC_result%2 !=0 ) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				forward(speed);
			}


		}

	}		
	
	if(sensor_read>6 && sensor_read<10 && ADC_result<16)
	{
		double_diff=ADC_result-sensor_read;

		if(double_diff>0)
		{
			if( ( (last_ADC_result==ADC_result+1 || last_ADC_result==ADC_result+2) && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				find_theta();
				turn( speed,speed/((5*cos_theta)+1) );
			}
		}

		else if(double_diff<0)
		{
			double_diff= sensor_read-ADC_result;
			if( ( (last_ADC_result==ADC_result-1 || last_ADC_result==ADC_result-2) && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
			{
				double_delay_n++;
			}
			else
			{
				double_delay_n=0;
				find_theta();
				turn( speed/((5*cos_theta)+1),speed );
			}
		}

		else if(double_diff==0 && ADC_result==8)
		{
			forward(speed);
		}
	
		else if(double_diff==0 && ADC_result!=8)
		{
				if( (last_ADC_result!=0 && ADC_result%2!=0) || (ADC_result=last_ADC_result && double_delay_n!=0 && double_delay_n<2) )
				{
					double_delay_n++;
				}
				else
				{
					double_delay_n=0;
					forward(speed);
				}

		}

	}	

	if(ADC_result==27)
	{
		if(last_ADC_result<8)
		{
			while(ADC_result!=27)
			{
				spin_left(50,50);
			}
		}
		else if(last_ADC_result>8)
		{
			while(ADC_result|=27)
			{
				spin_right(50,50);
			}		
		}
		while(ADC_result>4 && ADC_result<12)
		{
			front_line_follow();
		}

	}

	if(ADC_result>19 && ADC_result<23)
	{
		
		forward(75);
		temp_intersection++;
		if(temp_intersection>2 && enable_intersection==1)
		{
			intersection++;
			enable_intersection=0;
			temp_intersection=0;
		}
	}
	else
	{
		temp_intersection=0;
		enable_intersection=1;
	}
	if(ADC_result<4)
	{
		breaks('l');
	}

	if(ADC_result>12)
	{
		breaks('r');
	}

}
*/
/*
void reverse_line_follow(char speed_1)
{
	if(ADC_result==27)
	{
		ADC_result=9;
	}	
	single_diff= ADC_result-8;
	if(single_diff>1 && ADC_result<16)
	{
*/
/*		if( ( (last_ADC_result==(ADC_result+1)) && (ADC_result%2!=0) ) || (ADC_result==last_ADC_result && single_delay_n!=0 && single_delay_n<2) )
		{
			single_delay_n++;	
		}
		else
		{
*/
 /*			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
//			temp_pwm= speed_1/(5*cos_theta+1);
//			display_num((int)temp_pwm,4,1,6);
		
			turn_reverse( (speed_1/(4*cos_theta)+1), speed_1 );
//		}//if(single_1diff==5)
		//spin_right(0,50);
	}
	
	else if(single_diff<-1 && ADC_result<16)
	{
	//	bit_flip( single_diff, 0b11111111);
		single_diff=8-ADC_result;
*/
/*		if( (last_ADC_result==(ADC_result-1) && (ADC_result%2!=0)) || (ADC_result==last_ADC_result && single_delay_n!=0 && single_delay_n<2) )
		{
			single_delay_n++;	
		}
		else
		{
*/
/*			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
//			temp_pwm= speed_1/(5*cos_theta+1);
//			display_num((int)temp_pwm,4,1,6);
			turn_reverse( speed_1 ,(speed_1/(4*cos_theta)+1) );
//		}
	//	spin_left(50,0);
*/
/*	

	}
	else if(single_diff<2 && single_diff>-2)
	{
		if(momentum_reverse==1)
		{
			breaks('b');
			_delay_us(100);
			momentum_reverse=0;
		}
*/			
/*		if( (last_ADC_result!=ADC_result) || (ADC_result==last_ADC_result && single_delay_n!=0 && single_delay_n<2) )
		{
			single_delay_n++;	
		}
		else
		{
			single_delay_n=0;
*/ //			reverse(speed_1);
//		}
/*	}

	if(single_diff>1 && single_diff<-1)
	{
		momentum_reverse=1;
	}

	if(ADC_result>19 && ADC_result<23)
	{
		temp_intersection++;
		if(temp_intersection>2 && enable_intersection==1)
		{
			intersection++;
			enable_intersection=0;
			temp_intersection=0;
		}
	}
	else
	{
		temp_intersection=0;
		enable_intersection=1;
	}

	if(ADC_result<4)
	{
		breaks('r');
	}

	if(ADC_result>12)
	{
		breaks('l');
	}



}

*/
/*
void reverse_line_follow(char speed_1)
{
	read_sensor();
	if(sensor_read==27)
	{
		sensor_read=9;
	}	

	single_diff= sensor_read-8;
	if(single_diff>1 && sensor_read<16)
	{
		if( ( (last_sensor_read==(sensor_read+1)) && (sensor_read%2!=0) ) || (sensor_read==last_sensor_read && single_delay_n!=0 && single_delay_n<2) )
		{
			single_delay_n++;	
		}
		else
		{
			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
//			temp_pwm= speed_1/(5*cos_theta+1);
//			display_num((int)temp_pwm,4,1,6);
		
			turn_reverse( (speed_1/(4*cos_theta)+1), speed_1 );
//		}//if(single_1diff==5)
		//spin_right(0,50);
	}
	
	else if(single_diff<-1 && sensor_read<16)
	{
	//	bit_flip( single_diff, 0b11111111);
		single_diff=8-sensor_read;

		if( (last_sensor_read==(sensor_read-1) && (sensor_read%2!=0)) || (sensor_read==last_sensor_read && single_delay_n!=0 && single_delay_n<2) )
		{
			single_delay_n++;	
		}
		else
		{
			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
//			temp_pwm= speed_1/(5*cos_theta+1);
//			display_num((int)temp_pwm,4,1,6);
			turn_reverse( speed_1 ,(speed_1/(4*cos_theta)+1) );
//		}
	//	spin_left(50,0);
	

	}
	else if(single_diff<2 && single_diff>-2)
	{
		if(momentum_reverse==1)
		{
			breaks('b');
			_delay_us(100);
			momentum_reverse=0;
		}
			
		if( (last_sensor_read!=sensor_read) || (sensor_read==last_sensor_read && single_delay_n!=0 && single_delay_n<2) )
		{
			single_delay_n++;	
		}
		else
		{
			single_delay_n=0;
			reverse(speed_1);
//		}
	}

	if(single_diff>1 && single_diff<-1)
	{
		momentum_reverse=1;
	}

	if(sensor_read>17 && sensor_read<23)
	{
		temp_intersection++;
		if(temp_intersection>2 && enable_intersection==1)
		{
			intersection++;
			enable_intersection=0;
			temp_intersection=0;
		}
	}
	else
	{
		temp_intersection=0;
		enable_intersection=1;
	}

	if(sensor_read<4)
	{
		breaks('r');
	}

	if(sensor_read>12)
	{
		breaks('l');
	}
}
*/

void reverse_double_line_follow(char speed)
{

	read_sensor();
	if(sensor_read==27)
	{
		sensor_read=last_sensor_read;
	}
	
	if(ADC_result<16 && sensor_read<16)
	double_diff= sensor_read-ADC_result;

	if(sensor_read<7 && sensor_read>2 && ADC_result<16)
	{
		double_diff= sensor_read-ADC_result;

		if(double_diff>1)
		{	
			find_theta();
			turn_reverse(speed, speed/((4*cos_theta)+1) );
		}
		
		else if(double_diff<1)
		{
			double_diff=ADC_result-sensor_read;
			double_diff= double_diff+2;
			find_theta();
			turn_reverse( speed/((4*cos_theta)+1), speed );
		}
		else if(double_diff==1)
		{
			reverse(speed);
		}
	}
	
	else if(sensor_read<2 && ADC_result<16)
	{
		double_diff=ADC_result-sensor_read+2;
		while(ADC_result>1 && ADC_result<16)
		{
			turn_reverse(0,speed);
		}
//			turn_reverse(0,speed);
//			_delay_ms(200);
		breaks('b');
		read_sensor();
		while(sensor_read<3 && sensor_read!=21)
		{
			read_sensor();
			reverse(speed/2);
		}
		
	}
	
	else if(sensor_read>9 && sensor_read<14 && ADC_result<16)
	{

		if(double_diff>-1)
		{
			double_diff=double_diff+2;
			find_theta();
			turn_reverse( speed,speed/((4*cos_theta)+1));
		}
		
		else if(double_diff<-1)
		{
			double_diff=ADC_result-sensor_read;
			find_theta();
			turn_reverse(speed/((4*cos_theta)+1),speed);
		}
		
		else if(double_diff==-1)
		{
			reverse(speed);
		}
	}

	else if(sensor_read>14 && sensor_read<16 && ADC_result<16)
	{
		while(ADC_result<15 && ADC_result<16)
		{
			turn_reverse(speed,0);
		}
		breaks('b');
//			_delay_ms(200);
		read_sensor();
		while(sensor_read>13 && sensor_read<16)
		{
			read_sensor();
			reverse(speed/2);
		}

	}
	
	else if(sensor_read>6 && sensor_read<10 && ADC_result<16)
	{
		double_diff=sensor_read-ADC_result;		
		if(double_diff>1)
		{
			double_diff=double_diff+2;
			find_theta();
			turn_reverse(speed,0);
		}
	
		else if(double_diff<-1)
		{
			double_diff=ADC_result-sensor_read+2;
			find_theta();
			turn_reverse(0,speed);
		}
	
		else
		{
			reverse(speed);
		}	
	}

	if(sensor_read>16 && sensor_read<27)
	{
		reverse(speed);
	}

	if(final_counter>5)
	{
		temp_intersection++;
		if(temp_intersection>10 && enable_intersection==1)
		{
			intersection++;
			enable_intersection=0;
			temp_intersection=0;
		}
	}
	else
	{
		temp_intersection=0;
		enable_intersection=1;
	}


}






void power_play(void)
{
	breaks('b');

	if(ADC_result<7)
	{
		POWER_PLAY_PORT |= (_BV(POWER_PLAY_RIGHT));
		POWER_PLAY_PORT &= ~(_BV(POWER_PLAY_LEFT));
	}

	else if(ADC_result>9 && ADC_result<16)
	{
		POWER_PLAY_PORT |= (_BV(POWER_PLAY_LEFT));
		POWER_PLAY_PORT &= ~(_BV(POWER_PLAY_RIGHT));
	}

	else if(ADC_result>6 && ADC_result<10)
	{
		POWER_PLAY_PORT |= (_BV(POWER_PLAY_LEFT));
		POWER_PLAY_PORT |= (_BV(POWER_PLAY_RIGHT));
	}

	if(implied_intersection==1)
	{
		if(enable_intersection==1)
		{

			POWER_PLAY_PORT |= (_BV(POWER_PLAY_LEFT));
			POWER_PLAY_PORT |= (_BV(POWER_PLAY_RIGHT));
			
			intersection++;
			enable_intersection=0;
		}
	}
	else if(implied_intersection==0)
	{
		enable_intersection=1;
	}
}






void point_line_follow(char speed)
{
	if(ADC_result==27)
	{
		ADC_result= last_ADC_result;
	}
	if(ADC_result>9 && ADC_result<16)
	{
		point_right(speed);
	}	
	else if(ADC_result<7)
	{
		point_left(speed);
	}
	else if(ADC_result>=7 && ADC_result<=9)
	{
		forward(speed);
	}


	if( (ADC_result>19 && ADC_result<23) || implied_intersection==1)
	{
		temp_intersection++;
		if(temp_intersection>4 && enable_intersection==1)
		{
			intersection++;
			enable_intersection=0;
			temp_intersection=0;
		}
		forward(speed);
	}
	else
	{
		temp_intersection=0;
		enable_intersection=1;
	}

}
