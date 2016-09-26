/*
 * CIsapSlot.cpp
 *
 *  Created on: 2013-2-23
 *      Author: Administrator
 */

#include "CIsapSlot.h"

#include "CSTBus.h"
#include "CE1Channel.h"
#include "UID.h"
#include "CIsap100HardwareDesc.h"
#include "Mid_SPI.h"


CIsapSlot::~CIsapSlot() {
	// TODO Auto-generated destructor stub
}

CIsapSlot::CIsapSlot(int sn, CInterfaceCardCreatFactory* f) : CBaseSlot(sn, f) {
	for( int i = 0; i < 4; i++ ) {
		ST_E1 info = {sn+1, i};
		uint32 uid = UID::makeUID(&info);
		fixE1[i] = new CE1Channel(sn,
				CIsap100HardwareDesc::slotE1_channel_map[sn][i], i);
	}
	fixStbus = new CSTBus(sn, CIsap100HardwareDesc::slot_stbus_map[sn]);
}

int CIsapSlot::GetCardTypeIDFromHardware() {
	uint8 type = 0;
	ExtCPLDRegReadByte(GetSn()*4, 0, &type);
	return type;
}
