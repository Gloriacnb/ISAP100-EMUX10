/*
 * CPowerSlot.cpp
 *
 *  Created on: 2013-5-23
 *      Author: Administrator
 */

#include "CPowerSlot.h"
#include "Mid_power_voltage.h"

CPowerSlot::CPowerSlot(int sn, CInterfaceCardCreatFactory* f) : CBaseSlot(sn, f) {
	itsSlotNumber = sn;
	if( sn == 4 ) {
		powerSlotInit();
	}

}

CPowerSlot::~CPowerSlot() {
	// TODO Auto-generated destructor stub
}

int CPowerSlot::GetCardTypeIDFromHardware() {
	if( PowerCardExist(GetSn()) )
		return 0x80;
	return -1;
}
