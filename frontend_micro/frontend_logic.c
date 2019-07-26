/*
 * fronend_logic.c
 *
 *  Created on: Jul 21, 2019
 *      Author: LENOVO
 */
/*
 * Contains all logic of front end MICRO which interact with users.
 */

#include "frontend_logic.h"


static void FRONT_LOGIC_options();//Page 1.
static void FRONT_LOGIC_enterPassword();//Page 2.
static void FRONT_LOGIC_changePassword();//Page 3.
static void FRONT_LOGIC_checkPassword(uint8* password);
static void FRONT_LOGIC_passwordGui();
static uint8* FRONT_LOGIC_enterNewPassword(uint8*);
static uint8* FRONT_LOGIC_reEnterNewPassword(uint8*);
static uint8* FRONT_LOGIC_takeInput();
static void getPassword(uint8* password, uint8 check);
static void FRONT_LOGIC_confirmFromUser(uint8*,uint8);
static void FRONT_LOGIC_goToPage(uint8 page);
void FRONT_LOGIC_changePasswordChecker(uint8* new_pass, uint8* re_new_pass);



//By default Nav point set to page 1 which has index 0.
static uint8 nav_point  = 0;
static uint8 password_step = 1;
/*
 * Nav. system of Application.
 */
static void (*nav[ NAV_COUNTER ]) (void) = {FRONT_LOGIC_options,FRONT_LOGIC_enterPassword,FRONT_LOGIC_changePassword};
/*
 * FRONT_LOGIC init.
 */
void FRONT_LOGIC_init()
{
	/*
	 * In init process of front end logic.
	 * 1 - init SYSTEM GUI with
	 	 * Welcome message .. and please wait to init system.
	 	 	 * Init. keypad.
	 */

	DOOR_STATUS_DDR &= (~( 1 << DOOR_STATUS ));
	BLOCK_USER_DDR  &= (~( 1 << BLOCK_USER ));

	SYSTEM_GUI_init();
	SYSTEM_GUI_display((uint8*)"loading ..",CLEAR_DISPLAY);
	_delay_ms(1000);
	UART_init();

}

/*
 * FRONT_LOGIC run.
 * Have All Logic of FRONT_END MICRO.
 */

void FRONT_LOGIC_run()
{
	uint8 input = 0;//Related to nav system.
	(*nav[nav_point])();//Load New Content.
	do
	{
		FRONT_LOGIC_takeInput( &input );
	}while( input >= NAV_COUNTER );
	/*
	 * Identify each page user want.
	 */
	if ( (input) < NAV_COUNTER)
		nav_point = (input);
	else
		nav_point = 0;//Main Page.
}

/*
 * FRONT_LOGIC_options.
 * Page 1 in nav. system.
 */
static void FRONT_LOGIC_options()
{
	SYSTEM_GUI_display((uint8*)"Options : ",CLEAR_DISPLAY);
	SYSTEM_GUI_printNewLine(RESET_NEW_LINE);
	SYSTEM_GUI_display((uint8*)"(1)- Open door",UNCLEAR_DISPLAY);
	SYSTEM_GUI_printNewLine(UNRESET_NEW_LINE);
	SYSTEM_GUI_display((uint8*)"(2)- Change Password ", UNCLEAR_DISPLAY);
	SYSTEM_GUI_printNewLine(UNRESET_NEW_LINE);
	nav_point = 0;//Navigation page number 1.
	/*uint8 key;
	key = KEYPAD_getPressedKey();
	SYSTEM_GUI_displayInteger(key, CLEAR_DISPLAY);
	SYSTEM_GUI_printNewLine(RESET_NEW_LINE);*/
}

/*
 * FRONT_LOGIC takeInput
 */
static uint8* FRONT_LOGIC_takeInput(uint8* key_pressed)
{
	*key_pressed = KEYPAD_getPressedKey();
	_delay_ms(500);
	return key_pressed;
}

/*
 * FRONT_LOGIC goToPage.
 */
