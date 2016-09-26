/*
 * CMibVcgConfigTable.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibVcgConfigTable.h"
#include "CCommonDefine.h"
#include "DeviceLocal.h"
#include "CVCGGroup.h"
#include "UID.h"

column_info_T CMibVcgConfigTable::colInfo[vcg_port_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{6, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{7, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{8, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{9, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibVcgConfigTable::CMibVcgConfigTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibVcgConfigTable::~CMibVcgConfigTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibVcgConfigTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibVcgConfigTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case vcg_port_index:
		return new CMibVCGPortCol_index(sn, oid, oidLen, this);
	case vcg_port_name:
		return new CMibVCGPortCol_name(sn, oid, oidLen, this);
	case vcg_port_lcas:
		return new CMibVCGPortCol_lcas(sn, oid, oidLen, this);
	case vcg_port_member_number:
		return new CMibVCGPortCol_MbNumber(sn, oid, oidLen, this);
	case vcg_port_member_add:
		return new CMibVCGPortCol_mbadd(sn, oid, oidLen, this);
	case vcg_port_member_delete:
		return new CMibVCGPortCol_mbdelete(sn, oid, oidLen, this);
	case vcg_port_member_clear:
		return new CMibVCGPortCol_mbclear(sn, oid, oidLen, this);
	case vcg_port_desc:
		return new CMibVCGPortCol_desc(sn, oid, oidLen, this);
	case vcg_port_enable:
		return new CMibVCGPortCol_enable(sn, oid, oidLen, this);

	default:
		return 0;
	}
}
int CMibVcgConfigTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = DeviceLocal::instance().GetVcgGroupObject().getFirstVCGUID();
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).vcg.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}
int CMibVcgConfigTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	uint32 uid = DeviceLocal::instance().GetVcgGroupObject().getNextVCGUID(index->index[2]);
	if( uid ) {
		try {
			index->index[1] = UID::breakUID(uid).vcg.slot;
		}
		catch(...) {
			return -1;
		}
		index->index[2] = uid;
		return 1;
	}
	return -1;
}


int CMibVCGPortCol_index::CallbackGet(const index_info_T& index) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		return index.index[2];
	}
	return -1;
}

int CMibVCGPortCol_name::CallbackGet(const index_info_T& index, uint8* vl, uint32* len) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		std::string& name = vcg->GetName();
		*len = name.size();
		strcpy((char*)vl, name.c_str());
		return 1;
	}
	return -1;
}

int CMibVCGPortCol_enable::CallbackGet(const index_info_T& index) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		return vcg->getEnable();
	}
	return -1;

}
int CMibVCGPortCol_enable::callbackSet( const index_info_T& index, uint32 value) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		vcg->setEnable(value);
		return 0x5A;
	}
	return -1;
}

int CMibVCGPortCol_lcas::CallbackGet(const index_info_T& index) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		return vcg->getLcas();
	}
	return -1;
}
int CMibVCGPortCol_lcas::callbackSet( const index_info_T& index, uint32 value) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		vcg->setLcas(value);
		return 0x5A;
	}
	return -1;

}


int CMibVCGPortCol_MbNumber::CallbackGet(const index_info_T& index) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		return vcg->memberNumber();
	}
	return -1;

}

int CMibVCGPortCol_mbadd::callbackSet( const index_info_T& index, uint32 mid) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		if( vcg->addMember(mid) )
			return 0x5A;
	}
	return -1;

}

int CMibVCGPortCol_mbdelete::callbackSet( const index_info_T& index, uint32 mid) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		if( vcg->removeMember(mid) )
			return 0x5A;
	}
	return -1;

}


int CMibVCGPortCol_mbclear::callbackSet( const index_info_T& index, uint32 mid) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		if( vcg->clrMember() )
			return 0x5A;
	}
	return -1;

}

int CMibVCGPortCol_desc::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		uint8* temp = vcg->GetDesc(len);
		memcpy( desc, temp, *len);
		return 1;
	}
	return -1;

}
int CMibVCGPortCol_desc::callbackSet( const index_info_T& index, uint8* desc, uint32 len) {
	CVCG* vcg = DeviceLocal::instance().GetVcgGroupObject().GetObjectByUID(index.index[2]);
	if( vcg ) {
		vcg->SetDesc(desc, len);
		return 0x5a;
	}
	return -1;

}
