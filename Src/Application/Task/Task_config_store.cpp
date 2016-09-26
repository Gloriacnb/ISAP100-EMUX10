/*
 * Task_config_store.cpp
 *
 *  Created on: 2013-4-8
 *      Author: Administrator
 */

#include "Task_define.h"
#include <rtl.h>
#include "SDHGroup.h"
#include "DeviceLocal.h"

OS_TID t_config_store;

__task void T_Config_Store(void ) {
	static const uint32 delay = 50; //500ms
	while( 1 ) {
		os_evt_wait_or(evt_store, 0xffff);
		uint16 flgEvent = os_evt_get();

		switch( flgEvent ) {
		case evt_sdh_store: {
			static uint32 start = 0;
			if( start == 0 ) {
				start = os_time_get();
			}
			else if( start + delay > os_time_get() ) {
				start = 0;
				//store sdh config data
				DeviceLocal::instance().GetSdhObject().StoreConfigData();

			}
		}
			break;
		case evt_vcg_store:
			break;
		}
	}
}

