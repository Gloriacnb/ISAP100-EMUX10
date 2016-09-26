/*
 * CMibE1ChannelTable.cpp
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#include "CMibE1ChannelTable.h"
#include "CE1Channel.h"
#include "CCommonDefine.h"
#include "UID.h"

column_info_T CMibE1ChannelTable::colInfo[e1_Channel_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibE1ChannelTable::CMibE1ChannelTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibE1ChannelTable::~CMibE1ChannelTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibE1ChannelTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibE1ChannelTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case e1_Channel_uid:
		return new CMibE1ChannelCol_uid(sn, oid, oidLen, this);
	case e1_Channel_mapping:
		return new CMibE1ChannelCol_Mapping(sn, oid, oidLen, this);
	case e1_Channel_status:
		return new CMibE1ChannelCol_Status(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibE1ChannelTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CE1Channel::GetFirstE1Uid();
	if( uid != 0 ) {
		try {
			index->index[1] = UID::breakUID(uid).E1.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}
int CMibE1ChannelTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CE1Channel::GetNextE1Uid(index->index[2]);
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).E1.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}


int CMibE1ChannelCol_uid::CallbackGet(const index_info_T& index) {
	CE1Channel* e1 = CE1Channel::getE1(index.index[2]);
	if( e1 ) {
		return index.index[2];
	}
	return -1;
}


int CMibE1ChannelCol_Mapping::CallbackGet(const index_info_T& index) {
	CE1Channel* e1 = CE1Channel::getE1(index.index[2]);
	if( e1 ) {
		return e1->GetMapPartner();
	}
	return -1;
}

int CMibE1ChannelCol_Status::CallbackGet(const index_info_T& index) {
	CE1Channel* e1 = CE1Channel::getE1(index.index[2]);
	if( e1 ) {
		return e1->getActive();
	}
	return -1;
}
