/*
 * CMibE1PortTable.cpp
 *
 *  Created on: 2013-4-20
 *      Author: Administrator
 */

#include "CMibE1PortTable.h"
#include "DeviceLocal.h"
#include "UID.h"
#include "CCommonDefine.h"
#include "CUnframeE1.h"
#include <string.h>

column_info_T CMibE1PortTable::colInfo[e1_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
};


CMibE1PortTable::CMibE1PortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibE1PortTable::~CMibE1PortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibE1PortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibE1PortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case e1_port_name:
		return new CMibE1PortCol_name(sn, oid, oidLen, this);
	case e1_port_sn:
		return new CMibE1PortCol_sn(sn, oid, oidLen, this);
	case e1_port_slot:
		return new CMibE1PortCol_slot(sn, oid, oidLen, this);
	case e1_port_enable:
		return new CMibE1PortCol_enable(sn, oid, oidLen, this);
	case e1_port_desc:
		return new CMibE1PortCol_desc(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibE1PortTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CUnframeE1::GetFirstE1Uid();
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
int CMibE1PortTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CUnframeE1::GetNextUid(index->index[2]);
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


int CMibE1PortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		std::string s = e1->getName();
		*len = s.size();
		strcpy((char*)name, s.c_str());
		return 1;
	}
	return -1;
}

int CMibE1PortCol_sn::CallbackGet(const index_info_T& index) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		return e1->getPortSn();
	}
	else {
		return -1;
	}
}

int CMibE1PortCol_slot::CallbackGet(const index_info_T& index) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		return e1->getPortSlot();
	}
	else {
		return -1;
	}
}


int CMibE1PortCol_enable::CallbackGet(const index_info_T& index) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		return e1->getEnable();
	}
	return -1;
}

int CMibE1PortCol_enable::callbackSet( const index_info_T& index, uint32 en) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		if( e1->setEnable((uint8)en) < 0 ) {
			return -1;
		}
		return 0x5A;
	}
	return -1;
}

int CMibE1PortCol_desc::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		char* s = e1->getDescription(len);
		strcpy((char*)desc, s);
		return 1;
	}
	return -1;
}
int CMibE1PortCol_desc::callbackSet(const index_info_T& index, uint8*desc, uint32 len) {
	CUnframeE1* e1 = CUnframeE1::getE1(index.index[2]);
	if( e1 ) {
		e1->setDescription((char*)desc, len);
		return 0x5A;
	}
	return -1;
}

