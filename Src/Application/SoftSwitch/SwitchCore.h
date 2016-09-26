/*
 * SwitchCore.h
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 */

#ifndef SWITCHCORE_H_
#define SWITCHCORE_H_

#include <map>
#include "CFinishedPacket.h"
#include "MacPortMap.h"

class SwitchPort;
class PriPacket;
class SwitchCore {
	SwitchCore();
	SwitchCore(const SwitchCore&);
	SwitchCore& operator= (SwitchCore&);
	virtual ~SwitchCore();

	static SwitchCore sw;
public:
	static SwitchCore& instance(void) {
		return sw;
	};

	int processPacket(PriPacket& pkt);

	CFinishedPacket& getFinishedPkt(void) {
		return finishedPkt;
	};

	MacPortMap& getMacPortTable(void) {
		return macPortTable;
	};
private:
	std::map<int, SwitchPort*> portMap;
	CFinishedPacket finishedPkt;
	MacPortMap macPortTable;

};

#endif /* SWITCHCORE_H_ */
