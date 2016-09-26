/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ebbnetwork.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** FileName:				CCommonDefine.h
** Created by:				WangChangRong
** Created date:			2011-7-26
** Version:					1.0
** Descriptions:			
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**********************************************************************************************************************/


#ifndef CCOMMONDEFINE_H_
#define CCOMMONDEFINE_H_

#include "EZ_types.h"
//设备名称
static const uint8 ucGlbConstDeviceName[] = "ISAP100";

class CCommonDefine {
public:
	//设备索引ID定义
	static const uint32 uiConstDeviceIndex	= 1000;
	static const uint32 uiConstMainBoardIndex = 100;
	//设备型号名称
//	static const uint8 ucConstDeviceTypeName[] = ;
	//设备类型，0x40
	static const uint8 ucConstDeviceTypeID = 100;
	//设备子类型,使用主控卡的类型
	static const uint8 ucConstDeviceSubTypeID = 10;
	static const uint32 uiconstSlotNumber = 6;
//	/*		链表定义	Base  =   0x01000000  */
//	static const uint32 uiConstListNodeBasic = 0x01000000;
//	/*		链表节点定义	Base  =   0x01010000  */
//	static const uint32 uiConstListNodeTypeBasic = uiConstListNodeBasic+0x00010000;
//	static const uint32 uiConstListNodeTypePrivateProtocol = uiConstListNodeTypeBasic+1;
	static const uint32 uiConstFactoryDateIndex = 30000;

};


#endif /* CCOMMONDEFINE_H_ */
