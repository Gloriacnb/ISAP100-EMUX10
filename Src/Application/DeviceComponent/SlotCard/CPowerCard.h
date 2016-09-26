/*
 * CPowerCard.h
 *
 *  Created on: 2013-5-24
 *      Author: Administrator
 */

#ifndef CPOWERCARD_H_
#define CPOWERCARD_H_

#include "CBaseCard.h"
#include <string>

#define TYPE_power 0x80

class CPowerCard : public CBaseCard {
	CPowerCard();
	uint8 itsSlot;
public:
	CPowerCard(uint8 slot, std::string& name);
	virtual ~CPowerCard();

	virtual int GetCartTypeID();
	virtual int getNextVersionIndex(uint8 sn);
	virtual int getVersion(uint8 id, STVersion&);

};

#endif /* CPOWERCARD_H_ */
