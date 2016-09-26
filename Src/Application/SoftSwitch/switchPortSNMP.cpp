/*
 * switchPortSNMP.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "switchPortSNMP.h"
#include "SoftSwitch_define.h"
#include "PriPacket.h"
#include <string>

extern "C" void SendPacketDirect(uint8* pkt, uint32 pktlen);


switchPortSNMP::switchPortSNMP() : SwitchPortStd(SNMP_Port_Sn){
	// TODO Auto-generated constructor stub

}

switchPortSNMP::~switchPortSNMP() {
	// TODO Auto-generated destructor stub
}

//PriPacket& switchPortSNMP::makePacket(uint8* d, uint16 len) {
//	static uint16 tValue = 1;
//	Private_tag tag = {0};
//	tag.sn = tValue++;
//	memcpy( tag.decMAC, d, 6 );
//	memcpy( tag.srcMAC, d+6, 6 );
//	PriPacket* pkt = new PriPacket(tag, getPortSn(), d, len);
//	return *pkt;
//}


int switchPortSNMP::outputPacket(PriPacket& pkg) {
//	std::string& s = pkg.getStdStream();
	if( pkg.getSourcePort() == SNMP_Port_Sn ) {
		return -1;
	}
	uint16 len = 0;
	uint8* d = pkg.getStdStream(&len);
	SendPacketDirect(d, len);
	return 1;
}
