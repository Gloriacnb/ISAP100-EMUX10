/*
 * CIsapSlot.h
 *
 *  Created on: 2013-2-23
 *      Author: Administrator
 */

#ifndef CISAPSLOT_H_
#define CISAPSLOT_H_

#include "CBaseSlot.h"
#include "CMSSave.h"

class CInterfaceCardCreatFactory;
class CE1Channel;
class CSTBus;

class CIsapSlot : public CBaseSlot {
	static const int STBusBaseSn = 8;
//	static const int IsapSlotBaseSn = 1;
	CE1Channel* fixE1[4];
	CSTBus* fixStbus;
	CIsapSlot();
public:
	CIsapSlot(int sn, CInterfaceCardCreatFactory* f);
	virtual ~CIsapSlot();
	virtual int GetCardTypeIDFromHardware();

};

#endif /* CISAPSLOT_H_ */
