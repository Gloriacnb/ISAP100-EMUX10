/*
 * UpE1DCNChannelRcv.h
 *
 *  Created on: 2016��1��8��
 *      Author: Administrator
 */

#ifndef UPE1DCNCHANNELRCV_H_
#define UPE1DCNCHANNELRCV_H_

#include "DCCChannelRcv.h"

class UpE1DCNChannelRcv: public DCCChannelRcv {
public:
	UpE1DCNChannelRcv(uint32 uid);
	virtual ~UpE1DCNChannelRcv();
};

#endif /* UPE1DCNCHANNELRCV_H_ */
