/*
 * AlarmNumberTable.cpp
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#include "AlarmNumberTable.h"
#include "CCommonDefine.h"
#include "SingleCurrentAlarm.h"
#include "SingleHistoryAlarm.h"

column_info_T AlarmNumberTable::colInfo[alarm_number_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


AlarmNumberTable::AlarmNumberTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

AlarmNumberTable::~AlarmNumberTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* AlarmNumberTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* AlarmNumberTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case current_alarm_number:
		return new AlarmNumber_current(sn, oid, oidLen, this);
	case history_alarm_number:
		return new AlarmNumber_history(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int AlarmNumberTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	return 1;
}
int AlarmNumberTable::getNextIndex(index_info_T* index) {
	return -1;
}


int AlarmNumber_current::CallbackGet(const index_info_T& index) {
	return SingleCurrentAlarm::instance().getAlarmNumber();
}


int AlarmNumber_history::CallbackGet(const index_info_T& index) {
	return SingleHistoryAlarm::instance().getAlarmNumber();
}
