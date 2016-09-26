/*
 * CTSE1.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CTSE1_H_
#define CTSE1_H_

#include "EZ_types.h"
class CE1Channel;
class CTSE1 {
public:
	CTSE1(uint8 slot, uint8 Channelhid, uint8 tsE1Sn);
	virtual ~CTSE1();

private:
	CE1Channel* LinkChannel;
};

#endif /* CTSE1_H_ */
