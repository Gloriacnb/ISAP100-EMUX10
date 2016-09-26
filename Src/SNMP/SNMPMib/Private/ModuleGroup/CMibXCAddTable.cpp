/*
 * CMibXCAddTable.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibXCAddTable.h"

#include "DeviceLocal.h"
#include "CCommonDefine.h"
//#include "CE1CrossConnectionManager.h"
#include "CTSCrossConnectionManager.h"

column_info_T CMibXCAddTable::colInfo[xc_add_size] = {
		{1, Mib_write_only, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibXCAddTable::CMibXCAddTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibXCAddTable::~CMibXCAddTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibXCAddTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibXCAddTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case xc_add:
		return new CMibXCCol_add(sn, oid, oidLen, this);
	case xc_count:
		return new CMibXCCol_count(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibXCAddTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	return 1;
}

int CMibXCAddTable::getNextIndex(index_info_T* index) {
	return -1;
}

int CMibXCCol_add::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
	if( buf == 0 || len < 8 ) {
		return -1;
	}
	uint32 uiWestNode = (buf[0] << 24 ) | (buf[1] << 16 ) | (buf[2] << 8 ) | buf[3];
	uint32 uiEastNode = (buf[4] << 24 ) | (buf[5] << 16 ) | (buf[6] << 8 ) | buf[7];

	return DeviceLocal::instance().GetXcManager().CreatConnection(uiWestNode, uiEastNode);
}

int CMibXCCol_count::CallbackGet(const index_info_T& index) {
	return 0;
}
