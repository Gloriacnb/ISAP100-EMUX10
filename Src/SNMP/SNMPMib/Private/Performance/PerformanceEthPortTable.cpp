/*
 * PerformanceEthPortTable.cpp
 *
 *  Created on: 2014-4-17
 *      Author: Administrator
 */

#include "PerformanceEthPortTable.h"
#include "PortEth.h"
#include "CCommonDefine.h"

column_info_T PerformanceEthPortTable::colInfo[eth_performance_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


PerformanceEthPortTable::PerformanceEthPortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

PerformanceEthPortTable::~PerformanceEthPortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* PerformanceEthPortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* PerformanceEthPortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case eth_tx_counter:
		return new PerformanceEth_tx(sn, oid, oidLen, this);
	case eth_rx_counter:
		return new PerformanceEth_rx(sn, oid, oidLen, this);
	case eth_rx_drop_counter:
		return new PerformanceEth_drop(sn, oid, oidLen, this);
	case eth_rx_crcerr_counter:
		return new PerformanceEth_crc(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int PerformanceEthPortTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PortEth* p = PortEth::getFirstInstance();
    if( p ) {
        uint32 uid = p->getUID();
        index->index[1] = (uid >> 24);
        index->index[2] = uid;
        return 1;
    }
    return -1;
}
int PerformanceEthPortTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PortEth* p = PortEth::getNextInstance(index->index[2]);
    if( p ) {
        uint32 uid = p->getUID();
        index->index[1] = (uid >> 24);
        index->index[2] = uid;
        return 1;
    }
    return -1;
}

int PerformanceEth_tx::CallbackGet(const index_info_T& index) {
    PortEth* p = PortEth::getInstance(index.index[2]);
    if( p ) {
        return p->getTxCounter();
    }
    return -1;
}

int PerformanceEth_rx::CallbackGet(const index_info_T& index) {
    PortEth* p = PortEth::getInstance(index.index[2]);
    if( p ) {
        return p->getRxCounter();
    }
    return -1;
}

int PerformanceEth_drop::CallbackGet(const index_info_T& index) {
    PortEth* p = PortEth::getInstance(index.index[2]);
    if( p ) {
        return p->getRxDropCounter();
    }
    return -1;
}

int PerformanceEth_crc::CallbackGet(const index_info_T& index) {
    PortEth* p = PortEth::getInstance(index.index[2]);
    if( p ) {
        return p->getRxCRCerrCounter();
    }
    return -1;
}
