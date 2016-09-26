/*
 * CMibNMPortGroup.cpp
 *
 *  Created on: 2015年11月6日
 *      Author: Administrator
 */

#include "CMibNMPortGroup.h"
#include "CMibNMPortTable.h"

table_info_T CMibNMPortGroup::tableInfo[table_nmport_size] = {
        {1, nmport_size, 2}, //sn, col number, index number
};


CMibNMPortGroup::CMibNMPortGroup(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
    // TODO Auto-generated constructor stub
    creatTables(tableInfo, table_nmport_size);
}

CMibNMPortGroup::~CMibNMPortGroup() {
    // TODO Auto-generated destructor stub
}

CMibEntry* CMibNMPortGroup::MakeTable(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case table_nmport_list:
        return new CMibNMPortTable(oid, oidLen, &tableInfo[sn]);
    default:
        return 0;
    }
}
