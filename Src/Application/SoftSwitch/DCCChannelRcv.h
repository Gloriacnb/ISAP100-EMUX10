/*
 * DCCChannelRcv.h
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#ifndef DCCCHANNELRCV_H_
#define DCCCHANNELRCV_H_

#include <map>
#include "EZ_types.h"

class SwitchPortInner;
class DCCChannelRcv {
public:
	DCCChannelRcv(uint32 id);
	virtual ~DCCChannelRcv();

	static DCCChannelRcv* getRcvDccByUID(uint32 uid) {
		std::map<uint32, DCCChannelRcv*>::iterator it = DccRcvMap.find(uid);
		if( it != DccRcvMap.end() ) {
			return it->second;
		}
		return 0;
	};

	void setInnerPort(SwitchPortInner* p) {
		port = p;
	};

	SwitchPortInner* getInnerPort(void) {
		return port;
	};

	static DCCChannelRcv* getFirstRcvDcc(void) {
		std::map<uint32, DCCChannelRcv*>::iterator it = DccRcvMap.begin();
		if( it != DccRcvMap.end() ) {
			return it->second;
		}
		return 0;
	};
	static DCCChannelRcv* getNextRcvDcc(uint32 uid) {
		std::map<uint32, DCCChannelRcv*>::iterator it = DccRcvMap.find(uid);
		if( it != DccRcvMap.end() ) {
			++it;
			if( it != DccRcvMap.end() ) {
				return it->second;
			}
		}
		return 0;
	}

	uint32 getUID(void) {
		return uid;
	};

	uint32 getUpStreamPortUid(void) {
		return upstreamUid;
	};

	uint8* getUpStreamIP(void) {
		return upstreamIP;
	};

	uint8* getUpStreamIpMask(void) {
		return upstreamIpMask;
	};

	void setUpStreamPortUid(uint32 id) {
		upstreamUid = id;
	};

	void setUpStreamIP(uint8* ip) {
		for( int i = 0; i < 4; i++ ) {
			upstreamIP[i] = ip[i];
		}
	};

	void setUpStreamIpMask(uint8* mask) {
		for( int i = 0; i < 4; i++ ) {
			upstreamIpMask[i] = mask[i];
		}
	};

    void resetAgingCounter(void) {
        topoAgingCounter = 300;
    };
    bool AgingTopo(void) {
        if(topoAgingCounter == 0) {
            return false;
        }
        --topoAgingCounter;
        return topoAgingCounter == 0;
    };
private:
	uint32 uid;
	static std::map<uint32, DCCChannelRcv*> DccRcvMap;
	SwitchPortInner* port;

	uint32 upstreamUid;
	uint8 upstreamIP[4];
	uint8 upstreamIpMask[4];
    uint16 topoAgingCounter;
};

#endif /* DCCCHANNELRCV_H_ */
