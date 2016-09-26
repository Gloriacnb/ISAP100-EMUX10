/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpVariable.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-3
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSNMPVARIABLE_H_
#define CSNMPVARIABLE_H_
#include "EZ_types.h"
#include "CSnmpConstDefine.h"
class CSnmpVariable
{
private:
	uint32 uiIntegerValue;										//32位整型值对象
	uint32 uiIntegerValueLow;									//64位整型值对象的低32位
	uint32 uiLength;											//String或OID的有效长度
	uint8* ucpChangeString;										//超长String存放Buffer指针
	uint32 uiOIDValue[CSnmpConstDefine::uiConstOidMaxSize];		//存放OID的Buffer
	uint8 ucString[CSnmpConstDefine::uiConstStringMaxSize];		//存放String的Buffer
	uint8 ucSyntax;												//SNMP变量类型

public:
	CSnmpVariable();
	CSnmpVariable(CSnmpVariable& objVariable);									//拷贝构造函数
	CSnmpVariable(int iInteger32);												//整型构造函数
	CSnmpVariable(uint32 uiUnsignedInteger32,uint8 ucType);						//无符号整型构造函数
	CSnmpVariable(uint32 uiInteger64High,uint32 uiInteger64Low,uint8 ucType);	//64位整型构造函数
	CSnmpVariable(uint8* ucpBuffer,uint32 uiBufferLength,uint8 ucType);			//字符串构造函数
	CSnmpVariable(uint32* uipOID,uint32 uiOIDLength);							//OID构造函数
	virtual ~CSnmpVariable();


	//复制SNMP变量数据
	uint32 Clone(CSnmpVariable* objpVariable);

	//从数据Buffer中解码出对象
	uint32 Decode(uint8* ucpBuffer,uint32 uiBufferLength,uint32* uipOffset);
	//从对象中编码数据到Buffer
	uint32 Encode(uint8* ucpBuffer,uint32 uiValidLength,uint32* uipOffset);

	//获得变量类型
	uint8 GetSyntax();
	//设置变量类型
	uint32 SetSyntax(uint8 ucType);
	//获得32位整型值
	uint32 GetInteger32Value();
	//获得64位整型值
	uint32 GetInteger64Value(uint32* uipValueHigh,uint32* uipValueLow);
	//获得字符串值
	uint8* GetStringValue(uint32* uipLength);
	//获得OID值
	uint32* GetOIDValue(uint32* uipLength);

	//SNMP变量比较方法
	int CompareTo(CSnmpVariable* objpInVariable);
	//OID是否以给定OID开始
	uint32 StartWith(CSnmpVariable* objpInVariable);


};

#endif /* CSNMPVARIABLE_H_ */
