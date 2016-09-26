/*
 * GroupDeviceList.h
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#ifndef GROUPDEVICELIST_H_
#define GROUPDEVICELIST_H_

#include "CMibGroup.h"

enum {
	table_dev,
	table_dev_size
};

class GroupDeviceList : public CMibGroup {
	GroupDeviceList();
public:
	GroupDeviceList(uint32* oid, uint8 oidlen);
	virtual ~GroupDeviceList();

//	virtual table_info_T* getTableInfo(int sn);
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_dev_size];
};


#endif /* GROUPDEVICELIST_H_ */
