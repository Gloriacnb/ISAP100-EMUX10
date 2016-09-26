/*
 * AlarmGroup.cpp
 *
 *  Created on: 2013-5-1
 *      Author: Administrator
 */

#include "AlarmGroup.h"
#include "AlarmNumberTable.h"
#include "CurrentAlarmTable.h"
#include "HistoryAlarmTable.h"
#include "AlarmPropertyGlobalTable.h"

table_info_T AlarmGroup::tableInfo[table_alarm_size] = {
		{1, 2, 1},
		{2, 6, 2}, //sn, col number, index number
		{3, 6, 2},
		{4, 3, 2}
};


AlarmGroup::AlarmGroup(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_alarm_size);
}

AlarmGroup::~AlarmGroup() {
	// TODO Auto-generated destructor stub
}

CMibEntry* AlarmGroup::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_alarm_number:
		return new AlarmNumberTable(oid, oidLen, &tableInfo[sn]);
	case table_current_alarm:
		return new CurrentAlarmTable(oid, oidLen, &tableInfo[sn]);
	case table_history_alarm:
//		return new HistoryAlarmTable(oid, oidLen, &tableInfo[sn]);
	case table_global_property:
//		return new AlarmPropertyGlobalTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}

