/*
 * SwitchPort.h
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 */

#ifndef SWITCHPORT_H_
#define SWITCHPORT_H_

#include <map>
#include "EZ_types.h"
//#include <Net_Config.h>
#include "EthMemory.h"

class PriPacket;
class SwitchPort {
	static std::map<uint8, SwitchPort*> portGroup;
	SwitchPort();
public:
	SwitchPort(uint8 portSn);
	virtual ~SwitchPort();

	/* 交换端口有包收到 */
	int inputPacket(LAYER2FRAME* f);

	virtual PriPacket* makePacket(LAYER2FRAME* f) = 0;	//派生类实现私有二层包的生成
	virtual int outputPacket(PriPacket& pkg) = 0;

	/* group option */
	static SwitchPort* getSwitchPort(uint8 sn) {
		std::map<uint8, SwitchPort*>::iterator it = portGroup.find(sn);
		if( it != portGroup.end() ) {
			return it->second;
		}
		return 0;
	};

	static void broadcastThePacket( PriPacket& pkt );

	uint8 getPortSn(void) {
		return sn;
	};
private:
	uint8 sn;
};

#endif /* SWITCHPORT_H_ */
