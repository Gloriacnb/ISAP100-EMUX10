/*
 * CMibFunctionModuleGroup.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibFunctionModuleGroup.h"
#include "CMibMappingAddTable.h"
#include "CMibMappingProperty.h"
#include "CMibXCAddTable.h"
#include "CMibXCProperty.h"
#include "CMibLoopAddTable.h"
#include "CMibLoopPropertyTable.h"
#include "CMibLoopablePortTable.h"
#include "CMibBaseSwitchFunction.h"

table_info_T CMibFunctionModuleGroup::tableInfo[table_module_size] = {
		{1, mapping_add_size, 1},
		{2, mapping_property_size, 2}, //sn, col number, index number
		{5, xc_add_size, 1},
		{6, xc_property_size, 2},
		{7, loop_add_size, 1},
		{8, loop_col_size, 2},
		{9, loopable_port_size, 2},
		{10, sw_size, 1}
};


CMibFunctionModuleGroup::CMibFunctionModuleGroup(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_module_size);
}

CMibFunctionModuleGroup::~CMibFunctionModuleGroup() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibFunctionModuleGroup::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_mapping_option:
		return new CMibMappingAddTable(oid, oidLen, &tableInfo[sn]);
	case table_mapping_property:
		return new CMibMappingProperty(oid, oidLen, &tableInfo[sn]);
	case table_cross_option:
		return new CMibXCAddTable(oid, oidLen, &tableInfo[sn]);
	case table_cross_property:
		return new CMibXCProperty(oid, oidLen, &tableInfo[sn]);
	case table_loop_option:
		return new CMibLoopAddTable(oid, oidLen, &tableInfo[sn]);
	case table_loop_property:
		return new CMibLoopPropertyTable(oid, oidLen, &tableInfo[sn]);
	case table_loopable_port:
		return new CMibLoopablePortTable(oid, oidLen, &tableInfo[sn]);
	case table_switch_base:
		return new CMibBaseSwitchFunction(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
