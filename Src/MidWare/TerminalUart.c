/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			TerminalUart.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/TerminalUart.c
** Created by:          Administrator
** Created date:        2012-11-20
** Version:             V0.1
** Descriptions:        
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:				
** Descriptions:        
**
** Rechecked by:        
***********************************************************************************************************************/

#include "lpc_irq_fiq.h"
#include "lpc_arm922t_cp15_driver.h"
#include "lpc32xx_uart_driver.h"
#include "lpc32xx_intc_driver.h"
#include "lpc_string.h"
#include "TerminalUart.h"

#include <rtl.h>

OS_MUT mut_uart_snd;
OS_MUT mut_uart_rcv;
//OS_SEM sem_uart_snd;
OS_SEM sem_uart_rcv;


/* UART device handles */
static INT_32 uartdev;
static UNS_8 txbuff [512], rxbuff [512];
volatile static int txsize, rxsize;
static int txfill, rxget, txget, rxfill;
static UNS_8 crlf[] = "\r\n";
static volatile BOOL_32 uartbrk;

/***********************************************************************
 *
 * Function: term_dat_send_cb
 *
 * Purpose: UART transmit data callback
 *
 * Processing:
 *     Move data from the ring buffer to the driver.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: This function is called in interrupt context.
 *
 **********************************************************************/
void term_dat_send_cb(void)
{
  INT_32 bwrite, tosend = 512 - txget;

  if (tosend > txsize)
  {
    tosend = txsize;
  }

  /* Write data */
  bwrite = uart_write(uartdev, &txbuff[txget], tosend);
  txsize = txsize - bwrite;
  txget = txget + bwrite;
  if (txget >= 512)
  {
    txget = 0;
  }
}

/***********************************************************************
 *
 * Function: term_dat_recv_cb
 *
 * Purpose: UART receive data callback
 *
 * Processing:
 *     Read data from the driver into the RX ring buffer.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes:
 *     Ring buffer overflow is not accounted for in this application.
 *     This function is called in interrupt context.
 *
 **********************************************************************/
//extern OS_TID t_cli_process;


void term_dat_recv_cb(void)
{
  INT_32 bread, toreadmax = 512 - rxfill;

  /* Read data */
  bread = uart_read(uartdev, &rxbuff[rxfill], toreadmax);
  rxsize = rxsize + bread;
  rxfill = rxfill + bread;
  if (rxfill >= 512)
  {
    rxfill = 0;
  }
  /* send sem to serial rcv */
}

/***********************************************************************
 *
 * Function: term_status_cb
 *
 * Purpose: UART misc callback
 *
 * Processing:
 *     Tests for the break condition.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void term_status_cb(void)
{
	UNS_32 tmp;

	tmp = uart_ioctl(uartdev, UART_GET_STATUS, UART_GET_LINE_STATUS);
	if ((tmp & UART_LSR_BI) != 0)
	{
		uartbrk = TRUE;
	}
}

/***********************************************************************
 *
 * Function: term_dat_out_len
 *
 * Purpose: Send a number of characters on the terminal interface
 *
 * Processing:
 *     Move data into the UART ring buffer.
 *
 * Parameters:
 *     dat   : Data to send
 *     chars : Number of bytes to send
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: Will block until all bytes are sent.
 *
 **********************************************************************/
void term_dat_out_len(UNS_8 *dat,
				      int chars)
{
//	os_mut_wait(mut_uart_snd, 0xffff);
	while (chars > 0) {
		if (txsize < 512)
		{
			txbuff[txfill] = *dat;
			txfill++;
			if (txfill >= 512) {
				txfill = 0;
			}
			dat++;
			chars--;
			int_disable(IRQ_UART_IIR5);
			txsize++;
			int_enable(IRQ_UART_IIR5);
		}

		int_disable(IRQ_UART_IIR5);
		term_dat_send_cb();
		int_enable(IRQ_UART_IIR5);
	}
//	os_mut_release(mut_uart_snd);
}



/***********************************************************************
 *
 * Function: term_dat_out
 *
 * Purpose:
 *     Send some data on the terminal interface up to NULL character
 *
 * Processing:
 *     Move data into the UART ring buffer.
 *
 * Parameters:
 *     dat : Data to send
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: Will block until all bytes are sent.
 *
 **********************************************************************/
void term_dat_out(UNS_8 *dat)
{
	term_dat_out_len(dat, str_size(dat));
}



