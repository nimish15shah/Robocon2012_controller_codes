
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

void read_sensor(void)
{
	if(sensor_read!=27)
	{
		last_sensor_read=sensor_read;
	}
	sensor_read= ( SENSOR_PIN & 0b11111000 );
	sensor_read= (sensor_read >> 3);
}
