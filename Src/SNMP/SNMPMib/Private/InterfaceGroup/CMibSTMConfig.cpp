/*
 * CMibSTMConfig.cpp
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#include "CMibSTMConfig.h"
#include "DeviceLocal.h"
#include "SDHGroup.h"
#include "CCommonDefine.h"
#include <string>
#include <string.h>
#include "CSTM.h"

column_info_T CMibSTMConfig::colInfo[stm_cfg_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{5, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
		{6, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{7, Mib_read_write, CSnmpConstDefine::ucConstInteger32},

};



CMibSTMConfig::CMibSTMConfig(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibSTMConfig::~CMibSTMConfig() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibSTMConfig::getColInfo(int sn) {
	return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* CMibSTMConfig::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case stm_cfg_uid:
		return new CMibSTMConfigCol_uid(sn, oid, oidLen, this);
	case stm_cfg_name:
		return new CMibSTMConfigCol_name(sn, oid, oidLen, this);
	case stm_cfg_enable:
		return new CMibSTMConfigCol_enable(sn, oid, oidLen, this);
	case stm_cfg_als_enable:
		return new CMibSTMConfigCol_als(sn, oid, oidLen, this);
	case stm_cfg_port_backup:
		return new CMibSTMConfigCol_port_backup(sn, oid, oidLen, this);
	case stm_cfg_desc:
		return new CMibSTMConfigCol_desc(sn, oid, oidLen, this);
	case stm_cfg_als_mode:
		return new CMibSTMConfigCol_alsmode(sn, oid, oidLen, this);
	default:
		return 0;
	}
}


int CMibSTMConfig::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2]	= DeviceLocal::instance().GetSdhObject().GetFirstUid();
	return 1;
}
int CMibSTMConfig::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	index->index[1] = CCommonDefine::uiConstMainBoardIndex;
	index->index[2] = DeviceLocal::instance().GetSdhObject().GetNextUid(index->index[2]);
	if( index->index[2] == 0 ) {
		return -1;
	}
	return 1;

}


int CMibSTMConfigCol_uid::CallbackGet(const index_info_T& index) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		return index.index[2];
	}
	else {
		return -1;
	}
}

int CMibSTMConfigCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		std::string s = pstm->getName();
		*len = s.size();
		strcpy((char*)name, s.c_str());
		return 1;
	}
	return -1;
}

int CMibSTMConfigCol_enable::CallbackGet(const index_info_T& index) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		return pstm->getEnable();
	}
	return -1;
}

int CMibSTMConfigCol_enable::callbackSet( const index_info_T& index, uint32 en) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		pstm->setEnable((uint8)en);
		return 0x5A;
	}
	return -1;
}

//int CMibSTMConfigCol_als::CallbackGet(const index_info_T& index) {
//	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
//	if( pstm ) {
//		uint8 als = pstm->getAlsEnable();
//	}
//	return -1;
//}

//int CMibSTMConfigCol_als::callbackSet( const index_info_T& index, uint32 en) {
//	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
//	if( pstm ) {
//		pstm->setAlsEnable((uint8)en);
//		return 0x5A;
//	}
//	return -1;
//}

int CMibSTMConfigCol_als::CallbackGet(const index_info_T& index) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		return pstm->getAlsEnable();
	}
	return -1;
}
int CMibSTMConfigCol_als::callbackSet(  const index_info_T& index, uint32 data) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		pstm->setAls(data);
		return 0x5A;
	}
	return -1;
}



int CMibSTMConfigCol_port_backup::CallbackGet(const index_info_T& index) {
	return DeviceLocal::instance().GetSdhObject().getPortBackup();
}

int CMibSTMConfigCol_port_backup::callbackSet( const index_info_T& index, uint32 en) {
	DeviceLocal::instance().GetSdhObject().setPortBackup(en);
	return 0x5A;
}

int CMibSTMConfigCol_desc::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm ) {
		uint32 dlen = 0;
		uint8* p = pstm->getDescription(&dlen);
		if( p ) {
			*len = dlen;
			memcpy(desc, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}
int CMibSTMConfigCol_desc::callbackSet(const index_info_T& index, uint8*desc, uint32 len) {
	CSTM* pstm = DeviceLocal::instance().GetSdhObject().GetStmObjByUid(index.index[2]);
	if( pstm != 0 && len < 31) {
		pstm->setDescription(desc, (uint8)len);
		return 0x5A;
	}
	return -1;
}


int CMibSTMConfigCol_alsmode::CallbackGet(const index_info_T& index) {
	return DeviceLocal::instance().GetSdhObject().getALSMode();
}
int CMibSTMConfigCol_alsmode::callbackSet(  const index_info_T& index, uint32 data) {
	DeviceLocal::instance().GetSdhObject().setALSMode(data);
	return 0x5A;
}

