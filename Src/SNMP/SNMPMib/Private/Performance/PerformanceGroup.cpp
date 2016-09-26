/*
 * PerformanceGroup.cpp
 *
 *  Created on: 2014-4-17
 *      Author: Administrator
 */

#include "PerformanceGroup.h"
#include "PerformanceEthPortTable.h"

table_info_T PerformanceGroup::tableInfo[table_performance_size] = {
		{1, eth_performance_size, 3},
};


PerformanceGroup::PerformanceGroup(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_performance_size);
}

PerformanceGroup::~PerformanceGroup() {
	// TODO Auto-generated destructor stub
}

CMibEntry* PerformanceGroup::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_eth_performance:
		return new PerformanceEthPortTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
