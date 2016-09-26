/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ezwell-tech.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Liu Weifeng
** Created date:			2011-06-22
** Version:				    1.0
** Descriptions:			
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**********************************************************************************************************************/

#include "CDeviceAttribute.h"
#include "CErrorValueDefine.h"
#include "CAttributeFlash.h"
#include "string.h"
#include "CCommonDefine.h"
#include "CSlotCardConstDefine.h"
#include <iostream>
#include <Net_Config.h>
#include "Mid_RC7880A1App.h"

#include "ChipGluLogic.h"
#include "ChipOptLogic.h"
#include "ChipSlotLogic.h"
#include "CPPTools.h"

extern LOCALM localm[];

extern unsigned char const vertion_end[32];

#define DEFBootVersion 1
#define DEFMainVersion ( (vertion_end[0x13] << 8) | vertion_end[0x14] )
#define DEFHardVersion vertion_end[0x12]

/**********************************************************************************************************************
** Function name:			CDeviceAttribute
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				Liu Weifeng
** Created date:			2011-06-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:             wang ying
** Modified date:           2011-07-18
** Descriptions:            添加具体实现
**
**********************************************************************************************************************/
CDeviceAttribute::CDeviceAttribute() 
{
	uint8 i = 0;
	objpAttSave = &DevAttr;
	ucpExternalIP = NULL;
	ucpExternalMask = NULL;
	ucpGatewayIP = NULL;
	ucpInternalIP = NULL;
	ucpInternalMask = NULL;
	ucpTrapDestIP = NULL;
	for( i = 0; i < 6; i++){
		ucMACAddress[i] = 0;
	}
	usBasePort = 161;



}

/**********************************************************************************************************************
** Function name:			~CDeviceAttribute
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				Liu Weifeng
** Created date:			2011-06-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CDeviceAttribute::~CDeviceAttribute() 
{
}
/**********************************************************************************************************************
** Function name:			InitialClassObject
** Descriptions:			类初始化
** input parameters:		objpFlash 初始化类指针
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnSuccess   成功
** Created by:				Wang ying
** Created date:			2011-7-19
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CDeviceAttribute::InitialClassObject(CSystem* objpAttribute) {
//	objpCSystem = objpAttribute;
//	objpAttSave = CClassPointer::GetHardWarePointer()->GetFlashImplObject()->GetAttributeFlashobject();
//	return CErrorValueDefine::uiConstReturnSuccess;
//}

/**********************************************************************************************************************
** Function name:			InitialSystem
** Descriptions:			初始化系统
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
uint32 CDeviceAttribute::InitialSystem(void)
{
	objpAttSave->AttributeRecover();
	GetExternalIP();
	GetExternalMask();
	GetGatewayIP();
	GetInternalIP();
	GetInternalMask();
	GetBasePort();
	GetTrapDestIP();
//	FetchVersionB();

//	stVersion[4].uiVerNum = objpAttSave->GetSysSubDevice();

	ucMACAddress[0] = 0;
	ucMACAddress[1] = CCommonDefine::ucConstDeviceTypeID;
	STVersion ver;
	GetVersion(ver_pcb, ver);
	ucMACAddress[2] = (uint8)ver.uiVerNum;//Hardware_Version;
	ucMACAddress[3] = 0;
	ucMACAddress[4] = objpAttSave->GetVerionSerialNumber() >> 8;
	ucMACAddress[5] = (uint8)objpAttSave->GetVerionSerialNumber();
//	SetClockMode(objpAttSave->GetSysClock());


	return CErrorValueDefine::uiConstReturnSuccess;
}



/**********************************************************************************************************************
** Function name:			GetDeviceName  
** Descriptions:			读设备名称
** input parameters:		none
** output parameters:		uipLength   名称长度
** Returned value:			None
** Created by:				wang ying
** Created date:			2011-07-18
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CDeviceAttribute::GetDeviceName(uint32* uipLength)
{
	return objpAttSave->GetDeviceName(uipLength);
}

/**********************************************************************************************************************
** Function name:			GetDeviceUser
** Descriptions:			读设备用户名称  
** input parameters:		none
** output parameters:		uipLength   名称长度
** Returned value:			None
** Created by:				wang ying
** Created date:			2011-07-21
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CDeviceAttribute::GetDeviceUser(uint32* uipLength)
{
   	return objpAttSave->GetUserName(uipLength);
}

/**********************************************************************************************************************
** Function name:			GetDeviceDescription
** Descriptions:			读设备描述名称                    
** input parameters:		none
** output parameters:		uipLength   名称长度
** Returned value:			None
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CDeviceAttribute::GetDeviceDescription(uint32* uipLength)
{
	return objpAttSave->GetDescriberName(uipLength);
}

/**********************************************************************************************************************
** Function name:			GetDeviceBaseOther
** Descriptions:			读设备其他属性                     
** input parameters:		none
** output parameters:		uipLength   名称长度
** Returned value:			None
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CDeviceAttribute::GetDeviceBaseOther(uint32* uipLength)
{
	return objpAttSave->GetOther(uipLength);
}

/**********************************************************************************************************************
** Function name:			GetDeviceContact
** Descriptions:			读设备联系人
** input parameters:		none
** output parameters:		uipLength   设备联系人长度
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CDeviceAttribute::GetDeviceContact(uint32* uipLength)
{
	return objpAttSave->GetContact(uipLength);
}

/**********************************************************************************************************************
** Function name:			GetDeviceLocation
** Descriptions:			读设备位置描述
** input parameters:		none
** output parameters:		uipLength   设备位置描述长度
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint8* CDeviceAttribute::GetDeviceLocation(uint32* uipLength)
{
	return objpAttSave->GetLocation(uipLength);
}

/**********************************************************************************************************************
** Function name:			SetDeviceName
** Descriptions:			写设备名称
** input parameters:		ucpName   设备名称    
**                          uiLength   名称长度
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetDeviceName(uint8* ucpName, uint32 uiLength)
{
 	if( ( ucpName == NULL ) || ( uiLength > DEFMaxNameNumber ) ){
 		return CErrorValueDefine::uiConstReturnFailed;
 	}
/* 	CHardWare* p1 = objpAttSave->GetMainObject()->GetHardWareObject();
 	std::cout << "p1 = " << p1 << std::endl;
 	CFlashImpl* p2 = p1->GetFlashImplObject();
	std::cout << "p2 = " << p2 << std::endl;
	CAttributeFlash* p3 = p2->GetAttributeFlashobject();
	std::cout << "p3 = " << p3 << std::endl;
	return p3->SetDeviceName(ucpName, uiLength);*/

 	return objpAttSave->SetDeviceName(ucpName, uiLength);
}


