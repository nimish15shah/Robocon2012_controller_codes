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

void accelerate(char init, char final, char time)
{
	int accelerate_i,accelerate_j;
	for(accelerate_i=init;accelerate_i<final;accelerate_i++)
		for(accelerate_j=0;accelerate_j<time;accelerate_j++)
			front_line_follow(accelerate_i,1);
}

void deaccelerate(char init, char final, char time)
{
	int deaccelerate_i,deaccelerate_j;
	for(deaccelerate_i=init;deaccelerate_i>final;deaccelerate_i--)
		for(deaccelerate_j=0;deaccelerate_j<time;deaccelerate_j++)
			front_line_follow(deaccelerate_i,1);
}

