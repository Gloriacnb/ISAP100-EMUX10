/*
 * CMibGroup.h
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#ifndef CMIBGROUP_H_
#define CMIBGROUP_H_

#include "CMibEntry.h"

#include "Mib_define.h"

class CMibGroup : public CMibEntry {
	CMibGroup() {};
public:
	CMibGroup(uint32* oid, uint8 oidLen);
	virtual ~CMibGroup();

//	virtual table_info_T* getTableInfo(int sn) = 0;
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen) = 0;

	void creatTables(table_info_T*, uint32);
};

#endif /* CMIBGROUP_H_ */
