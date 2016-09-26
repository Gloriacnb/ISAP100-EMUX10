/*
 * CMibMappingAddTable.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibMappingAddTable.h"
#include "DeviceLocal.h"
#include "CCommonDefine.h"
#include "CVC12CrossConnectionMagager.h"

column_info_T CMibMappingAddTable::colInfo[mapping_add_size] = {
		{1, Mib_write_only, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibMappingAddTable::CMibMappingAddTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibMappingAddTable::~CMibMappingAddTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibMappingAddTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibMappingAddTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case mapping_add:
		return new CMibMappingCol_add(sn, oid, oidLen, this);
	case mapping_count:
		return new CMibMappingCol_count(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibMappingAddTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	return 1;
}

int CMibMappingAddTable::getNextIndex(index_info_T* index) {
	return -1;
}

int CMibMappingCol_add::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
	if( buf == 0 || len < 8 ) {
		return -1;
	}
	uint32 uiWestNode = (buf[0] << 24 ) | (buf[1] << 16 ) | (buf[2] << 8 ) | buf[3];
	uint32 uiEastNode = (buf[4] << 24 ) | (buf[5] << 16 ) | (buf[6] << 8 ) | buf[7];

	return DeviceLocal::instance().GetMappingManager().CreatConnection(uiWestNode, uiEastNode);
}

int CMibMappingCol_count::CallbackGet(const index_info_T& index) {
	return DeviceLocal::instance().GetMappingManager().GetCurrentMappingNumber();
}


