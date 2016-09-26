/*
 * CSTBus.cpp
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#include "CSTBus.h"
#include "UID.h"
#include "CTSChannel.h"

CSTBus::CSTBus(uint8 slot, uint8 hid) {
	for( int i = 0; i < 32; i++ ) {
		ST_Time_Slot tsInfo = {slot+1, hid, i};
		uint32 uid = UID::makeUID(&tsInfo);
		CTSChannel* ts = new CTSChannel(uid);
	}
}

CSTBus::~CSTBus() {
	// TODO Auto-generated destructor stub
}

