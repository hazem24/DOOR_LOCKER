/************************************************************************/
/* This File contains common macros which be useful to use in anyApp.    */
/************************************************************************/

#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/*
*Check if specific bit have one.
*/
#define CHECK_BIT(REG, BIT_NUMBER)\
		REG & (1 << BIT_NUMBER)
/*
*Set Bit to One.
*/
#define SET_BIT(REG, BIT_NUMBER)\
		REG = REG | ( 1 << BIT_NUMBER )


#define BIT_IS_CLEAR(REG,BIT_NUMBER)\
	(!(REG & (1 << BIT_NUMBER)))
/*
* Clear Bit.
*/
#define CLEAR_BIT(REG,BIT_NUMBER)\
		REG = REG & (~( 1 << BIT_NUMBER ))
#define TOGGLE_BIT(REG, BIT_NUMBER)\
		REG = REG ^ ( 1 << BIT_NUMBER)

#define ROTATE_RIGHT(REG, NUM_OF_BITS)\
		REG = (REG >> NUM_OF_BITS) | ( REG << 1 )
		
#define ROTATE_LEFT( REG, NUM_OF_BITS )\
		REG = (REG << NUM_OF_BITS) | ( REG >> 1 )
	
/*
 *	SET_BITS Macro works only in little endian archit.
 */
#define SET_BITS(REG, VALUE)\
		(REG = REG | ( VALUE ))

#define SET_BIT_WITH_VALUE(REG, BIT, VALUE)\
	if(VALUE == 0)\
		CLEAR_BIT(REG,BIT);\
	else\
		SET_BIT(REG, BIT);
#endif