static void FRONT_LOGIC_goToPage(uint8 page)
{
	if ( nav_point  < NAV_COUNTER) nav_point = page;
	password_step = 1;

}

/*
 * FRONT_LOGIC enterPassword Page.
 * Enter Password Logic.
 	 * 1 - User enter 5 number.--DONE--.
 	 	 * After Each Number .. system print '*'.--DONE--.
 	 * 2 - After Five Number system tell user to enter '#' to confirm or '*' to return back to option.
 	 	 * After press '#' .. waiting appear on the Screen.
 	 	 * After press '*' .. return back to option page.--DONE--.
 */
static void FRONT_LOGIC_enterPassword()
{
	uint8 password[PASSWORD_LENGTH];
	FRONT_LOGIC_passwordGui();
	getPassword(password, True);
}

/*
 * FRONT_LOGIC checkPassword user submit.
 */
static void FRONT_LOGIC_checkPassword(uint8* password)
{
	/*
	 * Sending Password Via UART to the second MICRO.--DONE--.
	 * We Can Check if password True Or False By Receiving "One or Zero" In UART.
	 * 1- check password if password is true.
	 	 *  Listen to the pin which indicate that door is open and appear MSG with timer to user.
	 * 2- if wrong MSG appear the password is
	 	 * wrong and user can try again UNTIL Block signal for 2 MIN coming from back end.
	 */
	uint8 check = 0;
	SYSTEM_GUI_display((uint8*)"Please Wait ..",CLEAR_DISPLAY);
	if ( nav_point == 1 )
		UART_sendByte( OPEN_DOOR_OPERATION );
	else
		UART_sendByte( ENTER_NEW_PASSWORD_SIGN );
	UART_sendString(password);
	check = UART_receiveByte();//Check if Password true or false.

	if ( check )
	{
		if ( nav_point == 1 )//Meaning that User Want to open door.
			//Listen to the pin which indicate that door is open and appear MSG with timer to user.
		{
			SYSTEM_GUI_display((uint8*) "Door is open.",CLEAR_DISPLAY);
			while(!BIT_IS_CLEAR(DOOR_STATUS_PIN, DOOR_STATUS));
		}
		else if ( nav_point == 2 )//SYSTEM_GUI_display((uint8*) "Enter New Password Logic",CLEAR_DISPLAY);
		{
			/*
			 * 1 - enter new password.
			 * 2 - re-enter new password.
			 * 3 - check if 1 and 2 equal.
			 */

			uint8 new_pass[PASSWORD_LENGTH];
			uint8 re_new_pass[PASSWORD_LENGTH];

			FRONT_LOGIC_enterNewPassword(new_pass);//Add New Password.
			FRONT_LOGIC_reEnterNewPassword(re_new_pass);//re-Add New Password.
			FRONT_LOGIC_changePasswordChecker(new_pass, re_new_pass);
		}
	}
	else
	{
		if (!BIT_IS_CLEAR(BLOCK_USER_PIN, BLOCK_USER))
		{
			SYSTEM_GUI_display((uint8*) "You tried many times door is blocked !.",CLEAR_DISPLAY);
			while(!BIT_IS_CLEAR(BLOCK_USER_PIN, BLOCK_USER));
		}else
		{
			SYSTEM_GUI_display((uint8*) "Wrong Password !",CLEAR_DISPLAY);
		 	 //* wrong and user can try again UNTIL Block signal for 2 MIN coming from back end -- Listened by pin from back-end.
			_delay_ms(3000);
		}

	}
	password_step = 1;
	FRONT_LOGIC_options();
}

/*
 * FRONT_LOGIC changePassword.
 */
static void FRONT_LOGIC_changePassword()
{
	/*
	 * Enter old password.
	 	 * If True.
	 	 	 * Enter New Password .. then re-enter it.
	 	 * If False.
	 	 	 * User Can try again for 3 Times UNTIL Block Signal Come from BACKEND.
	 */
	if ( password_step < 4 ) password_step++;
	if ( password_step == 2 ) FRONT_LOGIC_enterPassword();//Enter Old Password.

}

