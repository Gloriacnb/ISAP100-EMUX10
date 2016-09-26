/*
 * Layer2Tag.h
 *
 *  Created on: 2013-6-27
 *      Author: Administrator
 */

#ifndef LAYER2TAG_H_
#define LAYER2TAG_H_

#include "EZ_types.h"

class Layer2Tag {
public:
	Layer2Tag();
	virtual ~Layer2Tag();

	uint32 sn;
	uint8 srcMAC[6];
	uint8 decMAC[6];


    bool operator < (const Layer2Tag& t) const;

    Layer2Tag& operator = ( const Layer2Tag& t);
};

#endif /* LAYER2TAG_H_ */
