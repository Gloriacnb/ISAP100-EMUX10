/*
 * SwitchPortStd.h
 *
 *  Created on: 2013-6-26
 *      Author: Administrator
 */

#ifndef SWITCHPORTSTD_H_
#define SWITCHPORTSTD_H_

#include "SwitchPort.h"

class SwitchPortStd : public SwitchPort {
public:
	SwitchPortStd(uint8 sn);
	virtual ~SwitchPortStd();

	virtual PriPacket* makePacket(LAYER2FRAME* f);	//派生类实现私有二层包的生成
	virtual int outputPacket(PriPacket& pkg) = 0;
};

#endif /* SWITCHPORTSTD_H_ */
