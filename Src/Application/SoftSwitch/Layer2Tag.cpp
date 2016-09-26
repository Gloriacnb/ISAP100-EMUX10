/*
 * Layer2Tag.cpp
 *
 *  Created on: 2013-6-27
 *      Author: Administrator
 */

#include "Layer2Tag.h"
#include <string.h>

Layer2Tag::Layer2Tag() {
	// TODO Auto-generated constructor stub
	sn = 0;
}

Layer2Tag::~Layer2Tag() {
	// TODO Auto-generated destructor stub
}

bool Layer2Tag::operator <(const Layer2Tag& t) const {
	if (sn != t.sn) {
		return sn < t.sn;
	}

	int b = memcmp(decMAC, t.decMAC, 6);
	if (b != 0) {
		return (b < 0) ? true : false;
	}

	b = memcmp(srcMAC, t.srcMAC, 6);
	if (b != 0) {
		return (b < 0) ? true : false;
	}

	return false;
}

Layer2Tag& Layer2Tag::operator =(const Layer2Tag& t) {
	sn = t.sn;
	for (int i = 0; i < 6; i++) {
		srcMAC[i] = t.srcMAC[i];
		decMAC[i] = t.decMAC[i];
	}
	return *this;
}
;
