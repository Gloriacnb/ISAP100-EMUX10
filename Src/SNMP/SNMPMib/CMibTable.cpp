/*
 * CMibTable.cpp
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#include "CMibTable.h"
#include <string.h>

CMibTable::~CMibTable() {
	// TODO Auto-generated destructor stub
}

CMibTable::CMibTable(uint32* oid, uint32 oidLen, table_info_T* info) : CMibEntry(oid, oidLen) {

	tInfo = info;
}


void CMibTable::makeColumnOid(void) {
	uint32 oidLen = 0;
	uint32* oid = getVariable().GetOIDValue(&oidLen);
	//uint32 colOID[Max_oid_size] = {0};
	uint32* colOID = new uint32[oidLen+2];
	for(int i = 0; i < tInfo->table_col_num; i++) {
		column_info_T* colinfo = getColInfo(i);
		if( !colinfo ) {
			continue;
		}
		memcpy(colOID, oid, oidLen*4);
		colOID[oidLen] = table_entry;
		colOID[oidLen+1] = colinfo->col_sn;
		CMibNodeObject* pcol = MakeColumn(i, colOID, oidLen+2);
		if( pcol ) {
			InsertDownLinkNode( pcol );
		}
	}
	delete []colOID;
}
