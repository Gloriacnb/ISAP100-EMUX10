/*
 * CMibXE1PortTable.cpp
 *
 *  Created on: 2015Äê12ÔÂ30ÈÕ
 *      Author: Administrator
 */

#include "CMibXE1PortTable.h"
#include "CNME1Port.h"
#include "UID.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibXE1PortTable::colInfo[xe1_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{6, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
};


CMibXE1PortTable::CMibXE1PortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibXE1PortTable::~CMibXE1PortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibXE1PortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibXE1PortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case xe1_port_index:
		return new CMibXE1PortCol_uid(sn, oid, oidLen, this);
	case xe1_port_name:
		return new CMibXE1PortCol_name(sn, oid, oidLen, this);
	case xe1_port_sn:
		return new CMibXE1PortCol_sn(sn, oid, oidLen, this);
	case xe1_port_mode:
		return new CMibXE1PortCol_mode(sn, oid, oidLen, this);
	case xe1_port_enable:
		return new CMibXE1PortCol_enable(sn, oid, oidLen, this);
	case xe1_port_desc:
		return new CMibXE1PortCol_desc(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibXE1PortTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	CNME1Port* p = CNME1Port::getFirstInstance();
	if( p ) {
		index->index[1] = p->getUID() >> 24;
		index->index[2] = p->getUID();
		return 1;
	}
	return -1;
}
int CMibXE1PortTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	CNME1Port* p = CNME1Port::getNextInstance(index->index[2]);
	if( p ) {
		index->index[1] = p->getUID() >> 24;
		index->index[2] = p->getUID();
		return 1;
	}
	return -1;
}

int CMibXE1PortCol_uid::CallbackGet(const index_info_T& index) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		return p->getUID();
	}
	return -1;
}

int CMibXE1PortCol_name::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		*len = p->getName().size();
		strcpy((char*)buf, p->getName().c_str());
		return 1;
	}
	return -1;
}

int CMibXE1PortCol_sn::CallbackGet(const index_info_T& index) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		UN_Info info = UID::breakUID(p->getUID());
		return info.E1.E1 + 1;
	}
	return -1;
}

int CMibXE1PortCol_mode::CallbackGet(const index_info_T& index) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		return p->getMode();
	}
	return -1;
}
int CMibXE1PortCol_mode::callbackSet( const index_info_T& index, uint32 m) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		if( p->setMode(m) ) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibXE1PortCol_enable::CallbackGet(const index_info_T& index) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		return p->getEnable();
	}
	return -1;
}
int CMibXE1PortCol_enable::callbackSet( const index_info_T& index, uint32 en ) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		if( p->setEnable(en) ) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibXE1PortCol_desc::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		uint8* desc = p->getDesc(len);
		memcpy(buf, desc, *len);
		return 0x5A;
	}
	return -1;
}
int CMibXE1PortCol_desc::callbackSet(const index_info_T& index, uint8* buf, uint32 len) {
	CNME1Port* p = CNME1Port::getInstance(index.index[2]);
	if( p ) {
		if( p->setDesc(buf, len) ) {
			return 0x5A;
		}
	}
	return -1;

}
