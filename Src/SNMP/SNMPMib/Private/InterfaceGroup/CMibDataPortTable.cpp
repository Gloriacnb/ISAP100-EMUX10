/*
 * CMibDataPortTable.cpp
 *
 *  Created on: 2013-6-17
 *      Author: Administrator
 */

#include "CMibDataPortTable.h"
#include "CDataPort.h"
#include "CCommonDefine.h"
#include "UID.h"
#include <string.h>

column_info_T CMibDataPortTable::colInfo[dt_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstOctetString},	//ColumnDTPortName
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},		//ColumnDTPortType
		{3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},	//ColumnDTPortEnable
		{4, Mib_read_write, CSnmpConstDefine::ucConstOctetString},	//ColumnDTPortDescription
};


CMibDataPortTable::CMibDataPortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibDataPortTable::~CMibDataPortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibDataPortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibDataPortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case dt_port_name:
		return new CMibDataPortCol_name(sn, oid, oidLen, this);
 	case dt_port_type:
 		return new CMibDataPortCol_type(sn, oid, oidLen, this);
 	case dt_port_enable:
 		return new CMibDataPortCol_enable(sn, oid, oidLen, this);
	case dt_port_desc:
		return new CMibDataPortCol_Description(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibDataPortTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CDataPort::GetFirstDPUid();
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).ts.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}
int CMibDataPortTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CDataPort::GetNextDPUid(index->index[2]);
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).ts.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}


int CMibDataPortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	CDataPort* vf = CDataPort::getDataPort(index.index[2]);
	if( vf ) {
		std::string s = vf->getName();
		*len = s.size();
		strcpy((char*)name, s.c_str());
		return 1;
	}
	return -1;
}

int CMibDataPortCol_type::CallbackGet(const index_info_T& index) {
	CDataPort* vf = CDataPort::getDataPort(index.index[2]);
	if( vf ) {
		return vf->getPortType();
	}
	return -1;
}

int CMibDataPortCol_enable::CallbackGet(const index_info_T& index) {
	CDataPort* vf = CDataPort::getDataPort(index.index[2]);
	if( vf ) {
		return vf->getEnable();
	}
	return -1;
}

int CMibDataPortCol_enable::callbackSet( const index_info_T& index, uint32 nv) {
	CDataPort* vf = CDataPort::getDataPort(index.index[2]);
	if( vf ) {
		if( vf->setEnable(nv) > 0 ) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibDataPortCol_Description::CallbackGet(const index_info_T& index, uint8* vl, uint32* len) {
	CDataPort* vf = CDataPort::getDataPort(index.index[2]);
	if( vf ) {
		char* s = vf->getDesc(len);
		memcpy((char*)vl, s, *len);
		return 1;
	}
	return -1;

}

int CMibDataPortCol_Description::callbackSet( const index_info_T& index, uint8* vl, uint32 len) {
	CDataPort* vf = CDataPort::getDataPort(index.index[2]);
	if( vf ) {
		if( vf->setDesc((char*)vl, len) > 0 )
			return 0x5A;
	}
	return -1;
}
