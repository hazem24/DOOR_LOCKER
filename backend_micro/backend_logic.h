/*
 * backend_logic.h
 *
 *  Created on: Jul 25, 2019
 *      Author: LENOVO
 */

#ifndef BACKEND_LOGIC_H_
#define BACKEND_LOGIC_H_

#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "UART/uart.h"
#include "eeprom/external_eeprom.h"
#include "motor/motor_driver_l239d.h"


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



#define DOOR_STATUS_DDR  DDRA
#define BLOCK_USER_DDR   DDRA

#define DOOR_STATUS_PORT PORTA
#define BLOCK_USER_PORT  PORTA

#define BUZZER_DDR  DDRD
#define BUZZER_PORT PORTD

/*
 * Pins.
 */
#define BUZZER_PIN      PD4
#define DOOR_STATUS_PIN PA0
#define BLOCK_USER_PIN  PA1
/*
 * Start Address of first character.
 */
#define PWD_ADDRESS 0xA1
/*
 * BACKEND_LOGIC_init
 */
void BACKEND_LOGIC_init();

/*
 * BACKEND_LOGIC_run.
 */
void BACKEND_LOGIC_listen();


/*
 * BACKEND_LOGIC_action.
 */
static void BACKEND_LOGIC_action();
#endif /* BACKEND_LOGIC_H_ */