/*
 * FRONT_LOGIC password GUI.
 * Indicate the type of GUI That Must Be Appear in password page.
 */
static void FRONT_LOGIC_passwordGui()
{
	switch( password_step )
	{
		case 1:
			SYSTEM_GUI_enterPassword((uint8*)"Enter The Password", True);
			break;
		case 2:
			SYSTEM_GUI_enterPassword((uint8*)"Enter Old Password", True);
			break;
		case 3:
			SYSTEM_GUI_enterPassword((uint8*)"Enter New Password", False);
			break;
		case 4:
			SYSTEM_GUI_enterPassword((uint8*)"ReEnter New Password", False);
			break;
		default :
			break;
	}
}

/*
 * FRONT_LOGIC_reEnterNewPassword
 */
static uint8* FRONT_LOGIC_reEnterNewPassword(uint8* password)
{
	password_step++;
	FRONT_LOGIC_passwordGui();
	getPassword( password, False);
	return password;
}

/*
 * uint8* FRONT_LOGIC_enterNewPassword(uint8*).
 */
static uint8* FRONT_LOGIC_enterNewPassword(uint8* password)
{
	//Enter Password.
	password_step++;
	FRONT_LOGIC_passwordGui();
	getPassword( password, False);
	return password;
}

/*
 * FRONT_LOGIC getPassword.
 * Take Password from User.
 */
static void getPassword(uint8* password, uint8 check)
{
	uint8 i = 0;

	while(i < (PASSWORD_LENGTH - 1))
	{
		FRONT_LOGIC_takeInput(&(password[i]));
		if (password[i] == '*')
		{
			FRONT_LOGIC_options();
			password_step = 1;
			return;
		}
		SYSTEM_GUI_display((uint8*)"*",UNCLEAR_DISPLAY);
		password[i] = password[i] + 0x30;//Add 0x30 to convert it to ASCII.
		i++;
	}
	password[i] = '\0';//Null operator add to string password.
	FRONT_LOGIC_confirmFromUser(password, check);
}

/*
 * FRONT_LOGIC confirm from user.
 */
static void FRONT_LOGIC_confirmFromUser(uint8* password, uint8 check)
{
	uint8 confirm = 0;
	SYSTEM_GUI_printAtPosition(3,0);//Line 4 Col 0.
	SYSTEM_GUI_display((uint8*)"'#' to confirm.",UNCLEAR_DISPLAY);
	FRONT_LOGIC_takeInput(&(confirm));
	while( True )
	{
		if ( confirm == CONFIRM_SIGN)
		{
			if ( check == True ) FRONT_LOGIC_checkPassword(password);
			return;
		}
		else if ( confirm == CANCEL_SIGN && (password_step < 3))
		{
			password_step = 1;
			FRONT_LOGIC_options();
			return;
		}
	}
}


/*
 * FRONT_LOGIC change password checker.
 */
void FRONT_LOGIC_changePasswordChecker(uint8* new_pass, uint8* re_new_pass)
{
	if ( (password_step == 4) && (strncmp((cPtrToChar)new_pass, (cPtrToChar)re_new_pass, PASSWORD_LENGTH) == False) )
	{
		/*
		 * 4 - if equal send it to back-end .. with operation sign.
			 * if not equal send re-peat this operation until be equal or '*'.
		 *
		 */
		UART_sendString( new_pass );
		SYSTEM_GUI_display((uint8*)"Password Changed !",CLEAR_DISPLAY);
		_delay_ms(5000);
		/*
		 * Reset Flags.
		 */
		password_step = 1;

	}else
	{
		SYSTEM_GUI_display((uint8*)"The Two Password not Match !",CLEAR_DISPLAY);
		_delay_ms(5000);
		password_step = 1;
		FRONT_LOGIC_options();
	}
}
