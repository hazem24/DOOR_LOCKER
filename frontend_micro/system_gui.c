/*
 * system_gui.c
 *
 *  Created on: Jul 21, 2019
 *      Author: LENOVO
 */
#include "system_gui.h"

/*
 * SYSTEM GUI init.
 */
void SYSTEM_GUI_init()
{
	LCD_init();
	KEYPAD_Init();
}


/*
 * SYSTEM GUI display.
 */
void SYSTEM_GUI_display(uint8* msg, uint8 clear)
{
	if ( clear ==  CLEAR_DISPLAY )
	{
		LCD_clearScreen();
		LCD_displayString( msg );
	}
	else LCD_displayString( msg );
}
/*
 * SYSTEM_GUI displayInteger.
 */
void SYSTEM_GUI_displayInteger(uint16 number, uint8 clear)
{
	if ( clear ==  CLEAR_DISPLAY)
	{
		LCD_clearScreen();
		LCD_integerToString( number );
	}
	else LCD_integerToString( number );
}
/*
 * SYSTEM_GUI_printNewLine.
 */
void SYSTEM_GUI_printNewLine(uint8 reset)//Must be modified for last line logic.
{
	static uint8 lastLine = 2;
	if (reset == RESET_NEW_LINE) lastLine = 2;
	else lastLine++;
	LCD_goToRowColumn(lastLine,0);
}
/*
 * SYSTEM_GUI_printAtPosition
 */
void SYSTEM_GUI_printAtPosition(uint8 line, uint8 col)
{
	LCD_goToRowColumn( line, col);
}


/*
 * SYSTEM_GUI_enterPassword
 * This Function used for enter password and re-enter password.
 */
void SYSTEM_GUI_enterPassword(uint8* msg, uint8 back)
{
	SYSTEM_GUI_display( msg , CLEAR_DISPLAY);
	//Printing '*'.
	SYSTEM_GUI_printAtPosition(4,0);//Line 4 Col 0.
	if ( back == True )
		SYSTEM_GUI_display((uint8*)"'*' return back.",UNCLEAR_DISPLAY);
	//Go with crusor to the space which '*' of password appear.
	SYSTEM_GUI_printAtPosition(2,7);//Line 2 Col 7.
}

