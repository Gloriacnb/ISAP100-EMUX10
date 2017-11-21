/*
 * CEMUX10Factory.cpp
 *
 *  Created on: 2013-8-14
 *      Author: Administrator
 */

#include "CEMUX10Factory.h"
#include "CBaseSlot.h"
#include "CIsapSlot.h"
#include "CPowerSlot.h"
#include <string>
#include <sstream>
#include "CExtCard8VFG.h"
#include "CExtCard8VFA.h"
#include "CPowerCard.h"
#include "CExtCard8Data.h"

#include "ChipGluLogic.h"
#include "SlotLogicLX9.h"
#include "UID.h"
//#include "CUpE1Port.h"
#include "SysError.h"

static const uint8 slotMap[] = {
		normal_slot, normal_slot, normal_slot, normal_slot,
		power_slot, power_slot };


CEMUX10Factory::CEMUX10Factory() {
	// TODO Auto-generated constructor stub

}

CEMUX10Factory::~CEMUX10Factory() {
	// TODO Auto-generated destructor stub
}

CBaseCard* CEMUX10Factory::make(int TypeID, CBaseSlot* slot) {

	if( slot ) {
		switch( TypeID ) {
			case const8VFCardTypeID: {
				std::ostringstream s;
				s << "8VF";
				std::string name = s.str();
				CExtCard8VF* card = new CExtCard8VFA((uint8)slot->GetSn(), name);
				return card;
			}
			case constPowerCardTypeID: {
				std::ostringstream s;
				s << "POWER";
				std::string name = s.str();
				CPowerCard* card = new CPowerCard((uint8)slot->GetSn(), name);
				return card;
			}
			case const8DTCardTypeID: {
				std::ostringstream s;
				s << "8DATA";
				std::string name = s.str();
				CExtCard8Data* card = new CExtCard8Data((uint8)slot->GetSn(), name);
				return card;
			}
			case const8VFGCardTypeID: {
				std::ostringstream s;
				s << "8VFG";
				std::string name = s.str();
				CExtCard8VFG* card = new CExtCard8VFG((uint8)slot->GetSn(), name);
				return card;
			}
		}
	}
	return (CBaseCard*)0;
}

int CEMUX10Factory::destroy(CBaseCard* card) {
	if( card == 0 ) {
		return -1;
	}

	int TypeID = card->GetCartTypeID();
	if (TypeID == const8VFCardTypeID) {
		delete (CExtCard8VFA*)card;
		return TypeID;
	}
	else if(TypeID == const8VFGCardTypeID ) {
		delete (CExtCard8VFG*)card;
	}
	else if(TypeID == const8DTCardTypeID ) {
		delete (CExtCard8Data*)card;
	}
	else if(TypeID == constPowerCardTypeID) {
		delete (CPowerCard*)card;
	}
	return -1;
}

CBaseSlot* CEMUX10Factory::makeSlot(int sn) {
	if( sn >= sizeof(slotMap) ) {
		return 0;
	}
	int type = slotMap[sn];
	switch( type ) {
	case normal_slot:
		return new CIsapSlot(sn, this);
	case power_slot:
		return new CPowerSlot(sn, this);
	}
	return 0;
}

void CEMUX10Factory::initChips(void) {
	/* Init chip 1 */
	if( glulogic_open(&GluConfig) != TRUE ) {
		  throw SysError("!!!Glulogic chip init failed!");
	}

	/* Init chip 2 */
	SlotLogic_LX9 lx9;
	lx9.OpenSlotLogic();

//	ST_E1 info;
//	info.slot = 100;
//	for (int i = 0; i < 2; ++i) {
//		info.E1 = i;
//		uint32 uid = UID::makeUID(&info);
//		new CUpE1Port(uid, i+2);
//	}
}

