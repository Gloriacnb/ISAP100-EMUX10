/*
 * Task_Reset.cpp
 *
 *  Created on: 2013-3-18
 *      Author: Administrator
 */
#include "Task_define.h"
#include "ChipOptLogic.h"


OS_TID t_reset;

__task void T_Device_Reset(void) {
	os_evt_wait_or(0x0003, 0xffff);
	uint16 flgEvent = os_evt_get();

	if( flgEvent == 0x0001 ) {
		Rst_MCU(up_main);
	}
	else if( flgEvent == 0x0002 ) {
		Rst_MCU(up_fpga);
	}


}



