/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibInterface.h
 ** Created by:				WangChangRong
 ** Created date:			2011-10-25
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CMIBINTERFACE_H_
#define CMIBINTERFACE_H_

//CMibInterface
#include "CMibEntry.h"

class CMibInterface: public CMibEntry {
public:
	CMibInterface();
	virtual ~CMibInterface();
	//初始化组中对象
	virtual uint32 InitialGroup();
};

#endif /* CMIBINTERFACE_H_ */
