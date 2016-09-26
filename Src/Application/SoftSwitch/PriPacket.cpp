/*
 * PriPacket.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "PriPacket.h"
//#include "SoftSwitch_define.h"
#include <string.h>

const uint8 PriPacket::multicastAddress[6] = {0x1c, 0x88, 0x88, 0x88, 0x88, 0x88};
const uint8 PriPacket::broadcastAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


/*
 * 内部二层口收到包用次构造函数
 */
PriPacket::PriPacket(uint8 swport, LAYER2FRAME* f) {
	srcPort = swport;
	frame = f;
	stdData = &f->frame[4];
	stdDataLen = f->length - 4;
	uint8* d = f->frame;
	priTag.sn = (d[0] << 24) | (d[1] << 16) | (d[2] << 8 ) | d[3];
	memcpy( priTag.decMAC, (d+4), 6);
	memcpy( priTag.srcMAC, (d+10), 6);

//	streamPacket.assign((char*)(d+2), len-2);
//	int a = packetType();
}

/*
 * 标准二层口收到包用此构造函数
 */
PriPacket::PriPacket(Layer2Tag& tag, uint8 swport, LAYER2FRAME* f) {
	srcPort = swport;
	priTag = tag;
	frame = f;
	stdData = f->frame;
	stdDataLen = f->length;
//	streamPacket.assign((char*)d, len);
}

PriPacket::~PriPacket() {
	// TODO Auto-generated destructor stub
}

int PriPacket::packetType() {
	if( memcmp(priTag.decMAC, multicastAddress, 6) == 0 ) {
		return 2;//multicast;
	}
	else if( memcmp(priTag.decMAC, broadcastAddress, 6) == 0 ) {
		return 1;//broadcast;
	}
	return 0;//unicast;
}
