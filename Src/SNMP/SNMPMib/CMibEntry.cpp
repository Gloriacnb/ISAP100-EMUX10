/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMibEntry.cpp
 ** File path:			/EMUX300/Src/Main_Code/Communication/SNMPMib/CMibEntry.cpp
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

#include "CMibEntry.h"
#include <string.h>

CMibEntry::CMibEntry() {
	// TODO Auto-generated constructor stub

}

CMibEntry::CMibEntry(uint32* oid, uint32 oidLen) {

	CSnmpVariable objMib(oid,oidLen);
	InitialNode(&objMib);
}



CMibEntry::~CMibEntry() {
	// TODO Auto-generated destructor stub
}
