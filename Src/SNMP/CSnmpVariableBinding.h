/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpVariableBinding.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-1
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSNMPVARIABLEBINDING_H_
#define CSNMPVARIABLEBINDING_H_

//#include "CEventDistributor.h"
#include "CSnmpVariable.h"
class CSnmpVariableBinding {
private:
	CSnmpVariable objOID;						//OID对象
	CSnmpVariable objValue;						//Value值对象

public:
	CSnmpVariableBinding();
	virtual ~CSnmpVariableBinding();
	//获得OID对象
	CSnmpVariable* GetOIDObject();
	//获得Value对象
	CSnmpVariable* GetValueObject();

};

#endif /* CSNMPVARIABLEBINDING_H_ */
