/*
 * MidoptDCC.cpp
 *
 *  Created on: 2013-3-12
 *      Author: Administrator
 */

#include "MidoptDCC.h"
#include "ChipSlotLogic.h"
#include "EZ_types.h"
#include "Task_define.h"
#include "lpc32xx_intc_driver.h"
#include <stdlib.h>
#include "CUpE1Port.h"

#ifdef EZ_Debug
#include "TraceCounter.h"
#endif

extern void insert_dcc_list(DCC_FRAME frame);
extern OS_TID t_dcc_rcv;
extern "C" __irq void IntHandler_DCC(void) ;

__irq void IntHandler_DCC(void)  {

 	CUpE1Port* port = CUpE1Port::getFirstInstance();
 	while( port != 0 ) {
 		port->receivData();
 		port = CUpE1Port::getNextInstance(port->getUID());
 	}

	LAYER2FRAME *frame;
	DCC_FRAME df;
	uint32 ch = 0;
	uint8 flagok = 0;
	uint16 pkgLen;
#ifdef EZ_Debug
	dcc_trace.interrupt++;
#endif
loop:
 	if( ifHavePacket(0) == TRUE ) {
 		ch = 0;
 	}
 	else if( ifHavePacket(1) == TRUE ) {
 		ch = 1;
 	}
 	else if( ifHavePacket(2) == TRUE ) {
 		ch = 2;
 	}
 	else if( ifHavePacket(3) == TRUE ) {
 		ch = 3;
 	}
 	else{
 		if( flagok == 1 ) {
 			isr_evt_set(0x0001, t_dcc_rcv);
 		}
 		return;
 	}
#ifdef EZ_Debug
	dcc_trace.rcv++;
#endif
 	pkgLen = getPacketLen(ch);
 	if( pkgLen > DEF_DCC_MTU ) {
 		clearDccRdBufForce(ch);
 		goto loop;
 	}
 	frame = alloc_Eth_mem (pkgLen);
 	/* if 'alloc_mem()' has failed, ignore this packet. */
 	if (frame != NULL ) {
 		uint8* dp = frame->frame;
 		GetDCCPacket(ch, dp);
		df.chuid = ch;
		df.frame = frame;
		insert_dcc_list(df);
		flagok = 1;
#ifdef EZ_Debug
	dcc_trace.rcv_valid++;
#endif
//		}
 	}
 	else {
 		clearDccRdBufForce(ch);
 	}
 	goto loop;

}

void Dcc_interrupt_enable(void) {
	int_enable(IRQ_GPI_08);
}

void Dcc_interrupt_disable(void) {
	int_disable(IRQ_GPI_08);
}

void SIC_2_Enable(void) {
	int_enable(IRQ_SUB2IRQ);
}

void SIC_2_Disable(void) {
	int_disable(IRQ_SUB2IRQ);
}
// void transportOtherDCC(DCC_FRAME* frame) {
// 	uint8 ch = frame->ch ? 0 : 1;
// 	DccSendPacket( ch, (uint8*)(&frame->frame->data[0]), frame->frame->length );
// }
// void transport2DCC(LAYER2FRAME* frame) {
// 	DccSendPacket( 0, (uint8*) (&frame->data[0]), frame->length );
// 	DccSendPacket( 1, (uint8*) (&frame->data[0]), frame->length );
// }

// void transportByDcc(uint8 ch, LAYER2FRAME* frame) {
// 	DccSendPacket( ch, (uint8*) (&frame->data[0]), frame->length );
// }

void SdhDccSendDirect(uint8 ch, uint8* d, uint32 len) {
	if( (d == 0) || (len > DEF_DCN_MTU) ) {
		return;
	}
	DccSendPacket( ch, d, len );
}
