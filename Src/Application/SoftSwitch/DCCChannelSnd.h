/*
 * DCCChannelSnd.h
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#ifndef DCCCHANNELSND_H_
#define DCCCHANNELSND_H_

#include "EZ_types.h"
#include <map>

class DCCChannelSnd {
	DCCChannelSnd();
public:
	DCCChannelSnd(uint32 id);
	virtual ~DCCChannelSnd();

	virtual void sendData(uint8* d, uint32 len) = 0;
	virtual uint32 getPortUID(void) = 0;

	uint32 getUID(void) {
		return uid;
	};

	static DCCChannelSnd* getSendDccByUID(uint32 uid) {
		std::map<uint32, DCCChannelSnd*>::iterator it = DccSendMap.find(uid);
		if( it != DccSendMap.end() ) {
			return it->second;
		}
		return 0;
	};

	static void broadcastPacket(uint8* d, uint32 len) {
		std::map<uint32, DCCChannelSnd*>::iterator it = DccSendMap.begin();
		while( it != DccSendMap.end() ) {
			it->second->sendData(d, len);
			it++;
		}
	};

	static DCCChannelSnd* getFirstSndDcc(void) {
		std::map<uint32, DCCChannelSnd*>::iterator it = DccSendMap.begin();
		if( it != DccSendMap.end() ) {
			return it->second;
		}
		return 0;
	};
	static DCCChannelSnd* getNextSndDcc(uint32 uid) {
		std::map<uint32, DCCChannelSnd*>::iterator it = DccSendMap.find(uid);
		if( it != DccSendMap.end() ) {
			++it;
			if( it != DccSendMap.end() ) {
				return it->second;
			}
		}
		return 0;
	}

private:
	uint32 uid;
	static std::map<uint32, DCCChannelSnd*> DccSendMap;
};

#endif /* DCCCHANNELSND_H_ */
