/*
 * uart.h
 *
 *  Created on: Jun 9, 2019
 *      Author: LENOVO
 */

#ifndef UART_H_
#define UART_H_


#include "../data_type.h"
#include "../micro_config.h"
#include "../common_macros.h"
#include <string.h>

#define UART_DDR DDRD
#define UART_TRANSMITTER_PIN PD1
#define UART_RECEIVER_PIN    PD0


/*
 * BAUD_RATE
 */
#define BAUD_RATE 9600UL

/*
 * Prescaler .. can be 8 OR 16
 * In case of 16 .. ASYNC DOUBLE MODE MUST BE ACTIVE .. (U2X = 1).
 */
#define PRESCALER 8
/*
 * PRESCALER .. 8 OR 16.
 */
#define UBRR_VALUE ((F_CPU/(PRESCALER * BAUD_RATE)) - 1)
/*
 * UART init.
 */
void UART_init();
/*
 * UART sending byte.
 */
void UART_sendByte(uint8 byte);
/*
 * UART receive byte.
 */
uint8 UART_receiveByte();

/*
 * UART sendString.
 */
void UART_sendString(uint8* string);

/*
 * UART receive string.
 */
void UART_receiveString();
#endif /* UART_H_ */
