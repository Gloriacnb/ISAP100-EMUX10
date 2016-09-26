/*
 * CMibTableColumn.cpp
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#include "CMibTableColumn.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CCommonDefine.h"
#include "CMibTable.h"
#include <string.h>

CMibTableColumn::CMibTableColumn(int sn, uint32* oid, uint32 oidLen, CMibTable* uptable)
		: CMibColumn(oid, oidLen){
	table = uptable;
	col_info = table->getColInfo(sn);
	table_Info = table->getTableInfo();
	oid_len = oidLen + table->getTableInfo()->table_index_num;
	pos_index_begin = oidLen;
	pos_col = oidLen - 1;
}

CMibTableColumn::~CMibTableColumn() {
	// TODO Auto-generated destructor stub
}

uint32 CMibTableColumn::GetResponse(CSnmpCell* objpCell) {
	if( objpCell == 0  || col_info->col_access == Mib_write_only){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != oid_len || uipInOID[pos_index_begin] != CCommonDefine::uiConstDeviceIndex
			|| uipInOID[pos_col] != col_info->col_sn ){//长度和oid校验
		return CErrorValueDefine::uiConstReturnFailed;
	}

	index_info_T index;
	try {
		index = extractIndex(objpCell);
	}
	catch( uint32 error ) {
		return error;
	}

	switch( col_info->col_value_type ) {
	case CSnmpConstDefine::ucConstInteger32: {

		int result = CallbackGet(index);
		if( result < 0 ) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		CSnmpVariable objResponse(result);
		objpCell->SetResponse(objpOID,&objResponse);
	}
		break;
	case CSnmpConstDefine::ucConstOctetString: {

		uint32 len;
		uint8 buf[Max_value_octect_size];
		int result = CallbackGet(index, buf, &len);;
		if( result < 0 ) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		CSnmpVariable objResponse(buf, len, CSnmpConstDefine::ucConstOctetString);
		objpCell->SetResponse(objpOID,&objResponse);
	}
		break;
	default:
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


uint32 CMibTableColumn::SetResponse(CSnmpCell* objpCell) {
	if( objpCell == 0 || col_info->col_access == Mib_read_only ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != oid_len || uipInOID[pos_index_begin] != CCommonDefine::uiConstDeviceIndex
			|| uipInOID[pos_col] != col_info->col_sn){//长度和oid校验
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
	if( objInvalue->GetSyntax() != col_info->col_value_type ){//类型错误
		objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
		return CErrorValueDefine::uiConstReturnSuccess;
	}

	index_info_T index;
	try {
		index = extractIndex(objpCell);
	}
	catch( uint32 error ) {
		return error;
	}
	switch( col_info->col_value_type ) {
	case CSnmpConstDefine::ucConstInteger32: {

		int result = callbackSet( index, objInvalue->GetInteger32Value() );
		if( result < 0 ) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		CSnmpVariable objResponse(result);
		objpCell->SetResponse(objpOID,&objResponse);
	}
		break;
	case CSnmpConstDefine::ucConstOctetString: {

		uint32 len;
		uint8* buf = objInvalue->GetStringValue(&len);
		int result = callbackSet(index, buf, len);
		if( result < 0 ) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		CSnmpVariable objResponse(result);
		objpCell->SetResponse(objpOID,&objResponse);
	}
		break;
	default:
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*
 * 注意 getnext操作的最小单位为列，
 */
uint32 CMibTableColumn::GetFirstValidOID(CSnmpCell* objpCell) {
	index_info_T index;
	int result = table->getFirstIndex(&index);
	if( result < 0 || index.index_number != table_Info->table_index_num) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	makeoid(index, objpCell);
	return CErrorValueDefine::uiConstReturnSuccess;
}
uint32 CMibTableColumn::GetNextValidOID(CSnmpCell* objpCell) {

	index_info_T index;
	try{
		index = extractIndex(objpCell);
	}
	catch( uint32 error ) {
		return error;
	}
	int result = table->getNextIndex(&index);
	if( result < 0 ) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	makeoid(index, objpCell);
	return CErrorValueDefine::uiConstReturnSuccess;
}

void CMibTableColumn::makeoid(index_info_T& iInfo, CSnmpCell* objpCell) {
	uint32 coloidLen = 0;
	uint32* coloid = getVariable().GetOIDValue(&coloidLen);
	//uint32 oid[Max_oid_size];
	if( !coloid ) {
		return;
	}
	uint32 rLen = coloidLen + iInfo.index_number;
	uint32* oid = new uint32[rLen];
	for( int i = 0; i < coloidLen; i++ ) {
		oid[i] = coloid[i];
	}
	for( int i = 0; i < iInfo.index_number; i++ ) {
		oid[i+coloidLen] = iInfo.index[i];
	}
//	memcpy(oid, coloid, coloidLen*4);
//	memcpy(&oid[coloidLen], iInfo.index, iInfo.index_number*4);
	CSnmpVariable objFirst(oid,rLen);
	objpCell->GetCurrentVariable()->Clone(&objFirst);
	delete []oid;
}

index_info_T CMibTableColumn::extractIndex(CSnmpCell* objpCell) {
	CSnmpVariable* objTemp = objpCell->GetCurrentVariable();
	uint32 uiBaseLen = 0;
	uint32* uipBaseOID = objTemp->GetOIDValue(&uiBaseLen);

	if( uiBaseLen <= pos_index_begin ) {
		//return CErrorValueDefine::uiConstReturnFailed;
		throw CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	uint32 idLen = uiBaseLen-pos_index_begin;
	if( idLen > table_Info->table_index_num ) {
		idLen = table_Info->table_index_num;
	}
	index_info_T index = {
			idLen,
			{0}
	};
	memcpy(index.index, &uipBaseOID[pos_index_begin], idLen*4);
	return index;
}

/*
 * 默认虚函数实现
 */
int CMibTableColumn::CallbackGet(const index_info_T& index) {
	return -1;
}
int CMibTableColumn::CallbackGet(const index_info_T& index, uint8*, uint32* len) {
	return -1;
}

/*
 * 派生类需根据自己的值类型实现以下函数之一。
 */
int CMibTableColumn::callbackSet( const index_info_T& index, uint32 ) {
	return -1;
}
int CMibTableColumn::callbackSet( const index_info_T& index, uint8*, uint32 len) {
	return -1;
}


