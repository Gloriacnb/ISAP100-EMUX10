/*
 * CTSChannel.cpp
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#include "CTSChannel.h"
#include <sstream>


std::map<uint32, CTSChannel*> CTSChannel::Group;

CTSChannel::CTSChannel(uint32 uid) {
	iUID = uid;
	mapingPartner = 0;
	active = 0;
	std::ostringstream s;
	s << "TS-Channel-" << (uid & 0xff)+1;
	name = s.str();
	Group.insert(std::pair<uint32, CTSChannel*>(uid, this));
}

CTSChannel::~CTSChannel() {
	// TODO Auto-generated destructor stub
}

