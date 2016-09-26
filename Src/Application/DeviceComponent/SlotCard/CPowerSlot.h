/*
 * CPowerSlot.h
 *
 *  Created on: 2013-5-23
 *      Author: Administrator
 */

#ifndef CPOWERSLOT_H_
#define CPOWERSLOT_H_


#include "CBaseSlot.h"

class CInterfaceCardCreatFactory;

class CPowerSlot : public CBaseSlot {
public:
	CPowerSlot(int sn, CInterfaceCardCreatFactory* f);
	virtual ~CPowerSlot();
	virtual int GetCardTypeIDFromHardware();
private:
	int itsSlotNumber;
};

#endif /* CPOWERSLOT_H_ */
