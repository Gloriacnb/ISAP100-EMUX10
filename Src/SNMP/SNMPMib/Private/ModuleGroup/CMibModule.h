/*
 * CMibModule.h
 *
 *  Created on: 2013-3-1
 *      Author: Administrator
 */

#ifndef CMIBMODULE_H_
#define CMIBMODULE_H_

#include "CMibEntry.h"

class CMibModule: public CMibEntry {
public:
	CMibModule();
	virtual ~CMibModule();
	virtual uint32 InitialGroup(void);
};

#endif /* CMIBMODULE_H_ */
