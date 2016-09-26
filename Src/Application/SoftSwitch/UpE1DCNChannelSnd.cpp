/*
 * UpE1DCNChannelSnd.cpp
 *
 *  Created on: 2016Äê1ÔÂ8ÈÕ
 *      Author: Administrator
 */

#include "UpE1DCNChannelSnd.h"
#include "chipslotlogic.h"
#include "UID.h"
#include "CUpE1Port.h"

UpE1DCNChannelSnd::UpE1DCNChannelSnd(uint32 uid, CUpE1Port* p) : DCCChannelSnd(uid){
	port = p;
}

UpE1DCNChannelSnd::~UpE1DCNChannelSnd() {
	// TODO Auto-generated destructor stub
}

void UpE1DCNChannelSnd::sendData(uint8* d, uint32 len) {
	if( port != 0 ) {
		if( port->getType() != 0 ) {
			if( port->getEnable() != 0 ) {
				UN_Info info = UID::breakUID(getUID());
				uint8 hid = info.nm.sn + 2;
				sendDcnPacket(hid, d, len);

			}
		}
	}
}

uint32 UpE1DCNChannelSnd::getPortUID(void) {
	return port->getUID();
}
