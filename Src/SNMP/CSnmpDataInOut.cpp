/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpDataInOut.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-1
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CSnmpDataInOut.h"
#include "CErrorValueDefine.h"
#include "CSnmpCommand.h"
#include "CClassPointer.h"
//extern CClassPointer objGlbClassPointer;
/**********************************************************************************************************************
** Function name:			CSnmpDataInOut
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-01
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CSnmpDataInOut::CSnmpDataInOut()
{
	objpSnmpMib = NULL;					//上级SNMP和MIB对象指针
}
/**********************************************************************************************************************
** Function name:			~CSnmpDataInOut
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-01
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CSnmpDataInOut::~CSnmpDataInOut()
{
}
/**********************************************************************************************************************
** Function name:			InitialClassObject
** Descriptions:			初始化类对象，类使用前必须调用
** input parameters:		objpIn：			SNMP和MIB对象指针
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-1
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpDataInOut::InitialClassObject(CSnmpMib* objpIn)
{
	if(objpIn == NULL){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	objpSnmpMib = objpIn;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			InitialClassObject
** Descriptions:			接收数据
** input parameters:		objpUDPInterface：	UDP数据包接收源对象
** 							objData：			UDP数据包对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-1
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpDataInOut::ReceiverData(CUDPData* objData)
{
	if( objData == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	//创建对象
	CSnmpCommand* objpSnmp = new CSnmpCommand(this);
	if( objpSnmp == NULL){
		return CErrorValueDefine::uiConstReturnFailed;
	}
//	objpSnmp->SetUDPInterface(objpUDPInterface);
	objpSnmp->SetUDPData(objData);

	return objpSnmp->StartMibSearch();

//	//初始化对象
//	if( objpSnmp->InitialObject(objpUDPInterface,objData) != CErrorValueDefine::uiConstReturnSuccess){
//		objpSnmp->EventDestory();
//		//delete objpSnmp;
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	//注册任务
//	CTaskScheduling* objpTaskScheduling = objGlbClassPointer.GetTaskSchedulingPointer();
//	if( objpTaskScheduling!= NULL ){
//		objpTaskScheduling->RegisterTask(objpSnmp,0);
//	}
//	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			InitialClassObject
** Descriptions:			获得SNMP响应数据包缓存Buffer
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP响应数据包缓存Buffer
** Created by:				WangChangRong
** Created date:			2011-8-4
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CSnmpDataInOut::GetResponseBuffer()
{
	return ucResponseBuffer;
}
