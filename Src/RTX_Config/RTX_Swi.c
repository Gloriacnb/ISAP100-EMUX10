/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RTX_SWI.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2012 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "lpc_irq_fiq.h"
/*----------------------------------------------------------------------------
 * Software Interrupt Functions accept parameters, may return values
 * and run in Supervisor Mode (Interrupt protected)
 *---------------------------------------------------------------------------*/

void __swi(8)  EnterCritical (void);
void __SWI_8            (void) {
	disable_irq();
}


void __swi(9)  ExtiCritical (void);
void __SWI_9            (void) {
	enable_irq();
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/


