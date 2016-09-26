/*
 * CMibMappingProperty.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibMappingProperty.h"
#include "CCommonDefine.h"
#include <string>
#include "DeviceLocal.h"
#include "CVC12CrossConnectionMagager.h"
#include <string.h>

column_info_T CMibMappingProperty::colInfo[mapping_property_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{5, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{6, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{7, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibMappingProperty::CMibMappingProperty(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibMappingProperty::~CMibMappingProperty() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibMappingProperty::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibMappingProperty::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case mapping_index:
		return new CMibMappingPropertyCol_index(sn, oid, oidLen, this);
	case mapping_west_id:
		return new CMibMappingPropertyCol_westid(sn, oid, oidLen, this);
	case mapping_east_id:
		return new CMibMappingPropertyCol_eastid(sn, oid, oidLen, this);
	case mapping_name:
		return new CMibMappingPropertyCol_name(sn, oid, oidLen, this);
	case mapping_description:
		return new CMibMappingPropertyCol_desc(sn, oid, oidLen, this);
	case mapping_delete:
		return new CMibMappingPropertyCol_delete(sn, oid, oidLen, this);
	case mappint_sncp:
		return new CMibMappingPropertyCol_sncp(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibMappingProperty::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = DeviceLocal::instance().GetMappingManager().GetFirstSnOfConnection();
	if( index->index[1] != 0 )
		return 1;
	return -1;
}

int CMibMappingProperty::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = DeviceLocal::instance().GetMappingManager().GetNextSnConnection(index->index[1]);
	if( index->index[1] != 0 )
		return 1;
	return -1;
}

int CMibMappingPropertyCol_index::CallbackGet(const index_info_T& index) {
	return index.index[1];
}

int CMibMappingPropertyCol_westid::CallbackGet(const index_info_T& index) {
	uint32 id = DeviceLocal::instance().GetMappingManager().GetCCE1ID(index.index[1]);
	if( id )
		return id;
	return -1;
}
int CMibMappingPropertyCol_eastid::CallbackGet(const index_info_T& index) {
	uint32 id = DeviceLocal::instance().GetMappingManager().GetCCVC12ID(index.index[1]);
	if( id )
		return id;
	return -1;
}

int CMibMappingPropertyCol_name::CallbackGet(const index_info_T& index, uint8* data, uint32* len) {
	std::string name;
	uint32 temp = DeviceLocal::instance().GetMappingManager().GetXcName(index.index[1], name);
	if( temp ) {
		*len = name.size();
		memcpy( data, name.c_str(), (uint32)name.size() );
		return 1;
	}
	return -1;
}

int CMibMappingPropertyCol_name::callbackSet( const index_info_T& index, uint8* d, uint32 len) {
	std::string name((char*)d, len);
	uint32 temp = DeviceLocal::instance().GetMappingManager().SetXcName(index.index[1], name);
	if( temp ) {
		return 0x5A;
	}
	return -1;
}


int CMibMappingPropertyCol_desc::CallbackGet(const index_info_T& index, uint8* data, uint32* len) {
	std::string name;
	uint32 temp = DeviceLocal::instance().GetMappingManager().GetXcDescription(index.index[1], name);
	if( temp ) {
		*len = name.size();
		memcpy( data, name.c_str(), (uint32)name.size() );
		return 1;
	}
	return -1;
}
int CMibMappingPropertyCol_desc::callbackSet( const index_info_T& index, uint8* data, uint32 len) {
	std::string desc((char*)data, len);
	return DeviceLocal::instance().GetMappingManager().SetXcDescription(index.index[1], desc);
}

int CMibMappingPropertyCol_delete::callbackSet( const index_info_T& index, uint32 mapid) {
	if (DeviceLocal::instance().GetMappingManager().DeleteOneE1XCConnect(mapid) != 0 ) {
		return 0x5A;
	}
	return -1;
}

int CMibMappingPropertyCol_sncp::CallbackGet(const index_info_T& index) {
	 uint32 sncp = DeviceLocal::instance().GetMappingManager().getXcSncp(index.index[1]);
	 if( sncp != 0xff ) {
		 return sncp;
	 }
	 return -1;
}
int CMibMappingPropertyCol_sncp::callbackSet( const index_info_T& index, uint32 val) {
	return DeviceLocal::instance().GetMappingManager().setXcSncp(index.index[1], val);
}
