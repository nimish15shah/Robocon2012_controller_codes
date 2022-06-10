#define ADC_DDR		DDRA
#define ADC_PORT	PORTA
#define ADC_PIN		PINA

#define MOTOR_DDR  		DDRD
#define MOTOR_PORT  	PORTD
#define MOTOR_PIN		PIND
#define MOTOR_FRONT_1 	PD1
#define MOTOR_FRONT_2 	PD3

#define MOTOR_BACK_1  	PD6
#define MOTOR_BACK_2  	PD7

#define DDR_REAR_MOTOR	DDRA
#define PORT_REAR_MOTOR	PORTA
#define REAR_MOTOR_1  	PA6
#define REAR_MOTOR_2  	PA5
#define REAR_MOTOR_PWM 	PA7


#define COM_DDR			DDRC
#define COM_PORT		PORTC
#define COM_PIN			PINC
#define OUT_MAIN		PC7
#define IN_MAIN			PC6
#define OUT_SERVO		PC1
#define OUT_BACK_SENSOR PC3
#define IN_BACK_SENSOR	PC2

#define REMOTE_PORT			PORTB
#define REMOTE_DDR			DDRB
#define REMOTE_PIN			PINB
/*
#define MECHANISM_HIGH		PB3
#define MECHANISM_LOW		PB2
#define	REAR_HIGH			PB7
#define REAR_LOW			PB5
#define MECHANISM_HIGH_CONT	PB1
#define MECHANISM_LOW_CONT	PB0
#define REAR_HIGH_CONT		PD0
#define REAR_LOW_CONT		PB6
#define END_REMOTE			PD2
#define START_REMOTE		PD2
*/

#define MECHANISM_HIGH		PB6	//PB3
#define MECHANISM_LOW		PB5	//PB1
#define	REAR_HIGH			PB0 //PB7
#define REAR_LOW			PB2	//PD0
#define MECHANISM_HIGH_CONT	PD0	 //PB2
#define MECHANISM_LOW_CONT	PB7 //PB0
#define REAR_HIGH_CONT		PB1 //PB5
#define REAR_LOW_CONT		PB3	//PB6
#define END_REMOTE			PD2 //PD2
#define START_REMOTE		PD2 //PD2


#define LCD_DDR			 DDRB
#define LCD_PORT		 PORTB
#define CONTROL_DDR		 DDRD
#define CONTROL_PORT	 PORTD
#define E				 PD2
#define RS				 PD0

#define PATH_SELECT_DDR		DDRC
#define PATH_SELECT_PORT	PORTC
#define PATH_SELECT_PIN		PINC
#define START				PC4	//
#define RESTART				PC5	//
#define PENG_ON_DEI_GATE	PC0	//	
