/*
 * CMibXE1.cpp
 *
 *  Created on: 2015Äê12ÔÂ30ÈÕ
 *      Author: Administrator
 */

#include "CMibXE1.h"
#include "CMibXE1PortTable.h"
#include "CMibXE1AlarmPropertyTable.h"

table_info_T CMibXE1::tableInfo[table_XE1_size] = {
 		{1, xe1_port_size, 3}, //sn, col number, index number
		{2, XE1_Alarm_size, 4},
};


CMibXE1::CMibXE1(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_XE1_size);
}

CMibXE1::~CMibXE1() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibXE1::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_XE1_Port:
		return new CMibXE1PortTable(oid, oidLen, &tableInfo[sn]);
	case table_XE1_alarm_property:
		return new CMibXE1AlarmPropertyTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
