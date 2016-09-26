/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibVersionAttribute.h
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

#ifndef CMIBVERSIONATTRIBUTE_H_
#define CMIBVERSIONATTRIBUTE_H_

#include "CMibEntry.h"
#include "CMibColumn.h"

class CMibVersionAttribute: public CMibEntry {
public:
	CMibVersionAttribute();
	virtual ~CMibVersionAttribute();
	//初始化标准组中对象
	virtual uint32 InitialGroup();
};
class CMibVersionAttributeColumn: public CMibColumn {
public:
	CMibVersionAttributeColumn();
	virtual ~CMibVersionAttributeColumn();

	//Get的响应方法
	virtual uint32 GetResponse(CSnmpCell* objpCell);
	//Set的响应方法
	virtual uint32 SetResponse(CSnmpCell* objpCell);
	//GetNext调用方法1：获得第一个对象的OID
	virtual uint32 GetFirstValidOID(CSnmpCell* objpCell);
	//GetNext调用方法2：获得下一个对象的OID
	virtual uint32 GetNextValidOID(CSnmpCell* objpCell);
};

#endif /* CMIBVERSIONATTRIBUTE_H_ */
