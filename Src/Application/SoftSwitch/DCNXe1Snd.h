/*
 * DCNXe1Snd.h
 *
 *  Created on: 2015Äê12ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef DCNXE1SND_H_
#define DCNXE1SND_H_

#include "DCCChannelSnd.h"

class DCNXe1Snd : public DCCChannelSnd {
public:
	DCNXe1Snd(uint32 uid, uint32 portUID);
	virtual ~DCNXe1Snd();

	virtual void sendData(uint8* d, uint32 len);
    virtual uint32 getPortUID(void) {
        return puid;
    };
private:
	uint32 puid;
};

#endif /* DCNXE1SND_H_ */
