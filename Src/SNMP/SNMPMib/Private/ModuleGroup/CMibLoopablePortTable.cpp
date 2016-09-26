/*
 * CMibLoopablePortTable.cpp
 *
 *  Created on: 2013-6-3
 *      Author: Administrator
 */

#include "CMibLoopablePortTable.h"
#include "RealPortBase.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibLoopablePortTable::colInfo[loopable_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
};


CMibLoopablePortTable::CMibLoopablePortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibLoopablePortTable::~CMibLoopablePortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibLoopablePortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibLoopablePortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case loopable_port_index:
		return new CMibLoopablePort_index(sn, oid, oidLen, this);
	case loopable_port_name:
		return new CMibLoopablePort_name(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibLoopablePortTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	RealPortBase* rp = RealPortBase::getFirstInstance();
	if( rp ) {
		index->index[1] = rp->getUID();
		return 1;
	}
	return -1;
}

int CMibLoopablePortTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	RealPortBase* rp = RealPortBase::getNextInstance(index->index[1]);
	if( rp ) {
		index->index[1] = rp->getUID();
		return 1;
	}
	return -1;
}



int CMibLoopablePort_index::CallbackGet(const index_info_T& index) {
	return index.index[1];
}

int CMibLoopablePort_name::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	RealPortBase* rp = RealPortBase::getPortInstance(index.index[1]);
	if( rp ) {
		std::string& name = rp->getName();
		*len = name.size();
		strcpy((char*)buf, name.c_str());
		return 1;
	}
	return 0;

}
