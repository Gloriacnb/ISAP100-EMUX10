/*
 * Task_EthernetRcv.cpp
 *
 *  Created on: 2013-3-11
 *      Author: Administrator
 */

#include <rtl.h>
#include "Task_define.h"
#include <list>
#include <Net_Config.h>
//#include "LPC32_EMAC.h"
#include <LPC325x.H>                    /* LPC325x definitions               */
#include <string.h>
#include "MidoptDCC.h"
#include "DeviceLocal.h"

#include "SwitchPortInner.h"
#include "DCCChannelRcv.h"
#include "UID.h"

#include "MidWatchDog.h"

#ifdef EZ_Debug
#include "TraceCounter.h"
#include "TerminalUart.h"
#endif

#include "SwitchPort.h"
#include <sstream>
//#include "TerminalUart.h"

#include "EthMemory.h"

OS_TID t_eth_rcv;

OS_TID t_dcc_rcv;

extern "C" {
void int_enable_eth_real(void);
void int_disable_eth_real(void);
}
extern "C" void SendFrameDirect(LAYER2FRAME* frame);

std::list<LAYER2FRAME*> eth_list;
std::list<LAYER2FRAME*> eth_proccessing;

//typedef struct {
//	uint8 mac[6];
//	uint32 liveCnt;
//}Mac_address;
//std::list<Mac_address> up_mac_list;

extern "C" void insertEthList(LAYER2FRAME* frame);
extern "C" void SendFrameBySwitch(LAYER2FRAME* frame);

void insertEthList(LAYER2FRAME* frame) {
	if( eth_list.size() > 255 ) {
#ifdef EZ_Debug
		term_dat_out_crlf((uint8*)"eth frame buf full!");
#endif
	}
	else {
		eth_list.push_back(frame);
	}
}


/*
 * LPC3250以太口收包任务
 */
__task void T_Eth_Rcv(void) {
	while( 1 ) {
		os_evt_wait_or(0x0001, 0xffff);
		MidWatchDog::feed();
		eth_proccessing.clear();

		int_disable_eth_real();
		eth_proccessing.swap(eth_list);
		
		int_enable_eth_real();

//		std::ostringstream os;
//		os << "EMAC Pkgs: " << (int)eth_proccessing.size();
//		term_dat_out_crlf( (uint8*)os.str().c_str() );

		std::list<LAYER2FRAME*>::iterator it = eth_proccessing.begin();
		while( it != eth_proccessing.end() ) {
			SwitchPort::getSwitchPort(1)->inputPacket( (*it) );
			free_Eth_mem(*it);
			it++;
//			eth_proccessing.erase(it++);
		}
	}

}


#include "MidoptDCC.h"
#include "ChipSlotLogic.h"
#include <stdlib.h>
std::list<DCC_FRAME> dcc_INT_list;
std::list<DCC_FRAME> dcc_Processing;

extern void insert_dcc_list(DCC_FRAME frame);

 void insert_dcc_list(DCC_FRAME frame) {

	 if( dcc_INT_list.size() > 400 ) {
#ifdef EZ_Debug
		term_dat_out_crlf((uint8*)"DCC list buf full!");
#endif
	 }
	 dcc_INT_list.push_back(frame);

 }


/*
 * DCC 收包任务
 */
__task void T_DCC_Rcv(void) {
//	std::list<DCC_FRAME>::iterator it;
	while( true ) {
		os_evt_wait_or(0x0001, 0xffff);
		MidWatchDog::feed();

#ifdef EZ_Debug_out
		term_dat_out_crlf((uint8*)"2---T_DCC_Rcv start.");
#endif
		dcc_Processing.clear();
		Dcc_interrupt_disable();
		dcc_Processing.swap(dcc_INT_list);
		Dcc_interrupt_enable();

//		std::ostringstream os;
//		os << "DCC Pkgs: " << (int)dcc_Processing.size();
//		term_dat_out_crlf( (uint8*)os.str().c_str() );

		std::list<DCC_FRAME>::iterator it = dcc_Processing.begin();
		while( it != dcc_Processing.end() ) {
//			DCC_FRAME& f = (*it);
//			uint8* packet = (uint8*)f.frame->data[0];

//			uint32 uid = 0;
//			if( (*it).ch == 0 || (*it).ch == 1 ) {
//				//sdh dcc
//				ST_SDH_STM info = {100, (*it).ch};
//				uid = UID::makeUID(&info);
//			}
//			else if( (*it).ch == 2 || (*it).ch == 3) {
//				ST_E1 info = {100, (*it).ch-2};
//				uid = UID::makeUID(&info);
//			}
			DCCChannelRcv* ch = DCCChannelRcv::getRcvDccByUID((*it).chuid);
			if( ch ) {
				SwitchPortInner* port = ch->getInnerPort();
				if( port ) {
					port->currentRcvCh = ch;
					port->inputPacket((*it).frame);
				}
			}
//if( (*it).frame->length == 96 ) {
//	if((*it).frame->frame[4] != 0xff )
//		term_dat_out_len((*it).frame->frame, (*it).frame->length);
//}
			free_Eth_mem((*it).frame);
			it++;
		}

#ifdef EZ_Debug_out
		term_dat_out_crlf((uint8*)"2---T_DCC_Rcv end.");
#endif
	}

}


/*
 * mac 地址老化
 * note：此处应用了关以太中断，可能关闭任务调度更好些
 */
//__task void T_aging(void) {
//	while(1) {
//		os_dly_wait(100);
// 		int_disable_eth_real();
// 		std::list<Mac_address>::iterator it = up_mac_list.begin();
// 		for( ; it != up_mac_list.end(); it++ ) {
//			if( (os_time_get() - (*it).liveCnt) > 3000 ) {
//				up_mac_list.erase(it);
//				break;
//			}
//
// 		}
//		int_enable_eth_real();
//
//	}
//}
//

void SendFrameBySwitch(LAYER2FRAME* frame) {
	if( frame ) {
		SwitchPort::getSwitchPort(2)->inputPacket(frame);
	}
//	term_dat_out_len(frame->frame, frame->length);
}

void CommunicationInit(int mode) {
	InitEthMemory();
	if( mode == 0 ) {
		t_eth_rcv = os_tsk_create(T_Eth_Rcv, P_ETH_RCV);
		t_dcc_rcv = os_tsk_create(T_DCC_Rcv, P_DCC_RCV);
		t_aging = os_tsk_create(T_Aging, P_Agint_MAC);
		int_enable_eth_real();
		SIC_2_Enable();
		Dcc_interrupt_enable();
	}
	else {
		t_eth_rcv = os_tsk_create(T_Eth_Rcv, P_ETH_RCV);
		t_aging = os_tsk_create(T_Aging, P_Agint_MAC);
		int_enable_eth_real();

		/* remove later*/
		SIC_2_Enable();
		Dcc_interrupt_enable();
	}
}

