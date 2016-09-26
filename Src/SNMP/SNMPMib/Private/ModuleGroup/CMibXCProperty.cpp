/*
 * CMibXCProperty.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibXCProperty.h"
#include "CCommonDefine.h"
#include <string>
#include "DeviceLocal.h"
#include "CTSCrossConnectionManager.h"
#include <string.h>

column_info_T CMibXCProperty::colInfo[xc_property_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{5, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{6, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
};


CMibXCProperty::CMibXCProperty(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibXCProperty::~CMibXCProperty() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibXCProperty::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibXCProperty::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case xc_index:
		return new CMibXCPropertyCol_index(sn, oid, oidLen, this);
	case xc_west_id:
		return new CMibXCPropertyCol_westid(sn, oid, oidLen, this);
	case xc_east_id:
		return new CMibXCPropertyCol_eastid(sn, oid, oidLen, this);
	case xc_name:
		return new CMibXCPropertyCol_name(sn, oid, oidLen, this);
	case xc_description:
		return new CMibXCPropertyCol_desc(sn, oid, oidLen, this);
	case xc_delete:
		return new CMibXCPropertyCol_delete(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibXCProperty::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = DeviceLocal::instance().GetXcManager().GetFirstSnOfConnection();
	if( index->index[1] != 0 )
		return 1;
	return -1;
}

int CMibXCProperty::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = DeviceLocal::instance().GetXcManager().GetNextSnConnection(index->index[1]);
	if( index->index[1] != 0 )
		return 1;
	return -1;
}

int CMibXCPropertyCol_index::CallbackGet(const index_info_T& index) {
	return index.index[1];
}

int CMibXCPropertyCol_westid::CallbackGet(const index_info_T& index) {
	uint32 id = DeviceLocal::instance().GetXcManager().GetWestID(index.index[1]);
	if( id )
		return id;
	return -1;
}
int CMibXCPropertyCol_eastid::CallbackGet(const index_info_T& index) {
	uint32 id = DeviceLocal::instance().GetXcManager().GetEastID(index.index[1]);
	if( id )
		return id;
	return -1;
}

int CMibXCPropertyCol_name::CallbackGet(const index_info_T& index, uint8* data, uint32* len) {
	std::string name;
	uint32 temp = DeviceLocal::instance().GetXcManager().GetXcName(index.index[1], name);
	if( temp ) {
		*len = name.size();
		memcpy( data, name.c_str(), (uint32)name.size() );
		return 1;
	}
	return -1;
}
int CMibXCPropertyCol_name::callbackSet( const index_info_T& index, uint8* data, uint32 len) {
	std::string desc((char*)data, len);
	return DeviceLocal::instance().GetXcManager().SetXcName(index.index[1], desc);
}

int CMibXCPropertyCol_desc::CallbackGet(const index_info_T& index, uint8* data, uint32* len) {
	std::string name;
	uint32 temp = DeviceLocal::instance().GetXcManager().GetXcDescription(index.index[1], name);
	if( temp ) {
		*len = name.size();
		memcpy( data, name.c_str(), (uint32)name.size() );
		return 1;
	}
	return -1;
}
int CMibXCPropertyCol_desc::callbackSet( const index_info_T& index, uint8* data, uint32 len) {
	std::string desc((char*)data, len);
	return DeviceLocal::instance().GetXcManager().SetXcDescription(index.index[1], desc);
}

int CMibXCPropertyCol_delete::callbackSet( const index_info_T& index, uint32 mapid) {
	return DeviceLocal::instance().GetXcManager().DeleteOneTSXCConnect(mapid);
}
