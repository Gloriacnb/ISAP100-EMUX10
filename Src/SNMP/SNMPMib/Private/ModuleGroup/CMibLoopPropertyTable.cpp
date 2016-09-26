/*
 * CMibLoopPropertyTable.cpp
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#include "CMibLoopPropertyTable.h"
#include "CCommonDefine.h"
#include "CLoopModule.h"

column_info_T CMibLoopPropertyTable::colInfo[loop_col_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
};


CMibLoopPropertyTable::CMibLoopPropertyTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibLoopPropertyTable::~CMibLoopPropertyTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibLoopPropertyTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibLoopPropertyTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case loop_index:
		return new CMibLoopPropertyCol_index(sn, oid, oidLen, this);
	case loop_type:
		return new CMibLoopPropertyCol_type(sn, oid, oidLen, this);
	case loop_start_time:
		return new CMibLoopPropertyCol_start(sn, oid, oidLen, this);
	case loop_end_time:
		return new CMibLoopPropertyCol_end(sn, oid, oidLen, this);
	case loop_clear:
		return new CMibLoopPropertyCol_clear(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibLoopPropertyTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CLoopModule::instance().getFirstLoopPortUID();
	if( index->index[1] != 0 )
		return 1;
	return -1;
}

int CMibLoopPropertyTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CLoopModule::instance().getNextLoopPortUID(index->index[1]);
	if( index->index[1] != 0 )
		return 1;
	return -1;
}


int CMibLoopPropertyCol_index::CallbackGet(const index_info_T& index) {
	return index.index[1];
}

int CMibLoopPropertyCol_type::CallbackGet(const index_info_T& index) {
	CLoopRecord* lp = CLoopModule::instance().getLoopRecord(index.index[1]);
	if( lp )
		return lp->getLoopType();
	return -1;
}

int CMibLoopPropertyCol_start::CallbackGet(const index_info_T& index) {
	CLoopRecord* lp = CLoopModule::instance().getLoopRecord(index.index[1]);
	if( lp )
		return lp->getStartTime();
	return -1;
}
int CMibLoopPropertyCol_end::CallbackGet(const index_info_T& index) {
	CLoopRecord* lp = CLoopModule::instance().getLoopRecord(index.index[1]);
	if( lp )
		return lp->getEndTime();
	return -1;
}

int CMibLoopPropertyCol_clear::callbackSet( const index_info_T& index, uint32 mapid) {
	return  CLoopModule::instance().deleteLoopRecord(index.index[1]);
}