/**********************************************************************************************************************
** Function name:			SetDeviceUser
** Descriptions:			写设备用户名称  
** input parameters:		ucpName   设备用户名称
**                          uiLength   名称长度
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetDeviceUser(uint8* ucpName, uint32 uiLength)
{
	if( ( ucpName == NULL ) || ( uiLength > DEFMaxNameNumber ) ){
	 		return CErrorValueDefine::uiConstReturnFailed;
	}
	return objpAttSave->SetUserName(ucpName, uiLength);
}

/**********************************************************************************************************************
** Function name:			SetDeviceDescription
** Descriptions:			写设备描述                            
** input parameters:		ucpName   设备描述
**                          uiLength   长度
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetDeviceDescription(uint8* ucpName, uint32 uiLength)
{
	if( ( ucpName == NULL ) || ( uiLength > DEFMaxNameNumber ) ){
	 		return CErrorValueDefine::uiConstReturnFailed;
	}
	return objpAttSave->SetDescriberName(ucpName, uiLength);
}


/**********************************************************************************************************************
** Function name:			SetDeviceBaseOther
** Descriptions:			写设备其他名称                      
** input parameters:		ucpName   设备其他名称
**                          uiLength   名称长度
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetDeviceBaseOther(uint8* ucpName, uint32 uiLength)
{
	if( ( ucpName == NULL ) || ( uiLength > DEFMaxNameNumber ) ){
	 		return CErrorValueDefine::uiConstReturnFailed;
	}
	return objpAttSave->SetOther(ucpName, uiLength);
}


/**********************************************************************************************************************
** Function name:			SetDeviceContact
** Descriptions:			写设备联系人
** input parameters:		ucpName   设备联系人
**                          uiLength   设备联系人长度
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				WangChangRong
** Created date:			2011-08-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetDeviceContact(uint8* ucpName, uint32 uiLength)
{
	if( ( ucpName == NULL ) || ( uiLength > DEFMaxNameNumber ) ){
	 		return CErrorValueDefine::uiConstReturnFailed;
	}
	return objpAttSave->SetContact(ucpName, uiLength);
}
/**********************************************************************************************************************
** Function name:			SetDeviceLocation
** Descriptions:			写设备位置描述
** input parameters:		ucpName   设备位置描述
**                          uiLength   设备位置描述长度
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				WangChangRong
** Created date:			2011-08-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetDeviceLocation(uint8* ucpName, uint32 uiLength)
{
	if( ( ucpName == NULL ) || ( uiLength > DEFMaxNameNumber ) ){
	 		return CErrorValueDefine::uiConstReturnFailed;
	}
	return objpAttSave->SetLocation(ucpName, uiLength);
}


/**********************************************************************************************************************
** Function name:			SetExternalIP
** Descriptions:			写外网IP       
** input parameters:		ucpIP  外网IP
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetExternalIP(uint8* ucpIP)
{
	if( ucpIP == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( objpAttSave->SetExtIP( ucpIP, 4 ) == CErrorValueDefine::uiConstReturnSuccess ){
		GetExternalIP();
		memcpy (localm[NETIF_ETH].IpAdr, ucpExternalIP, 4 );
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}



/**********************************************************************************************************************
** Function name:			GetExternalIP
** Descriptions:			读取外网IP     
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetExternalIP(void)
{
	uint32 uiLength = 0;
	ucpExternalIP = objpAttSave->GetExtIP(&uiLength);
	if( ( ucpExternalIP == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			SetExternalMask
** Descriptions:			写外网掩码                          
** input parameters:		ucpIP   外网掩码
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

uint32 CDeviceAttribute::SetExternalMask(uint8* ucpIP)
{
	if( ucpIP == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( objpAttSave->SetExtMask( ucpIP, 4 ) == CErrorValueDefine::uiConstReturnSuccess ){
		GetExternalMask();
		memcpy (localm[NETIF_ETH].NetMask, ucpExternalMask, 4 );

		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			GetExternalMask
** Descriptions:			读取外网掩码               
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetExternalMask(void)
{
	uint32 uiLength = 0;
	ucpExternalMask = objpAttSave->GetExtMask(&uiLength);
	if( ( ucpExternalMask == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			SetGatewayIP
** Descriptions:			写网关IP
** input parameters:		ucpIP   外网掩码
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetGatewayIP(uint8* ucpIP)
{
	if( ucpIP == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( objpAttSave->SetGatIP( ucpIP, 4 ) == CErrorValueDefine::uiConstReturnSuccess ){
		GetGatewayIP();
//		uip_ipaddr_t ipaddr;
//		uint8* ucpEIP =  ReadGatewayIP();
//		uip_ipaddr(ipaddr, ucpEIP[0],ucpEIP[1],ucpEIP[2],ucpEIP[3]);
//		uip_setdraddr(ipaddr);	/* host IP address */
		memcpy (localm[NETIF_ETH].DefGW, ucpGatewayIP, 4 );

		//加入方法，设置Trap发送的间隔方法
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}


