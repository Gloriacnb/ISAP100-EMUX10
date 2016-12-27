/*
 * DCCSdhSnd.cpp
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#include "DCCSdhSnd.h"
#include "MidoptDCC.h"
#include "UID.h"


DCCSdhSnd::DCCSdhSnd(uint32 uid, uint32 portUID) : DCCChannelSnd(uid) {
	puid = portUID;

}

DCCSdhSnd::~DCCSdhSnd() {
	// TODO Auto-generated destructor stub
}

void DCCSdhSnd::sendData(uint8* d, uint32 len) {
	uint32 uid = getUID();
	try {
		UN_Info info = UID::breakUID(uid);
		uint8 ch = info.nm.sn;
		SdhDccSendDirect(ch, d, len);
	}
	catch(...) {
		return;
	}
}
