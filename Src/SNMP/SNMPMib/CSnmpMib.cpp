/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpMib.cpp
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

#include "CSnmpMib.h"
#include "CErrorValueDefine.h"
//#include "CCommunication.h"
/**********************************************************************************************************************
** Function name:			CSnmpMib
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
CSnmpMib::CSnmpMib()
{
//	objpCommunication = NULL;				//上级通信对象指针

}
/**********************************************************************************************************************
** Function name:			~CSnmpMib
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
CSnmpMib::~CSnmpMib()
{
}
/**********************************************************************************************************************
** Function name:			InitialClass
** Descriptions:			初始化类对象，类使用前必须调用
** input parameters:		objpIn：			通信对象指针
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
uint32 CSnmpMib::InitialClassObject(void/*CCommunication* objpIn*/)
{
//	if(objpIn == NULL){
//		return CErrorValueDefine::uiConstReturnInputNULLPointer;
//	}
//	objpCommunication = objpIn;
	objDataInOut.InitialClassObject(this);
	objMibImpl.InitialClassObject(this);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			GetCommunication
** Descriptions:			获得上级通信对象指针
** input parameters:		None
** output parameters:		None
** Returned value:			上级通信对象指针
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//CCommunication* CSnmpMib::GetCommunication()
//{
//	return objpCommunication;
//}

/**********************************************************************************************************************
** Function name:			GetSnmpDataInOut
** Descriptions:			获得SNMP数据输入输出对象
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP数据输入输出对象
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CSnmpDataInOut* CSnmpMib::GetSnmpDataInOut()
{
	return &objDataInOut;
}

/**********************************************************************************************************************
** Function name:			GetMibImpl
** Descriptions:			获得MIB库实现
** input parameters:		None
** output parameters:		None
** Returned value:			MIB库实现
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibImpl* CSnmpMib::GetMibImpl()
{
	return &objMibImpl;
}

