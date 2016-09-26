/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibInterface.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-10-25
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CMibInterface.h"
//#include "CMibSTMInteface.h"
#include "CErrorValueDefine.h"

//#include "CMibVC4Inteface.h"
//#include "CMibVC12Inteface.h"
#include "CMibE1.h"
#include "CMibVC12.h"
#include "CMibVcgGroup.h"
#include "CMibSTM.h"
#include "CMibTS.h"
#include "CMibETH.h"
#include "CMibXE1.h"
#include "CMibNMPortGroup.h"

//#include "CMibE1Inteface.h"
/**********************************************************************************************************************
** Function name:			CMibInterface
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-10-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibInterface::CMibInterface() {
}

/**********************************************************************************************************************
** Function name:			~CMibInterface
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-10-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CMibInterface::~CMibInterface() {
}
/**********************************************************************************************************************
** Function name:			InitialGroup
** Descriptions:			初始化标准组中对象
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-10-25
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibInterface::InitialGroup()
{
	//初始化
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,8,0};
	uint32 TableIndex = 10;
	CSnmpVariable objMib(uiInOID,10);
	InitialNode(&objMib);

	//STM接口,1.1.8.1
	uiInOID[TableIndex] = 1;
	CMibSTM* objpSTM = new CMibSTM(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
	InsertDownLinkNode(objpSTM);

	//VC4接口，1.1.8.2
	
	//VC12接口，1.1.8.3
	CMibVC12* objpVC12 = new CMibVC12();
	objpVC12->InitialGroup();
	InsertDownLinkNode(objpVC12);
	//ETH接口 1.1.8.4
 	uiInOID[TableIndex] = 4;
 	CMibETH* objpETH = new CMibETH(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
	InsertDownLinkNode(objpETH);
	//VCG接口，1.1.8.5
 	uiInOID[TableIndex] = 5;
 	CMibVcgGroup* objpVCG = new CMibVcgGroup(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
//	objpVCG->InitialGroup();
	InsertDownLinkNode(objpVCG);

	//E1接口，1.1.8.7
 	uiInOID[TableIndex] = 7;
	CMibE1* objpE1 = new CMibE1(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
 	InsertDownLinkNode(objpE1);

 	//64k接口 1.1.8.8
  	uiInOID[TableIndex] = 8;
  	CMibTS* objpTS = new CMibTS(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
  	InsertDownLinkNode(objpTS);

	//XE1接口 1.1.8.9
  	uiInOID[TableIndex] = 9;
  	CMibXE1* objpxe1 = new CMibXE1(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
  	InsertDownLinkNode(objpxe1);
	
    //CMibNMPortGroup
    uiInOID[TableIndex] = 11;
    CMibNMPortGroup* objpNMPort = new CMibNMPortGroup(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
    InsertDownLinkNode(objpNMPort);

    return CErrorValueDefine::uiConstReturnSuccess;


}
