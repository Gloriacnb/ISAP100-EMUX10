/*
 * Task_aging.cpp
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */


#include "Task_define.h"
#include "SwitchCore.h"

OS_TID t_aging;


__task void T_Aging(void ) {
	while( 1 ) {
		os_dly_wait(100);
		SwitchCore::instance().getFinishedPkt().aging();
		SwitchCore::instance().getMacPortTable().aging();
	}

}

