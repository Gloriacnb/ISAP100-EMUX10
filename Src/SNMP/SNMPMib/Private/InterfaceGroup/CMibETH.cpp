/*
 * CMibETH.cpp
 *
 *  Created on: 2014-4-16
 *      Author: Administrator
 */

#include "CMibETH.h"
#include "CMibETHPortTable.h"

table_info_T CMibETH::tableInfo[table_eth_size] = { { 4, eth_port_size, 3 }, //sn, col number, index number
		};

CMibETH::CMibETH(uint32* oid, uint8 oidlen) :
		CMibGroup(oid, oidlen) {
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_eth_size);
}

CMibETH::~CMibETH() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibETH::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch (sn) {
	case table_eth_config:
		return new CMibETHPortTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
