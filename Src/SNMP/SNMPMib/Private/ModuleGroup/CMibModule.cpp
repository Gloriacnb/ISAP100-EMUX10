/*
 * CMibModule.cpp
 *
 *  Created on: 2013-3-1
 *      Author: Administrator
 */

#include "CMibModule.h"
#include "CMibFunctionModuleGroup.h"
#include "CErrorValueDefine.h"


CMibModule::CMibModule() {
	// TODO Auto-generated constructor stub

}

CMibModule::~CMibModule() {
	// TODO Auto-generated destructor stub
}

uint32 CMibModule::InitialGroup(void) {
	//初始化
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,7,0};
	CSnmpVariable objMib(uiInOID,10);
	InitialNode(&objMib);

	//交叉连接 1.3.6.1.4.1.25449.1.1.7.5
	uiInOID[10] = 5;
	CMibFunctionModuleGroup* objpcc = new CMibFunctionModuleGroup(uiInOID, 11);
// 	objpcc->InitialGroup();
 	InsertDownLinkNode(objpcc);

	return CErrorValueDefine::uiConstReturnSuccess;

}
