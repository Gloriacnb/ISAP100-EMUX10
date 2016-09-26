/*
 * CMibTS.cpp
 *
 *  Created on: 2013-4-26
 *      Author: Administrator
 */

#include "CMibTS.h"
#include "CMibVFPortTable.h"
#include "CMibTSChannelTable.h"
#include "CMibDataPortTable.h"

table_info_T CMibTS::tableInfo[table_ts_size] = {
		{1, 3, 3},
		{2, 8, 3}, //sn, col number, index number
		{3, 3, 4},
		{4, 4, 3},
		{5, 3, 4}

};


CMibTS::CMibTS(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_ts_size);
}

CMibTS::~CMibTS() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibTS::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_ts_channel:
		return new CMibTSChannelTable(oid, oidLen, &tableInfo[sn]);
	case table_ts_vf_port:
		return new CMibVFPortTable(oid, oidLen, &tableInfo[sn]);
	case table_ts_vf_alarm_property:
//		return new CMibE1AlarmPropertyTable(oid, oidLen, &tableInfo[sn]);
		break;
	case table_ts_data_port:
		return new CMibDataPortTable(oid, oidLen, &tableInfo[sn]);
	case table_ts_data_alarm_property:
		break;
	default:
		return 0;
	}
	return 0;
}

