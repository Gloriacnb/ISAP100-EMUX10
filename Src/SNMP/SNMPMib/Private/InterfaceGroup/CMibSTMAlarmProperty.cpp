/*
 * CMibSTMAlarmProperty.cpp
 *
 *  Created on: 2013-4-24
 *      Author: Administrator
 */

#include "CMibSTMAlarmProperty.h"
#include "CSTM.h"
#include "DeviceLocal.h"
#include "SDHGroup.h"
#include "CCommonDefine.h"
#include "AlarmElement.h"
#include <string.h>

column_info_T CMibSTMAlarmProperty::colInfo[stm_Alarm_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_only, CSnmpConstDefine::ucConstOctetString}
};



CMibSTMAlarmProperty::CMibSTMAlarmProperty(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibSTMAlarmProperty::~CMibSTMAlarmProperty() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibSTMAlarmProperty::getColInfo(int sn) {
	return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* CMibSTMAlarmProperty::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case stm_Alarm_type:
		return new CMibSTMAlarmCol_uid(sn, oid, oidLen, this);
	case stm_Alarm_Property:
		return new CMibSTMAlarmCol_Property(sn, oid, oidLen, this);
	case stm_Alarm_name:
		return new CMibSTMAlarmCol_Name(sn, oid, oidLen, this);
	default:
		return 0;
	}
}


int CMibSTMAlarmProperty::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2]	= DeviceLocal::instance().GetSdhObject().GetFirstUid();
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index->index[2]);
	index->index[3]	= pstm->getFirstAlarmType();
	return 1;
}
int CMibSTMAlarmProperty::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	while( 1 ) {
		CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index->index[2]);
		if( pstm ) {
			index->index[3] = pstm->getNextAlarmType(index->index[3]);
			if( index->index[3] != 0 ) {
				return 1;
			}
			else {
				index->index[2] = DeviceLocal::instance().GetSdhObject().GetNextUid(index->index[2]);
				continue;
			}
		}
		else {
			break;
		}
	}
	return -1;

}

int CMibSTMAlarmCol_uid::CallbackGet(const index_info_T& index) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		if( pstm->getAlarmObject(index.index[3]) ) {
			return index.index[3];
		}
	}
	return -1;
}

int CMibSTMAlarmCol_Property::CallbackGet(const index_info_T& index, uint8* value, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		AlarmElement* alm = pstm->getAlarmObject(index.index[3]);
		if( alm ) {
			*len = 3;
			value[0] = alm->getPropertyLevel();
			value[1] = alm->getPropertyTrap();
			value[2] = alm->getPropertyMask();
			return 1;
		}
	}
	return -1;
}

int CMibSTMAlarmCol_Property::callbackSet(const index_info_T& index, uint8* value, uint32 len) {
	if( value == 0 || len < 3 ) {
		return -1;
	}
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		if( pstm->setAlarmProperty(index.index[3], value) ) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibSTMAlarmCol_Name::CallbackGet(const index_info_T& index, uint8* value, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		char name[10];
		if( pstm->getAlarmName(index.index[3], name) == 1) {
			*len = strlen(name);
			strcpy((char*)value, name);
			return 1;
		}
	}
	return -1;
}


