/*
 * CMibBaseSwitchFunction.cpp
 *
 *  Created on: 2014-4-4
 *      Author: Administrator
 */

#include "CMibBaseSwitchFunction.h"
#include "CCommonDefine.h"
#include "SwitchModule.h"

column_info_T CMibBaseSwitchFunction::colInfo[sw_size] = {
		{ 1, Mib_read_write, CSnmpConstDefine::ucConstInteger32 },
		{ 4, Mib_read_write, CSnmpConstDefine::ucConstInteger32 },
//		{3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		};

CMibBaseSwitchFunction::CMibBaseSwitchFunction(uint32* oid, uint32 oidLen,
		table_info_T* tInfo) :
		CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibBaseSwitchFunction::~CMibBaseSwitchFunction() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibBaseSwitchFunction::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibBaseSwitchFunction::MakeColumn(int sn, uint32* oid,
		uint32 oidLen) {
	switch (sn) {
	case sw_mode:
		return new CMibBaseSwitch_mode(sn, oid, oidLen, this);
	case sw_mtu:
		return new CMibBaseSwitch_mtu(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibBaseSwitchFunction::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	return 1;
}

int CMibBaseSwitchFunction::getNextIndex(index_info_T* index) {
	return -1;
}

int CMibBaseSwitch_mode::CallbackGet(const index_info_T& index) {
	SwitchModule* m = SwitchModule::getInstance();
	return m->getSwitchMode();
}
int CMibBaseSwitch_mode::callbackSet(const index_info_T& index, uint32 mode) {
	SwitchModule* m = SwitchModule::getInstance();
	if (m) {
		m->setSwitchMode(mode);
		return 0x5A;
	}
	return -1;
}

int CMibBaseSwitch_mtu::CallbackGet(const index_info_T& index) {
	SwitchModule* m = SwitchModule::getInstance();
	return m->getSwitchMTU();
}
int CMibBaseSwitch_mtu::callbackSet(const index_info_T& index, uint32 mode) {
	SwitchModule* m = SwitchModule::getInstance();
	if (m) {
		m->setSwitchMTU(mode);
		return 0x5A;
	}
	return -1;
}
