/*
 * pwm.h
 *
 *  Created on: Jul 16, 2019
 *      Author: LENOVO
 */

#ifndef PWM_H_
#define PWM_H_

#include "../data_type.h"
#include "../micro_config.h"
#include "../common_macros.h"

#define DDR_OC0  DDRB
#define PORT_OC0 PORTB
#define OC0      PB3
/*
 * Module To Create Pulse Width Modulation With TIMER0 ATMEGA32/16.
 */


/*
 * PWM mode wave generated frequency changed by changing prescaler only.
 */
typedef enum
{
	NO_FREQ,NO_PRESCALER,PRESCALER_8,PRESCALER_64,PRESCALER_256,PRESCALER_1024,
	EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RAISING
}PWM_CLOCK;
/*
 * PWM_init.
 */
void PWM_init(PWM_CLOCK freq);

/*
 * PWM_dutyCycle
 */
void PWM_dutyCycle(uint8 duty);

/*
 * Change Wave Frequnce.
 */
void PWM_changeWaveFrequency(PWM_CLOCK freq);

/*
 * Stop Wave.
 */
void PWM_stop();
#endif /* PWM_H_ */