/***********************************************************************
 *
 * Function: term_dat_out_crlf
 *
 * Purpose:
 *     Send some data on the terminal interface up to NULL character
 *     with a linefeed
 *
 * Processing:
 *     Move data into the UART ring buffer.
 *
 * Parameters:
 *     dat : Data to send
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: Will block until all bytes are sent.
 *
 **********************************************************************/
void term_dat_out_crlf(UNS_8 *dat)
{
	term_dat_out(dat);
	term_dat_out(crlf);
}

/***********************************************************************
 *
 * Function: term_dat_in
 *
 * Purpose: Read some data from the terminal interface
 *
 * Processing:
 *     Move data from the ring buffer to the passed buffer.
 *
 * Parameters:
 *     buff  : Where to place the data
 *     bytes : Number of bytes to read
 *
 * Outputs: None
 *
 * Returns: Number of bytes actually read
 *
 * Notes: None
 *
 **********************************************************************/
int term_dat_in(UNS_8 *buff,
				int bytes) {
	int bread = 0;
	os_mut_wait(mut_uart_rcv, 0xffff);
	while ((bytes > 0)/* && (rxsize > 0)*/) {
	    os_sem_wait(sem_uart_rcv,0xffff);
		*buff = rxbuff[rxget];
		buff++;
		rxget++;
		if (rxget >= 512) {
			rxget = 0;
		}
		bytes--;
		bread++;
		int_disable(IRQ_UART_IIR5);
		rxsize--;
		int_enable(IRQ_UART_IIR5);
	}
	os_mut_release(mut_uart_rcv);
	return bread;
}

/***********************************************************************
 *
 * Function: term_dat_in_ready
 *
 * Purpose:
 *    Determine how many bytes are waiting on the terminal interface
 *
 * Processing:
 *     Return the RX ring buffer size.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Number of bytes waiting to be read
 *
 * Notes: None
 *
 **********************************************************************/
int term_dat_in_ready(void) {
	return rxsize;
}


int term_dat_out_active(void) {
	return txsize;
}


int sendchar (int ch) {
    UNS_8 c = ch;
    UNS_8 buf[1] = {'\r'};
    if( c == '\n')
        term_dat_out_len(buf, 1);
    term_dat_out_len(&c, 1);
    return c;
}

int getkey (void) {
    UNS_8 c = 0;
    term_dat_in(&c, 1);
    return c;
}

/***********************************************************************
 *
 * Function: term_break
 *
 * Purpose: Check for latched terminal break condition
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if a break was detected, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 term_break(void)
{
    BOOL_32 bhit = uartbrk;
    uartbrk = FALSE;
    return bhit;
}

/***********************************************************************
 *
 * Function: term_dat_flush
 *
 * Purpose: Flush data in the terminal input buffer
 *
 * Processing:
 *     Flush the UART FIFOs.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void term_dat_flush(void) {
	uart_ioctl(uartdev, UART_CLEAR_FIFOS, (UART_FCR_TXFIFO_FLUSH |
		UART_FCR_RXFIFO_FLUSH));
}



/***********************************************************************
 *
 * Function: TerminalUARTInit
 *
 * Purpose: Initialize terminal I/O interface
 *
 * Processing:
 *     Use the UART driver to open and initialize the serial port
 *     session.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void TerminalUARTInit(void) {
	  UART_CBS_T cbs;
	  UART_CONTROL_T ucntl;

	  os_mut_init(mut_uart_rcv);
	  os_mut_init(mut_uart_snd);

	  os_sem_init(sem_uart_rcv, 0);

	  /* Setup UART for 115.2K, 8 data bits, no parity, 1 stop bit */
	  ucntl.baud_rate = 115200;
	  ucntl.parity = UART_PAR_NONE;
	  ucntl.databits = 8;
	  ucntl.stopbits = 1;
	  uartdev = uart_open((void *) UART5, (INT_32) & ucntl);
	  if (uartdev != 0)
	  {
	    /* Setup RX and TX callbacks */
	    cbs.rxcb = term_dat_recv_cb;
	    cbs.txcb = term_dat_send_cb;
	    cbs.rxerrcb = term_status_cb;
	    uart_ioctl(uartdev, UART_INSTALL_CBS, (INT_32) &cbs);
	    int_enable(IRQ_UART_IIR5);
	  }

	  /* Initialize TX and RX ring buffers */
	  txfill = txget = rxfill = rxget = txsize = rxsize = 0;

	  /* Enable interrupts */
	  int_enable(IRQ_UART_IIR5);
	  term_dat_out_crlf("UART Terminal has been initializationed.");
	  term_dat_out_crlf("Setup UART 5 for 115.2K, 8 data bits, no parity, 1 stop bit.");
}
