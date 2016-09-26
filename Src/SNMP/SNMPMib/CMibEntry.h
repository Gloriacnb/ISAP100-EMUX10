/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CMibEntry.h
 ** File path:			/EMUX300/Src/Main_Code/Communication/SNMPMib/CMibEntry.h
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

#ifndef CMIBENTRY_H_
#define CMIBENTRY_H_

#include "CMibNodeObject.h"
#include "CErrorValueDefine.h"

/*
 *
 */
class CMibEntry : public CMibNodeObject {
public:
	CMibEntry();
	CMibEntry(uint32* oid, uint32 oidLen);
	virtual ~CMibEntry();

	virtual uint32 InitialGroup(void) {return 0;};
	virtual uint32 GetResponse(CSnmpCell*) {
		return CErrorValueDefine::uiConstReturnFailed;
	};
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell*) {
		return CErrorValueDefine::uiConstReturnFailed;
	};
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell*) {
		return CErrorValueDefine::uiConstReturnFailed;
	};
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell*) {
		return CErrorValueDefine::uiConstReturnFailed;
	};


};

#endif /* CMIBENTRY_H_ */
