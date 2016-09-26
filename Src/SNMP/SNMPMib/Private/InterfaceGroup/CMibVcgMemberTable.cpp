/*
 * CMibVcgMemberTable.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibVcgMemberTable.h"
#include "DeviceLocal.h"
#include "CVCGGroup.h"
#include "CCommonDefine.h"
#include "UID.h"

column_info_T CMibVcgMemberTable::colInfo[vcg_member_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibVcgMemberTable::CMibVcgMemberTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibVcgMemberTable::~CMibVcgMemberTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibVcgMemberTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibVcgMemberTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case vcg_member_index:
		return new CMibVCGMemberCol_index(sn, oid, oidLen, this);
	case vcg_member_sncp:
		return new CMibVCGMemberCol_sncp(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibVcgMemberTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2] = DeviceLocal::instance().GetVcgGroupObject().getFirstVCGUID();

	while( 1 ) {
		CVCG* pvcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index->index[2]);
		if( pvcg ) {
			index->index[3] = pvcg->getFirstMemberUID();
			if( index->index[3] != 0 ) {
				return 1;
			}
			else {
				index->index[2] =  DeviceLocal::instance().GetVcgGroupObject().getNextVCGUID(index->index[2]);
				continue;
			}
		}
		else {
			break;
		}
	}
	return -1;

}
int CMibVcgMemberTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;

	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	while( 1 ) {
		CVCG* pvcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index->index[2]);
		if( pvcg ) {
			if( index->index[3] == 0 ) {
				index->index[3] = pvcg->getFirstMemberUID();
			}
			else {
				index->index[3] = pvcg->getNextMemberUID(index->index[3]);
			}
			if( index->index[3] != 0 ) {
				return 1;
			}
			else {
				index->index[2] =  DeviceLocal::instance().GetVcgGroupObject().getNextVCGUID(index->index[2]);
				index->index[3] = 0;

				continue;
			}
		}
		else {
			break;
		}
	}
	return -1;


}


int CMibVCGMemberCol_index::CallbackGet(const index_info_T& index) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		return index.index[3];
	}
	return -1;
}


int CMibVCGMemberCol_sncp::CallbackGet(const index_info_T& index) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		return vcg->getSNCP(index.index[3]);
	}
	return -1;
}
int CMibVCGMemberCol_sncp::callbackSet( const index_info_T& index, uint32 val) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		if( vcg->setSNCP(index.index[3], val) ) {
			return 0x5A;
		}
	}
	return -1;
}
