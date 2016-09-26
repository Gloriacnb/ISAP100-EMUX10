/*
 * DCCChannelRcv.cpp
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#include "DCCChannelRcv.h"

std::map<uint32, DCCChannelRcv*> DCCChannelRcv::DccRcvMap;

DCCChannelRcv::DCCChannelRcv(uint32 id) {
	// TODO Auto-generated constructor stub
	uid = id;
	upstreamUid = 0;
	DccRcvMap.insert( std::pair<uint32, DCCChannelRcv*>(uid, this) );
	port = 0;
	resetAgingCounter();
}

DCCChannelRcv::~DCCChannelRcv() {
	// TODO Auto-generated destructor stub
	DccRcvMap.erase(uid);
}

