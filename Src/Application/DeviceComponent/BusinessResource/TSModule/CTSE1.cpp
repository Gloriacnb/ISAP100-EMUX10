/*
 * CTSE1.cpp
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#include "CTSE1.h"
#include "UID.h"
#include "CE1Channel.h"
#include "CTSChannel.h"

CTSE1::CTSE1(uint8 slot, uint8 Channelhid, uint8 tsE1Sn) {
	ST_E1 info = {slot+1, Channelhid};
	uint32 uid = UID::makeUID(&info);
	LinkChannel = CE1Channel::getE1(uid);
	if( LinkChannel )
		LinkChannel->setActive(true);

	for( int i = 0; i < 32; i++ ) {
		if( i == 0 || i == 16 ) {
			continue;
		}
		ST_Time_Slot tsInfo = {slot+1, tsE1Sn, i};
		uint32 uid = UID::makeUID(&tsInfo);
		CTSChannel* ts = new CTSChannel(uid);
		if( ts ) {
			ts->setActive(1);
		}
	}

}

CTSE1::~CTSE1() {
	// TODO Auto-generated destructor stub
}

