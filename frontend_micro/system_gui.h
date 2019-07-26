/*
 * system_gui.h
 *
 *  Created on: Jul 21, 2019
 *      Author: LENOVO
 */
#ifndef SYSTEM_GUI_H
#define SYSTEM_GUI_H

#include "LCD/lcd.h"
#include "keypad/keypad.h"


#define UNCLEAR_DISPLAY  0
#define CLEAR_DISPLAY    1

#define UNRESET_NEW_LINE 0
#define RESET_NEW_LINE   1


/*
 * Structure Navigation.
 */
/*typedef struct
{

}SYSTEM_GUI_;*/
/*
 * SYSTEM GUI init.
 */
void SYSTEM_GUI_init();


/*
 * SYSTEM GUI display.
 */
void SYSTEM_GUI_display(uint8* msg, uint8 clear);

/*
 * SYSTEM_GUI displayInteger.
 */
void SYSTEM_GUI_displayInteger(uint16 number, uint8 clear);
/*
 * SYSTEM_GUI_printNewLine.
 */
void SYSTEM_GUI_printNewLine(uint8 reset);
/*
 * SYSTEM_GUI_printAtPosition
 */
void SYSTEM_GUI_printAtPosition(uint8 line, uint8 col);

/*
 * SYSTEM_GUI_enterPassword
 * This Function used for enter password and re-enter password.
 */
void SYSTEM_GUI_enterPassword(uint8* msg, uint8 back);
#endif
