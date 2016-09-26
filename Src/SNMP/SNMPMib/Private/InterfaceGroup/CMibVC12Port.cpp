/*
 * CMibVC12Port.cpp
 *
 *  Created on: 2013-3-3
 *      Author: Administrator
 */

#include "CMibVC12Port.h"
#include "CSnmpCell.h"
#include "CSTM.h"
#include "CVC12.h"
#include "CErrorValueDefine.h"
#include "CCommonDefine.h"
#include "CSnmpConstDefine.h"

CMibVC12Port::CMibVC12Port() {
	// TODO Auto-generated constructor stub

}

CMibVC12Port::~CMibVC12Port() {
	// TODO Auto-generated destructor stub
}

uint32 CMibVC12Port::InitialGroup(void) {
	//初始化
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,8,3,2,1,0};
	CSnmpVariable objMib(uiInOID,12);
	InitialNode(&objMib);

	//初始化列
	for( uint32 i=0; i < 6;i++ ){//6个成员
		CMibColumn* objpColumn = new CMibVC12PortColumn();
		uiInOID[13] = i+1;
		CSnmpVariable objMib(uiInOID,14);
		objpColumn->InitialNode(&objMib);
		InsertDownLinkNode(objpColumn);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


uint32 CMibVC12PortColumn::GetResponse(CSnmpCell* objpCell) {
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 17 || uipInOID[14] != CCommonDefine::uiConstDeviceIndex ){//长度和oid校验
		return CErrorValueDefine::uiConstReturnFailed;
	}
	switch( uipInOID[13] ){//分类
		case 1: {  //eciIfMdVC12ChannelIndex
			CSnmpVariable objResponse(uipInOID[16]);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		case 2: {   //eciIfMdVC12ChannelName
			CVC12* pvc12 = CSTM::GetVc12Object(uipInOID[16]);
			if( pvc12 ) {
				std::string name = pvc12->getName();
				CSnmpVariable objResponse((uint8*)name.c_str(), name.size(), CSnmpConstDefine::ucConstOctetString);
				objpCell->SetResponse(objpOID,&objResponse);
				return CErrorValueDefine::uiConstReturnSuccess;
			}
		}
			break;
		case 3:   //eciIfMdVC12ChannelSerialN
			break;
		case 4:  { //eciIfMdVC12ChannelMappingIndex
			CVC12* pvc12 = CSTM::GetVc12Object(uipInOID[16]);
			if( pvc12 ) {
				CSnmpVariable objResponse(pvc12->GetMappingPartner());
				objpCell->SetResponse(objpOID,&objResponse);
				return CErrorValueDefine::uiConstReturnSuccess;
			}
		}
			break;
		case 5:   //eciIfMdVC12ChannelSNCPEnable
			break;
		case 6:   //eciIfMdVC12ChannelSNCPMappingIndex
			break;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}
//Set的响应方法
uint32 CMibVC12PortColumn::SetResponse(CSnmpCell* objpCell) {
	return CErrorValueDefine::uiConstReturnFailed;
}
//GetNext调用方法1：获得第一个对象的OID
uint32 CMibVC12PortColumn::GetFirstValidOID(CSnmpCell* objpCell) {
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable* objpSelf = GetNodeOIDVariable();
	if( objpSelf == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiSelfOIDLength = 0;
	uint32* uipOID = objpSelf->GetOIDValue(&uiSelfOIDLength);


	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,8,3,2,1,0,0,0,0};
	uiInOID[13] = uipOID[13];
	uiInOID[14] = CCommonDefine::uiConstDeviceIndex;
	uiInOID[15] = CCommonDefine::uiConstMainBoardIndex;
	uiInOID[16] = CSTM::GetFirstVC12Uid();
	CSnmpVariable objFirst(uiInOID,17);
	objpCell->GetCurrentVariable()->Clone(&objFirst);
	return CErrorValueDefine::uiConstReturnSuccess;
}
//GetNext调用方法2：获得下一个对象的OID
uint32 CMibVC12PortColumn::GetNextValidOID(CSnmpCell* objpCell) {
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable objTemp;
	objTemp.Clone(objpCell->GetCurrentVariable());
	uint32 uiBaseLen = 0;
	uint32* uipBaseOID = objTemp.GetOIDValue(&uiBaseLen);
	for(uint32 i=uiBaseLen;i<17;i++){
		uipBaseOID[i] = 0;
	}

	if( uipBaseOID[14] < CCommonDefine::uiConstDeviceIndex
			|| uipBaseOID[15] < CCommonDefine::uiConstMainBoardIndex ) {
		return GetFirstValidOID(objpCell);
	}
	uint32 firstuid = CSTM::GetFirstVC12Uid();
	if( uipBaseOID[16] < firstuid ) {
		return GetFirstValidOID(objpCell);
	}
	uint32 nextuid = CSTM::GetNextVC12Uid(uipBaseOID[16]);
	if( nextuid != 0 ) {
		uipBaseOID[14] = CCommonDefine::uiConstDeviceIndex;
		uipBaseOID[15] = nextuid >> 24;
		uipBaseOID[16] = nextuid;
		CSnmpVariable objNext(uipBaseOID,17);
		objpCell->GetCurrentVariable()->Clone(&objNext);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}