/**********************************************************************************************************************
** Function name:			GetGatewayIP
** Descriptions:			读取网关IP
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetGatewayIP(void)
{
	uint32 uiLength = 0;
	ucpGatewayIP = objpAttSave->GetGatIP(&uiLength);
	if( ( ucpGatewayIP == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			SetInternalIP
** Descriptions:			写内网IP
** input parameters:		ucpIP   内网ip
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetInternalIP(uint8* ucpIP)
{
	if( ucpIP == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( objpAttSave->SetIntIP( ucpIP, 4 ) == CErrorValueDefine::uiConstReturnSuccess ){
		GetInternalIP();
		//加入方法，设置Trap发送的间隔方法
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			GetInternalIP
** Descriptions:			读取网关IP
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetInternalIP(void)
{
	uint32 uiLength = 0;
	ucpInternalIP = objpAttSave->GetIntIP(&uiLength);
	if( ( ucpInternalIP == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			SetInternalMask
** Descriptions:			写内网掩码
** input parameters:		ucpIP   内网掩码
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetInternalMask(uint8* ucpIP)
{
	if( ucpIP == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( objpAttSave->SetIntMask( ucpIP, 4 ) == CErrorValueDefine::uiConstReturnSuccess ){
		GetInternalMask();
		//加入方法，设置Trap发送的间隔方法
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}


/**********************************************************************************************************************
** Function name:			GetInternalMask
** Descriptions:			读取内网掩码
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetInternalMask(void)
{
	uint32 uiLength = 0;
	ucpInternalMask = objpAttSave->GetIntMask(&uiLength);
	if( ( ucpInternalMask == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			SetMACAddress
** Descriptions:			写MAC地址
** input parameters:		ucpIP   内网掩码
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetMACAddress(uint8* ucpMac)
{
 	if( ucpMac == NULL ){
 		return CErrorValueDefine::uiConstReturnFailed;
 	}
 	if( objpAttSave->SetMacAdd(ucpMac, 6) != CErrorValueDefine::uiConstReturnSuccess ){
 		return CErrorValueDefine::uiConstReturnFailed;
 	}
    //加入方法，再IP上设置uip
 	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			SetBasePort
** Descriptions:			写基端口
** input parameters:		usPort  基端口
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetBasePort(uint16 usPort)
{
	if( objpAttSave->SetBasePort(usPort) != CErrorValueDefine::uiConstReturnSuccess ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	usBasePort = usPort;
	return CErrorValueDefine::uiConstReturnSuccess ;
}

/**********************************************************************************************************************
** Function name:			GetBasePort
** Descriptions:			读基端口号
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetBasePort(void)
{
	objpAttSave->GetBasePort(&usBasePort);
	return usBasePort;
}



/**********************************************************************************************************************
** Function name:			SetTrapDestIP
** Descriptions:			写Trap目标IP地址
** input parameters:		ucpIP   目标IP
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::SetTrapDestIP(uint8* ucpIP)
{
	if( ucpIP == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( objpAttSave->SetTrapIP( ucpIP, 4 ) == CErrorValueDefine::uiConstReturnSuccess ){
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	return CErrorValueDefine::uiConstReturnFailed;
}


/**********************************************************************************************************************
** Function name:			GetInternalMask
** Descriptions:			读取内网掩码
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-07-22
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetTrapDestIP(void)
{
	uint32 uiLength = 0;
	ucpTrapDestIP = objpAttSave->GetTrapIP(&uiLength);
	if( ( ucpTrapDestIP == NULL ) || ( uiLength != 4 ) ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetVersion
** Descriptions:			读版本信息
** input parameters:		uiIndex     版本索引
**
** output parameters:		stVersion
** Returned value:			-1        函数执行失败
**                          1   函数执行成功
** Created by:				wang ying
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				Shqp
** Modified date:			2013-5-17
** Descriptions:
**
**********************************************************************************************************************/
//STVersion* CDeviceAttribute::GetVersion(uint32 uiIndex)
//{
//    if(uiIndex > 10)
//	{
//	    return (STVersion*)NULL;
//	}
//	 return &stVersion[uiIndex - 1];
//}

