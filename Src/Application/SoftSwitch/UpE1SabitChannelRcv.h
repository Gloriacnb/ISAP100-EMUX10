/*
 * UpE1SabitChannelRcv.h
 *
 *  Created on: 2016��1��8��
 *      Author: Administrator
 */

#ifndef UPE1SABITCHANNELRCV_H_
#define UPE1SABITCHANNELRCV_H_

#include "DCCChannelRcv.h"

class UpE1SabitChannelRcv: public DCCChannelRcv {
public:
	UpE1SabitChannelRcv(uint32 uid);
	virtual ~UpE1SabitChannelRcv();
};

#endif /* UPE1SABITCHANNELRCV_H_ */
