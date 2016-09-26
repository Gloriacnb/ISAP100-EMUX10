/*
 * CMibNEStruct.h
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#ifndef CMIBNESTRUCT_H_
#define CMIBNESTRUCT_H_

#include "CMibEntry.h"
class CMibNEStruct : public CMibEntry {
public:
	CMibNEStruct();
	virtual ~CMibNEStruct();

	virtual uint32 InitialGroup(void);
};

#endif /* CMIBNESTRUCT_H_ */
