/*
 * CMibTSChannelTable.cpp
 *
 *  Created on: 2013-4-26
 *      Author: Administrator
 */

#include "CMibTSChannelTable.h"
#include "CCommonDefine.h"
#include "CTSChannel.h"
#include "UID.h"

column_info_T CMibTSChannelTable::colInfo[ts_Channel_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibTSChannelTable::CMibTSChannelTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibTSChannelTable::~CMibTSChannelTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibTSChannelTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibTSChannelTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
 	case ts_Channel_uid:
 		return new CMibTSChannelCol_uid(sn, oid, oidLen, this);
 	case ts_Channel_mapping:
 		return new CMibTSChannelCol_Mapping(sn, oid, oidLen, this);
 	case ts_Channel_status:
 		return new CMibTSChannelCol_Status(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibTSChannelTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CTSChannel::getFirstUid();
	if( uid != 0 ) {
		try {
			index->index[1] = UID::breakUID(uid).ts.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}
int CMibTSChannelTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CTSChannel::getNextUid(index->index[2]);
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).ts.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}


int CMibTSChannelCol_uid::CallbackGet(const index_info_T& index) {
	CTSChannel* ts = CTSChannel::getTSChannelByUid(index.index[2]);
	if( ts ) {
		return index.index[2];
	}
	return -1;
}


int CMibTSChannelCol_Mapping::CallbackGet(const index_info_T& index) {
	CTSChannel* ts = CTSChannel::getTSChannelByUid(index.index[2]);
	if( ts ) {
		return ts->getMapPartner();
	}
	return -1;
}

int CMibTSChannelCol_Status::CallbackGet(const index_info_T& index) {
	CTSChannel* ts = CTSChannel::getTSChannelByUid(index.index[2]);
	if( ts ) {
		return ts->ifActive();
	}
	return -1;
}
