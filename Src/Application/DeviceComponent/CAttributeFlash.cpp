/****************************************Copyright (c)*****************************************************************
 **
 **                               Easy Broadband Technology Co., Ltd.
 **
 **                                  http://www.ebbnetwork.com
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CAttributeSave.cpp
 ** Created by:          wang ying
 ** Created date:        2011-7-19
 ** Descriptions:        �豸���ԵĴ洢
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Version:
 ** Descriptions:
 ** Rechecked by:
 ***********************************************************************************************************************/
#include "CAttributeFlash.h"
#include "CErrorValueDefine.h"
#include "string.h"
#include "CMSSave.h"
#include "CNandFlashDef.h"
#include "CCheckData.h"
#include <string>
//#include "CardAttributeDefine.h"
//#include "CSlotManager.h"
//#include "CCheckData.h"
//#include "CMSMCUSyncManager.h"
#include "Mid_FlashData.h"

/**********************************************************************************************************************
** Function name:			CAttributeSave
** Descriptions:			�๹�캯��
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				Wang ying
** Created date:			2011-7-19
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CAttributeFlash::CAttributeFlash()
{
	memset((uint8*)&stAttributeStore,0x00,sizeof(STDeviceAttributeStore));
	EZ_FLASH_DATA_T info;
	info.BlockFirst = SYS_Attribut_Block_Start;
	info.BufAddr  = (uint32)&stAttributeStore;
	info.ByteNums = sizeof(stAttributeStore);
	int a = info.ByteNums/2048;
	info.SecsUsed = (info.ByteNums % 2048) ? (a+1) : a;
	setInfo(info);

}

/**********************************************************************************************************************
** Function name:			~CAttributeSave
** Descriptions:			����������
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				Wang ying
** Created date:			2011-7-19
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CAttributeFlash::~CAttributeFlash()
{

}

/**********************************************************************************************************************
** Function name:			AttributeRecover
** Descriptions:			�豸�����ϵ�ָ�
** input parameters:		None
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-7-19
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CAttributeFlash::AttributeRecover()
{
	uint32 uiCRCValue = 0;
	if( ReadData((uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore)) != CErrorValueDefine::uiConstReturnSuccess ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &uiCRCValue);
	if( uiCRCValue != stAttributeStore.uiCRCResult ){
		LoadAttributeDefault();
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			LoadAttributeDefault
** Descriptions:			����Ĭ������
** input parameters:		None
** output parameters:		None
** Returned value:			none
** Created by:				Wang ying
** Created date:			2011-7-19
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
void CAttributeFlash::LoadAttributeDefault(void)
{
	stAttributeStore.ucExtIP[0] = 192;
	stAttributeStore.ucExtIP[1] = 168;
	stAttributeStore.ucExtIP[2] = 1;
	stAttributeStore.ucExtIP[3] = 64;
	SetExtIP(stAttributeStore.ucExtIP, 4);

	stAttributeStore.ucExtMask[0] = 0xff;
	stAttributeStore.ucExtMask[1] = 0xff;
	stAttributeStore.ucExtMask[2] = 0xff;
	stAttributeStore.ucExtMask[3] = 0;
	SetExtMask(stAttributeStore.ucExtMask, 4);

	stAttributeStore.ucGatIP[0] = 192;
	stAttributeStore.ucGatIP[1] = 168;
	stAttributeStore.ucGatIP[0] = 0;
	stAttributeStore.ucGatIP[3] = 1;
	SetGatIP(stAttributeStore.ucGatIP, 4);

	stAttributeStore.ucIntIP[0] = 10;
	stAttributeStore.ucIntIP[1] = 10;
	stAttributeStore.ucIntIP[2] = 10;
	stAttributeStore.ucIntIP[3] = 83;
	SetIntIP(stAttributeStore.ucIntIP, 4);

	stAttributeStore.ucIntMask[0] = 0xff;
	stAttributeStore.ucIntMask[1] = 0xff;
	stAttributeStore.ucIntMask[2] = 0xff;
	stAttributeStore.ucIntMask[3] = 0;
	SetIntMask(stAttributeStore.ucIntMask, 4);

	stAttributeStore.ucBasePort[1] = ((161 >> 8) & 0xff );
	stAttributeStore.ucBasePort[0] = (161 & 0xff);

	stAttributeStore.ucSysClock = 0;
	stAttributeStore.ucSysSubDevice = 13;
	stAttributeStore.ucPcmClock = 3;
    std::string s("RC3000-2E1");
    SetDeviceName( (uint8*)s.c_str(), (uint32)s.size() );
    s= "UserName";
    SetUserName( (uint8*)s.c_str(), (uint32)s.size() );
    s = "DescriberName";
    SetDescriberName( (uint8*)s.c_str(), (uint32)s.size() );
    s = "Other";
    SetOther( (uint8*)s.c_str(), (uint32)s.size() );

}


/*********************************************************************************************************
** Function name:			SetDeviceName
** Descriptions:			д�豸����(��һ���ֽڴ泤��)
** input parameters:		ucpBuffer:		д�������
**							uiLength��	д�����ݳ��ȣ�������31�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetDeviceName(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength>31 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	stAttributeStore.ucDeviceName[0] = (uint8)uiLength;
	for( uint32 i = 0; i < uiLength; i++){
		stAttributeStore.ucDeviceName[i+1] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);
	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*********************************************************************************************************
** Function name:			GetDeviceName
** Descriptions:			���豸����
** input parameters:		None
** output parameters:		uipLength��	���ص����ݳ��ȣ�������31�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2010-09-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetDeviceName(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = stAttributeStore.ucDeviceName[0];
	if( *uipLength > 31 ){
		*uipLength = 0;
	}
	return &stAttributeStore.ucDeviceName[1];
}


/*********************************************************************************************************
** Function name:			SetUserName
** Descriptions:			д�豸�û���Ϣ
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�������31�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetUserName(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength > 31 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	stAttributeStore.ucUserName[0] = (uint8)uiLength;
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucUserName[i+1] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetUserName
** Descriptions:			���豸�û���Ϣ
** input parameters:		None
** output parameters:		length��	���ص����ݳ��ȣ�������31�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang changrong
** Created date:			2010-09-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetUserName(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = stAttributeStore.ucUserName[0];
	if( *uipLength > 31 ){
		*uipLength = 0;
	}
	return &stAttributeStore.ucUserName[1];
}


/*********************************************************************************************************
** Function name:			SetDescriberName
** Descriptions:			д�豸����
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�������31�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetDescriberName(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength > 31 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	stAttributeStore.ucDescriberName[0] = (uint8)uiLength;
	for(uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucDescriberName[i+1] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetDescriberName
** Descriptions:			���豸����
** input parameters:		None
** output parameters:		uipLength��	���ص����ݳ��ȣ�������31�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetDescriberName(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = stAttributeStore.ucDescriberName[0];
	if( *uipLength > 31 ){
		*uipLength = 0;
	}
	return &stAttributeStore.ucDescriberName[1];
}


/*********************************************************************************************************
** Function name:			SetOther
** Descriptions:			д�豸��������
** input parameters:		uipBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�������31�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetOther(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength > 31 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	stAttributeStore.ucOther[0] = (uint8)uiLength;
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucOther[i+1] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetOther
** Descriptions:			���豸��������
** input parameters:		None
** output parameters:		uiLength��	���ص����ݳ��ȣ�������31�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetOther(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = stAttributeStore.ucOther[0];
	if( *uipLength > 31 ){
		*uipLength = 0;
	}
	return &stAttributeStore.ucOther[1];
}


/*********************************************************************************************************
** Function name:			SetContact
** Descriptions:			д�豸��ϵ��
** input parameters:		uipBuffer:		д������Buffer
**							uiLength��	д�����ݳ��ȣ�������31�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetContact(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength > 31 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	stAttributeStore.ucContact[0] = (uint8)uiLength;
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucContact[i+1] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetContact
** Descriptions:			���豸��ϵ��
** input parameters:		None
** output parameters:		uiLength��	���ص����ݳ��ȣ�������31�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetContact(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = stAttributeStore.ucContact[0];
	if( *uipLength > 31 ){
		*uipLength = 0;
	}
	return &stAttributeStore.ucContact[1];
}


/*********************************************************************************************************
** Function name:			SetLocation
** Descriptions:			д�豸λ��
** input parameters:		ucpBuffer:		д������Buffer
**							uiLength��	д�����ݳ��ȣ�������31�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetLocation(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength > 31 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	stAttributeStore.ucLocation[0] = (uint8)uiLength;
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucLocation[i+1] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*********************************************************************************************************
** Function name:			GetLocation
** Descriptions:			���豸λ��
** input parameters:		None
** output parameters:		uiLength��	���ص����ݳ��ȣ�������31�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetLocation(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = stAttributeStore.ucLocation[0];
	if( *uipLength > 31 ){
		*uipLength = 0;
	}
	return &stAttributeStore.ucLocation[1];
}


/*********************************************************************************************************
** Function name:			SetExtIP
** Descriptions:			д�豸�ⲿIP��ַ
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�4�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetExtIP(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed ;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucExtIP[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetExtIP
** Descriptions:			���豸�ⲿIP��ַ
** input parameters:		None
** output parameters:		uiLength��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetExtIP(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 4;
	return stAttributeStore.ucExtIP;
}


/*********************************************************************************************************
** Function name:			SetExtMask
** Descriptions:			д�豸�ⲿIP����
** input parameters:		ucpBuffer:		д������Buffer
**							uiLength��	д�����ݳ��ȣ�4�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetExtMask(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed ;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucExtMask[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*********************************************************************************************************
** Function name:			GetExtMask
** Descriptions:			���豸�ⲿIP����
** input parameters:		None
** output parameters:		length��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang changrong
** Created date:			2010-09-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetExtMask(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 4;
	return stAttributeStore.ucExtMask;
}


/*********************************************************************************************************
** Function name:			SetGatIP
** Descriptions:			д�豸����IP��ַ
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�4�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetGatIP(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed ;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucGatIP[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetGatIP
** Descriptions:			���豸����IP��ַ
** input parameters:		None
** output parameters:		uiLength��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-20
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetGatIP(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 4;
	return stAttributeStore.ucGatIP;
}


/*********************************************************************************************************
** Function name:			SetIntIP
** Descriptions:			д�豸�ڲ�IP��ַ
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�4�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetIntIP(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed ;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucIntIP[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*********************************************************************************************************
** Function name:			GetIntIP
** Descriptions:			���豸�ڲ�IP��ַ
** input parameters:		None
** output parameters:		uipLength��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetIntIP(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 4;
	return stAttributeStore.ucIntIP;
}


/*********************************************************************************************************
** Function name:			SetIntMask
** Descriptions:			д�豸�ڲ�IP����
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�4�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetIntMask(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed ;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucIntMask[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetIntMask
** Descriptions:			���豸�ڲ�IP����
** input parameters:		None
** output parameters:		uiLength��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetIntMask(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 4;
	return stAttributeStore.ucIntMask;
}


/*********************************************************************************************************
** Function name:			SetMacAdd
** Descriptions:			д�豸MAC��ַ
** input parameters:		ucpBuffer:		д������Buffer
**							uiLength��	д�����ݳ��ȣ�6�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetMacAdd(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 6 ) ){
		return CErrorValueDefine::uiConstReturnFailed ;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucMacAdd[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetMacAdd
** Descriptions:			���豸MAC��ַ
** input parameters:		None
** output parameters:		uipLength��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetMacAdd(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 6;
	return stAttributeStore.ucMacAdd;
}


/*********************************************************************************************************
** Function name:			SetTrapIP
** Descriptions:			д�豸����TrapĿ��IP��ַ
** input parameters:		ucpBuffer:		д������
**							uiLength��	д�����ݳ��ȣ�4�ֽ�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetTrapIP(uint8* ucpBuffer,uint32 uiLength)
{
	if( ( ucpBuffer == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	for( uint32 i = 0; i < uiLength; i++ ){
		stAttributeStore.ucTrapIP[i] = ucpBuffer[i];
	}
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetTrapIP
** Descriptions:			���豸����TrapĿ��IP��ַ
** input parameters:		None
** output parameters:		uipLength��	���ص����ݳ��ȣ�4�ֽ�
** Returned value:			����ɹ��������ݻ����ַ�����򷵻�NULL
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint8* CAttributeFlash::GetTrapIP(uint32* uipLength)
{
	if( uipLength == NULL ){
		return NULL;
	}
	*uipLength = 4;
	return stAttributeStore.ucTrapIP;
}


/*********************************************************************************************************
** Function name:			SetBasePort
** Descriptions:			д�豸���˿�
** input parameters:		usPort:		д����˿�
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetBasePort(uint16 usPort)
{
	stAttributeStore.ucBasePort[1] = (uint8)((usPort >> 8) & 0xff);
	stAttributeStore.ucBasePort[0] = (uint8)((usPort) & 0xff);
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}

uint32 CAttributeFlash::GetSysClock(void) {
	return stAttributeStore.ucSysClock;
}
uint32 CAttributeFlash::SetSysClock(uint32 mode) {
	stAttributeStore.ucSysClock = mode;
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}

uint32 CAttributeFlash::GetPcmClock(void) {
	return stAttributeStore.ucPcmClock;
}
uint32 CAttributeFlash::SetPcmClock(uint32 mode) {
	stAttributeStore.ucPcmClock = mode;
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetBasePort
** Descriptions:			���豸���˿�
** input parameters:		None
** output parameters:		uspPort:		���˿�
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::GetBasePort(uint16* uspPort)
{
	if(uspPort == NULL){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uspPort = (uint16)( ( ( stAttributeStore.ucBasePort[1] << 8 ) & 0xff00 )
			   | ( stAttributeStore.ucBasePort[0] & 0xff ) );
	return CErrorValueDefine::uiConstReturnSuccess;
}


///*********************************************************************************************************
//** Function name:			SetVerionPower
//** Descriptions:			д�豸�汾:		��Դ
//** input parameters:		uiVersion:		�汾
//** output parameters:		None
//** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::SetVerionPower(uint32 uiVersion)
//{
//	stAttributeStore.stVersion.ucPower = (uint8)uiVersion;
//	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);
//
//	SaveData(5);
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
///*********************************************************************************************************
//** Function name:			GetVerionPower
//** Descriptions:			���豸�汾:		��Դ
//** input parameters:		None
//** output parameters:		uipVersion:		�汾
//** Returned value:			SUCCESS: ����ɹ�
//**                          CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
//**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::GetVerionPower(uint32* uipVersion)
//{
//	if( uipVersion == NULL ){
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	*uipVersion = stAttributeStore.stVersion.ucPower;
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
///*********************************************************************************************************
//** Function name:			SetVerionProducePlace
//** Descriptions:			д�豸�汾:		����
//** input parameters:		uiVersion:		�汾
//** output parameters:		None
//** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::SetVerionProducePlace(uint32 uiVersion)
//{
//	stAttributeStore.stVersion.ucProducePlace = (uint8)uiVersion;
//	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);
//
//	SaveData(5);
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
///*********************************************************************************************************
//** Function name:			GetVerionProducePlace
//** Descriptions:			���豸�汾:		����
//** input parameters:		None
//** output parameters:		uipVersion:		�汾
//** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
//**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::GetVerionProducePlace(uint32* uipVersion)
//{
//	if( uipVersion == NULL ){
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	*uipVersion = stAttributeStore.stVersion.ucProducePlace;
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
///*********************************************************************************************************
//** Function name:			SetVerionActing
//** Descriptions:			д�豸�汾:		����
//** input parameters:		uiVersion:		�汾
//** output parameters:		None
//** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::SetVerionActing(uint32 uiVersion)
//{
//	stAttributeStore.stVersion.ucActVersion = (uint8)uiVersion;
//	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);
//
//	SaveData(5);
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
//
///*********************************************************************************************************
//** Function name:			GetVerionActing
//** Descriptions:			���豸�汾:		����
//** input parameters:		None
//** output parameters:		uipVersion:		�汾
//** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
//**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::GetVerionActing(uint32* uipVersion)
//{
//	if( uipVersion == NULL ){
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	*uipVersion = stAttributeStore.stVersion.ucActVersion;
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
///*********************************************************************************************************
//** Function name:			SetVerionConsumer
//** Descriptions:			д�豸�汾:		�û�
//** input parameters:		uiVersion:		�汾
//** output parameters:		None
//** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::SetVerionConsumer(uint32 uiVersion)
//{
//	stAttributeStore.stVersion.ucConsumer[1] = (uint8)(( uiVersion >> 8 ) & 0xff);
//	stAttributeStore.stVersion.ucConsumer[0] = (uint8)(uiVersion & 0xff);
//	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);
//
//	SaveData(5);
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//
//
///*********************************************************************************************************
//** Function name:			GetVerionConsumer
//** Descriptions:			���豸�汾:		�û�
//** input parameters:		None
//** output parameters:		uipVersion:		�汾
//** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
//**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
//** Created by:				Wang ying
//** Created date:			2011-07-21
//**--------------------------------------------------------------------------------------------------------
//** Modified by:
//** Modified date:
//** Descriptions:
//**
//*********************************************************************************************************/
//uint32 CAttributeFlash::GetVerionConsumer(uint32* uipVersion)
//{
//	if( uipVersion == NULL ){
//		return CErrorValueDefine::uiConstReturnFailed;
//	}
//	*uipVersion = ( ( stAttributeStore.stVersion.ucConsumer[1] << 8) & 0xff00)
//			      | ( stAttributeStore.stVersion.ucConsumer[0] & 0xff);
//	return CErrorValueDefine::uiConstReturnSuccess;
//}
//

