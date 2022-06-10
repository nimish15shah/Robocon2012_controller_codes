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


void init_line_follow(void)
{
	enable_intersection=1;
	intersection=0;
	temp_intersection=0;
	debounce=0;
	single_delay_n=0;
	double_delay_n=0;
}

void clear_intersection()
{
	enable_intersection=1;
	intersection=0;
	temp_intersection=0;
}

void front_line_follow(char speed_1,char normal)
{
		if(ADC_result!=31)
		{
			last_ADC_result=ADC_result;
		}
		else
		{
			ADC_result= last_ADC_result;
		}

	single_diff= ADC_result-11;
	
	if(single_diff>0 && ADC_result<22)
	{
			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
			point_right(speed_1);	
	//		turn( speed_1, (speed_1*normal/((1*cos_theta)+1)) );
	}

	else if(single_diff<0 && ADC_result<22)
	{
		single_diff=11-ADC_result;

			single_delay_n=0;
			single_diff= single_diff+2;
			find_theta_single();
			point_left(speed_1);
//			turn( (speed_1*normal/((1*cos_theta)+1)), speed_1 );
	}

	else if(single_diff==0)
	{
/*		if(momentum==1)
		{
			breaks('b');
			momentum=0;
		}
*/			
			forward(speed_1);
	}
	if(single_diff>1 && single_diff<-1)
	{
		momentum=1;
	}
	
	if((ADC_result>24 && ADC_result<28) || final_counter>5)
	{
		temp_intersection++;
		if(temp_intersection>0 && enable_intersection==1)
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


	if(ADC_result>21 && ADC_result<31)
	{
		forward(speed_1);
	}
	


	if(ADC_result<10)
	{
		breaks('l');
	}

	if(ADC_result>18 && ADC_result<22)
	{
		breaks('r');
	}

}

void reverse_double_line_follow(char speed)
{

	read_sensor();

	if(ADC_result<16 && sensor_read<16)
	double_diff= sensor_read-ADC_result;

	if(sensor_read<7 && sensor_read>2 && ADC_result<16)
	{
		double_diff= sensor_read-ADC_result;

		if(double_diff>2)
		{	
			find_theta();
			turn_reverse(speed, speed/((4*cos_theta)+1) );
		}
		
		else if(double_diff<2)
		{
			double_diff=ADC_result-sensor_read;
			double_diff= double_diff+2;
			find_theta();
			turn_reverse( speed/((4*cos_theta)+1), speed );
		}
		else if(double_diff==2)
		{
			reverse(speed);
		}
	}
	
	else if(sensor_read<3 && ADC_result<16)
	{
		double_diff=ADC_result-sensor_read+2;
		while(ADC_result>1 && ADC_result<16)
		{
			turn_reverse(0,speed);
		}
		while(sensor_read<3 && sensor_read!=21)
		{
			read_sensor();
			reverse(speed/2);
		}
		
	}
	
	else if(sensor_read>9 && sensor_read<14 && ADC_result<16)
	{

		if(double_diff>-2)
		{
			double_diff=double_diff+2;
			find_theta();
			turn_reverse( speed,speed/((4*cos_theta)+1));
		}
		
		else if(double_diff<-2)
		{
			double_diff=ADC_result-sensor_read;
			find_theta();
			turn_reverse(speed/((4*cos_theta)+1),speed);
		}
		
		else if(double_diff==-2)
		{
			reverse(speed);
		}
	}

	else if(sensor_read>13 && sensor_read<16 && ADC_result<16)
	{
		while(ADC_result<15 && ADC_result<16)
		{
			turn_reverse(speed,0);
		}

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
		temp_intersection++;
		if(temp_intersection>0 && enable_intersection==1)
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
