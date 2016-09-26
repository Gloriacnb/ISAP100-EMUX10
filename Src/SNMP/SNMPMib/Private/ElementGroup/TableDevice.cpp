/*
 * TableDevice.cpp
 *
 *  Created on: 2013-7-9
 *      Author: Administrator
 */

#include "TableDevice.h"
#include "CCommonDefine.h"
#include "DeviceLocal.h"
#include <string.h>
#include "ChipOptLogic.h"

column_info_T TableDevice::colInfo[device_column_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{5, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{6, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{7, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{8, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{9, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{10,Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{11,Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{12,Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{13,Mib_read_write, CSnmpConstDefine::ucConstInteger32}

};



TableDevice::TableDevice(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

TableDevice::~TableDevice() {
	// TODO Auto-generated destructor stub
}

column_info_T* TableDevice::getColInfo(int sn) {
	return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* TableDevice::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case device_index:
		return new TableDeviceCol_index(sn, oid, oidLen, this);
	case device_name:
		return new TableDeviceCol_name(sn, oid, oidLen, this);
	case device_typeID:
		return new TableDeviceCol_typeID(sn, oid, oidLen, this);
	case device_desc:
		return new TableDeviceCol_desc(sn, oid, oidLen, this);
	case device_status:
		return new TableDeviceCol_status(sn, oid, oidLen, this);
	case device_net_position:
		return new TableDeviceCol_netpos(sn, oid, oidLen, this);
	case device_Chassis:
		return new TableDeviceCol_chassis(sn, oid, oidLen, this);
	case device_slot_number:
		return new TableDeviceCol_slotnum(sn, oid, oidLen, this);
	case device_special_command:
		return new TableDeviceCol_command(sn, oid, oidLen, this);
	case device_clock_source:
		return new TableDeviceCol_clk(sn, oid, oidLen, this);
	case device_active_card_number:
		return new TableDeviceCol_cardnum(sn, oid, oidLen, this);
	case device_remote_reset:
		return new TableDeviceCol_rmtreset(sn, oid, oidLen, this);
	case device_pcm_clock:
		return new TableDeviceCol_pcmclk(sn, oid, oidLen, this);
	default:
		return 0;
	}
}


int TableDevice::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
//	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
//	index->index[2]	= DeviceLocal::instance().GetSdhObject().GetFirstUid();
	return 1;
}
int TableDevice::getNextIndex(index_info_T* index) {
	return -1;
}

int TableDeviceCol_index::CallbackGet(const index_info_T& index) {
	return index.index[0];
}

int TableDeviceCol_name::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	*len = sizeof(ucGlbConstDeviceName);
	memcpy( buf, ucGlbConstDeviceName,  *len);
	return 1;
}


int TableDeviceCol_typeID::CallbackGet(const index_info_T& index) {
	return CCommonDefine::ucConstDeviceTypeID;
}

int TableDeviceCol_desc::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	uint8* desc = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceName(len);
	memcpy( buf, desc, *len);
	return 1;
}

int TableDeviceCol_status::CallbackGet(const index_info_T& index) {
	return 1;
}

int TableDeviceCol_netpos::CallbackGet(const index_info_T& index) {
	return 0;
}

int TableDeviceCol_chassis::CallbackGet(const index_info_T& index) {
	return 1;
}

int TableDeviceCol_slotnum::CallbackGet(const index_info_T& index) {
	return CCommonDefine::uiconstSlotNumber;
}

int TableDeviceCol_command::CallbackGet(const index_info_T& index, uint8*, uint32* len) {
	return -1;
}
int TableDeviceCol_command::callbackSet( const index_info_T& index, uint8*, uint32 len) {
	return -1;
}

int TableDeviceCol_clk::CallbackGet(const index_info_T& index) {
	return DeviceLocal::instance().GetDeviceAttributeObject().GetSysClock();
}

int TableDeviceCol_clk::callbackSet( const index_info_T& index, uint32 mode) {
	return DeviceLocal::instance().GetDeviceAttributeObject().SetSysClock(mode);
}

int TableDeviceCol_cardnum::CallbackGet(const index_info_T& index) {
	return 0;
}

int TableDeviceCol_rmtreset::callbackSet( const index_info_T& index, uint32 value) {
	ResetRemote(value);
	return 0x5A;
}

int TableDeviceCol_pcmclk::CallbackGet(const index_info_T& index) {
	return DeviceLocal::instance().GetDeviceAttributeObject().GetPcmClock();
}

int TableDeviceCol_pcmclk::callbackSet( const index_info_T& index, uint32 mode) {
	return DeviceLocal::instance().GetDeviceAttributeObject().SetPcmClock(mode);
}

