/*
 * DCNXe1Rcv.h
 *
 *  Created on: 2015��12��25��
 *      Author: Administrator
 */

#ifndef DCNXE1RCV_H_
#define DCNXE1RCV_H_

#include "DCCChannelRcv.h"

class DCNXe1Rcv: public DCCChannelRcv {
public:
	DCNXe1Rcv(uint32 uid);
	virtual ~DCNXe1Rcv();
};

#endif /* DCNXE1RCV_H_ */
