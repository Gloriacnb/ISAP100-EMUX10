/*
 * CMibETHPortTable.cpp
 *
 *  Created on: 2014-4-16
 *      Author: Administrator
 */

#include "CMibETHPortTable.h"
#include "PortEth.h"
#include "CCommonDefine.h"
#include <string.h>


column_info_T CMibETHPortTable::colInfo[eth_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{6, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{7, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{8, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{9, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{10, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{11, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{12, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{13, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
};


CMibETHPortTable::CMibETHPortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibETHPortTable::~CMibETHPortTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibETHPortTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibETHPortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case eth_port_index:
		return new CMibETHPortCol_index(sn, oid, oidLen, this);
	case eth_port_name:
		return new CMibETHPortCol_name(sn, oid, oidLen, this);
	case eth_port_enable:
		return new CMibETHPortCol_enable(sn, oid, oidLen, this);
	case eth_port_speed:
		return new CMibETHPortCol_speed(sn, oid, oidLen, this);
	case eth_port_duplex:
		return new CMibETHPortCol_duplex(sn, oid, oidLen, this);
	case eth_port_pause:
		return new CMibETHPortCol_pause(sn, oid, oidLen, this);
	case eth_port_auto:
		return new CMibETHPortCol_mtu(sn, oid, oidLen, this);
	case eth_port_desc:
		return new CMibETHPortCol_desc(sn, oid, oidLen, this);
	case eth_port_linktype:
		return new CMibETHPortCol_linktype(sn, oid, oidLen, this);
	case eth_port_PVID:
		return new CMibETHPortCol_pvid(sn, oid, oidLen, this);
	case eth_port_EVIDlst:
		return new CMibETHPortCol_evidlst(sn, oid, oidLen, this);
	case eth_port_addevid:
		return new CMibETHPortCol_addevid(sn, oid, oidLen, this);
	case eth_port_rmvevid:
		return new CMibETHPortCol_rmvevid(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibETHPortTable::getFirstIndex(index_info_T* index) {
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
int CMibETHPortTable::getNextIndex(index_info_T* index) {
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

int CMibETHPortCol_index::CallbackGet(const index_info_T& index) {
    PortEth* p = PortEth::getInstance(index.index[2]);
    if( p ) {
        return p->getUID();
    }
    return -1;
}

int CMibETHPortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		std::string s = p->getName();
		*len = s.size();
		strcpy((char*)name, s.c_str());
		return 1;
	}
	return -1;
}


int CMibETHPortCol_enable::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getEnable();
	}
	return -1;
}

int CMibETHPortCol_enable::callbackSet( const index_info_T& index, uint32 en) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setEnable((uint8)en) ) {
            return 0x5A;
		}
	}
	return -1;
}


int CMibETHPortCol_speed::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getSpeed();
	}
	return -1;
}

int CMibETHPortCol_speed::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setSpeed((uint8)data) ) {
            return 0x5A;
		}
	}
	return -1;
}

int CMibETHPortCol_duplex::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getDuplex();
	}
	return -1;
}

int CMibETHPortCol_duplex::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setDuplex((uint8)data) ) {
            return 0x5A;
		}
	}
	return -1;
}

int CMibETHPortCol_pause::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getPause();
	}
	return -1;
}

int CMibETHPortCol_pause::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setPause((uint8)data) ) {
            return 0x5A;
		}
	}
	return -1;
}

int CMibETHPortCol_mtu::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getAuto();
	}
	return -1;
}

int CMibETHPortCol_mtu::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setAuto((uint8)data) ) {
            return 0x5A;
		}
	}
	return -1;
}


int CMibETHPortCol_desc::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		uint8* s = p->getDescription(len);
		memcpy(desc, s, *len);
		return 1;
	}
	return -1;
}
int CMibETHPortCol_desc::callbackSet(const index_info_T& index, uint8*desc, uint32 len) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setDescription(desc, len) ) {
		    return 0x5A;
		}
	}
	return -1;
}


int CMibETHPortCol_linktype::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getLinktype();
	}
	return -1;
}

int CMibETHPortCol_linktype::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setLinktype((uint8)data) ) {
            return 0x5A;
		}
	}
	return -1;
}


int CMibETHPortCol_pvid::CallbackGet(const index_info_T& index) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		return p->getPVID();
	}
	return -1;
}

int CMibETHPortCol_pvid::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->setPVID((uint16)data) ) {
            return 0x5A;
		}
	}
	return -1;
}

int CMibETHPortCol_evidlst::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		uint8* s = p->getEVIDList(len);
		memcpy(desc, s, *len);
		return 1;
	}
	return -1;
}

int CMibETHPortCol_addevid::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->addEVID((uint16)data) ) {
            return 0x5A;
		}
	}
	return -1;
}

int CMibETHPortCol_rmvevid::callbackSet( const index_info_T& index, uint32 data) {
	PortEth* p = PortEth::getInstance(index.index[2]);
	if( p ) {
		if( p->removeEVID((uint16)data) ) {
            return 0x5A;
		}
	}
	return -1;
}
