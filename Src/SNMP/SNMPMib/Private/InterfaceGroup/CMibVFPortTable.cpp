/*
 * CMibVFPortTable.cpp
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#include "CMibVFPortTable.h"
#include "CCommonDefine.h"
#include "CVFPort.h"
#include "UID.h"
#include <string.h>

column_info_T CMibVFPortTable::colInfo[vf_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstOctetString},	//ColumnVFPortName
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},		//ColumnVFPortType
		{3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},	//ColumnVFPortEnable
		{4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},	//ColumnVFPortWorkModel
		{5, Mib_read_write, CSnmpConstDefine::ucConstInteger32},	//ColumnVFPortPolarTurn
		{6, Mib_read_write, CSnmpConstDefine::ucConstInteger32},	//ColumnVFPortADGain
		{7, Mib_read_write, CSnmpConstDefine::ucConstInteger32},	//ColumnVFPortDAGain
		{8, Mib_read_write, CSnmpConstDefine::ucConstOctetString},	//ColumnVFPortDescription
};


CMibVFPortTable::CMibVFPortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibVFPortTable::~CMibVFPortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibVFPortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibVFPortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case vf_port_name:
		return new CMibVFPortCol_name(sn, oid, oidLen, this);
 	case vf_port_type:
 		return new CMibVFPortCol_type(sn, oid, oidLen, this);
 	case vf_port_enable:
 		return new CMibVFPortCol_enable(sn, oid, oidLen, this);
 	case vf_port_work_model:
 		return new CMibVFPortCol_mode(sn, oid, oidLen, this);
 	case vf_port_polar_turn:
 		return new CMibVFPortCol_polar(sn, oid, oidLen, this);
	case vf_port_rcv_gain:
		return new CMibVFPortCol_RcvGain(sn, oid, oidLen, this);
	case vf_port_snd_gain:
		return new CMibVFPortCol_SndGain(sn, oid, oidLen, this);
	case vf_port_desc:
		return new CMibVFPortCol_Description(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibVFPortTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CVFPort::GetFirstE1Uid();
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
int CMibVFPortTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = CVFPort::GetNextE1Uid(index->index[2]);
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

int CMibVFPortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		std::string s = vf->getName();
		*len = s.size();
		strcpy((char*)name, s.c_str());
		return 1;
	}
	return -1;
}

int CMibVFPortCol_type::CallbackGet(const index_info_T& index) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		return vf->getPortType();
	}
	return -1;
}

int CMibVFPortCol_enable::CallbackGet(const index_info_T& index) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		return vf->getEnable();
	}
	return -1;
}

int CMibVFPortCol_enable::callbackSet( const index_info_T& index, uint32 nv) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		if( vf->setEnable(nv) > 0 ) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibVFPortCol_mode::CallbackGet(const index_info_T& index) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		return vf->getWorkMode();
	}
	return -1;
}

int CMibVFPortCol_mode::callbackSet( const index_info_T& index, uint32 nv) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		if( vf->setWorkMode(nv) > 0 ) {
			return 0x5A;
		}
	}
	return -1;
}


int CMibVFPortCol_polar::CallbackGet(const index_info_T& index) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		return vf->getPolarTurn();
	}
	return -1;
}

int CMibVFPortCol_polar::callbackSet( const index_info_T& index, uint32 nv) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		if( vf->setPolarTurn(nv) > 0 ) {
			return 0x5A;
		}
	}
	return -1;
}

int CMibVFPortCol_RcvGain::CallbackGet(const index_info_T& index) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if(( vf->getPortType() ==2 ) || (vf->getPortType() ==5)) {//2W or 4W
//		memcpy(vl, , 2);
		return vf->getRcvGain();
	}
	return -1;

}

int CMibVFPortCol_RcvGain::callbackSet( const index_info_T& index, uint32 vl) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( ( vf->getPortType() ==2 ) || (vf->getPortType() ==5) ) {
		if( vf->setRcvGain((uint8)vl) > 0 )
			return 0x5A;
	}
	return -1;
}


int CMibVFPortCol_SndGain::CallbackGet(const index_info_T& index) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( ( vf->getPortType() ==2 ) || (vf->getPortType() ==5) ) {
		return vf->getSndGain();
	}
	return -1;

}

int CMibVFPortCol_SndGain::callbackSet( const index_info_T& index, uint32 vl) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( ( vf->getPortType() ==2 ) || (vf->getPortType() ==5) ) {
		if( vf->setSndGain((uint8)vl) > 0 )
			return 0x5A;
	}
	return -1;
}

int CMibVFPortCol_Description::CallbackGet(const index_info_T& index, uint8* vl, uint32* len) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		char* s = vf->getDesc(len);
		memcpy((char*)vl, s, *len);
		return 1;
	}
	return -1;

}

int CMibVFPortCol_Description::callbackSet( const index_info_T& index, uint8* vl, uint32 len) {
	CVFPort* vf = CVFPort::getVFPort(index.index[2]);
	if( vf ) {
		if( vf->setDesc((char*)vl, len) > 0 )
			return 0x5A;
	}
	return -1;
}
