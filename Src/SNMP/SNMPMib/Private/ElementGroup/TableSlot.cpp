/*
 * TableSlot.cpp
 *
 *  Created on: 2013-7-10
 *      Author: Administrator
 */

#include "TableSlot.h"
#include "CCommonDefine.h"
#include "CBaseSlot.h"
#include "DeviceLocal.h"
#include "CBaseCard.h"
#include "CSlotManager.h"
#include <string.h>

column_info_T TableSlot::colInfo[table_slot_columns] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{5, Mib_read_only, CSnmpConstDefine::ucConstInteger32},

};


TableSlot::TableSlot(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

TableSlot::~TableSlot() {
	// TODO Auto-generated destructor stub
}

column_info_T* TableSlot::getColInfo(int sn) {
	return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* TableSlot::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case slot_index:
		return new TableSlotCol_index(sn, oid, oidLen, this);
	case card_name:
		return new TableSlotCol_name(sn, oid, oidLen, this);
	case card_typeID:
		return new TableSlotCol_typeID(sn, oid, oidLen, this);
	case card_desc:
		return new TableSlotCol_desc(sn, oid, oidLen, this);
	case card_status:
		return new TableSlotCol_status(sn, oid, oidLen, this);
	default:
		return 0;
	}
}


int TableSlot::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = 1;
//	index->index[2]	= DeviceLocal::instance().GetSdhObject().GetFirstUid();
	return 1;
}
int TableSlot::getNextIndex(index_info_T* index) {
	if( index->index[1] >= 6 ) {
		return -1;
	}
	index->index[1] += 1;
	return 1;
}


int TableSlotCol_index::CallbackGet(const index_info_T& index) {
	return index.index[1];
}

int TableSlotCol_name::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	CBaseSlot* objpSlot = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index.index[1]-1);
	if( objpSlot ) {
		CBaseCard* objpCard = objpSlot->GetCardObject();
		if( objpCard ) {
			std::string& name = objpCard->GetName();
			*len = name.size();
			memcpy( buf, name.c_str(), *len );
		}
		else {
			char s[] = "No Card.";
			*len = sizeof(s);
			memcpy( buf, s, *len );
		}
		return 1;
	}
	return -1;
}

int TableSlotCol_typeID::CallbackGet(const index_info_T& index) {
	CBaseSlot* objpSlot = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index.index[1]-1);
	if( objpSlot ) {
		CBaseCard* objpCard = objpSlot->GetCardObject();
		if( objpCard ) {
			return objpCard->GetCartTypeID();
		}
		else {
			return 0;
		}
	}
	return -1;

}

int TableSlotCol_desc::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	CBaseSlot* objpSlot = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index.index[1]-1);
	if( objpSlot ) {
		CBaseCard* objpCard = objpSlot->GetCardObject();
		if( objpCard ) {
			std::string& desc = objpCard->GetCardDescr();
			*len = desc.size();
			memcpy( buf, desc.c_str(), *len );
		}
		else {
			char s[] = "No Card.";
			*len = sizeof(s);
			memcpy( buf, s, *len );
		}
		return 1;
	}
	return -1;
}

int TableSlotCol_status::CallbackGet(const index_info_T& index) {
	CBaseSlot* objpSlot = DeviceLocal::instance().GetSlotManager().GetSlotBySn(index.index[1]-1);
	if( objpSlot ) {
		CBaseCard* objpCard = objpSlot->GetCardObject();
		if( objpCard ) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return -1;
}

