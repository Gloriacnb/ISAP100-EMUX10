/*
 * CExtCard8VFA.h
 *
 *  Created on: 2017年11月20日
 *      Author: Administrator
 */

#ifndef SRC_APPLICATION_DEVICECOMPONENT_SLOTCARD_CEXTCARD8VFA_H_
#define SRC_APPLICATION_DEVICECOMPONENT_SLOTCARD_CEXTCARD8VFA_H_

#include "CExtCard8VF.h"

class CExtCard8VFA : public CExtCard8VF {
	static const int itsTypeID = TYPE_8VF;
public:
	CExtCard8VFA();
	virtual ~CExtCard8VFA();
	CExtCard8VFA(uint8 slot, std::string& name);

	virtual int GetCartTypeID();
};

#endif /* SRC_APPLICATION_DEVICECOMPONENT_SLOTCARD_CEXTCARD8VFA_H_ */
