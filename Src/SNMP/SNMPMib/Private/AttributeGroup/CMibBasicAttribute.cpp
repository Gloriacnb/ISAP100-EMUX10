/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibBasicAttribute.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-24
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CMibBasicAttribute.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CCommonDefine.h"
//#include "CClassPointer.h"
//#include "CMain.h"
#include "DeviceLocal.h"
#include "Task_define.h"
#include <string.h>

//extern CClassPointer objGlbClassPointer;
/**********************************************************************************************************************
** Function name:			CMibBasicAttribute
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibBasicAttribute::CMibBasicAttribute()
{
}
/**********************************************************************************************************************
** Function name:			~CMibBasicAttribute
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibBasicAttribute::~CMibBasicAttribute()
{
}
/**********************************************************************************************************************
** Function name:			InitialGroup
** Descriptions:			初始化标准组中对象
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibBasicAttribute::InitialGroup()
{
	//初始化
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,9,1,1,1};
	CSnmpVariable objMib(uiInOID,11);
	InitialNode(&objMib);

	{//初始化基本属性表
		for( uint32 i=0;i<12;i++ ){//10个成员
			CMibBasicAttributeColumn* objpColumn = new CMibBasicAttributeColumn();
			uiInOID[12] = i+1;
			CSnmpVariable objMib(uiInOID,13);
			objpColumn->InitialNode(&objMib);
			InsertDownLinkNode(objpColumn);
		}
	}

	return CErrorValueDefine::uiConstReturnSuccess;


}

/**********************************************************************************************************************
** Function name:			CMibBasicAttributeColumn
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibBasicAttributeColumn::CMibBasicAttributeColumn()
{
}
/**********************************************************************************************************************
** Function name:			~CMibElementColumn
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibBasicAttributeColumn::~CMibBasicAttributeColumn()
{
}


/**********************************************************************************************************************
** Function name:			GetResponse
** Descriptions:			Get的响应方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibBasicAttributeColumn::GetResponse(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 14 || uipInOID[13] != CCommonDefine::uiConstDeviceIndex ){//长度和oid校验
		return CErrorValueDefine::uiConstReturnFailed;
	}
 	switch( uipInOID[12] ){//分类
 		case 1://eciDPBasicDeviceName
 		{
 			uint32 uiLen  =7 ;
 			uint8* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceName(&uiLen);
 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 2://eciDPBasicUser
 		{
 			uint32 uiLen  =0 ;
 			uint8* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceUser(&uiLen);
 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 3://eciDPBasicDesc
 		{
 			uint32 uiLen  =0 ;
 			uint8* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceDescription(&uiLen);
 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 4://eciDPBasicOther
 		{
 			uint32 uiLen  =0 ;
 			uint8* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceBaseOther(&uiLen);
 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 5://eciDPBasicContact
 		{
 			uint32 uiLen  =0 ;
 			uint8* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceContact(&uiLen);
 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 6://eciDPBasicLocation
 		{
 			uint32 uiLen  =0 ;
 			uint8* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceLocation(&uiLen);
 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 7://eciDPBasicSoftwareReset
 		case 8://eciDPBasicHardwareReset
 		case 9://eciDPBasicDeviceReset
 			break;
 		case 10://eciDPBasicDefaultSetting
 		{
 			CSnmpVariable objResponse(0);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 //		break;
 		case 11: {
 			char* ucBuf = DeviceLocal::instance().GetDeviceAttributeObject().GetProductionDate();
 			CSnmpVariable objResponse((uint8*)ucBuf,strlen(ucBuf),CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 12: {
 			uint16 sn = DeviceLocal::instance().GetDeviceAttributeObject().GetSerialNumber();
 			CSnmpVariable objResponse(sn);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;

 		}
 	}
	return CErrorValueDefine::uiConstReturnFailed;
}


/**********************************************************************************************************************
** Function name:			SetResponse
** Descriptions:			Set的响应方法
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibBasicAttributeColumn::SetResponse(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 14 || uipInOID[13] != CCommonDefine::uiConstDeviceIndex ){//长度和oid校验
		return CErrorValueDefine::uiConstReturnFailed;
	}
 	switch( uipInOID[12] ){//分类
 		case 1://eciDPBasicDeviceName
 		{
 			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
 			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//类型错误
 				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
 				return CErrorValueDefine::uiConstReturnSuccess;
 			}
 			uint32 uiTempLen = 0;
 			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
 			uint32 uiRet = DeviceLocal::instance().GetDeviceAttributeObject().SetDeviceName(ucpTempBuf,uiTempLen);
 			CSnmpVariable objResponse(uiRet);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 2://eciDPBasicUser
 		{
 			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
 			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//类型错误
 				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
 				return CErrorValueDefine::uiConstReturnSuccess;
 			}
 			uint32 uiTempLen = 0;
 			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
 			uint32 uiRet = DeviceLocal::instance().GetDeviceAttributeObject().SetDeviceUser(ucpTempBuf,uiTempLen);
 			CSnmpVariable objResponse(uiRet);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 3://eciDPBasicDesc
 		{
 			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
 			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//类型错误
 				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
 				return CErrorValueDefine::uiConstReturnSuccess;
 			}
 			uint32 uiTempLen = 0;
 			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
 			uint32 uiRet = DeviceLocal::instance().GetDeviceAttributeObject().SetDeviceDescription(ucpTempBuf,uiTempLen);
 			CSnmpVariable objResponse(uiRet);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 4://eciDPBasicOther
 		{
 			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
 			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//类型错误
 				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
 				return CErrorValueDefine::uiConstReturnSuccess;
 			}
 			uint32 uiTempLen = 0;
 			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
 			uint32 uiRet = DeviceLocal::instance().GetDeviceAttributeObject().SetDeviceBaseOther(ucpTempBuf,uiTempLen);
 			CSnmpVariable objResponse(uiRet);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 5://eciDPBasicContact
 		{
 			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
 			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//类型错误
 				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
 				return CErrorValueDefine::uiConstReturnSuccess;
 			}
 			uint32 uiTempLen = 0;
 			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
 			uint32 uiRet = DeviceLocal::instance().GetDeviceAttributeObject().SetDeviceContact(ucpTempBuf,uiTempLen);
 			CSnmpVariable objResponse(uiRet);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 6://eciDPBasicLocation
 		{
 			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
 			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//类型错误
 				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
 				return CErrorValueDefine::uiConstReturnSuccess;
 			}
 			uint32 uiTempLen = 0;
 			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
 			uint32 uiRet = DeviceLocal::instance().GetDeviceAttributeObject().SetDeviceLocation(ucpTempBuf,uiTempLen);
 			CSnmpVariable objResponse(uiRet);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 		case 9://eciDPBasicDeviceReset
 			break;
 		case 7: {//eciDPBasicSoftwareReset
			os_evt_set(0x0001, t_reset);
 			CSnmpVariable objResponse(0x5A);
			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
		}

 		case 8: {//eciDPBasicHardwareReset
			os_evt_set(0x0002, t_reset);
 			CSnmpVariable objResponse(0x5A);
			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
		}
 		case 10://eciDPBasicDefaultSetting
 			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorNotWriteable);
 			return CErrorValueDefine::uiConstReturnSuccess;
// 		break;
 	}

	return CErrorValueDefine::uiConstReturnFailed;
}
/**********************************************************************************************************************
** Function name:			GetFirstValidOID
** Descriptions:			GetNext调用方法1：获得第一个对象的OID
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibBasicAttributeColumn::GetFirstValidOID(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable* objpSelf = GetNodeOIDVariable();
	if( objpSelf == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiSelfOIDLength = 0;
	uint32* uipOID = objpSelf->GetOIDValue(&uiSelfOIDLength);


	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,9,1,1,1,0};
	uiInOID[12] = uipOID[12];
	uiInOID[13] = CCommonDefine::uiConstDeviceIndex;
	CSnmpVariable objFirst(uiInOID,14);
	objpCell->GetCurrentVariable()->Clone(&objFirst);

	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			GetNextValidOID
** Descriptions:			GetNext调用方法2：获得下一个对象的OID
** input parameters:		objpCell：		SNMP命令对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							正在处理返回CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibBasicAttributeColumn::GetNextValidOID(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable objTemp;
	objTemp.Clone(objpCell->GetCurrentVariable());
	uint32 uiBaseLen = 0;
	uint32* uipBaseOID = objTemp.GetOIDValue(&uiBaseLen);
	for(uint32 i=uiBaseLen;i<14;i++){
		uipBaseOID[i] = 0;
	}
	if( uipBaseOID[13] < CCommonDefine::uiConstDeviceIndex){
		uipBaseOID[13] = CCommonDefine::uiConstDeviceIndex;
		CSnmpVariable objNext(uipBaseOID,14);
		objpCell->GetCurrentVariable()->Clone(&objNext);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;

}
