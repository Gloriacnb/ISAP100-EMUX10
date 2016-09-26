/*
 * DCCSdhRcv.h
 *
 *  Created on: 2013-6-28
 *      Author: Administrator
 */

#ifndef DCCSDHRCV_H_
#define DCCSDHRCV_H_

#include "DCCChannelRcv.h"

class DCCSdhRcv : public DCCChannelRcv {
public:
	DCCSdhRcv( uint32 id );
	virtual ~DCCSdhRcv();
};

#endif /* DCCSDHRCV_H_ */
