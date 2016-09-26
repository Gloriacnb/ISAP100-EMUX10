/*
 * SwitchPort.cpp
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 */

#include "SwitchPort.h"
#include "SwitchCore.h"
#include "SoftSwitch_define.h"
#include "PriPacket.h"

std::map<uint8, SwitchPort*> SwitchPort::portGroup;


SwitchPort::~SwitchPort() {
	portGroup.erase(sn);
}

SwitchPort::SwitchPort(uint8 portSn) {
	sn = portSn;
	portGroup.insert( std::pair<uint8, SwitchPort*>(sn, this) );
}


int SwitchPort::inputPacket(LAYER2FRAME* f) {
	PriPacket* p = makePacket(f);
	if( p == 0 ) {
		return -1;
	}
	int r = SwitchCore::instance().processPacket(*p);
	delete p;
	return r;
}


void SwitchPort::broadcastThePacket( PriPacket& pkt ) {
	std::map<uint8, SwitchPort*>::iterator it = portGroup.begin();
	while( it != portGroup.end() ) {
		it->second->outputPacket(pkt);
		it++;
	}
}
