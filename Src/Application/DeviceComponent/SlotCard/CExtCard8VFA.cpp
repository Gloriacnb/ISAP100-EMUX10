/*
 * CExtCard8VFA.cpp
 *
 *  Created on: 2017年11月20日
 *      Author: Administrator
 */

#include "CExtCard8VFA.h"
#include "CIsap100HardwareDesc.h"
#include "CVFPortA.h"
#include "UID.h"

__task void T_MT_Wave(void* card );

CExtCard8VFA::~CExtCard8VFA() {
	// TODO Auto-generated destructor stub
}

CExtCard8VFA::CExtCard8VFA(uint8 slot, std::string& name) : CExtCard8VF(slot, name) {
//	slotNumber = slot;
	for( int i = 0; i < portNumber; i++ ) {
		ST_Time_Slot info = {slot+1, CIsap100HardwareDesc::slot_stbus_map[slot], CIsap100HardwareDesc::VF_port_channel_Map[i]};
		uint32 uid = UID::makeUID(&info);

		vf[i] = new CVFPortA(uid, i,	&configData.port[i],&configData.group[i/4], &stroer);
	}
}


int CExtCard8VFA::GetCartTypeID() {
	return itsTypeID;
}
