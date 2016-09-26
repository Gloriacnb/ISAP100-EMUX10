/*
 * MacPortMap.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "MacPortMap.h"
#include "PriPacket.h"

#include <rtl.h>

OS_MUT mut_portmac;

MacPortMap::MacPortMap() {
	// TODO Auto-generated constructor stub
	os_mut_init(mut_portmac);
}

MacPortMap::~MacPortMap() {
	// TODO Auto-generated destructor stub
}

void MacPortMap::learnAddress(PriPacket& pkt) {
	MACAddr m(pkt.getPrivateTag().srcMAC);
	PortRecord r(pkt.getSourcePort());
	os_mut_wait(mut_portmac, 0xffff);
	std::map<MACAddr, PortRecord>::iterator it = macPortTable.find(m);
	if( it != macPortTable.end() ) {
		it->second = r;
	}
	else {
		macPortTable.insert( std::pair<MACAddr, PortRecord>(m, r));
	}
	os_mut_release(mut_portmac);
}

int MacPortMap::findOutputPort(PriPacket& pkt) {
	MACAddr m(pkt.getPrivateTag().decMAC);
	os_mut_wait(mut_portmac, 0xffff);
	std::map<MACAddr, PortRecord>::iterator it = macPortTable.find(m);
	os_mut_release(mut_portmac);
	if( it != macPortTable.end() ) {
		return it->second.portSn;
	}
	return -1;
}


void MacPortMap::aging(void) {
	os_mut_wait(mut_portmac, 0xffff);
	std::map<MACAddr, PortRecord>::iterator it = macPortTable.begin();
	while( it != macPortTable.end() ) {
		if( it->second.AgingCounter == 0 ) {
			macPortTable.erase(it++);
		}
		else{
			--(it->second.AgingCounter);
			++it;
		}
	}
	os_mut_release(mut_portmac);
}
