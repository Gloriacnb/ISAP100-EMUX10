/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMibColumn.cpp
 ** File path:			/EMUX300/Src/Main_Code/Communication/SNMPMib/CMibColumn.cpp
 ** Created by:          Shqp
 ** Created date:        2012-3-23
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#include "CMibColumn.h"

CMibColumn::CMibColumn() {
	// TODO Auto-generated constructor stub

}

CMibColumn::~CMibColumn() {
	// TODO Auto-generated destructor stub
}

CMibColumn::CMibColumn(uint32* oid, uint32 oidLen) {
	CSnmpVariable objMib(oid,oidLen);
	InitialNode(&objMib);
}
