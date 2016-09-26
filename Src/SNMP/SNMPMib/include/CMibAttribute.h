/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibAttribute.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-24
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CMIBATTRIBUTE_H_
#define CMIBATTRIBUTE_H_

#include "CMibEntry.h"

class CMibAttribute: public CMibEntry
{
public:
	CMibAttribute();
	virtual ~CMibAttribute();
	//初始化组中对象
	virtual uint32 InitialGroup();
};

#endif /* CMIBATTRIBUTE_H_ */
