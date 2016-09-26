/*
 * CMibVersionInfoTable.cpp
 *
 *  Created on: 2013-5-17
 *      Author: Administrator
 */

#include "CMibVersionInfoTable.h"
#include "CDeviceAttribute.h"
#include "CBaseCard.h"
#include "CCommonDefine.h"
#include "DeviceLocal.h"
#include "CSlotManager.h"
#include "CBaseCard.h"
#include "CBaseSlot.h"
#include <string.h>

column_info_T CMibVersionInfoTable::colInfo[version_column_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibVersionInfoTable::CMibVersionInfoTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibVersionInfoTable::~CMibVersionInfoTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibVersionInfoTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibVersionInfoTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case version_index:
		return new CMibVersionCol_index(sn, oid, oidLen, this);
	case version_name:
		return new CMibVersionCol_name(sn, oid, oidLen, this);
	case version_number:
		return new CMibVersionCol_number(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibVersionInfoTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::ucConstDeviceTypeID;
	index->index[2] = CDeviceAttribute::GetFirstVersionIndex();
	return 1;
}
int CMibVersionInfoTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	if(index->index[1] == CCommonDefine::ucConstDeviceTypeID) {
		uint32 next;
		int rtn = CDeviceAttribute::GetNextVersionIndexbyIndex(index->index[2], &next);
		if( rtn == CErrorValueDefine::uiConstReturnSuccess ) { //主板中的版本信息
			index->index[2] = next;
			return 1;
		}
		/*非主板信息，返回第一个扩展卡版本id*/
		CBaseCard* c = DeviceLocal::instance().GetSlotManager().getFirstCard();
		if( c ) {
			index->index[1]	= c->getSn()+1;
			index->index[2] = 1;
			return 1;
		}
	}
	else {
		CBaseSlot* slt = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index->index[1]-1);
		if(!slt) {
			return -1;
		}
		CBaseCard* c = slt->GetCardObject();
		while( c ) {
			int next =  c->getNextVersionIndex(index->index[2]);
			if(next > 0 ) {
				index->index[1] = c->getSn()+1;
				index->index[2] = next;
				return 1;
			}
			c =  DeviceLocal::instance().GetSlotManager().getNextCard(c->getSn());
			index->index[2] = 0;
		}
	}


	return -1;
}

int CMibVersionCol_index::CallbackGet(const index_info_T& index) {
	return index.index[2];
}


int CMibVersionCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	if( index.index[1] == CCommonDefine::ucConstDeviceTypeID ) {
		STVersion ver;
		int rtn = DeviceLocal::instance().GetDeviceAttributeObject().GetVersion(index.index[2], ver);
		strcpy((char*)name, ver.ucpVerName);
		*len = strlen(ver.ucpVerName);
		return 1;
	}
	else {
		CBaseSlot* slt = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index.index[1]-1);
		if( !slt ) {
			return -1;
		}
		CBaseCard* c = slt->GetCardObject();
		if( c ) {
			STVersion ver;
			int rtn = c->getVersion(index.index[2], ver);
			if( rtn ) {
				strcpy((char*)name, ver.ucpVerName);
				*len = strlen(ver.ucpVerName);
				return 1;
			}
		}
	}
	return -1;
}

int CMibVersionCol_number::CallbackGet(const index_info_T& index) {
	if( index.index[1] == CCommonDefine::ucConstDeviceTypeID ) {
		STVersion ver;
		int rtn = DeviceLocal::instance().GetDeviceAttributeObject().GetVersion(index.index[2], ver);
		return ver.uiVerNum;
	}
	else {
		CBaseSlot* slt = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index.index[1]-1);
		if( !slt ) {
			return -1;
		}
		CBaseCard* c = slt->GetCardObject();
		if( c ) {
			STVersion ver;
			int rtn = c->getVersion(index.index[2], ver);
			if( rtn ) {
				return ver.uiVerNum;
			}
		}
	}
	return -1;
}
