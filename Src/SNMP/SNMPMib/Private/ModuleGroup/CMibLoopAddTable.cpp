/*
 * CMibLoopAddTable.cpp
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#include "CMibLoopAddTable.h"
#include "UID.h"
#include "CCommonDefine.h"
#include "CLoopModule.h"

column_info_T CMibLoopAddTable::colInfo[loop_add_size] = {
		{1, Mib_write_only, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibLoopAddTable::CMibLoopAddTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibLoopAddTable::~CMibLoopAddTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibLoopAddTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibLoopAddTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case loop_add:
		return new CMibLoopAddColumn_add(sn, oid, oidLen, this);
	case loop_count:
		return new CMibLoopCol_count(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibLoopAddTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	return 1;
}

int CMibLoopAddTable::getNextIndex(index_info_T* index) {
	return -1;
}



int CMibLoopAddColumn_add::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
	if( buf == 0 || len < 9 ) {
		return -1;
	}

	uint8 loopType = buf[0];
	uint32 portIndex = 	( buf[1] << 24 ) |
						( buf[2] << 16 ) |
						( buf[3] << 8 ) |
						( buf[4] << 0 ) ;

	uint32 loopTime =  	( buf[5] << 24 ) |
						( buf[6] << 16 ) |
						( buf[7] << 8 ) |
						( buf[8] << 0 ) ;
	
	return CLoopModule::instance().addLoopRecord(portIndex, loopType, loopTime);

}


int CMibLoopCol_count::CallbackGet(const index_info_T& index) {
	return CLoopModule::instance().getLoopRecordNumber();
}

