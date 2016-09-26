/*
 * CMibGroup.cpp
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#include "CMibGroup.h"
#include "Mib_define.h"
#include <string.h>

CMibGroup::~CMibGroup() {
	// TODO Auto-generated destructor stub
}

CMibGroup::CMibGroup(uint32* oid, uint8 oidLen) : CMibEntry(oid, oidLen){


}

void CMibGroup::creatTables(table_info_T* tableInfo, uint32 tnum) {
	uint32 oidlen = 0;
	uint32* oid = getVariable().GetOIDValue(&oidlen);
	uint32* toid = new uint32[oidlen+1];
	for( int i = 0; i < tnum; i++ ) {
		//table_info_T* info = getTableInfo(i);
		memcpy(toid, oid, oidlen*4);
		toid[oidlen] = tableInfo[i].table_sn;
		CMibEntry* ptable = MakeTable(i, toid, oidlen+1);
		if( ptable ) {
			InsertDownLinkNode( ptable );
		}
	}
	delete []toid;
}
