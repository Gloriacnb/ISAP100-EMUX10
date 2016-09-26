/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			TerminalUart.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/TerminalUart.h
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


#ifndef TERMINALUART_H_
#define TERMINALUART_H_

#include "lpc_types.h"
#include <rtl.h>
#if defined (__cplusplus)
extern "C"
{
#endif

void term_dat_out_len(UNS_8 *dat, int chars);
void term_dat_out(UNS_8 *dat);
void term_dat_out_crlf(UNS_8 *dat);
int term_dat_in(UNS_8 *buff, int bytes);
void TerminalUARTInit(void);
int term_dat_in_ready(void);
int term_dat_out_active(void);
BOOL_32 term_break(void);
int getkey (void);
int sendchar (int ch);


extern OS_SEM sem_uart_rcv;

#if defined (__cplusplus)
}
#endif /*__cplusplus */
#endif /* TERMINALUART_H_ */
