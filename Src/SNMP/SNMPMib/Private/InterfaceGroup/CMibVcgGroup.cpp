/*
 * CMibVcgGroup.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibVcgGroup.h"
#include "CMibVcgConfigTable.h"
#include "CMibVcgMemberTable.h"

table_info_T CMibVcgGroup::tableInfo[table_vcg_size] = {
		{2, vcg_port_size, 3}, //sn, col number, index number
		{3, vcg_member_size, 4}
};


CMibVcgGroup::CMibVcgGroup(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_vcg_size);
}

CMibVcgGroup::~CMibVcgGroup() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibVcgGroup::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_vcg_config:
		return new CMibVcgConfigTable(oid, oidLen, &tableInfo[sn]);
	case table_vcg_member:
		return new CMibVcgMemberTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