int CDeviceAttribute::GetVersion(uint32 uiIndex, STVersion& stVersion) {
	if( uiIndex > ver_size ) {
		return -1;
	}
	switch( uiIndex ) {
	case ver_boot:
		strcpy(stVersion.ucpVerName,"BootVersion");
		stVersion.uiVerNum = DEFBootVersion;
		break;
	case ver_mainsoft:
		strcpy(stVersion.ucpVerName,"MainVersion");
		stVersion.uiVerNum = DEFMainVersion;
		break;
	case ver_pcb: {
		strcpy(stVersion.ucpVerName,"PCBVersion");
		if( GetDeviceSubtype() == type_emux_v10 ) {
			stVersion.uiVerNum = ver_num_V10;
		}
		else if( GetDeviceSubtype() == type_emux_v12 ) {
			stVersion.uiVerNum = ver_num_V10+2;
		}
		else {
			stVersion.uiVerNum = getRealPCBVersion();
		}
	}
		break;
	case ver_glulogic:
		strcpy(stVersion.ucpVerName,"ChipGluLogicVersion");
		stVersion.uiVerNum = getGluLogicVersion();
		break;
	case ver_slotlogic:
		strcpy(stVersion.ucpVerName,"ChipSlotLogicVersion");
		stVersion.uiVerNum = getSlotLogicVersion();
		break;
	case ver_optlogic:
		strcpy(stVersion.ucpVerName,"ChipOptLogicVersion");
		if( GetDeviceSubtype() == type_emux_v12 ||
				GetDeviceSubtype() == type_emux_v10 ) {
			stVersion.uiVerNum = 0;
		}
		else {
			stVersion.uiVerNum = getOptLogicVersion();
		}
		break;
	default:
		return -1;

	}
	return 1;
}



