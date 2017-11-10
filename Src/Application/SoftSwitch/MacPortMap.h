/*
 * MacPortMap.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#ifndef MACPORTMAP_H_
#define MACPORTMAP_H_

#include <map>
#include <string.h>
#include "EZ_types.h"

class PriPacket;
class MacPortMap {
public:
	const static uint16 LiveSecs = 3000;

	MacPortMap();
	virtual ~MacPortMap();

	void learnAddress(PriPacket&);

	int findOutputPort(PriPacket&);

	void aging(void);

private:
	class MACAddr {
	public:
		MACAddr() {};
		MACAddr(uint8* d) {
			memcpy( mac, d, 6);
		};
//		MACAddr(MACAddr& m) {
//			memcpy( mac, m.mac, 6);
//		};
		~MACAddr() {};
	    uint8 mac[6];

	    bool operator < (const MACAddr& m) const {
	    	for( int i = 0; i < 6; i++ ) {
	    		if( mac[i] != m.mac[i] ) {
	    			return mac[i] < m.mac[i];
	    		}
	    	}
	    	return false;
	    };

	};

	class PortRecord {
	public:
		PortRecord();
		~PortRecord() {};
//		PortRecord(PortRecord& t) {
//			portSn = t.portSn;
//			AgingCounter = t.AgingCounter;
//		};
		PortRecord(uint8 port) {
			portSn = port;
			AgingCounter = MacPortMap::LiveSecs;
		};

		uint8 portSn;
		uint16 AgingCounter;
		PortRecord& operator = ( const PortRecord& t) {
			portSn = t.portSn;
			AgingCounter = t.AgingCounter;
			return *this;
		};
	};

	std::map<MACAddr, PortRecord> macPortTable;

};

#endif /* MACPORTMAP_H_ */
