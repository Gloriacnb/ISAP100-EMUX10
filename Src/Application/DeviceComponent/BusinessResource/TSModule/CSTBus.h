/*
 * CSTBus.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CSTBUS_H_
#define CSTBUS_H_

#include "EZ_types.h"

class CSTBus {
	CSTBus();
public:
	CSTBus(uint8 slot, uint8 hid);
	virtual ~CSTBus();
private:
};

#endif /* CSTBUS_H_ */
