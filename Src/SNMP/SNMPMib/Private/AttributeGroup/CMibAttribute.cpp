/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibAttribute.cpp
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

#include "CMibAttribute.h"
#include "CMibBasicAttribute.h"
#include "CErrorValueDefine.h"
#include "CMibCommunicationAttribute.h"
#include "CMibDateAttribute.h"
#include "CMibVersionAttribute.h"
#include "CMibVersionInfoTable.h"
//#include "CclockMib.h"
//#include "CMibBitFileAttribute.h"
//#include "CMibBitFileLoadAttribute.h"
/**********************************************************************************************************************
 ** Function name:			CMibAttribute
 ** Descriptions:			类构造函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-23
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CMibAttribute::CMibAttribute() {
}
/**********************************************************************************************************************
 ** Function name:			~CMibAttribute
 ** Descriptions:			类析构函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-23
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/

CMibAttribute::~CMibAttribute() {
}
/**********************************************************************************************************************
 ** Function name:			InitialGroup
 ** Descriptions:			初始化标准组中对象
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-8-23
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CMibAttribute::InitialGroup() {
	//初始化
	uint32 uiInOID[] = { 1, 3, 6, 1, 4, 1, 25449, 1, 1, 9, 0 };
	CSnmpVariable objMib(uiInOID, 10);
	InitialNode(&objMib);

	//基本属性,1.1.9.1
	CMibBasicAttribute* objpBasic = new CMibBasicAttribute();
	objpBasic->InitialGroup();
	InsertDownLinkNode(objpBasic);

	//通信参数,1.1.9.2
	CMibCommunicationAttribute* objpComm = new CMibCommunicationAttribute();
	objpComm->InitialGroup();
	InsertDownLinkNode(objpComm);

	//时间参数,1.1.9.3
	CMibDateAttribute* objpDate = new CMibDateAttribute();
	objpDate->InitialGroup();
	InsertDownLinkNode(objpDate);

	//版本数据,1.1.9.4
// 	CMibVersionAttribute* objpVersion = new CMibVersionAttribute();
// 	objpVersion->InitialGroup();
// 	InsertDownLinkNode(objpVersion);

	table_info_T info = { 4, 3, 3 };
	uiInOID[10] = 4;
	CMibVersionInfoTable* objpVersion = new CMibVersionInfoTable(uiInOID,
			sizeof(uiInOID) / sizeof(uiInOID[0]), &info);
	InsertDownLinkNode(objpVersion);

// 	//时钟源,1.1.9.5
// 	CclockMib* objpClock = new CclockMib();
// 	objpClock->InitialGroup();
// 	InsertDownLinkNode(objpClock);
//	//Bit文件信息,1.1.9.8
//	CMibBitFileAttribute* objpBitFile = new CMibBitFileAttribute();
//	objpBitFile->InitialGroup();
//	InsertDownLinkNode(objpBitFile);
//
//	//Bit文件加载信息,1.1.9.9
//	CMibBitFileLoadAttribute* objpBitFileLoad = new CMibBitFileLoadAttribute();
//	objpBitFileLoad->InitialGroup();
//	InsertDownLinkNode(objpBitFileLoad);

	return CErrorValueDefine::uiConstReturnSuccess;

}
