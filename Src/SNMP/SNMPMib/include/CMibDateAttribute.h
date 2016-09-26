/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibDateAttribute.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-30
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CMIBDATEATTRIBUTE_H_
#define CMIBDATEATTRIBUTE_H_

#include "CMibEntry.h"
#include "CMibColumn.h"

class CMibDateAttribute: public CMibEntry {
public:
	CMibDateAttribute();
	virtual ~CMibDateAttribute();
	//初始化标准组中对象
	virtual uint32 InitialGroup();
};
class CMibDateAttributeColumn: public CMibColumn
{
public:
	CMibDateAttributeColumn();
	virtual ~CMibDateAttributeColumn();

	//Get的响应方法
	virtual uint32 GetResponse(CSnmpCell* objpCell);
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell* objpCell);
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell);
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell);
};

#endif /* CMIBDATEATTRIBUTE_H_ */
