/*
 * backend_micro.c
 *
 *  Created on: Jul 21, 2019
 *      Author: LENOVO
 */

#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "backend_logic.h"
int main()
{
	/*
	 * Init.
	 */
	BACKEND_LOGIC_init();
	/*
	 * App.
	 */
	uint8 password[6];
	while( True )
	{
		BACKEND_LOGIC_listen();
	}
}
