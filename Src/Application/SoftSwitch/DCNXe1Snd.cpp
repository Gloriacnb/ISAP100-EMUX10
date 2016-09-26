/*
 * DCNXe1Snd.cpp
 *
 *  Created on: 2015Äê12ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "DCNXe1Snd.h"
#include "chipslotLogic.h"
#include "UID.h"

DCNXe1Snd::DCNXe1Snd(uint32 uid, uint32 portUID) : DCCChannelSnd(uid) {
	puid = portUID;

}

DCNXe1Snd::~DCNXe1Snd() {
	// TODO Auto-generated destructor stub
}

void DCNXe1Snd::sendData(uint8* d, uint32 len) {
	uint8 chsn = UID::breakUID(getUID()).E1.E1 + 2;
	DccSendPacket(chsn, d, len);
}
