/*
 * CMibUPortTable.cpp
 *
 *  Created on: 2013-7-30
 *      Author: Administrator
 */

#include "CMibUPortTable.h"
#include "CUInterface.h"
#include "CCommonDefine.h"
#include "UID.h"
#include <string.h>

column_info_T CMibUPortTable::colInfo[u_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{6, Mib_read_write, CSnmpConstDefine::ucConstInteger32}
};


CMibUPortTable::CMibUPortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibUPortTable::~CMibUPortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibUPortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibUPortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case u_port_name:
		return new CMibUPortCol_name(sn, oid, oidLen, this);
	case u_port_sn:
		return new CMibUPortCol_sn(sn, oid, oidLen, this);
	case u_port_slot:
		return new CMibUPortCol_slot(sn, oid, oidLen, this);
	case u_port_enable:
		return new CMibUPortCol_enable(sn, oid, oidLen, this);
	case u_port_desc:
		return new CMibUPortCol_desc(sn, oid, oidLen, this);
	case u_port_mode:
		return new CMibUPortCol_mode(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibUPortTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CUInterface::GetFirstUid();
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).E1.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}
int CMibUPortTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CUInterface::GetNextUid(index->index[2]);
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).E1.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}

int CMibUPortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		std::string s = e1->getName();
		*len = s.size();
		strcpy((char*)name, s.c_str());
		return 1;
	}
	return -1;
}

int CMibUPortCol_sn::CallbackGet(const index_info_T& index) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		return e1->getPortSn();
	}
	else {
		return -1;
	}
}

int CMibUPortCol_slot::CallbackGet(const index_info_T& index) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		return e1->getPortSlot();
	}
	else {
		return -1;
	}
}


int CMibUPortCol_enable::CallbackGet(const index_info_T& index) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		return e1->getEnable();
	}
	return -1;
}

int CMibUPortCol_enable::callbackSet( const index_info_T& index, uint32 en) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		e1->setEnable((uint8)en);
		return 0x5A;
	}
	return -1;
}

int CMibUPortCol_desc::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		char* s = e1->getDescription(len);
		strcpy((char*)desc, s);
		return 1;
	}
	return -1;
}
int CMibUPortCol_desc::callbackSet(const index_info_T& index, uint8*desc, uint32 len) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		e1->setDescription((char*)desc, len);
		return 0x5A;
	}
	return -1;
}


int CMibUPortCol_mode::CallbackGet(const index_info_T& index) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		return e1->getMode();
	}
	return -1;
}

int CMibUPortCol_mode::callbackSet( const index_info_T& index, uint32 en) {
	CUInterface* e1 = CUInterface::getPort(index.index[2]);
	if( e1 ) {
		e1->setMode((uint8)en);
		return 0x5A;
	}
	return -1;
}
