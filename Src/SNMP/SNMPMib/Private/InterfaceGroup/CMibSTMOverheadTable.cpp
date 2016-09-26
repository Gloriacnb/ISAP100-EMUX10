/*
 * CMibSTMOverheadTable.cpp
 *
 *  Created on: 2013-4-19
 *      Author: Administrator
 */

#include "CMibSTMOverheadTable.h"
#include "CSTM.h"
#include "DeviceLocal.h"
#include "SDHGroup.h"
#include "CCommonDefine.h"
#include "string.h"

column_info_T CMibSTMOverheadTable::colInfo[stm_oh_size] = { { 1,
		Mib_read_write, CSnmpConstDefine::ucConstOctetString }, { 2,
		Mib_read_write, CSnmpConstDefine::ucConstOctetString }, { 3,
		Mib_read_only, CSnmpConstDefine::ucConstOctetString } };

CMibSTMOverheadTable::CMibSTMOverheadTable(uint32* oid, uint32 oidLen,
		table_info_T* tInfo) :
		CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibSTMOverheadTable::~CMibSTMOverheadTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibSTMOverheadTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibSTMOverheadTable::MakeColumn(int sn, uint32* oid,
		uint32 oidLen) {
	switch (sn) {
	case stm_oh_J0_Transmit:
		return new CMibSTMOverheadCol_J0Transmit(sn, oid, oidLen, this);
	case stm_oh_J0_expected:
		return new CMibSTMOverheadCol_J0Expected(sn, oid, oidLen, this);
	case stm_oh_J0_Receive:
		return new CMibSTMOverheadCol_J0Receive(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibSTMOverheadTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2] = DeviceLocal::instance().GetSdhObject().GetFirstUid();
	return 1;
}
int CMibSTMOverheadTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2] = DeviceLocal::instance().GetSdhObject().GetNextUid(
			index->index[2]);
	if (index->index[2] == 0) {
		return -1;
	}
	return 1;
}

int CMibSTMOverheadCol_J0Transmit::CallbackGet(const index_info_T& index,
		uint8* j0, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(
			index.index[2]);
	if (pstm) {
		uint32 dlen = 0;
		uint8* p = pstm->getJ0Transmit(&dlen);
		if (p) {
			*len = dlen;
			memcpy(j0, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}
int CMibSTMOverheadCol_J0Transmit::callbackSet(const index_info_T& index,
		uint8* j0, uint32 len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(
			index.index[2]);
	if (pstm) {
		pstm->setJ0Transmit(j0, (uint8) len);
		return 0x5A;
	}
	return -1;
}

int CMibSTMOverheadCol_J0Expected::CallbackGet(const index_info_T& index,
		uint8* j0, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(
			index.index[2]);
	if (pstm) {
		uint32 dlen = 0;
		uint8* p = pstm->getJ0Expected(&dlen);
		if (p) {
			*len = dlen;
			memcpy(j0, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}
int CMibSTMOverheadCol_J0Expected::callbackSet(const index_info_T& index,
		uint8* j0, uint32 len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(
			index.index[2]);
	if (pstm) {
		pstm->setJ0Expected(j0, (uint8) len);
		return 0x5A;
	}
	return -1;
}

int CMibSTMOverheadCol_J0Receive::CallbackGet(const index_info_T& index,
		uint8* j0, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(
			index.index[2]);
	if (pstm) {
		uint32 dlen = 0;
		uint8* p = pstm->getJ0Received(&dlen);
		if (p) {
			*len = dlen;
			memcpy(j0, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}

