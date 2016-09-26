/*
 * SwitchPortInner.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "SwitchPortInner.h"
#include "PriPacket.h"
#include "DCCChannelSnd.h"
#include "DCCChannelRcv.h"
#include <string.h>

uint8 SwitchPortInner::pSnBase = 3;

SwitchPortInner::SwitchPortInner() : SwitchPort(pSnBase++) {
	// TODO Auto-generated constructor stub
	currentRcvCh = 0;
}

SwitchPortInner::SwitchPortInner(uint8 sn) : SwitchPort(sn) {
	currentRcvCh = 0;
}


SwitchPortInner::~SwitchPortInner() {
	// TODO Auto-generated destructor stub
}

PriPacket* SwitchPortInner::makePacket(LAYER2FRAME* f) {
	PriPacket* pkt = new PriPacket(getPortSn(), f);
	return pkt;
}

int SwitchPortInner::outputPacket(PriPacket& pkg) {
	uint32 sn = pkg.getPrivateTag().sn;
	uint16 priLen = pkg.getPriLen();
	uint8* ch = new uint8[priLen];
	if( ch == 0 ) {
		return -1;
	}
	ch[0] = sn>>24;
	ch[1] = sn>>16;
	ch[2] = sn>>8;
	ch[3] = sn>>0;
	uint16 len = 0;
	uint8* stdd = pkg.getStdStream(&len);
	memcpy( &ch[4], stdd, len);
//	std::string head(ch, sizeof(ch));
//	std::string s = head + pkg.getStdStream();
	std::map<uint32, DCCChannelSnd*>::iterator it = dccSnd.begin();
	while( it != dccSnd.end() ) {
		it->second->sendData(ch, priLen);
		++it;
	}
	delete []ch;
	return 1;
}


void SwitchPortInner::addDcc(DCCChannelRcv* ch) {
	ch->setInnerPort(this);
}

void SwitchPortInner::addDcc(DCCChannelSnd* ch) {
	dccSnd.insert( std::pair<uint32, DCCChannelSnd*>( ch->getUID(), ch) );
}

void SwitchPortInner::removeDcc(DCCChannelRcv* ch) {
	ch->setInnerPort(0);
}
void SwitchPortInner::removeDcc(DCCChannelSnd* ch) {
	dccSnd.erase(ch->getUID());
}

