/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMibColumn.h
 ** File path:			/EMUX300/Src/Main_Code/Communication/SNMPMib/CMibColumn.h
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

#ifndef CMIBCOLUMN_H_
#define CMIBCOLUMN_H_

#include "CMibNodeObject.h"
/*
 *
 */
class CMibColumn : public CMibNodeObject {
public:
	CMibColumn();
	CMibColumn(uint32* oid, uint32 oidLen);
	virtual ~CMibColumn();

	virtual uint32 GetResponse(CSnmpCell* objpCell) = 0;
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell* objpCell) = 0;
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell) = 0;
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell) = 0;
};

#endif /* CMIBCOLUMN_H_ */
