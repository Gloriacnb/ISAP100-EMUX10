/*
 * CMibVC12.h
 *
 *  Created on: 2013-3-3
 *      Author: Administrator
 */

#ifndef CMIBVC12_H_
#define CMIBVC12_H_

#include "CMibEntry.h"

class CMibVC12  : public CMibEntry{
public:
	CMibVC12();
	virtual ~CMibVC12();

	virtual uint32 InitialGroup(void);
};



#endif /* CMIBVC12_H_ */
