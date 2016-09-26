/*
 * UpE1DCNChannelSnd.h
 *
 *  Created on: 2016Äê1ÔÂ8ÈÕ
 *      Author: Administrator
 */

#ifndef UPE1DCNCHANNELSND_H_
#define UPE1DCNCHANNELSND_H_

#include "DCCChannelSnd.h"
class CUpE1Port;
class UpE1DCNChannelSnd: public DCCChannelSnd {
public:
	UpE1DCNChannelSnd(uint32 uid, CUpE1Port* p);
	virtual ~UpE1DCNChannelSnd();

	virtual void sendData(uint8* d, uint32 len);
    virtual uint32 getPortUID(void);
private:
	CUpE1Port* port;
};

#endif /* UPE1DCNCHANNELSND_H_ */
