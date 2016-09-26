/*
 * SwitchPortStd.cpp
 *
 *  Created on: 2013-6-26
 *      Author: Administrator
 */

#include "SwitchPortStd.h"
#include "SoftSwitch_define.h"
#include "PriPacket.h"
#include <string.h>
#include "Layer2Tag.h"

//#include "TerminalUart.h"

SwitchPortStd::SwitchPortStd(uint8 sn) : SwitchPort(sn) {
	// TODO Auto-generated constructor stub

}

SwitchPortStd::~SwitchPortStd() {
	// TODO Auto-generated destructor stub
}

PriPacket* SwitchPortStd::makePacket(LAYER2FRAME* f) {
	static uint32 tValue = 1;
	uint8* d = f->frame;
	Layer2Tag tag;
	if( tValue >= 0x7fffffff ) {
		tValue = 1;
	}
	tag.sn = tValue++;
	memcpy( tag.decMAC, d, 6 );
	memcpy( tag.srcMAC, d+6, 6 );
	PriPacket* pkt = new PriPacket(tag, getPortSn(), f);
	return pkt;
}
