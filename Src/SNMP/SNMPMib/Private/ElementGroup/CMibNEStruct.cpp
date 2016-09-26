/*
 * CMibNEStruct.cpp
 *
 *  Created on: 2013-7-8
 *      Author: Administrator
 */

#include "CMibNEStruct.h"

#include "GroupDeviceList.h"
#include "GroupCardList.h"
#include "GroupTopology.h"


CMibNEStruct::CMibNEStruct() {
	// TODO Auto-generated constructor stub

}

CMibNEStruct::~CMibNEStruct() {
	// TODO Auto-generated destructor stub
}

uint32 CMibNEStruct::InitialGroup(void) {
	//初始化
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,3,0};
	uint32 TableIndex = 10;
	CSnmpVariable objMib(uiInOID,10);
	InitialNode(&objMib);

	//设备组,1.1.3.1
	uiInOID[TableIndex] = 1;
	GroupDeviceList* objpdevice = new GroupDeviceList(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
	InsertDownLinkNode(objpdevice);

	//板卡组，1.1.3.2

	uiInOID[TableIndex] = 2;
	GroupCardList* objpCard = new GroupCardList(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
	InsertDownLinkNode(objpCard);

	//拓扑组 1.1.3.3

	uiInOID[TableIndex] = 3;
	GroupTopology* objpTopo = new GroupTopology(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
	InsertDownLinkNode(objpTopo);
	
	return 0x5A;
}
