/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibCommunicationAttribute.cpp
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

#include "CMibCommunicationAttribute.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CCommonDefine.h"
#include "CClassPointer.h"
#include "CDeviceAttribute.h"
#include "DeviceLocal.h"
//#include "CMain.h"
//extern CClassPointer objGlbClassPointer;
/**********************************************************************************************************************
** Function name:			CMibCommunicationAttribute
** Descriptions:			�๹�캯��
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
CMibCommunicationAttribute::CMibCommunicationAttribute() {
}
/**********************************************************************************************************************
** Function name:			~CMibCommunicationAttribute
** Descriptions:			����������
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

CMibCommunicationAttribute::~CMibCommunicationAttribute() {
}
/**********************************************************************************************************************
** Function name:			InitialGroup
** Descriptions:			��ʼ����׼���ж���
** input parameters:		None
** output parameters:		None
** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibCommunicationAttribute::InitialGroup()
{
	//��ʼ��
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,9,2,1,1};
	CSnmpVariable objMib(uiInOID,11);
	InitialNode(&objMib);

	{//��ʼ���������Ա�
		for( uint32 i=0;i<8;i++ ){//8����Ա
			CMibCommunicationAttributeColumn* objpColumn = new CMibCommunicationAttributeColumn();
			uiInOID[12] = i+1;
			CSnmpVariable objMib(uiInOID,13);
			objpColumn->InitialNode(&objMib);
			InsertDownLinkNode(objpColumn);
		}
	}

	return CErrorValueDefine::uiConstReturnSuccess;


}

/**********************************************************************************************************************
** Function name:			CMibCommunicationAttributeColumn
** Descriptions:			�๹�캯��
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

CMibCommunicationAttributeColumn::CMibCommunicationAttributeColumn()
{
}
/**********************************************************************************************************************
** Function name:			~CMibCommunicationAttributeColumn
** Descriptions:			����������
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

CMibCommunicationAttributeColumn::~CMibCommunicationAttributeColumn()
{
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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibCommunicationAttributeColumn::GetResponse(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 14 || uipInOID[13] != CCommonDefine::uiConstDeviceIndex ){//���Ⱥ�oidУ��
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CDeviceAttribute* objpDeviceAttribute = &DeviceLocal::instance().GetDeviceAttributeObject();
	switch( uipInOID[12] ){//����
	case 1://eciDPCommExternalIP
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadExternalIP(),4,CSnmpConstDefine::ucConstIPAddress);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 2://eciDPCommExternalMask
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadExternalMask(),4,CSnmpConstDefine::ucConstIPAddress);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 3: //eciDPCommGateway
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadGatewayIP(),4,CSnmpConstDefine::ucConstIPAddress);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 4: //eciDPCommInternalIP
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadInternalIP(),4,CSnmpConstDefine::ucConstIPAddress);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 5://eciDPCommInternalMask
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadExternalMask(),4,CSnmpConstDefine::ucConstIPAddress);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 6: //eciDPCommMACAddress
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadMACAddress(),6,CSnmpConstDefine::ucConstOctetString);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 7: //eciDPCommBasePort
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadBasePort());
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 8: //eciDPCommTrapDestIP
	{
		CSnmpVariable objResponse(objpDeviceAttribute->ReadTrapDestIP(),4,CSnmpConstDefine::ucConstIPAddress);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}

	}
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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibCommunicationAttributeColumn::SetResponse(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 14 || uipInOID[13] != CCommonDefine::uiConstDeviceIndex ){//���Ⱥ�oidУ��
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CDeviceAttribute* objpDeviceAttribute = &DeviceLocal::instance().GetDeviceAttributeObject();
	switch( uipInOID[12] ){//����
	case 1://eciDPCommExternalIP
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstIPAddress ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiTempLen = 0;
		uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
		if( uiTempLen != 4){
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongValue);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiRet = objpDeviceAttribute->SetExternalIP(ucpTempBuf);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 2://eciDPCommExternalMask
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstIPAddress ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiTempLen = 0;
		uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
		if( uiTempLen != 4){
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongValue);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiRet = objpDeviceAttribute->SetExternalMask(ucpTempBuf);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 3: //eciDPCommGateway
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstIPAddress ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiTempLen = 0;
		uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
		if( uiTempLen != 4){
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongValue);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiRet = objpDeviceAttribute->SetGatewayIP(ucpTempBuf);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 4: //eciDPCommInternalIP
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstIPAddress ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiTempLen = 0;
		uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
		if( uiTempLen != 4){
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongValue);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiRet = objpDeviceAttribute->SetInternalIP(ucpTempBuf);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 5://eciDPCommInternalMask
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstIPAddress ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiTempLen = 0;
		uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
		if( uiTempLen != 4){
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongValue);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiRet = objpDeviceAttribute->SetInternalMask(ucpTempBuf);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 6: //eciDPCommMACAddress
	{
		objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorNotWriteable);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 7: //eciDPCommBasePort
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstInteger32 ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiPort = objInvalue->GetInteger32Value();
		uint32 uiRet = objpDeviceAttribute->SetBasePort( (uint16)uiPort);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	case 8: //eciDPCommTrapDestIP
	{
		CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
		if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstIPAddress ){//���ʹ���
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiTempLen = 0;
		uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
		if( uiTempLen != 4){
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongValue);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		uint32 uiRet = objpDeviceAttribute->SetTrapDestIP(ucpTempBuf);
		CSnmpVariable objResponse(uiRet);
		objpCell->SetResponse(objpOID,&objResponse);
		return CErrorValueDefine::uiConstReturnSuccess;
	}

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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibCommunicationAttributeColumn::GetFirstValidOID(CSnmpCell* objpCell)
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


	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,9,2,1,1,0};
	uiInOID[12] = uipOID[12];
	uiInOID[13] = CCommonDefine::uiConstDeviceIndex;
	CSnmpVariable objFirst(uiInOID,14);
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
** Created date:			2011-08-30
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibCommunicationAttributeColumn::GetNextValidOID(CSnmpCell* objpCell)
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
