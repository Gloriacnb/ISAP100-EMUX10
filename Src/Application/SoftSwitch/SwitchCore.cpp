/*
 * SwitchCore.cpp
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 */

#include "SwitchCore.h"
#include "PriPacket.h"
#include "SwitchPort.h"
#include "TerminalUart.h"
#include <sstream>
#include <rtl.h>
#include "TopoManager.h"

OS_MUT mut_switch;
SwitchCore SwitchCore::sw;


SwitchCore::SwitchCore() {
	// TODO Auto-generated constructor stub
	os_mut_init(mut_switch);
}

SwitchCore::~SwitchCore() {
	// TODO Auto-generated destructor stub
}

int SwitchCore::processPacket(PriPacket& pkt) {
    if( pkt.packetType() == multicast ) {
        TopoManager::proccessTopoSearch(pkt);
        return 0;
    }
	if( finishedPkt.finished(pkt) ) {
		return -1;
	}

	finishedPkt.finishThePacket(pkt);

	macPortTable.learnAddress(pkt);

	switch( pkt.packetType() ) {

	case unicast: {
		int port = macPortTable.findOutputPort(pkt);
		if( port > 0 ) {
			SwitchPort* p = SwitchPort::getSwitchPort(port);
			if( p ) {
				p->outputPacket(pkt);
			}
		}
	}
	break;

	case broadcast:{
		SwitchPort::broadcastThePacket(pkt);
	}
		break;
	default:
		break;
	}
	return pkt.packetType();

}
