/*
 * Task_OnlineCheck.cpp
 *
 *  Created on: 2013-2-23
 *      Author: Administrator
 */
#include "Task_define.h"
#include "CCardOnlineChecker.h"
#include "DeviceLocal.h"
#include "CSlotManager.h"
#include "CBaseSlot.h"

//os_mbx_declare(MailPOC, 4);

#define MAX_Slot_Check	6

__task void T_Online_Check(void) {
	
	
	CCardOnlineChecker* coc[MAX_Slot_Check];


//	os_mbx_init(MailPOC, sizeof(MailPOC));

//	while( os_mbx_check(&MailPOC) != 0);
//	int sn = 0;
//	while( sn < 4 ) {
//		os_mbx_wait(MailPOC, &oc[sn], 0xffff);
//		++sn;
//
//	}
	for( int i = 0; i < MAX_Slot_Check; i++ ) {
		coc[i] = DeviceLocal::instance().GetSlotManager().GetSlotBySn(i)->getChecker();
	}

	while( 1 ) {

		for( int i = 0; i < MAX_Slot_Check; i++ ) {
			if( coc[i] ) {
				coc[i]->TaskRun();
			}
			os_dly_wait(100);
		}
	}

}



