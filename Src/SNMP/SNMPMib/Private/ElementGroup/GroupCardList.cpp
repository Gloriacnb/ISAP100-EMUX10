/*
 * GroupCardList.cpp
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#include "GroupCardList.h"
#include "TableSlot.h"

table_info_T GroupCardList::tableInfo[table_card_size] = { { 2,
		table_slot_columns, 2 }, //sn, col number, index number
		};

GroupCardList::~GroupCardList() {
	// TODO Auto-generated destructor stub
}

GroupCardList::GroupCardList(uint32* oid, uint8 oidlen) :
		CMibGroup(oid, oidlen) {
	creatTables(tableInfo, table_card_size);
}

CMibEntry* GroupCardList::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch (sn) {
	case table_card:
		return new TableSlot(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
