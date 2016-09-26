/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpStatic.cpp
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

#include "CSnmpStatic.h"
#include "CSnmpConstDefine.h"
#include "CSnmpVariableBinding.h"
#include "CSnmpVariable.h"
#include "CErrorValueDefine.h"

/**********************************************************************************************************************
 ** Function name:			DecodeLengthSection
 ** Descriptions:			从数据Buffer中获得长度字段
 ** input parameters:		ucpBuffer：			数据Buffer
 ** 							uiBufferLength：		数据Buffer长度
 ** output parameters:		uipLengthValue：		长度字段值
 ** 							uipOffset：			字段占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::DecodeLengthSection(uint8* ucpBuffer, uint32 uiBufferLength,
		uint32* uipLengthValue, uint32* uipOffset) {

	if (ucpBuffer == NULL || uipLengthValue == NULL || uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;;
	}
	if (uiBufferLength == 0) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}

	if (ucpBuffer[0] < 0x80) {
		*uipOffset = 1;
		*uipLengthValue = ucpBuffer[0];
		return CErrorValueDefine::uiConstReturnSuccess;
	} else {
		uint32 uiTemp = (ucpBuffer[0] & 0x7f);
		//长度错误
		if (uiTemp > 4) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		//长度不够
		if ((uiTemp + 1) > uiBufferLength) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		if (uiTemp == 1) {
			*uipOffset = 2;
			*uipLengthValue = ucpBuffer[1] & 0xff;
			return CErrorValueDefine::uiConstReturnSuccess;
		} else if (uiTemp == 2) {
			*uipOffset = 3;
			*uipLengthValue = ((ucpBuffer[1] & 0xff) << 8)
					| (ucpBuffer[2] & 0xff);
			return CErrorValueDefine::uiConstReturnSuccess;
		} else if (uiTemp == 3) {
			*uipOffset = 4;
			*uipLengthValue = ((ucpBuffer[1] & 0xff) << 16)
					| ((ucpBuffer[2] & 0xff) << 8) | (ucpBuffer[3] & 0xff);
			return CErrorValueDefine::uiConstReturnSuccess;
		} else if (uiTemp == 4) {
			*uipOffset = 5;
			*uipLengthValue = ((ucpBuffer[1] & 0xff) << 24)
					| ((ucpBuffer[2] & 0xff) << 16)
					| ((ucpBuffer[3] & 0xff) << 8) | (ucpBuffer[4] & 0xff);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	}
	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
 ** Function name:			DecodeInteger32
 ** Descriptions:			从数据Buffer中获得Integer32类型值
 ** input parameters:		ucpBuffer：			数据Buffer
 ** 							uiBufferLength：		数据Buffer长度
 ** output parameters:		uipInteger32：		Integer32类型值
 ** 							uipOffset：			字段占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::DecodeInteger32(uint8* ucpBuffer, uint32 uiBufferLength,
		uint32* uipInteger32, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipInteger32 == NULL || uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;;
	}
	if (uiBufferLength < 2) { //最少2字节
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	//是否是integer32类型
	if (ucpBuffer[0] != CSnmpConstDefine::ucConstInteger32) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiIntegerLen = 0;
	uint32 uiOffsettemp = 0;
	if (DecodeLengthSection(&(ucpBuffer[1]), uiBufferLength - 1, &uiIntegerLen,
			&uiOffsettemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiIntegerLen == 0 || uiIntegerLen > 4 || uiOffsettemp != 1) { //长度不应该大于4字节
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiBufferLength < uiIntegerLen + 2) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if ((ucpBuffer[2] & 0x80) > 0) {
		*uipInteger32 = 0xffff;
	} else {
		*uipInteger32 = 0x00;
	}
	for (uint32 i = 0; i < uiIntegerLen; i++) {
		*uipInteger32 = ((*uipInteger32) << 8) | ucpBuffer[2 + i];
	}
	*uipOffset = (uiIntegerLen + 2);
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			DecodeUnsignedInteger32
 ** Descriptions:			从数据Buffer中获得无符号Integer32类型值
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiBufferLength：				数据Buffer长度
 ** output parameters:		uipUnsignedInteger32：		无符号Integer32类型值
 ** 							uipOffset：					字段占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-03
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::DecodeUnsignedInteger32(uint8* ucpBuffer,
		uint32 uiBufferLength, uint32* uipUnsignedInteger32,
		uint32* uipOffset) {
	if (ucpBuffer == NULL || uipUnsignedInteger32 == NULL
			|| uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;;
	}
	if (uiBufferLength < 2) { //最少2字节
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	//是否是UnsignedInteger32类型
	if (ucpBuffer[0] != CSnmpConstDefine::ucConstCounter32
			&& ucpBuffer[0] != CSnmpConstDefine::ucConstGauge32
			&& ucpBuffer[0] != CSnmpConstDefine::ucConstTimeTicks) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//合法性检查
	uint32 uiIntegerLen = 0;
	uint32 uiOffsettemp = 0;
	if (DecodeLengthSection(&(ucpBuffer[1]), uiBufferLength - 1, &uiIntegerLen,
			&uiOffsettemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiIntegerLen == 0 || uiIntegerLen > 5 || uiOffsettemp != 1) { //长度不应该大于4字节
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiBufferLength < uiIntegerLen + 2) {
		return CErrorValueDefine::uiConstReturnFailed;
	}

	if (((uiIntegerLen > 4) && (ucpBuffer[2] != 0x00))) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//解码
	*uipUnsignedInteger32 = 0;

	uint32 i = 0;
	if (ucpBuffer[2] == 0x00) {
		i = 1;
	}
	for (; i < uiIntegerLen; i++) {
		*uipUnsignedInteger32 = ((*uipUnsignedInteger32) << 8)
				| (ucpBuffer[i + 2] & 0xff);
	}
	*uipOffset = uiIntegerLen + 2;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			DecodeInteger64
 ** Descriptions:			从数据Buffer中获得Integer64类型值
 ** input parameters:		ucpBuffer：			数据Buffer
 ** 							uiBufferLength：		数据Buffer长度
 ** output parameters:		uipInteger64High：	Integer64高32位值
 ** 							uipInteger64Low：	Integer64低32位值
 ** 							uipOffset：			字段占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::DecodeInteger64(uint8* ucpBuffer, uint32 uiBufferLength,
		uint32* uipInteger64High, uint32* uipInteger64Low, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipInteger64High == NULL || uipInteger64Low == NULL
			|| uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;;
	}
	if (uiBufferLength < 2) { //最少2字节
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	//是否是integer64类型
	if (ucpBuffer[0] != CSnmpConstDefine::ucConstCounter64) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//合法性检查
	uint32 uiIntegerLen = 0;
	uint32 uiOffsettemp = 0;
	if (DecodeLengthSection(&(ucpBuffer[1]), uiBufferLength - 1, &uiIntegerLen,
			&uiOffsettemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiIntegerLen == 0 || uiIntegerLen > 9 || uiOffsettemp != 1) { //长度不应该大于4字节
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiBufferLength < uiIntegerLen + 2) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (((uiIntegerLen > 8) && (ucpBuffer[2] != 0x00))) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//解码
	*uipInteger64High = 0;
	*uipInteger64Low = 0;
	if (uiIntegerLen == 1) {
		*uipInteger64Low = ucpBuffer[2] & 0xff;
	} else if (uiIntegerLen == 2) {
		*uipInteger64Low = (ucpBuffer[3] & 0xff) | ((ucpBuffer[2] & 0xff) << 8);
	} else if (uiIntegerLen == 3) {
		*uipInteger64Low = (ucpBuffer[4] & 0xff) | ((ucpBuffer[3] & 0xff) << 8)
				| ((ucpBuffer[2] & 0xff) << 16);
	} else if (uiIntegerLen == 4) {
		*uipInteger64Low = (ucpBuffer[5] & 0xff) | ((ucpBuffer[4] & 0xff) << 8)
				| ((ucpBuffer[3] & 0xff) << 16) | ((ucpBuffer[2] & 0xff) << 24);
	} else if (uiIntegerLen == 5) {
		*uipInteger64High = ucpBuffer[2] & 0xff;
		*uipInteger64Low = (ucpBuffer[6] & 0xff) | ((ucpBuffer[5] & 0xff) << 8)
				| ((ucpBuffer[4] & 0xff) << 16) | ((ucpBuffer[3] & 0xff) << 24);
	} else if (uiIntegerLen == 6) {
		*uipInteger64High = (ucpBuffer[3] & 0xff)
				| ((ucpBuffer[2] & 0xff) << 8);
		*uipInteger64Low = (ucpBuffer[7] & 0xff) | ((ucpBuffer[6] & 0xff) << 8)
				| ((ucpBuffer[5] & 0xff) << 16) | ((ucpBuffer[4] & 0xff) << 24);
	} else if (uiIntegerLen == 7) {
		*uipInteger64High = (ucpBuffer[4] & 0xff) | ((ucpBuffer[3] & 0xff) << 8)
				| ((ucpBuffer[2] & 0xff) << 16);
		*uipInteger64Low = (ucpBuffer[8] & 0xff) | ((ucpBuffer[7] & 0xff) << 8)
				| ((ucpBuffer[6] & 0xff) << 16) | ((ucpBuffer[5] & 0xff) << 24);
	} else if (uiIntegerLen == 8) {
		*uipInteger64High = (ucpBuffer[5] & 0xff) | ((ucpBuffer[4] & 0xff) << 8)
				| ((ucpBuffer[3] & 0xff) << 16) | ((ucpBuffer[2] & 0xff) << 24);
		*uipInteger64Low = (ucpBuffer[9] & 0xff) | ((ucpBuffer[8] & 0xff) << 8)
				| ((ucpBuffer[7] & 0xff) << 16) | ((ucpBuffer[6] & 0xff) << 24);
	} else if (uiIntegerLen == 9) {
		*uipInteger64High = (ucpBuffer[6] & 0xff) | ((ucpBuffer[5] & 0xff) << 8)
				| ((ucpBuffer[4] & 0xff) << 16) | ((ucpBuffer[3] & 0xff) << 24);
		*uipInteger64Low = (ucpBuffer[10] & 0xff) | ((ucpBuffer[9] & 0xff) << 8)
				| ((ucpBuffer[8] & 0xff) << 16) | ((ucpBuffer[7] & 0xff) << 24);
	}

	*uipOffset = (uiIntegerLen + 2);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			DecodeOctetString
 ** Descriptions:			从数据Buffer中获得OctetString类型值
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uipBufferLength：			数据Buffer长度，注意传入值会改变
 ** output parameters:		ucpString：					String类型值Buffer指针
 ** 							uipOffset：					字段占用的字节数
 ** 							uipBufferLength：			String类型值有效长度，注意传入值会改变
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-03
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::DecodeOctetString(uint8* ucpBuffer, uint32* uipBufferLength,
		uint8* ucpString, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipBufferLength == NULL || ucpString == NULL
			|| uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;;
	}
	if (*uipBufferLength < 2) { //最少2字节
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	//是否是String类型
	if (ucpBuffer[0] != CSnmpConstDefine::ucConstOctetString
			&& ucpBuffer[0] != CSnmpConstDefine::ucConstIPAddress) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//合法性检查
	uint32 uiIntegerLen = 0;
	uint32 uiOffsettemp = 0;
	if (DecodeLengthSection(&(ucpBuffer[1]), *uipBufferLength - 1,
			&uiIntegerLen, &uiOffsettemp)
			!= CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (*uipBufferLength < uiIntegerLen + 1 + uiOffsettemp) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	for (uint32 i = 0; i < uiIntegerLen; i++) {
		ucpString[i] = ucpBuffer[i + uiOffsettemp + 1];
	}
	*uipBufferLength = uiIntegerLen;
	*uipOffset = uiIntegerLen + 1 + uiOffsettemp;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			DecodeOID
 ** Descriptions:			从数据Buffer中获得OID类型值
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uipBufferLength：			数据Buffer长度，注意传入值会改变
 ** output parameters:		uipOID：						OID类型值Buffer指针
 ** 							uipOffset：					字段占用的字节数
 ** 							uipBufferLength：			OID类型值有效长度，注意传入值会改变
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-03
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::DecodeOID(uint8* ucpBuffer, uint32* uipBufferLength,
		uint32* uipOID, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipBufferLength == NULL || uipOID == NULL
			|| uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;;
	}
	if (*uipBufferLength < 2) { //最少2字节
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	//是否是OID类型
	if (ucpBuffer[0] != CSnmpConstDefine::ucConstOID) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//合法性检查
	uint32 uiIntegerLen = 0;
	uint32 uiOffsettemp = 0;
	if (DecodeLengthSection(&(ucpBuffer[1]), *uipBufferLength - 1,
			&uiIntegerLen, &uiOffsettemp)
			!= CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (*uipBufferLength < uiIntegerLen + 1 + uiOffsettemp) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiIntegerLen == 0) {
		uipOID[0] = uipOID[1] = 0;
	}

	int iSubIdentifier;
	int iPostion = 1;
	int iTempPoint = uiOffsettemp + 1;
	int iLength = uiIntegerLen;

	while (iLength > 0) {
		iSubIdentifier = 0;
		int b;
		do { /* shift and add in low order 7 bits */
			int iNext = ucpBuffer[iTempPoint];
			iTempPoint++;

			b = iNext & 0xFF;
			iSubIdentifier = (iSubIdentifier << 7) + (b & 0x7f);
			iLength--;
		} while ((iLength > 0) && ((b & 0x80) != 0)); /* last byte has high bit clear */
		uipOID[iPostion] = iSubIdentifier;
		iPostion++;
		if (iPostion >= CSnmpConstDefine::uiConstOidMaxSize) { //oid长度超过最大值
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}

	/*
	 * The first two subidentifiers are encoded into the first component
	 * with the value (X * 40) + Y, where:
	 *	X is the value of the first subidentifier.
	 *  Y is the value of the second subidentifier.
	 */
	iSubIdentifier = uipOID[1];
	if (iSubIdentifier == 0x2B) {
		uipOID[0] = 1;
		uipOID[1] = 3;
	} else {
		uipOID[1] = (iSubIdentifier % 40);
		uipOID[0] = ((iSubIdentifier - uipOID[1]) / 40);
	}
	if (iPostion < 2) {
		iPostion = 2;
	}

	*uipBufferLength = iPostion;
	*uipOffset = uiIntegerLen + 1 + uiOffsettemp;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			EncodeVariableBinding
 ** Descriptions:			从VariableBinding中编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							objpVB：						变量绑定对象指针
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeVariableBinding(uint8* ucpBuffer,
		uint32 uiValidLength, CSnmpVariableBinding* objpVB, uint32* uipOffset) {
	if (ucpBuffer == NULL || objpVB == NULL || uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiOffsetTemp = 0;
	//编码Value
	CSnmpVariable* objpValue = objpVB->GetValueObject();
	if (objpValue->Encode(ucpBuffer, uiValidLength, &uiOffsetTemp)
			!= CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//编码OID
	objpValue = objpVB->GetOIDObject();
	if (objpValue->Encode(ucpBuffer, uiValidLength - *uipOffset, &uiOffsetTemp)
			!= CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//编码长度
	if (EncodeLengthSection(ucpBuffer, uiValidLength - *uipOffset, *uipOffset,
			&uiOffsetTemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//头部0x30
	ucpBuffer[uiValidLength - *uipOffset - 1] = 0x30;
	*uipOffset = (*uipOffset) + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			EncodeLengthSection
 ** Descriptions:			长度字段值编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							uipValue：					长度字段值
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeLengthSection(uint8* ucpBuffer, uint32 uiValidLength,
		uint32 uipValue, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	int iValue = (int) uipValue;

	if (iValue < 0) {
		if (uiValidLength < 5) { //长度判断
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 5] = 0x84;
		ucpBuffer[uiValidLength - 4] = (uint8) ((iValue >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((iValue >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((iValue >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((iValue) & 0xff);
		*uipOffset = 5;
	} else if (iValue < 0x80) {
		if (uiValidLength < 1) { //长度判断
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 1] = (uint8) iValue;
		*uipOffset = 1;
	} else if (iValue <= 0xff) {
		if (uiValidLength < 2) { //长度判断
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 2] = 0x81;
		ucpBuffer[uiValidLength - 1] = (uint8) iValue;
		*uipOffset = 2;
	} else if (iValue <= 0xffff) {
		if (uiValidLength < 3) { //长度判断
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 3] = 0x82;
		ucpBuffer[uiValidLength - 2] = (uint8) ((iValue >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((iValue) & 0xff);
		*uipOffset = 3;
	} else if (iValue <= 0xffffff) {
		if (uiValidLength < 4) { //长度判断
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 4] = 0x83;
		ucpBuffer[uiValidLength - 3] = (uint8) ((iValue >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((iValue >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((iValue) & 0xff);
		*uipOffset = 4;
	} else if (iValue <= 0xffffffff) {
		if (uiValidLength < 5) { //长度判断
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 5] = 0x84;
		ucpBuffer[uiValidLength - 4] = (uint8) ((iValue >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((iValue >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((iValue >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((iValue) & 0xff);
		*uipOffset = 5;
	} else {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			EncodeInteger32
 ** Descriptions:			Integer32值编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							uipVariable：				Integer32对象
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeInteger32(uint8* ucpBuffer, uint32 uiValidLength,
		CSnmpVariable* uipVariable, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL || uipVariable == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiValueTemp = uipVariable->GetInteger32Value();
	uint32 uiSize = GetInteger32BerLength(uiValueTemp);
	if (uiValidLength <= uiSize) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	for (uint32 i = 0; i < uiSize; i++) {
		ucpBuffer[uiValidLength - 1 - i] = (uint8) ((uiValueTemp >> (i * 8))
				& 0xff);
	}
	*uipOffset = uiSize;
	uint32 uiOffsetTemp = 0;
	//编码长度
	if (EncodeLengthSection(ucpBuffer, uiValidLength - *uipOffset, *uipOffset,
			&uiOffsetTemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//类型
	ucpBuffer[uiValidLength - *uipOffset - 1] = uipVariable->GetSyntax();
	*uipOffset = (*uipOffset) + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			GetInteger32BerLength
 ** Descriptions:			获得Integer32类型编码长度
 ** input parameters:		uiValue：					Integer32类型值
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::GetInteger32BerLength(uint32 uiValue) {
	int iValue = uiValue;
	int iSize = 4;
	/*
	 * Truncate "unnecessary" bytes off of the most significant end of this
	 * 2's complement integer.  There should be no sequence of 9
	 * consecutive 1's or 0's at the most significant end of the
	 * integer.
	 */
	uint32 uiMask = 0xFF800000;
	/* mask is 0xFF800000 on a big-endian machine */
	while ((((iValue & uiMask) == 0) || ((iValue & uiMask) == uiMask))
			&& iSize > 1) {
		iSize--;
		iValue <<= 8;
	}
	return iSize;
}

/**********************************************************************************************************************
 ** Function name:			EncodeUnsignedInteger32
 ** Descriptions:			无符号Integer32值编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							uipVariable：				无符号Integer32对象
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeUnsignedInteger32(uint8* ucpBuffer,
		uint32 uiValidLength, CSnmpVariable* uipVariable, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL || uipVariable == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiValueTemp = uipVariable->GetInteger32Value();
	uint32 uiSize = GetUnsignedInteger32BerLength(uiValueTemp);
	if (uiValidLength <= uiSize) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiSize == 5) {
		ucpBuffer[uiValidLength - 5] = 0x00;
		for (uint32 x = 1; x < uiSize; x++) {
			ucpBuffer[uiValidLength - 5 + x] = (uint8) ((uiValueTemp
					>> (8 * (4 - x))) & 0xff);
		}
	} else {
		for (uint32 x = 0; x < uiSize; x++) {
			ucpBuffer[uiValidLength - uiSize + x] = (uint8) ((uiValueTemp
					>> (8 * ((uiSize - 1) - x))) & 0xff);
		}
	}
	*uipOffset = uiSize;
	uint32 uiOffsetTemp = 0;
	//编码长度
	if (EncodeLengthSection(ucpBuffer, uiValidLength - *uipOffset, *uipOffset,
			&uiOffsetTemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//类型
	ucpBuffer[uiValidLength - *uipOffset - 1] = uipVariable->GetSyntax();
	*uipOffset = (*uipOffset) + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetUnsignedInteger32BerLength
 ** Descriptions:			获得无符号Integer32类型编码长度
 ** input parameters:		uiValue：					无符号Integer32类型值
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::GetUnsignedInteger32BerLength(uint32 uiValue) {
	uint32 uiLen = 1;
	if (((uiValue >> 24) & 0xff) != 0) {
		uiLen = 4;
	} else if (((uiValue >> 16) & 0xff) != 0) {
		uiLen = 3;
	} else if (((uiValue >> 8) & 0xff) != 0) {
		uiLen = 2;
	}
	// check for 5 byte len where first byte will be
	// a null
	if (((uiValue >> (8 * (uiLen - 1))) & 0x080) != 0) {
		uiLen++;
	}
	return uiLen;
}
/**********************************************************************************************************************
 ** Function name:			EncodeInteger64
 ** Descriptions:			Integer64值编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							uipVariable：				Integer64对象
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeInteger64(uint8* ucpBuffer, uint32 uiValidLength,
		CSnmpVariable* uipVariable, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL || uipVariable == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiValueTempHigh = 0;
	uint32 uiValueTempLow = 0;
	uipVariable->GetInteger64Value(&uiValueTempHigh, &uiValueTempLow);

	uint32 uiSize = GetInteger64BerLength(uiValueTempHigh, uiValueTempLow);
	if (uiValidLength <= uiSize) {
		return CErrorValueDefine::uiConstReturnFailed;
	}

	if (uiSize == 9) {
		ucpBuffer[uiValidLength - 9] = 0x00;
		ucpBuffer[uiValidLength - 8] = (uint8) ((uiValueTempHigh >> 24) & 0xff);
		ucpBuffer[uiValidLength - 7] = (uint8) ((uiValueTempHigh >> 16) & 0xff);
		ucpBuffer[uiValidLength - 6] = (uint8) ((uiValueTempHigh >> 8) & 0xff);
		ucpBuffer[uiValidLength - 5] = (uint8) ((uiValueTempHigh) & 0xff);
		ucpBuffer[uiValidLength - 4] = (uint8) ((uiValueTempLow >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 1) {
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 2) {
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 3) {
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 4) {
		ucpBuffer[uiValidLength - 4] = (uint8) ((uiValueTempLow >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 5) {
		ucpBuffer[uiValidLength - 5] = (uint8) ((uiValueTempHigh) & 0xff);
		ucpBuffer[uiValidLength - 4] = (uint8) ((uiValueTempLow >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 6) {
		ucpBuffer[uiValidLength - 6] = (uint8) ((uiValueTempHigh >> 8) & 0xff);
		ucpBuffer[uiValidLength - 5] = (uint8) ((uiValueTempHigh) & 0xff);
		ucpBuffer[uiValidLength - 4] = (uint8) ((uiValueTempLow >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 7) {
		ucpBuffer[uiValidLength - 7] = (uint8) ((uiValueTempHigh >> 16) & 0xff);
		ucpBuffer[uiValidLength - 6] = (uint8) ((uiValueTempHigh) & 0xff);
		ucpBuffer[uiValidLength - 5] = (uint8) ((uiValueTempHigh) & 0xff);
		ucpBuffer[uiValidLength - 4] = (uint8) ((uiValueTempLow >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	} else if (uiSize == 8) {
		ucpBuffer[uiValidLength - 8] = (uint8) ((uiValueTempHigh >> 24) & 0xff);
		ucpBuffer[uiValidLength - 7] = (uint8) ((uiValueTempHigh >> 16) & 0xff);
		ucpBuffer[uiValidLength - 6] = (uint8) ((uiValueTempHigh >> 8) & 0xff);
		ucpBuffer[uiValidLength - 5] = (uint8) ((uiValueTempHigh) & 0xff);
		ucpBuffer[uiValidLength - 4] = (uint8) ((uiValueTempLow >> 24) & 0xff);
		ucpBuffer[uiValidLength - 3] = (uint8) ((uiValueTempLow >> 16) & 0xff);
		ucpBuffer[uiValidLength - 2] = (uint8) ((uiValueTempLow >> 8) & 0xff);
		ucpBuffer[uiValidLength - 1] = (uint8) ((uiValueTempLow) & 0xff);
	}

	*uipOffset = uiSize;
	uint32 uiOffsetTemp = 0;
	//编码长度
	if (EncodeLengthSection(ucpBuffer, uiValidLength - *uipOffset, *uipOffset,
			&uiOffsetTemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//类型
	ucpBuffer[uiValidLength - *uipOffset - 1] = uipVariable->GetSyntax();
	*uipOffset = (*uipOffset) + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			GetInteger64BerLength
 ** Descriptions:			获得Integer64类型编码长度
 ** input parameters:		uiValueHigh：					Integer64类型值高位字段
 ** 							uiValueLow：						Integer64类型值低位字段
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::GetInteger64BerLength(uint32 uiValueHigh,
		uint32 uiValueLow) {
	if ((uiValueHigh & 0x80000000) != 0)
		return 9;
	if (uiValueHigh == 0 && (uiValueLow < 0x80))
		return 1;
	if (uiValueHigh == 0 && (uiValueLow < 0x8000))
		return 2;
	if (uiValueHigh == 0 && (uiValueLow < 0x800000))
		return 3;
	if (uiValueHigh == 0 && (uiValueLow < 0x80000000))
		return 4;
	if (uiValueHigh == 0 && (uiValueLow >= 0x80000000))
		return 5;
	if (uiValueHigh < 0x80)
		return 5;
	if (uiValueHigh < 0x8000)
		return 6;
	if (uiValueHigh < 0x800000)
		return 7;
	if (uiValueHigh < 0x80000000)
		return 8;
	return 8;
}
/**********************************************************************************************************************
 ** Function name:			EncodeOctetString
 ** Descriptions:			OctetString值编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							uipVariable：				OctetString对象
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeOctetString(uint8* ucpBuffer, uint32 uiValidLength,
		CSnmpVariable* uipVariable, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL || uipVariable == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiSize = 0;
	uint8* ucpBufferTemp = uipVariable->GetStringValue(&uiSize);
	//长度为0，空字符串
	if (uiSize == 0) {
		if (uiValidLength < 2) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 1] = 0x00;
		ucpBuffer[uiValidLength - 2] = uipVariable->GetSyntax();
		*uipOffset = 2;
		return CErrorValueDefine::uiConstReturnSuccess;
	}
	if (ucpBufferTemp == NULL) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiValidLength <= uiSize) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	for (uint32 i = 0; i < uiSize; i++) {
		ucpBuffer[uiValidLength - uiSize + i] = ucpBufferTemp[i];
	}

	*uipOffset = uiSize;
	uint32 uiOffsetTemp = 0;
	//编码长度
	if (EncodeLengthSection(ucpBuffer, uiValidLength - *uipOffset, *uipOffset,
			&uiOffsetTemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//类型
	ucpBuffer[uiValidLength - *uipOffset - 1] = uipVariable->GetSyntax();
	*uipOffset = (*uipOffset) + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			EncodeOID
 ** Descriptions:			OID值编码到Buffer，从Buffer的后面填入数据
 ** input parameters:		ucpBuffer：					数据Buffer
 ** 							uiValidLength：				数据Buffer有效长度
 ** 							uipVariable：				OID对象
 ** output parameters:		uipOffset：					编码后占用的字节数
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::EncodeOID(uint8* ucpBuffer, uint32 uiValidLength,
		CSnmpVariable* uipVariable, uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL || uipVariable == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	uint32 uiOIDLength = 0;
	uint32* uipOIDTemp = uipVariable->GetOIDValue(&uiOIDLength);
	uint32 uiSize = GetOIDBerLength(uipOIDTemp, uiOIDLength);
	if (uiValidLength <= uiSize) {
		return CErrorValueDefine::uiConstReturnFailed;
	}

	int uiEncodedLength = uiOIDLength;
	int uiRPos = 0;

	if (uiOIDLength < 2) {
		ucpBuffer[uiValidLength - uiSize] = 0x00;
		uiEncodedLength = 0;
	} else {
		ucpBuffer[uiValidLength - uiSize] = (uint8) ((uipOIDTemp[1]
				+ (uipOIDTemp[0] * 40)) & 0xFF);
		uiEncodedLength -= 2;
		uiRPos = 2;
	}
	int i = 0;
	while (uiEncodedLength-- > 0) {
		int uiSubID = (uipOIDTemp[uiRPos++] & 0xFFFFFFFF);
		if (uiSubID < 127) {
			ucpBuffer[uiValidLength - uiSize + 1 + i] =
					(uint8) (uiSubID & 0xFF);
			i++;
		} else {
			uint32 uiMask = 0x7F; /* handle subid == 0 case */
			uint32 uiBits = 0;

			/* testmask *MUST* !!!! be of an unsigned type */
			for (uint32 uiTestMask = 0x7F, uiTestBits = 0; uiTestMask != 0;
					uiTestMask <<= 7, uiTestBits += 7) {
				if ((uiSubID & uiTestMask) > 0) { /* if any bits set */
					uiMask = uiTestMask;
					uiBits = uiTestBits;
				}
			}
			/* mask can't be zero here */
			for (; uiMask != 0x7F; uiMask >>= 7, uiBits -= 7) {
				/* fix a mask that got truncated above */
				if (uiMask == 0x1E00000) {
					uiMask = 0xFE00000;
				}
				ucpBuffer[uiValidLength - uiSize + 1 + i] = (uint8) (((uiSubID
						& uiMask) >> uiBits) | 0x80);
				i++;
			}
			ucpBuffer[uiValidLength - uiSize + 1 + i] = (uint8) (uiSubID
					& uiMask);
			i++;
		}
	}

	*uipOffset = uiSize;
	uint32 uiOffsetTemp = 0;
	//编码长度
	if (EncodeLengthSection(ucpBuffer, uiValidLength - *uipOffset, *uipOffset,
			&uiOffsetTemp) != CErrorValueDefine::uiConstReturnSuccess) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipOffset = (*uipOffset) + uiOffsetTemp;
	//长度判断
	if (uiValidLength <= *uipOffset) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//类型
	ucpBuffer[uiValidLength - *uipOffset - 1] = uipVariable->GetSyntax();
	*uipOffset = (*uipOffset) + 1;
	return CErrorValueDefine::uiConstReturnSuccess;
}
//获得OID类型编码长度

/**********************************************************************************************************************
 ** Function name:			GetOIDBerLength
 ** Descriptions:			获得OID类型编码长度
 ** input parameters:		uipOID：					OID类型值Buffer
 ** 							uiLength：				OID类型值Buffer的长度
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpStatic::GetOIDBerLength(uint32* uipOID, uint32 uiLength) {
	if (uipOID == NULL) {
		return 1;
	}
	uint32 uiTemp = 1; // for first 2 subids
	for (uint32 i = 2; i < uiLength; i++) {
		uint32 uiValue = uipOID[i] & 0xFFFFFFFF;
		if (uiValue < 0x80) { //  7 bits long subid
			uiTemp += 1;
		} else if (uiValue < 0x4000) { // 14 bits long subid
			uiTemp += 2;
		} else if (uiValue < 0x200000) { // 21 bits long subid
			uiTemp += 3;
		} else if (uiValue < 0x10000000) { // 28 bits long subid
			uiTemp += 4;
		} else { // 32 bits long subid
			uiTemp += 5;
		}
	}
	return uiTemp;
}
