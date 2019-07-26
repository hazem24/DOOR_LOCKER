/*
 * frontend_logic.h
 *
 *  Created on: Jul 21, 2019
 *      Author: LENOVO
 */

#ifndef FRONTEND_LOGIC_H_
#define FRONTEND_LOGIC_H_

/*
 * Contains all logic of front end micro with interact with users.
 */
#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "system_gui.h"
#include "UART/uart.h"
#include <string.h>
//#include "led.h"//Hardware Abstract for led.

/*
 * Counting Nav system in App.
 */
#define NAV_COUNTER 3

/*
 * Password Length.
 */
#define PASSWORD_LENGTH 6

/*
 * Open door operation.
 */
#define OPEN_DOOR_OPERATION     'O'
/*
 * Change Password operation.
 */
#define ENTER_NEW_PASSWORD_SIGN 'C'


#define DOOR_STATUS_DDR  DDRD
#define BLOCK_USER_DDR   DDRD

#define DOOR_STATUS_PIN  PIND
#define BLOCK_USER_PIN   PIND

/*
 * Pins.
 */
#define DOOR_STATUS      PD6
#define BLOCK_USER       PD7

/*
 * Define Confirm sign.
 */
#define CONFIRM_SIGN '#'
/*
 * Define Cancel Sign.
 */
#define CANCEL_SIGN '*'

/*
 * FRONT_LOGIC init.
 */
void FRONT_LOGIC_init();


/*
 * FRONT_LOGIC run.
 * Have All Logic of FRONT_END micro.
 */
void FRONT_LOGIC_run();
#endif /* FRONTEND_LOGIC_H_ */
