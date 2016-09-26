/*
 * DCCSdhSnd.h
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#ifndef DCCSDHSND_H_
#define DCCSDHSND_H_

#include "DCCChannelSnd.h"


class DCCSdhSnd : public DCCChannelSnd {
public:
	DCCSdhSnd(uint32 uid, uint32 portUID);
	virtual ~DCCSdhSnd();

	virtual void sendData(uint8* d, uint32 len);
	virtual uint32 getPortUID(void) {
		return puid;
	};

private:
	uint32 puid;
};

#endif /* DCCSDHSND_H_ */