uint32 CDeviceAttribute::SetSerialNumber(uint32 uiVersion) {
	return objpAttSave->SetVerionSerialNumber(uiVersion);
}
uint32 CDeviceAttribute::GetSerialNumber(void) {
	return objpAttSave->GetVerionSerialNumber();
}
uint32 CDeviceAttribute::SetProductionDate(DATE_TIME_T* s) {
	std::string sdate =
			CPPTools::number2string(s->year) + "-" +
			CPPTools::number2string(s->month) + "-" +
			CPPTools::number2string(s->day) + " " +
			CPPTools::number2string(s->hour) + ":" +
			CPPTools::number2string(s->minute) + ":" +
			CPPTools::number2string(s->second);
	return objpAttSave->SetVerionDate(sdate.c_str());
}
char* CDeviceAttribute::GetProductionDate(void) {
	return objpAttSave->GetVerionDate();
}

/**********************************************************************************************************************
** Function name:			FetchVersionB
** Descriptions:			刷新版本B的版本信息（供电，产地，序列号等）
** input parameters:		none
** output parameters:		none
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CDeviceAttribute::FetchVersionB(void)
//{
//	objpAttSave->GetVerionPower(&stVersion[5].uiVerNum);
//	objpAttSave->GetVerionProducePlace(&stVersion[6].uiVerNum);
//	objpAttSave->GetVerionActing(&stVersion[7].uiVerNum);
//	objpAttSave->GetVerionConsumer(&stVersion[8].uiVerNum);
//	objpAttSave->GetVerionSerialNumber(&stVersion[9].uiVerNum);
//	objpAttSave->GetVerionDate(&stVersion[10].uiVerNum);
//	return CErrorValueDefine::uiConstReturnSuccess;
//}


/**********************************************************************************************************************
** Function name:			GetNextVersionIndexbyIndex
** Descriptions:			利用索引读下一个版本信息
** input parameters:		uiIndex      输入索引
** output parameters:	    uiNextIndex    读出的下一条版本的索引值
** Returned value:			CErrorValueDefine::uiConstReturnFailed        函数执行失败
**                          CErrorValueDefine::uiConstReturnSuccess       函数执行成功
** Created by:				wang ying
** Created date:			2011-08-24
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				WangChangRong
** Modified date:			2011-08-25
** Descriptions:			uiIndex的取值会大于10
**
**********************************************************************************************************************/
uint32 CDeviceAttribute::GetNextVersionIndexbyIndex(uint32 uiIndex, uint32* uiNextIndex)
{
	if((uiNextIndex == NULL || uiIndex >= ver_size-1 )){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uiNextIndex = uiIndex + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}

uint32 CDeviceAttribute::GetSysClock(void) {
//	return GetClockMode();
	return objpAttSave->GetSysClock();
}
uint32 CDeviceAttribute::SetSysClock(uint32 mode, bool save) {
	if( save ) {
		objpAttSave->SetSysClock(mode);
	}
	CLOCK_SOURCE_OP_E clkSrc = (CLOCK_SOURCE_OP_E)mode;
//	if( GetDeviceSubtype() == type_emux_v12 ||
//			GetDeviceSubtype() == type_emux_v10 ) {
//		setPCMClockSource(clkSrc);
//	}
	SetClockMode(clkSrc);
	return CErrorValueDefine::uiConstReturnSuccess;
}

uint32 CDeviceAttribute::GetPcmClock(void) {
	return objpAttSave->GetPcmClock();
}
uint32 CDeviceAttribute::SetPcmClock(uint32 mode, bool save) {
	if( save ) {
		objpAttSave->SetPcmClock(mode);
	}
	CLOCK_SOURCE_OP_E clkSrc = (CLOCK_SOURCE_OP_E)mode;
	setPCMClockSource(clkSrc);
	return 0x5A;
}


uint32 CDeviceAttribute::GetDeviceSubtype(void) {
	return objpAttSave->GetSysSubDevice();
}


/**********************************************************************************************************************
 ** Function name:			GetFirstVersionIndex
 ** Descriptions:			获得第一个版本索引
 ** input parameters:		None
 ** output parameters:	    None
 ** Returned value:			第一个版本索引
 ** Created by:				WangChangRong
 ** Created date:			2011-08-30
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CDeviceAttribute::GetFirstVersionIndex()
{
	return ver_mainsoft;
}

