/*
 * backend_logic.c
 *
 *  Created on: Jul 25, 2019
 *      Author: LENOVO
 */

#include "backend_logic.h"



static void BACKEND_LOGIC_action();
static void BACKEND_LOGIC_putPassword(uint8* password);
static uint8 BACKEND_LOGIC_changePassword();
static void BACKEND_LOGIC_getPassword(uint8* password);
static void BACKEND_LOGIC_wrongPassword();

static uint8 operation = OPEN_DOOR_OPERATION;
/*
 * The Default password used for first time.
 */
static uint8 default_pass[PASSWORD_LENGTH] = "12345";


/*
 * try_counter.
 * How many times user try to put wrong password.
 */
static uint8 try_counter = 0;
/*
 * BACKEND_LOGIC_init
 */
void BACKEND_LOGIC_init()
{
	UART_init();
	EEPROM_init();
	MOTOR_init();
	/*
	 * Init LED Indicators.
	 */
	DOOR_STATUS_DDR |= ( 1 << DOOR_STATUS_PIN );
	BLOCK_USER_DDR  |= ( 1 << BLOCK_USER_PIN );
	BUZZER_DDR      |= ( 1 << BUZZER_PIN );
	/*
	* 1 - check if there's a password in EEPROM.
	* if no change it .. Put default password '12345'.--DONE--.
	*/
	uint8 first_character;

	if ((first_character > 0x39) || ( first_character < 0x30 ))
	{
		BACKEND_LOGIC_putPassword(default_pass);
	}


}

/*
 * BACKEND_LOGIC_run.
 */
void BACKEND_LOGIC_listen()
{
	/*
	 * 1 - take the coming operation from FRONT_END.
	 * 2 - go to logic associated with this operation.
	 */
	operation = UART_receiveByte();
	BACKEND_LOGIC_action();

}


/*
 * BACKEND_LOGIC_action.
 */
static void BACKEND_LOGIC_action()
{
	/*
	 * Get Password from user .. to do the specific operation.--DONE--.
	 */
	uint8 password[ PASSWORD_LENGTH ];

	uint8 eeprom_password[ PASSWORD_LENGTH ];//Password Saved in EEPROM.

	UART_receiveString(password);//Take Password from user.
	BACKEND_LOGIC_getPassword(eeprom_password);//Save Password.

	uint8 check = !(strncmp( (const char*)password , (const char*)eeprom_password, PASSWORD_LENGTH));//Check two pass.
	uint8 changePassword[ PASSWORD_LENGTH ];

	switch( operation )
	{

		case OPEN_DOOR_OPERATION:
			/*
			 * 1 - check password.
			 	 * if true open the door.
			 	 * else counter 3 times before blocked user and buzzer work for 30 sec.
			 */
			//LCD_displayString((uint8*)"Open Door Operation.");
			if ( check == True )
			{
				/*
				 * 1 - open door .. ( Motor clock wise ).--DONE--.
				 * 2 - change door status to 'ON'.--DONE--.
				 * 3 - wait for 40 sec.
				 * 4 - door closed anti-clock.
				 * 5 - door status to 'OFF'.
				 */
				UART_sendByte(True);
				MOTOR_start(CLOCK_WISE);
				DOOR_STATUS_PORT |= ( 1 << DOOR_STATUS_PIN );
				_delay_ms(10000);
				MOTOR_reverseDirection();
				_delay_ms(10000);
				DOOR_STATUS_PORT &= (~( 1 << DOOR_STATUS_PIN ));
				MOTOR_stop();
				try_counter = 0;
			}else
			{
				BACKEND_LOGIC_wrongPassword();
			}
			break;
		case ENTER_NEW_PASSWORD_SIGN:
			/*
			 * 1 - change password in the EEPROM.
			 * if password changed .. send true to FRONTEND.
			 * else false.
			 */
			if ( check == True )
			{
				UART_sendByte(True);//Right Password.
				UART_receiveString(changePassword);
				BACKEND_LOGIC_changePassword(changePassword);
			}else
			{
				BACKEND_LOGIC_wrongPassword();
			}
			break;
		default:
			break;
	}
}

/*
 * BACKEND_LOGIC_changePassword.
 */
static uint8 BACKEND_LOGIC_changePassword(uint8* password)
{
	BACKEND_LOGIC_putPassword(password);
	return True;
}

/*
 * BACKEND_LOGIC_getPassword.
 * get password from EEPROM.
 */
static void BACKEND_LOGIC_getPassword(uint8* password)
{
	uint8 i;
	for (i = 0; i < PASSWORD_LENGTH; i++)
	{
		EEPROM_readByte((PWD_ADDRESS + i) ,(password + i));
		_delay_ms(15);
	}
	*(password + i ) = '\0';
}

/*
 * BACKEND_LOGIC_putPassword.
 * put password in EEPROM.
 */
static void BACKEND_LOGIC_putPassword(uint8* password)
{
	uint8 i;
	for (i = 0; i < PASSWORD_LENGTH; i++)
	{
		EEPROM_writeByte((PWD_ADDRESS + i), *(password + i));
		_delay_ms(15);
	}
}

/*
 * BACKEND_LOGIC_wrongPassword.
 */
static void BACKEND_LOGIC_wrongPassword()
{
	UART_sendByte(False);//Send false to the front end wrong password.
	/*
	* 1 - counter_wrong_password++.
	* 2 - if counter_wrong password == 3 (BUZZER_WORK for 30 sec)
		* BLOCKED_USER 'ON' .. for 30 MIN.
	*/
	try_counter++;
	if ( try_counter == 3 )
	{
	/*
	 * BUZZER WORK .. for 30 sec.
	 * BLOCKED_USER_ON .. for 30 sec.
	*/

		BUZZER_PORT |= ( 1 << BUZZER_PIN );
		BLOCK_USER_PORT |= ( 1 << BLOCK_USER_PIN );
		_delay_ms(10000);
		BUZZER_PORT &= (~( 1 << BUZZER_PIN ));
		BLOCK_USER_PORT &= (~( 1 << BLOCK_USER_PIN ));
		try_counter = 0;
	}
}
