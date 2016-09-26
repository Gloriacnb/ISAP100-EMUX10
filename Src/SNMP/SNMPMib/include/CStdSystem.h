/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CStdSystem.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-8
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSTDSYSTEM_H_
#define CSTDSYSTEM_H_
#include "CMibColumn.h"
#include "EZ_types.h"

class CStdSystem: public CMibColumn {
public:
	CStdSystem();
	virtual ~CStdSystem();
	//初始化标准组中对象
	uint32 InitialGroup();

	//Get的响应方法
	virtual uint32 GetResponse(CSnmpCell* objpCell);
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell* objpCell);
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell);
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell);
};

#endif /* CSTDSYSTEM_H_ */
