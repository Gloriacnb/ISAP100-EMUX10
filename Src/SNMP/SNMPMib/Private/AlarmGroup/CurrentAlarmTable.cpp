/*
 * CurrentAlarmTable.cpp
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#include "CurrentAlarmTable.h"

#include "CCommonDefine.h"
#include "SingleCurrentAlarm.h"
#include "AlarmItem.h"
#include <string>
#include <string.h>

column_info_T CurrentAlarmTable::colInfo[current_alarm_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{6, Mib_read_only, CSnmpConstDefine::ucConstOctetString}
};


CurrentAlarmTable::CurrentAlarmTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CurrentAlarmTable::~CurrentAlarmTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CurrentAlarmTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CurrentAlarmTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case current_alarm_index:
		return new CurrentAlarmCol_index(sn, oid, oidLen, this);
	case current_alarm_type:
		return new CurrentAlarmCol_type(sn, oid, oidLen, this);
	case current_alarm_level:
		return new CurrentAlarmCol_level(sn, oid, oidLen, this);
	case current_alarm_source:
		return new CurrentAlarmCol_source(sn, oid, oidLen, this);
	case current_alarm_start_time:
		return new CurrentAlarmCol_startTime(sn, oid, oidLen, this);
	case current_alarm_start_secs:
		return new CurrentAlarmCol_startSecs(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CurrentAlarmTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = SingleCurrentAlarm::instance().getFirstAlarmItemIndex();
	if( index->index[1] != 0 )
		return 1;
	return -1;
}
int CurrentAlarmTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = SingleCurrentAlarm::instance().getNextAlarmItemIndex(index->index[1]);
	if( index->index[1] != 0 )
		return 1;
	return -1;
}


int CurrentAlarmCol_index::CallbackGet(const index_info_T& index) {
	AlarmItem* it = SingleCurrentAlarm::instance().getAlarmItemByIndex(index.index[1]);
	if( it ) {
		return index.index[1];
	}
	return -1;
}

int CurrentAlarmCol_type::CallbackGet(const index_info_T& index) {
	AlarmItem* it = SingleCurrentAlarm::instance().getAlarmItemByIndex(index.index[1]);
	if( it ) {
		return it->itsType();
	}
	return -1;
}

int CurrentAlarmCol_level::CallbackGet(const index_info_T& index) {
	AlarmItem* it = SingleCurrentAlarm::instance().getAlarmItemByIndex(index.index[1]);
	if( it ) {
		return it->itsLevel();
	}
	return -1;
}

int CurrentAlarmCol_source::CallbackGet(const index_info_T& index) {
	AlarmItem* it = SingleCurrentAlarm::instance().getAlarmItemByIndex(index.index[1]);
	if( it ) {
		return it->itsSource();
	}
	return -1;

}

int CurrentAlarmCol_startTime::CallbackGet(const index_info_T& index, uint8* time, uint32* len) {
	AlarmItem* it = SingleCurrentAlarm::instance().getAlarmItemByIndex(index.index[1]);
	if( it ) {
		std::string& s = it->itsStartTime();
		*len = s.size();
		memcpy( time, s.c_str(), *len);
		return 1;
	}
	return -1;

}

int CurrentAlarmCol_startSecs::CallbackGet(const index_info_T& index, uint8* time, uint32* len) {
	AlarmItem* it = SingleCurrentAlarm::instance().getAlarmItemByIndex(index.index[1]);
	if( it ) {
		std::string s(it->getStringItem());
		*len = s.size();
		memcpy( time, s.c_str(), *len);
		return 1;
	}
	return -1;

}

