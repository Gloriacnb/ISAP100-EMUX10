/*
 * switchPortSNMP.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#ifndef SWITCHPORTSNMP_H_
#define SWITCHPORTSNMP_H_

#include "SwitchPortStd.h"

class switchPortSNMP : public SwitchPortStd {
public:
	switchPortSNMP();
	virtual ~switchPortSNMP();

//	virtual PriPacket& makePacket(uint8* d, uint16 len);	//派生类实现私有二层包的生成
	virtual int outputPacket(PriPacket& pkg);
};

#endif /* SWITCHPORTSNMP_H_ */
