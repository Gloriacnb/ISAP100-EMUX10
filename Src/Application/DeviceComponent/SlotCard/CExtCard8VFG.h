/*
 * CExtCard8VFG.h
 *
 *  Created on: 2017年11月17日
 *      Author: Administrator
 */

#ifndef SRC_APPLICATION_DEVICECOMPONENT_SLOTCARD_CEXTCARD8VFG_H_
#define SRC_APPLICATION_DEVICECOMPONENT_SLOTCARD_CEXTCARD8VFG_H_

#include "CExtCard8VF.h"

class CExtCard8VFG: public CExtCard8VF {
	static const int itsTypeID = TYPE_8VFG;
public:
	CExtCard8VFG();
	virtual ~CExtCard8VFG();
	CExtCard8VFG(uint8 slot, std::string& name);

	virtual int GetCartTypeID();

};

#endif /* SRC_APPLICATION_DEVICECOMPONENT_SLOTCARD_CEXTCARD8VFG_H_ */
