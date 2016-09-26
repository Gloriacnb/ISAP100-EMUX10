/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibDateAttribute.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-30
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CMibDateAttribute.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CCommonDefine.h"
#include "CClassPointer.h"
#include "RTC.h"
#include "ChipLM75A.h"
/**********************************************************************************************************************
** Function name:			CMibDateAttribute
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibDateAttribute::CMibDateAttribute() {
}

/**********************************************************************************************************************
** Function name:			~CMibDateAttribute
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibDateAttribute::~CMibDateAttribute() {
}
/**********************************************************************************************************************
** Function name:			InitialGroup
** Descriptions:			初始化标准组中对象
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibDateAttribute::InitialGroup()
{
	//初始化
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,9,3,1,1,1};
	CSnmpVariable objMib(uiInOID,11);
	InitialNode(&objMib);

	{//初始化基本属性表
		for( uint32 i = 0; i < 3; i++ ){//3个成员
			CMibDateAttributeColumn* objpColumn = new CMibDateAttributeColumn();
			uiInOID[12] = i+1;
			CSnmpVariable objMib(uiInOID,13);
			objpColumn->InitialNode(&objMib);
			InsertDownLinkNode(objpColumn);
		}
	}

	return CErrorValueDefine::uiConstReturnSuccess;


}

/**********************************************************************************************************************
** Function name:			CMibDateAttributeColumn
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibDateAttributeColumn::CMibDateAttributeColumn()
{
}
/**********************************************************************************************************************
** Function name:			~CMibDateAttributeColumn
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibDateAttributeColumn::~CMibDateAttributeColumn()
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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibDateAttributeColumn::GetResponse(CSnmpCell* objpCell)
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
		case 1://eciDPCurrentTime
		{
			std::string Temp = RTC::getCurrentStringTime();
			CSnmpVariable objResponse((unsigned char*)Temp.c_str(),Temp.size(), CSnmpConstDefine::ucConstOctetString);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		case 2:
		{
			uint32 time = RTC::getCurrentSecsTime();
			CSnmpVariable objResponse(time);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		case 3:	//temperature
		{
			uint32 temp = ChipLM75A::getDeviceTemperature();
			CSnmpVariable objResponse(temp);
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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibDateAttributeColumn::SetResponse(CSnmpCell* objpCell)
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
 	switch (uipInOID[12]) {//分类
		case 2://UTC
		{
			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstInteger32 ){//类型错误
				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
				return CErrorValueDefine::uiConstReturnSuccess;
			}
			uint32 Temp = objInvalue->GetInteger32Value();
			RTC::setUTC(Temp);
			CSnmpVariable objResponse(0x5A);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}

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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibDateAttributeColumn::GetFirstValidOID(CSnmpCell* objpCell)
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


	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,9,3,1,1,1,0};
	uiInOID[13] = uipOID[13];
	uiInOID[14] = CCommonDefine::uiConstDeviceIndex;
	CSnmpVariable objFirst(uiInOID,15);
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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibDateAttributeColumn::GetNextValidOID(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable objTemp;
	objTemp.Clone(objpCell->GetCurrentVariable());
	uint32 uiBaseLen = 0;
	uint32* uipBaseOID = objTemp.GetOIDValue(&uiBaseLen);
	for(uint32 i=uiBaseLen;i<15;i++){
		uipBaseOID[i] = 0;
	}
	if( uipBaseOID[14] < CCommonDefine::uiConstDeviceIndex){
		uipBaseOID[14] = CCommonDefine::uiConstDeviceIndex;
		CSnmpVariable objNext(uipBaseOID,15);
		objpCell->GetCurrentVariable()->Clone(&objNext);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;

}
