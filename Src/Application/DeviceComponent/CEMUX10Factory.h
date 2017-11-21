/*
 * CEMUX10Factory.h
 *
 *  Created on: 2013-8-14
 *      Author: Administrator
 */

#ifndef CEMUX10FACTORY_H_
#define CEMUX10FACTORY_H_

#include "CInterfaceCardCreatFactory.h"
#include "CExtCard8VF_define.h"
#include "CExtCard8Data_define.h"
#include "CPowerCard.h"

class CBaseCard;
class CBaseSlot;

typedef enum {
	normal_slot,
	power_slot
}EMUX10_slot_type;

class CEMUX10Factory : public CInterfaceCardCreatFactory{
	static const uint8 const8VFCardTypeID = TYPE_8VF;
	static const uint8 const8DTCardTypeID = TYPE_8Data;
	static const uint8 constPowerCardTypeID = TYPE_power;
	static const uint8 const8VFGCardTypeID = TYPE_8VFG;

public:
	CEMUX10Factory();
	virtual ~CEMUX10Factory();
	virtual CBaseCard* make(int iTypeID, CBaseSlot*);
	virtual int destroy(CBaseCard*);

	virtual CBaseSlot* makeSlot(int sn);

	virtual void initChips(void);

};

#endif /* CEMUX10FACTORY_H_ */
