/*
 * frontend_micro.c
 *
 *  Created on: Jul 21, 2019
 *      Author: LENOVO
 */


#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "frontend_logic.h"



int main()
{
	/*
	 * Init.
	 */
	FRONT_LOGIC_init();
	/*
	 * App.
	 */

	while( True )
	{
		FRONT_LOGIC_run();
	}

}
