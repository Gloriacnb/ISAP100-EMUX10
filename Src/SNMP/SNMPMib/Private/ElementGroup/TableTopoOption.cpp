/*
 * TableTopoOption.cpp
 *
 *  Created on: 2013-7-12
 *      Author: Administrator
 */

#include "TableTopoOption.h"
#include "TopoManager.h"
#include "CCommonDefine.h"

column_info_T TableTopoOption::colInfo[topo_option_size] = {
		{1, Mib_write_only, CSnmpConstDefine::ucConstInteger32},

};


TableTopoOption::TableTopoOption(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

TableTopoOption::~TableTopoOption() {
	// TODO Auto-generated destructor stub
}

column_info_T* TableTopoOption::getColInfo(int sn) {
	return &colInfo[sn];
}


/*
 * STMConfig table ��������
 */
CMibNodeObject* TableTopoOption::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case topo_start_search:
		return new TableTopoOptionCol_search(sn, oid, oidLen, this);
	default:
		return 0;
	}
}


int TableTopoOption::getFirstIndex(index_info_T* index) {
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	return 1;
}
int TableTopoOption::getNextIndex(index_info_T* index) {
	return -1;
}

int TableTopoOptionCol_search::callbackSet( const index_info_T& index, uint32 value) {
	if( value != 0x454242 ) {
		return -1;
	}
//	TopoManager::startTopoSearch();
	return 0x5A;
}

