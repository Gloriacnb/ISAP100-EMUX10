/*
 * DCCChannelSnd.cpp
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#include "DCCChannelSnd.h"

std::map<uint32, DCCChannelSnd*> DCCChannelSnd::DccSendMap;


DCCChannelSnd::DCCChannelSnd(uint32 id) {
	uid = id;
	DccSendMap.insert( std::pair<uint32, DCCChannelSnd*>(uid, this) );
}

DCCChannelSnd::~DCCChannelSnd() {
	// TODO Auto-generated destructor stub
	DccSendMap.erase(uid);
}