/*********************************************************************************************************
** Function name:			SetVerionSerialNumber
** Descriptions:			д�豸�汾:		���к�
** input parameters:		uiVersion:		�汾
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetVerionSerialNumber(uint32 uiVersion)
{
	stAttributeStore.ucSerialNumber = (uint16)uiVersion;
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}


/*********************************************************************************************************
** Function name:			GetVerionSerialNumber
** Descriptions:			���豸�汾:		���к�
** input parameters:		None
** output parameters:		uipVersion:		�汾
** Returned value:			CErrorValueDefine::uiConstReturnFailed        ����ִ��ʧ��
**                          CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::GetVerionSerialNumber(void)
{
	return stAttributeStore.ucSerialNumber;
}


/*********************************************************************************************************
** Function name:			SetVerionDate
** Descriptions:			д�豸�汾:		��������
** input parameters:		uiVersion:		�汾
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnSuccess       ����ִ�гɹ�
** Created by:				Wang ying
** Created date:			2011-07-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
uint32 CAttributeFlash::SetVerionDate(const char* s)
{
	if( strlen(s) > 19 ) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	strcpy(stAttributeStore.cProductiDate, s);
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
} 


/*********************************************************************************************************
** Function name:			GetVerionDate
** Descriptions:			���豸�汾:		��������
** input parameters:		None
** output parameters:		ver:		�汾
** Returned value:			SUCCESS: ����ɹ�
**                          FAILED:  ����ʧ��
** Created by:				Wang changrong
** Created date:			2010-09-21
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
*********************************************************************************************************/
char* CAttributeFlash::GetVerionDate(void)
{
	return stAttributeStore.cProductiDate;
}


uint32 CAttributeFlash::GetSysSubDevice(void) {
	return stAttributeStore.ucSysSubDevice;
}

uint32 CAttributeFlash::SetSysSubDevice(uint32 type) {
	stAttributeStore.ucSysSubDevice = type;
	CCheckData::CRCCheck1( (uint8*)&stAttributeStore, sizeof(STDeviceAttributeStore) - 12, &stAttributeStore.uiCRCResult);

	SaveData(5);
	return CErrorValueDefine::uiConstReturnSuccess;
}
