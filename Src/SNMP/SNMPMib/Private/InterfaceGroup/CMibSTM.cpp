/*
 * CMibSTM.cpp
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#include "CMibSTM.h"
#include <string.h>
#include "CMibSTMConfig.h"
#include "CMibSTMOverheadTable.h"
#include "CMibSTMAlarmProperty.h"

table_info_T CMibSTM::tableInfo[table_stm_size] = {
		{3, stm_Alarm_size, 4},
		{5, stm_cfg_size, 3}, //sn, col number, index number
		{6, stm_oh_size, 3},
};

CMibSTM::~CMibSTM() {
	// TODO Auto-generated destructor stub
}

//CMibSTM::CMibSTM(uint8* oid, uint8 oidlen) : CMibEntry( oid, oidlen){
//
//}

CMibSTM::CMibSTM(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	creatTables(tableInfo, table_stm_size);
}

//table_info_T* CMibSTM::getTableInfo(int sn) {
//	return &tableInfo[sn];
//}

CMibEntry* CMibSTM::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_stm_alarm_property:
		return new CMibSTMAlarmProperty(oid, oidLen, &tableInfo[sn]);
	case table_stm_config: {
		return new CMibSTMConfig(oid, oidLen, &tableInfo[sn]);
	}
	case table_stm_overhead:
		return new CMibSTMOverheadTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
