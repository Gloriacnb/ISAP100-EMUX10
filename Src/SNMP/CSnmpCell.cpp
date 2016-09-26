/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpCell.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-2
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CSnmpCell.h"
#include "CClassPointer.h"
#include "CSnmpCommand.h"
#include "CErrorValueDefine.h"
#include "CMibImpl.h"
//extern CClassPointer objGlbClassPointer;

/**********************************************************************************************************************
 ** Function name:			CSnmpCell
 ** Descriptions:			类构造函数
 ** input parameters:		objpIn：			SNMP命令对象指针
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/

CSnmpCell::CSnmpCell(CSnmpCommand* objpIn) {
	objpCommand = objpIn;						//所属的SNMP命令对象
	ucErrorStatus = CSnmpConstDefine::ucConstSnmpErrorSuccess;			//差错状态
}
/**********************************************************************************************************************
 ** Function name:			~CSnmpCell
 ** Descriptions:			类析构函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/

CSnmpCell::~CSnmpCell() {
}

/**********************************************************************************************************************
 ** Function name:			GetSnmpCommand
 ** Descriptions:			获得SNMP命令对象
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			SNMP命令对象
 ** Created by:				WangChangRong
 ** Created date:			2011-08-08
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpCommand* CSnmpCell::GetSnmpCommand() {
	return objpCommand;
}

/**********************************************************************************************************************
 ** Function name:			GetRequestVB
 ** Descriptions:			获得请求VB对象
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			请求VB对象
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariableBinding* CSnmpCell::GetRequestVB() {
	return &objRequestVB;
}

/**********************************************************************************************************************
 ** Function name:			GetCurrentVariable
 ** Descriptions:			获得正在处理的变量对象
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			正在处理的VB对象
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable* CSnmpCell::GetCurrentVariable() {
	return &objCurrentVariable;
}

/**********************************************************************************************************************
 ** Function name:			GetResponseVB
 ** Descriptions:			获得响应VB对象
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			响应VB对象
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariableBinding* CSnmpCell::GetResponseVB() {
	return &objResponseVB;
}
/**********************************************************************************************************************
 ** Function name:			GetErrorStatus
 ** Descriptions:			获得差错状态
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			差错状态
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8 CSnmpCell::GetErrorStatus() {
	return ucErrorStatus;
}
/**********************************************************************************************************************
 ** Function name:			GetRequestVB
 ** Descriptions:			启动MIB检索和查询，获取响应
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/

uint32 CSnmpCell::StartMibSearch() {
	//Get、Set、GetNext处理

	CMibImpl* objpMib = CClassPointer::GetMibImplPointer();
	if (objpMib == NULL) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	objCurrentVariable.Clone(objRequestVB.GetOIDObject());
	uint32 uiRet = CErrorValueDefine::uiConstReturnFailed;
	if (objpCommand->GetCurrentRequestType() == CSnmpConstDefine::ucConstGet
			|| objpCommand->GetCurrentRequestType()
					== CSnmpConstDefine::ucConstSet) {
		uiRet = objpMib->GetSetMibSearch(this);
		if (uiRet != CErrorValueDefine::uiConstReturnSuccess
				&& uiRet != CErrorValueDefine::uiConstReturnProcessing) {
			CSnmpVariable objNoSuch;
			objNoSuch.SetSyntax(CSnmpConstDefine::ucConstNoSuchObject);
			SetResponse(objRequestVB.GetOIDObject(), &objNoSuch);
			//SetErrorResponse(objRequestVB.GetOIDObject(),CSnmpConstDefine::ucConstSnmpErrorNoSuchName);
		}
		if (uiRet == CErrorValueDefine::uiConstReturnProcessing) {
			return uiRet;
		}
	} else if (objpCommand->GetCurrentRequestType()
			== CSnmpConstDefine::ucConstGetNext) {
		uiRet = objpMib->GetNextMibSearch(this);
		if (uiRet != CErrorValueDefine::uiConstReturnSuccess
				&& uiRet != CErrorValueDefine::uiConstReturnProcessing) {
			CSnmpVariable objEndMib;
			objEndMib.SetSyntax(CSnmpConstDefine::ucConstEndofMibView);
			SetResponse(objRequestVB.GetOIDObject(), &objEndMib);
		}
		if (uiRet == CErrorValueDefine::uiConstReturnProcessing) {
			return uiRet;
		}
	} else {
	}

	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			SetResponse
 ** Descriptions:			设置响应
 ** input parameters:		objpOID：	响应的OID
 ** 							objpValue：	响应的值
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
 ** Created by:				WangChangRong
 ** Created date:			2011-08-09
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpCell::SetResponse(CSnmpVariable* objpOID,
		CSnmpVariable* objpValue) {
	if (objpOID == NULL || objpValue == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	objResponseVB.GetOIDObject()->Clone(objpOID);
	objResponseVB.GetValueObject()->Clone(objpValue);
//	SetThreadTaskStatus(CThreadTask::uiThreadTaskStatusSuccess);
	ucErrorStatus = CSnmpConstDefine::ucConstSnmpErrorSuccess;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			SetErrorResponse
 ** Descriptions:			设置错误响应
 ** input parameters:		objpOID：	响应的OID
 ** 							ucError：	错误类型，取值参见CSnmpConstDefine类定义
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
 ** Created by:				WangChangRong
 ** Created date:			2011-08-09
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpCell::SetErrorResponse(CSnmpVariable* objpOID, uint8 ucError) {
	if (objpOID == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	objResponseVB.GetOIDObject()->Clone(objpOID);
	CSnmpVariable objNull;
	objNull.SetSyntax(CSnmpConstDefine::ucConstNull);
	objResponseVB.GetValueObject()->Clone(&objNull);
//	SetThreadTaskStatus(CThreadTask::uiThreadTaskStatusSuccess);
	ucErrorStatus = ucError;
	return CErrorValueDefine::uiConstReturnSuccess;

}
//设置请求
/**********************************************************************************************************************
 ** Function name:			SetResponse
 ** Descriptions:			设置响应
 ** input parameters:		objpOID：	响应的OID
 ** 							objpValue：	响应的值
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
 ** Created by:				WangChangRong
 ** Created date:			2011-08-09
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpCell::SetRequest(CSnmpVariable* objpOID, CSnmpVariable* objpValue) {
	if (objpOID == NULL || objpValue == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	objResponseVB.GetOIDObject()->Clone(objpOID);
	objResponseVB.GetValueObject()->Clone(objpValue);
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			Notify
 ** Descriptions:			任务唤醒
 ** 							只对伪线程任务有效，对定时任务、高优先级任务和低优先级任务无效
 ** input parameters:		uiNotifyType:	唤醒类型
 ** 							objpSourceTask:	唤醒的源伪线程任务对象
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2012-3-16
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
//uint32 CSnmpCell::Notify(uint32 uiNotifyType,CThreadTask* objpSourceTask)
//{
//	if( objpSourceTask == NULL
//			|| uiNotifyType == CThreadTask::uiThreadTaskStatusFailed
//			|| uiNotifyType == CThreadTask::uiThreadTaskStatusTimeout){
//		//有错需要Undo
//		ThreadTaskUndo();
//		//通知上级
//		SetThreadTaskStatus(uiNotifyType);
//		NotifyToUpThread(uiNotifyType);
//	}
//	else{
//		CThreadTask* objpDown = GetFirstDownLink();
//		uint32 uiSuccessFlag = true;
//		while(objpDown != NULL){
//			//判断是否所有任务都完成
//			if( objpDown->GetThreadTaskStatus() != CThreadTask::uiThreadTaskStatusSuccess){
//				uiSuccessFlag = false;
//				break;
//			}
//			objpDown = objpDown->GetNextDownLink(objpDown);
//		}
//		if( uiSuccessFlag == true ){//任务都完成
//			SetThreadTaskStatus(CThreadTask::uiThreadTaskStatusSuccess);
//			NotifyToUpThread(CThreadTask::uiThreadTaskStatusSuccess);
//		}
//	}
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
/**********************************************************************************************************************
 ** Function name:			SetErrorStatus
 ** Descriptions:			设置差错状态
 ** input parameters:		ucError：		设置差错状态
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2012-03-18
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpCell::SetErrorStatus(uint8 ucError) {
	ucErrorStatus = ucError;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			Notify
 ** Descriptions:			对象克隆
 ** input parameters:		objpCell:	克隆对象
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							输入空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2012-3-18
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpCell::Clone(CSnmpCell* objpCell) {
	if (objpCell == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	ucErrorStatus = objpCell->GetErrorStatus();
	objRequestVB.GetOIDObject()->Clone(
			objpCell->GetRequestVB()->GetOIDObject());
	objRequestVB.GetValueObject()->Clone(
			objpCell->GetRequestVB()->GetValueObject());
	objCurrentVariable.Clone(objpCell->GetCurrentVariable());
	objResponseVB.GetOIDObject()->Clone(
			objpCell->GetResponseVB()->GetOIDObject());
	objResponseVB.GetValueObject()->Clone(
			objpCell->GetResponseVB()->GetValueObject());
	return CErrorValueDefine::uiConstReturnSuccess;
}
