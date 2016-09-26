/*
 * UpE1SabitChannelSnd.h
 *
 *  Created on: 2016Äê1ÔÂ8ÈÕ
 *      Author: Administrator
 */

#ifndef UPE1SABITCHANNELSND_H_
#define UPE1SABITCHANNELSND_H_

#include "DCCChannelSnd.h"

class CUpE1Port;
class UpE1SabitChannelSnd: public DCCChannelSnd {
public:
	UpE1SabitChannelSnd(uint32 uid, CUpE1Port* p);
	virtual ~UpE1SabitChannelSnd();

	virtual void sendData(uint8* d, uint32 len);
    virtual uint32 getPortUID(void);
private:
	CUpE1Port* port;
};

#endif /* UPE1SABITCHANNELSND_H_ */
