/*
 * SwitchPortInner.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#ifndef SWITCHPORTINNER_H_
#define SWITCHPORTINNER_H_

#include "SwitchPort.h"
#include <map>

class DCCChannelRcv;
class DCCChannelSnd;
class SwitchPortInner : public SwitchPort {
	static uint8 pSnBase;
	SwitchPortInner();
public:
	SwitchPortInner(uint8 sn);
	virtual ~SwitchPortInner();

	virtual PriPacket* makePacket(LAYER2FRAME* f);	//派生类实现私有二层包的生成
	virtual int outputPacket(PriPacket& pkg);

	void addDcc(DCCChannelRcv*);
	void addDcc(DCCChannelSnd*);

	void removeDcc(DCCChannelRcv*);
	void removeDcc(DCCChannelSnd*);

	DCCChannelRcv* currentRcvCh;

private:
	std::map<uint32, DCCChannelRcv*> dccRcv;
	std::map<uint32, DCCChannelSnd*> dccSnd;
};

#endif /* SWITCHPORTINNER_H_ */
