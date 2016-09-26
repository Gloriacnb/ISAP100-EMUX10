/*
 * Taskwdt.cpp
 *
 *  Created on: 2013-7-24
 *      Author: Administrator
 */

#include "Task_define.h"
#include "MidWatchDog.h"
#include <rtl.h>

OS_TID t_wdt;

__task void T_WDT(void) {
	MidWatchDog::WatchDogInitial();
	MidWatchDog::start();
	while( 1 ) {
		os_dly_wait(100);
		MidWatchDog::feed();
	}
}
