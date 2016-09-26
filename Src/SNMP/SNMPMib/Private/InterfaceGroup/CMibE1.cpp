/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMibE1.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/CMibE1.cpp
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

#include "CMibE1.h"

#include "CMibE1ChannelTable.h"
#include "CMibE1PortTable.h"
#include "CMibE1AlarmPropertyTable.h"
#include "CMibUPortTable.h"

table_info_T CMibE1::tableInfo[table_E1_size] = {
		{1, e1_Channel_size, 3},
		{2, e1_port_size, 3}, //sn, col number, index number
		{3, E1_Alarm_size, 4},
		{4, u_port_size, 3}
};


CMibE1::CMibE1(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_E1_size);
}

CMibE1::~CMibE1() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibE1::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_E1_channel:
		return new CMibE1ChannelTable(oid, oidLen, &tableInfo[sn]);
	case table_E1_port:
		return new CMibE1PortTable(oid, oidLen, &tableInfo[sn]);
	case table_E1_alarm_property:
		return new CMibE1AlarmPropertyTable(oid, oidLen, &tableInfo[sn]);
	case table_U_port:
		return new CMibUPortTable(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}

