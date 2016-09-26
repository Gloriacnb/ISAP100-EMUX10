/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpStatic.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-2
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSNMPSTATIC_H_
#define CSNMPSTATIC_H_
#include "EZ_types.h"
class CSnmpVariableBinding;
class CSnmpVariable;
class CSnmpStatic
{
public:
	//从数据Buffer中获得长度字段
	static uint32 DecodeLengthSection(uint8* ucpBuffer,uint32 uiBufferLength,uint32* uipLengthValue,uint32* uipOffset);

	//从数据Buffer中获得Integer32类型值
	static uint32 DecodeInteger32(uint8* ucpBuffer,uint32 uiBufferLength,uint32* uipInteger32,uint32* uipOffset);
	//从数据Buffer中获得无符号Integer32类型值
	static uint32 DecodeUnsignedInteger32(uint8* ucpBuffer,uint32 uiBufferLength,uint32* uipUnsignedInteger32,uint32* uipOffset);
	//从数据Buffer中获得Integer64类型值
	static uint32 DecodeInteger64(uint8* ucpBuffer,uint32 uiBufferLength,uint32* uipInteger64High,uint32* uipInteger64Low,uint32* uipOffset);
	//从数据Buffer中获得OctetString类型值
	static uint32 DecodeOctetString(uint8* ucpBuffer,uint32* uipBufferLength,uint8* ucpString,uint32* uipOffset);
	//从数据Buffer中获得OID类型值
	static uint32 DecodeOID(uint8* ucpBuffer,uint32* uipBufferLength,uint32* uipOID,uint32* uipOffset);

	//从VariableBinding中编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeVariableBinding(uint8* ucpBuffer,uint32 uiValidLength,CSnmpVariableBinding* objpVB,uint32* uipOffset);
	//长度字段值编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeLengthSection(uint8* ucpBuffer,uint32 uiValidLength,uint32 uipValue,uint32* uipOffset);
	//Integer32值编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeInteger32(uint8* ucpBuffer,uint32 uiValidLength,CSnmpVariable* uipVariable,uint32* uipOffset);
	//获得Integer32类型编码长度
	static uint32 GetInteger32BerLength(uint32 uiValue);
	//无符号Integer32值编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeUnsignedInteger32(uint8* ucpBuffer,uint32 uiValidLength,CSnmpVariable* uipVariable,uint32* uipOffset);
	//获得无符号Integer32类型编码长度
	static uint32 GetUnsignedInteger32BerLength(uint32 uiValue);
	//Integer64值编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeInteger64(uint8* ucpBuffer,uint32 uiValidLength,CSnmpVariable* uipVariable,uint32* uipOffset);
	//获得Integer64类型编码长度
	static uint32 GetInteger64BerLength(uint32 uiValueHigh,uint32 uiValueLow);
	//OctetString值编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeOctetString(uint8* ucpBuffer,uint32 uiValidLength,CSnmpVariable* uipVariable,uint32* uipOffset);
	//OID值编码到Buffer，从Buffer的后面填入数据
	static uint32 EncodeOID(uint8* ucpBuffer,uint32 uiValidLength,CSnmpVariable* uipVariable,uint32* uipOffset);
	//获得OID类型编码长度
	static uint32 GetOIDBerLength(uint32* uipOID,uint32 uiLength);
};

#endif /* CSNMPSTATIC_H_ */
