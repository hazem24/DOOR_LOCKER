/*
 * motor_driver_l239d.c
 *
 *  Created on: Jul 16, 2019
 *      Author: LENOVO
 */

#include "motor_driver_l239d.h"


/*
 * Flag to determine direction of motor.
 */
static uint8 MOTOR_direction = 0;

/*
 * MOTOR_init.
 */
void MOTOR_init()
{
	/*
	 * INPUT1,INPUT2,ENABLE.
	 */
	MOTOR_DDR  |= ( 1 << INPUT1 ) | ( 1 << INPUT2 ) | ( 1 << ENABLE_1 );
}

/*
 * MOTOR_start
 */
void MOTOR_start(MOTOR_DRIVER_L239D_Direction direction)
{
	MOTOR_PORT = (MOTOR_PORT & ((~( 1 << INPUT1 )) & (~( 1 << INPUT2 )))) | (direction << INPUT1);
	MOTOR_PORT |= (1 << ENABLE_1);
	MOTOR_direction = direction;
}

/*
 * MOTOR stop.
 */
void MOTOR_stop()
{
	MOTOR_PORT &= ((~( 1 << INPUT1 )) & (~( 1 << INPUT2 )));
}

/*
 * MOTOR changeSpeed
 */
void MOTOR_changeSpeed(uint8 duty)
{
}

/*
 * Motor reverse.
 */
void MOTOR_reverseDirection()
{
	switch( MOTOR_direction )
	{
		case CLOCK_WISE:
			MOTOR_PORT = (MOTOR_PORT & ((~( 1 << INPUT1 )) & (~( 1 << INPUT2 )))) | (ANTI_CLOCK_WISE << INPUT1);
			MOTOR_direction = ANTI_CLOCK_WISE;
			break;
		case ANTI_CLOCK_WISE:
			MOTOR_PORT = (MOTOR_PORT & ((~( 1 << INPUT1 )) & (~( 1 << INPUT2 )))) | (CLOCK_WISE << INPUT1);
			MOTOR_direction  = CLOCK_WISE;
			break;
		default:
			break;
	};
}
