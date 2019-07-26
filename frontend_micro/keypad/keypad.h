/*
 * keypad.h
 *
 *  Created on: Jun 5, 2019
 *      Author: LENOVO
 */

/*
 * This Module Works for 4x3 keypad and 4x4 just change the number of columns to 3 or 4.
 * Pins works must br first four pins in the specific port.
 */
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../common_macros.h"
#include "../data_type.h"
#include "../micro_config.h"

#define KEY_PAD_ROWS    4
#define KEY_PAD_COLUMNS 3

#define KEYPAD_ROWS_DDR    DDRC
#define KEYPAD_COLUMNS_DDR DDRC

#define KEYPAD_ROWS_PORT    PORTC
#define KEYPAD_COLUMNS_PORT PORTC
#define KEYPAD_COLUMNS_PIN  PINC


/*
 * Init module.
 */
void KEYPAD_Init();
/*
 * Function used to get key which pressed.
 */
uint8 KEYPAD_getPressedKey();


#endif /* KEYPAD_H_ */
