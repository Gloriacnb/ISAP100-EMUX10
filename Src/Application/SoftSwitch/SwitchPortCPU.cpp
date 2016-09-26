/*
 * SwitchPortCPU.cpp
 *
 *  Created on: 2013-6-26
 *      Author: Administrator
 */

#include "SwitchPortCPU.h"
#include <rtl.h>
#include "Task_define.h"
#include "SoftSwitch_define.h"
#include "PriPacket.h"
#include <Net_Config.h>
#include <string.h>
#include "MidoptDCC.h"

SwitchPortCPU::SwitchPortCPU() : SwitchPortStd(CPU_Port_Sn){
	// TODO Auto-generated constructor stub

}

SwitchPortCPU::~SwitchPortCPU() {
	// TODO Auto-generated destructor stub
}

int SwitchPortCPU::outputPacket(PriPacket& pkg) {

	if( pkg.getSourcePort() == CPU_Port_Sn ) {
		return -1;
	}
	int RxLen = pkg.getStdLen();
    OS_FRAME* frame = alloc_mem (RxLen | 0x80000000);
    /* if 'alloc_mem()' has failed, ignore this packet. */
	if (frame != NULL) {
		uint16 len = 0;
		memcpy( &frame->data[0], pkg.getStdStream(&len), RxLen);
		put_in_queue(frame);
		os_evt_set(0x0001, t_tcpTask);
		return 1;
	}
	return -1;
}
