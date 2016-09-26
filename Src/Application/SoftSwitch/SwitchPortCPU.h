/*
 * SwitchPortCPU.h
 *
 *  Created on: 2013-6-26
 *      Author: Administrator
 */

#ifndef SWITCHPORTCPU_H_
#define SWITCHPORTCPU_H_


#include "SwitchPortStd.h"

class PriPacket;
class SwitchPortCPU : public SwitchPortStd {

public:
	SwitchPortCPU();
	virtual ~SwitchPortCPU();

//	virtual PriPacket& makePacket(uint8* d, uint16 len);	//派生类实现私有二层包的生成
	virtual int outputPacket(PriPacket& pkg);
};

#endif /* SWITCHPORTCPU_H_ */
