/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibDebug.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-11
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CMibDebug.h"
//#include "CDebug.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CSnmpConstDefine.h"
#include "SlotLogicLX9.h"
#include "Lpc3250upload.h"
#include "MidoptDCC.h"
#include "Task_define.h"

//extern int updata_main(uint8*);
extern "C" {
void int_enable_eth_real(void);
void int_disable_eth_real(void);
void __swi(8) EnterCritical (void);
void __swi(9) ExtiCritical (void);
}
/**********************************************************************************************************************
 ** Function name:			CMibDebug
 ** Descriptions:			�๹�캯��
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CMibDebug::CMibDebug() {
}

/**********************************************************************************************************************
 ** Function name:			~CMibDebug
 ** Descriptions:			����������
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CMibDebug::~CMibDebug() {
}

/**********************************************************************************************************************
 ** Function name:			InitialGroup
 ** Descriptions:			��ʼ����׼���ж���
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
 ** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-8-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CMibDebug::InitialGroup() {
//��ʼ��
uint32 uiInOID[] = { 1, 3, 6, 1, 4, 1, 25449, 1, 1, 11, 1, 0, 0 };
CSnmpVariable objMib(uiInOID, 10);
InitialNode(&objMib);

//��ʼ����
for (uint32 i = 0; i < 2; i++) { //6����Ա
	CMibColumn* objpColumn = new CMibDebugColumn();
	uiInOID[11] = i + 1;
	CSnmpVariable objMib(uiInOID, 12);
	objpColumn->InitialNode(&objMib);
	InsertDownLinkNode(objpColumn);
}
return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			GetResponse
 ** Descriptions:			Get����Ӧ����
 ** input parameters:		objpCell��		SNMP�������
 ** output parameters:		None
 ** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
 ** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
 ** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CMibDebugColumn::GetResponse(CSnmpCell* objpCell) {
//	if( objpCell == NULL ){
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
//	uint32 uiOIDLen = 0;
//	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
//	if( uiOIDLen != 13 ){//���Ⱥ�oidУ��
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	switch( uipInOID[11] ){//����
//	case 1://updata lpc3250
//		{
//		}
//	case 2://updata lx9
//		{
//		}
//	}
return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
 ** Function name:			SetResponse
 ** Descriptions:			Set����Ӧ����
 ** input parameters:		objpCell��		SNMP�������
 ** output parameters:		None
 ** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
 ** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
 ** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CMibDebugColumn::SetResponse(CSnmpCell* objpCell) {
if (objpCell == NULL) {
	return CErrorValueDefine::uiConstReturnFailed;
}
CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
uint32 uiOIDLen = 0;
uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
if (uiOIDLen != 13) { //���Ⱥ�oidУ��
	return CErrorValueDefine::uiConstReturnFailed;
}
switch (uipInOID[11]) { //����
case 1: //updata lpc3250
{
	CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
	if (objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString) { //���ʹ���
		objpCell->SetErrorResponse(objpOID,
				CSnmpConstDefine::ucConstSnmpErrorWrongType);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	//
	uint32 uiTempLen = 0;
	uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);

	try {
		Lpc3250_upload upLoad(ucpTempBuf, uiTempLen);
		if (upLoad.startUpload()) {
			CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnSuccess);
			objpCell->SetResponse(objpOID, &objResponse);
			//os_evt_set(0x0001, t_reset);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	} catch (...) {
	}
	CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnFailed);
	objpCell->SetResponse(objpOID, &objResponse);
	return CErrorValueDefine::uiConstReturnSuccess;
}
//		break;
case 2: //updata lx9
{
	CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
	if (objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString) { //���ʹ���
		objpCell->SetErrorResponse(objpOID,
				CSnmpConstDefine::ucConstSnmpErrorWrongType);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	uint32 uiTempLen = 0;
	uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
	//�������fpga
	try {
		SlotLogic_LX9 lx9(ucpTempBuf, uiTempLen);

////				int_disable_eth_real();
//				Dcc_interrupt_disable();
//				tsk_lock();
//				EnterCritical();
		bool rtn = lx9.UpDataLx9();
//				ExtiCritical();

//				tsk_unlock();
////				Dcc_interrupt_enable();
////				int_enable_eth_real();

		if (rtn) {
			CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnSuccess);
			objpCell->SetResponse(objpOID, &objResponse);
			//os_evt_set(0x0002, t_reset);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	} catch (...) {
	}
	CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnFailed);
	objpCell->SetResponse(objpOID, &objResponse);
	return CErrorValueDefine::uiConstReturnSuccess;
}
//		break;
}
return CErrorValueDefine::uiConstReturnFailed;
}
/**********************************************************************************************************************
 ** Function name:			GetFirstValidOID
 ** Descriptions:			GetNext���÷���1����õ�һ�������OID
 ** input parameters:		objpCell��		SNMP�������
 ** output parameters:		None
 ** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
 ** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
 ** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CMibDebugColumn::GetFirstValidOID(CSnmpCell* objpCell) {
if (objpCell == NULL) {
	return CErrorValueDefine::uiConstReturnInputNULLPointer;
}
uint32 uiInOID[] = { 1, 3, 6, 1, 4, 1, 25449, 1, 1, 11, 1, 0 };
CSnmpVariable objFirst(uiInOID, 12);
objpCell->GetCurrentVariable()->Clone(&objFirst);
return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetNextValidOID
 ** Descriptions:			GetNext���÷���2�������һ�������OID
 ** input parameters:		objpCell��		SNMP�������
 ** output parameters:		None
 ** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
 ** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
 ** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CMibDebugColumn::GetNextValidOID(CSnmpCell* objpCell) {
if (objpCell == NULL) {
	return CErrorValueDefine::uiConstReturnInputNULLPointer;
}
CSnmpVariable objTemp;
objTemp.Clone(objpCell->GetCurrentVariable());
uint32 uiBaseLen = 0;
uint32* uipBaseOID = objTemp.GetOIDValue(&uiBaseLen);
for (uint32 i = uiBaseLen; i < 12; i++) {
	uipBaseOID[i] = 0;
}
if (uiBaseLen == 11) { //such as 1,3,6,1,4,1,25449,1,1,11.2
	if (uipBaseOID[10] == 0) {
		uipBaseOID[10] = 1;
	} else if (uipBaseOID[10] > 3) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
} else { //���ȴ��ڵ���12
	uipBaseOID[10]++;
	if (uipBaseOID[10] > 3) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uipBaseOID[11] = 0;
}
CSnmpVariable objNext(uipBaseOID, 12);
objpCell->GetCurrentVariable()->Clone(&objNext);
return CErrorValueDefine::uiConstReturnSuccess;
}
