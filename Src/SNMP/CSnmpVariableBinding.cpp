/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpVariableBinding.cpp
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

#include "CSnmpVariableBinding.h"
/**********************************************************************************************************************
** Function name:			CSnmpVariableBinding
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-01
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CSnmpVariableBinding::CSnmpVariableBinding()
{
}
/**********************************************************************************************************************
** Function name:			~CSnmpVariableBinding
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-01
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CSnmpVariableBinding::~CSnmpVariableBinding()
{
}

/**********************************************************************************************************************
** Function name:			GetOIDObject
** Descriptions:			获得OID对象
** input parameters:		None
** output parameters:		None
** Returned value:			OID对象
** Created by:				WangChangRong
** Created date:			2011-08-03
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CSnmpVariable* CSnmpVariableBinding::GetOIDObject()
{
	return &objOID;
}

/**********************************************************************************************************************
** Function name:			GetOIDObject
** Descriptions:			获得Value对象
** input parameters:		None
** output parameters:		None
** Returned value:			Value对象
** Created by:				WangChangRong
** Created date:			2011-08-03
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CSnmpVariable* CSnmpVariableBinding::GetValueObject()
{
	return &objValue;
}


