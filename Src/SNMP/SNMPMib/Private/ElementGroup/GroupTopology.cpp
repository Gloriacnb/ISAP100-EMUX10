/*
 * GroupTopology.cpp
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#include "GroupTopology.h"
#include "TableTopoOption.h"
#include "TableTopoStatus.h"

table_info_T GroupTopology::tableInfo[table_topology_size] = { { 1,
		topo_option_size, 1 }, //sn, col number, index number
		{ 2, topo_status_size, 2 } };

GroupTopology::~GroupTopology() {
	// TODO Auto-generated destructor stub
}

GroupTopology::GroupTopology(uint32* oid, uint8 oidlen) :
		CMibGroup(oid, oidlen) {
	creatTables(tableInfo, table_topology_size);
}

CMibEntry* GroupTopology::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch (sn) {
	case table_topology_option:
		return new TableTopoOption(oid, oidLen, &tableInfo[sn]);
	case table_topology_status:
		return new TableTopoStatus(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
