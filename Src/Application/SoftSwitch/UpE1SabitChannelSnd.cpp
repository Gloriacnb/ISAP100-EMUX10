/*
 * UpE1SabitChannelSnd.cpp
 *
 *  Created on: 2016Äê1ÔÂ8ÈÕ
 *      Author: Administrator
 */

#include "UpE1SabitChannelSnd.h"
#include "ChipSlotLogic.h"
#include "UID.h"
#include "CUpE1Port.h"
#include "MidoptDcc.h"

UpE1SabitChannelSnd::UpE1SabitChannelSnd(uint32 uid, CUpE1Port* p) : DCCChannelSnd(uid) {
	port = p;

}

UpE1SabitChannelSnd::~UpE1SabitChannelSnd() {
	// TODO Auto-generated destructor stub
}

void UpE1SabitChannelSnd::sendData(uint8* d, uint32 len) {
	if( port != 0 ) {
		if( (port->getEnable() != 0) && (port->getType() == 0) ) {
			UN_Info info = UID::breakUID(getUID());
			uint8 hid = info.nm.sn + 2;
			if( len < DEF_DCC_MTU ) {
				sendSabitPacket(hid, d, len);
			}
		}
	}
}

uint32 UpE1SabitChannelSnd::getPortUID(void) {
    return port->getUID();
}
