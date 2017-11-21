/*
 * CISAP100Factory.cpp
 *
 *  Created on: 2013-2-22
 *      Author: Administrator
 */

#include "CISAP100Factory.h"
#include "CBaseSlot.h"
#include "CIsapSlot.h"
#include "CPowerSlot.h"
#include "CExtCard4E1.h"
#include <string>
#include <sstream>
#include "CExtCard8VFG.h"
#include "CExtCard8VFA.h"
#include "CPowerCard.h"
#include "CExtCard8Data.h"
#include "CExtCard2BD.h"

#include "ChipGluLogic.h"
#include "SlotLogicLX9.h"
//#include "ChipSlotLogic.h"
#include "ChipOptLogic.h"
#include "Mid_RC6400App.h"
#include "Mid_RC7880A1App.h"
#include "SysError.h"

static const uint8 slotMap[] = {
		slot_normal, slot_normal, slot_normal, slot_normal,
		slot_power, slot_power };


CISAP100Factory::CISAP100Factory() {
	// TODO Auto-generated constructor stub

}

CISAP100Factory::~CISAP100Factory() {
	// TODO Auto-generated destructor stub
}

CBaseCard* CISAP100Factory::make(int TypeID, CBaseSlot* slot) {

	if( slot ) {
		switch( TypeID ) {
			case const4E1CardTypeID: {
				std::ostringstream s;
				s << "4E1";
				std::string name = s.str();
				CExtCard4E1* card = new CExtCard4E1((uint8)slot->GetSn(), name);
				return card;
			}
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
			case const2BDCardTypeID: {
				std::ostringstream s;
				s << "2B+D";
				std::string name = s.str();
				CExtCard2BD* card = new CExtCard2BD((uint8)slot->GetSn(), name);
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

int CISAP100Factory::destroy(CBaseCard* card) {
	if( card == 0 ) {
		return -1;
	}

	int TypeID = card->GetCartTypeID();
	if( TypeID == const4E1CardTypeID ) {
		delete (CExtCard4E1*)card;
		return TypeID;
	}
	else if (TypeID == const8VFCardTypeID) {
		delete (CExtCard8VF*)card;
		return TypeID;
	}
	else if(TypeID == const8DTCardTypeID ) {
		delete (CExtCard8Data*)card;
	}
	else if(TypeID == constPowerCardTypeID) {
		delete (CPowerCard*)card;
	}
	else if( TypeID == const2BDCardTypeID) {
		delete (CExtCard2BD*)card;
	}
	else if(TypeID == const8VFGCardTypeID ) {
		delete (CExtCard8VFG*)card;
	}
	return -1;
}

CBaseSlot* CISAP100Factory::makeSlot(int sn) {
	if( sn >= sizeof(slotMap) ) {
		return 0;
	}
	int type = slotMap[sn];
	switch( type ) {
	case slot_normal:
		return new CIsapSlot(sn, this);
	case slot_power:
		return new CPowerSlot(sn, this);
	}
	return 0;
}

/*
 * chip 1 XO2640
 * chip 2 LX9
 * chip 3 1200
 * chip 4 RC7880A1
 * chip 5 RC6400
 */
void CISAP100Factory::initChips(void) {
	/* Init chip 1 */
	if( glulogic_open(&GluConfig) != TRUE ) {
		throw SysError("!!!Glulogic chip open failed!");
	}

	/* Init chip 2 */
	SlotLogic_LX9 lx9;
	lx9.OpenSlotLogic();

	/* Init chip 3 */
	if( optlogic_open(OptLogic_REGPTR) != TRUE ) {
	  throw SysError("!!!Optlogic chip init failed!");
	}

	/* Init chip 4 */
	if( open_rc7880a1(1) != TRUE ) {
		  throw SysError("!!!RC7880 chip init failed!");
	}

	/* Init chip 5 */
	if( open_rc6400() != TRUE ) {
		  throw SysError("!!!RC6400 chip init failed!");
	}

}
