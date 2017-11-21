/*
 * CISAP100Factory.h
 *
 *  Created on: 2013-2-22
 *      Author: Administrator
 */

#ifndef CISAP100FACTORY_H_
#define CISAP100FACTORY_H_

#include "CInterfaceCardCreatFactory.h"
#include "CExtCard4E1_define.h"
#include "CExtCard8VF_define.h"
#include "CPowerCard.h"
#include "CExtCard2BD_define.h"

class CBaseCard;
class CBaseSlot;

enum {
	slot_normal, slot_power
};

class CISAP100Factory: public CInterfaceCardCreatFactory {
	static const uint8 const4E1CardTypeID = TYPE_4E1;
	static const uint8 const8VFCardTypeID = TYPE_8VF;
	static const uint8 const8DTCardTypeID = 0x52;
	static const uint8 constPowerCardTypeID = TYPE_power;
	static const uint8 const2BDCardTypeID = TYPE_2BD;
	static const uint8 const8VFGCardTypeID = TYPE_8VFG;

public:
	CISAP100Factory();
	virtual ~CISAP100Factory();
	virtual CBaseCard* make(int iTypeID, CBaseSlot*);
	virtual int destroy(CBaseCard*);

	virtual CBaseSlot* makeSlot(int sn);

	virtual void initChips(void);

};

#endif /* CISAP100FACTORY_H_ */
