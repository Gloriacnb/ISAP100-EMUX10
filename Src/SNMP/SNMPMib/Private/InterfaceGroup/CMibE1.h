/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMibE1.h
 ** File path:			/EMUX300/Src/Main_Code/3G/CMibE1.h
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

#ifndef CMIBE1_H_
#define CMIBE1_H_

#include "CMibGroup.h"
/*
 *
 */

typedef enum {
	table_E1_channel,
	table_E1_port,
	table_E1_alarm_property,
	table_U_port,
	table_E1_size
}Mib_E1_Table_E;


class CMibE1 : public CMibGroup {
	CMibE1();
public:
	CMibE1(uint32* oid, uint8 oidlen);
	virtual ~CMibE1();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_E1_size];
};

#endif /* CMIBE1_H_ */
