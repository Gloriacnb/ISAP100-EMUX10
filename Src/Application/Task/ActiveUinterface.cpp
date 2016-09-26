/*
 * ActiveUinterface.cpp
 *
 *  Created on: 2013-9-7
 *      Author: Administrator
 */



#include "Task_define.h"
#include "CUInterface.h"
#include <stdio.h>

OS_TID t_UActive;


__task void T_UActive(void* pui ) {
	CUInterface* uif = (CUInterface*)pui;
	while( 1 ) {
		if( uif ) {
			if( uif->active() ) {
				os_dly_wait(900);
			}
			else {
				os_dly_wait(100);
			}
		}
	}
}

