/************************************************************************/
/* This file defined avr configuration.                                                                     */
/************************************************************************/
#ifndef MICRO_CONFIG
#define MICRO_CONFIG

#ifdef F_CPU
#undef F_CPU
#endif

#define F_CPU 8000000UL

/*#ifndef F_CPU
#define F_CPU 8000000UL
#endif*/

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"




#endif  /* End Micro Config. */




