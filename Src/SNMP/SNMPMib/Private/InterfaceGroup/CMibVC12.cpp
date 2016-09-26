/*
 * CMibVC12.cpp
 *
 *  Created on: 2013-3-3
 *      Author: Administrator
 */

#include "CMibVC12.h"
#include "CMibVC12Port.h"
CMibVC12::CMibVC12(){
	// TODO Auto-generated constructor stub

}

CMibVC12::~CMibVC12() {
	// TODO Auto-generated destructor stub
}

uint32 CMibVC12::InitialGroup(void) {
	uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,8,3};
	CSnmpVariable objMib(uiInOID,11);
	InitialNode(&objMib);


	//vc12接口列表,		1.3.6.1.4.1.25449.1.1.8.3.2
	CMibVC12Port* objpPort= new CMibVC12Port();
	objpPort->InitialGroup();
	InsertDownLinkNode(objpPort);
	return 0x5A;
}
