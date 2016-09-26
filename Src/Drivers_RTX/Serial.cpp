/*
 * Serial.cpp
 *
 *  Created on: 2013-2-16
 *      Author: Administrator
 */

//#include "Serial.h"
#include "TerminalUart.h"
#include <Net_Config.h>


void init_serial (void) {
  /* Initialize the serial interface */
	TerminalUARTInit();
}


/*--------------------------- com_putchar -----------------------------------*/

BOOL com_putchar (U8 c) {
	term_dat_out_len(&c, 1);
	return (__TRUE);
}


/*--------------------------- com_getchar -----------------------------------*/

int com_getchar (void) {
  /* Read a byte from serial interface */
  if ( term_dat_in_ready() == 0 ) {
    /* Serial receive buffer is empty. */
    return (-1);
  }
  UNS_8 byte;
  term_dat_in(&byte, 1);
  return (byte);
}


/*--------------------------- com_tx_active ---------------------------------*/

BOOL com_tx_active (void) {
  /* Return status Transmitter active/not active.         */
  /* When transmit buffer is empty, 'tx_active' is FALSE. */
  return (term_dat_out_active());
}
