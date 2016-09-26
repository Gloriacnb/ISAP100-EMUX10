/*
 * CMibE1AlarmPropertyTable.cpp
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#include <string.h>
#include "CMibE1AlarmPropertyTable.h"
#include "CCommonDefine.h"
#include "CUnframeE1.h"
#include "AlarmElement.h"

column_info_T CMibE1AlarmPropertyTable::colInfo[E1_Alarm_size] = { { 1,
		Mib_read_only, CSnmpConstDefine::ucConstInteger32 }, { 2,
		Mib_read_write, CSnmpConstDefine::ucConstOctetString }, { 3,
		Mib_read_only, CSnmpConstDefine::ucConstOctetString } };

CMibE1AlarmPropertyTable::CMibE1AlarmPropertyTable(uint32* oid, uint32 oidLen,
		table_info_T* tInfo) :
		CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibE1AlarmPropertyTable::~CMibE1AlarmPropertyTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibE1AlarmPropertyTable::getColInfo(int sn) {
	return &colInfo[sn];
}

/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* CMibE1AlarmPropertyTable::MakeColumn(int sn, uint32* oid,
		uint32 oidLen) {
	switch (sn) {
	case E1_Alarm_type:
		return new CMibE1AlarmCol_uid(sn, oid, oidLen, this);
	case E1_Alarm_Property:
		return new CMibE1AlarmCol_Property(sn, oid, oidLen, this);
	case E1_Alarm_name:
		return new CMibE1AlarmCol_Name(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibE1AlarmPropertyTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2] = CUnframeE1::GetFirstE1Uid();
	CUnframeE1* pe1 = CUnframeE1::getE1(index->index[2]);
	index->index[3] = pe1->getFirstAlarmType();
	return 1;
}
int CMibE1AlarmPropertyTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	while (1) {
		CUnframeE1* pe1 = CUnframeE1::getE1(index->index[2]);
		if (pe1) {
			index->index[3] = pe1->getNextAlarmType(index->index[3]);
			if (index->index[3] != 0) {
				return 1;
			} else {
				index->index[2] = pe1->GetNextUid(index->index[2]);
				continue;
			}
		} else {
			break;
		}
	}
	return -1;

}

int CMibE1AlarmCol_uid::CallbackGet(const index_info_T& index) {
	CUnframeE1* pe1 = CUnframeE1::getE1(index.index[2]);
	if (pe1) {
		if (pe1->getAlarmObject(index.index[3])) {
			return index.index[3];
		}
	}
	return -1;
}

int CMibE1AlarmCol_Property::CallbackGet(const index_info_T& index,
		uint8* value, uint32* len) {
	CUnframeE1* pe1 = CUnframeE1::getE1(index.index[2]);
	if (pe1) {
		AlarmElement* alm = pe1->getAlarmObject(index.index[3]);
		if (alm) {
			*len = 3;
			value[0] = alm->getPropertyLevel();
			value[1] = alm->getPropertyTrap();
			value[2] = alm->getPropertyMask();
			return 1;
		}
	}
	return -1;
}

int CMibE1AlarmCol_Property::callbackSet(const index_info_T& index,
		uint8* value, uint32 len) {
	if (value == 0 || len < 3) {
		return -1;
	}
	CUnframeE1* pe1 = CUnframeE1::getE1(index.index[2]);
	if (pe1) {
		if (pe1->setAlarmProperty(index.index[3], value)) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibE1AlarmCol_Name::CallbackGet(const index_info_T& index, uint8* value,
		uint32* len) {
	CUnframeE1* pe1 = CUnframeE1::getE1(index.index[2]);
	if (pe1) {
		char name[10];
		if (pe1->getAlarmName(index.index[3], name) == 1) {
			*len = strlen(name);
			strcpy((char*) value, name);
			return 1;
		}
	}
	return -1;
}

