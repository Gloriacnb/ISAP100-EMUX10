/*
 * Task_alarm.cpp
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */


#include "Task_define.h"
#include <rtl.h>
#include "SDHGroup.h"
#include "DeviceLocal.h"
#include "CSTM.h"
#include "CUnframeE1.h"
#include "CVCGGroup.h"
#include "CLoopModule.h"
#include "CMainBoard.h"

OS_TID t_alarm_process;

__task void T_Alarm_process_ISAP(void ) {
	while( 1 ) {
		os_dly_wait(100);

		/* stm port alarm */
		uint32 uid = DeviceLocal::instance().GetSdhObject().GetFirstUid();
		do {
			CSTM* stm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(uid);
			if( stm ) {
				stm->processAlarm();
			}
		}
		while( (uid = DeviceLocal::instance().GetSdhObject().GetNextUid(uid)) != 0 );

		/* E1 port alarm */
		uid = CUnframeE1::GetFirstE1Uid();

		while( uid != 0 ) {
			CUnframeE1* e1 = CUnframeE1::getE1(uid);
			if( e1 ) {
				e1->processAlarm();
			}
			uid = CUnframeE1::GetNextUid(uid);
		}

		/* vcg Alarm */
		DeviceLocal::instance().GetVcgGroupObject().processAlarm();

		/* Loop Check */
		CLoopModule::instance().runLoopCheck();

		/*NMPort E1 alarm*/
		DeviceLocal::instance().getMainBoard()->processAlarm();
	}

}

__task void T_Alarm_process_PCM(void ) {
	while( 1 ) {
		os_dly_wait(100);

		/* Loop Check */
		CLoopModule::instance().runLoopCheck();
		/*NMPort E1 alarm*/
		DeviceLocal::instance().getMainBoard()->processAlarm();
	}
}


