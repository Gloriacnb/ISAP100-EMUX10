/*
 * GroupDeviceList.cpp
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#include "GroupDeviceList.h"
#include "TableDevice.h"

table_info_T GroupDeviceList::tableInfo[table_dev_size] = {
		{2, device_column_size, 1},//sn, col number, index number
};

GroupDeviceList::~GroupDeviceList() {
	// TODO Auto-generated destructor stub
}


GroupDeviceList::GroupDeviceList(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	creatTables(tableInfo, table_dev_size);
}

CMibEntry* GroupDeviceList::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_dev:
		return new TableDevice(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
