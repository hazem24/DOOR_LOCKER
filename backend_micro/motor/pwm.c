/*
 * pwm.c
 *
 *  Created on: Jul 16, 2019
 *      Author: LENOVO
 */

#include "pwm.h"


/*
 * PWM_init.
 */
void PWM_init(PWM_CLOCK freq)
{
	/*
	 * FAST PMW Mode.
	 * non-Inverting Mode.
	 */
	TCCR0 = freq | ( 1 << WGM00 ) | ( 1 << WGM01 ) | ( 1 << COM01 );

	/*
	 * Init OC0 as output pin.
	 */
	DDR_OC0 |= ( 1 << OC0);

}

/*
 * PWM_dutyCycle
 */
void PWM_dutyCycle(uint8 duty)
{
	OCR0 = ((((float)duty/100) * 256) - 1);
}

/*
 * Change Wave Frequency.
 */
void PWM_changeWaveFrequency(PWM_CLOCK freq)
{
	TCCR0 = (TCCR0 & (0xF8)) | (freq);
}

/*
 * Stop Wave.
 */
void PWM_stop()
{
	TCCR0 = 0;
}
