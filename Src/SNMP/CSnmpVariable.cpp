/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpVariable.cpp
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

#include "CSnmpVariable.h"
#include "CErrorValueDefine.h"
#include "CSnmpStatic.h"
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			类构造函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-03
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable() {
	ucSyntax = CSnmpConstDefine::ucConstNull;		//SNMP变量类型
	uiIntegerValue = 0;										//32位整型值对象
	uiIntegerValueLow = 0;									//64位整型值对象的低32位
	uiLength = 0;											//String或OID的有效长度
	ucpChangeString = NULL;									//超长String存放Buffer指针
}
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			拷贝构造函数
 ** input parameters:		objVariable:	拷贝对象
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable(CSnmpVariable& objVariable) {
	ucSyntax = objVariable.GetSyntax();
	objVariable.GetInteger64Value(&uiIntegerValue, &uiIntegerValueLow);
	if (ucSyntax == CSnmpConstDefine::ucConstOID) {
		uint32 uiLen = 0;
		uint32* uiBuf = objVariable.GetOIDValue(&uiLen);
		if (uiLen > CSnmpConstDefine::uiConstOidMaxSize) {
			uiLength = 0;
		} else {
			for (uint32 i = 0; i < uiLen; i++) {
				uiOIDValue[i] = uiBuf[i];
			}
			uiLength = uiLen;
		}
	} else {
		uint32 uiLen = 0;
		uint8* ucBuf = objVariable.GetStringValue(&uiLen);
		if (ucBuf == NULL) {
			uiLength = 0;
			ucpChangeString = NULL;
			return;
		}
		if (uiLen >= CSnmpConstDefine::uiConstStringMaxSize) {//超过预分配内存，需要动态申请空间
			ucpChangeString = new uint8[uiLen];
			for (uint32 i = 0; i < uiLen; i++) {
				ucpChangeString[i] = ucBuf[i];
			}
			uiLength = uiLen;
		} else {
			ucpChangeString = NULL;
			for (uint32 i = 0; i < uiLen; i++) {
				ucString[i] = ucBuf[i];
			}
			uiLength = uiLen;
		}
	}

}
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			整型构造函数
 ** input parameters:		iInteger32:	整型值，设置类型为Integer32
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable(int iInteger32) {
	ucSyntax = CSnmpConstDefine::ucConstInteger32;		//SNMP变量类型
	uiIntegerValue = iInteger32;									//32位整型值对象
	uiIntegerValueLow = 0;									//64位整型值对象的低32位
	uiLength = 0;											//String或OID的有效长度
	ucpChangeString = NULL;									//超长String存放Buffer指针

}
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			无符号整型构造函数
 ** input parameters:		uiUnsignedInteger32:	无符号整型值，设置类型为ucType
 ** 							ucType：				·	数据类型
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable(uint32 uiUnsignedInteger32, uint8 ucType) {
	if (ucType != CSnmpConstDefine::ucConstGauge32
			&& ucType != CSnmpConstDefine::ucConstCounter32
			&& ucType != CSnmpConstDefine::ucConstTimeTicks) {
		ucSyntax = CSnmpConstDefine::ucConstNull;		//SNMP变量类型
		uiIntegerValue = 0;										//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针
	} else {
		ucSyntax = ucType;						//SNMP变量类型
		uiIntegerValue = uiUnsignedInteger32;						//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针

	}

}
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			64位整型构造函数
 ** input parameters:		uiInteger64High:	64位整型值高位
 ** 							uiInteger64Low:		64位整型值低位
 ** 							ucType：				·	数据类型
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable(uint32 uiInteger64High, uint32 uiInteger64Low,
		uint8 ucType) {
	if (ucType != CSnmpConstDefine::ucConstCounter64) {
		ucSyntax = CSnmpConstDefine::ucConstNull;		//SNMP变量类型
		uiIntegerValue = 0;										//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针
	} else {
		ucSyntax = ucType;						//SNMP变量类型
		uiIntegerValue = uiInteger64High;							//32位整型值对象
		uiIntegerValueLow = uiInteger64Low;						//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针
	}
}
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			字符串构造函数
 ** input parameters:		ucpBuffer:			字符串Buffer
 ** 							uiBufferLength：		字符串Buffer长度
 ** 							ucType：				数据类型
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable(uint8* ucpBuffer, uint32 uiBufferLength,
		uint8 ucType) {
	if (ucType != CSnmpConstDefine::ucConstIPAddress
			&& ucType != CSnmpConstDefine::ucConstOctetString) {
		ucSyntax = CSnmpConstDefine::ucConstNull;		//SNMP变量类型
		uiIntegerValue = 0;										//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针
	} else {

		ucSyntax = ucType;						//SNMP变量类型
		uiIntegerValue = 0;										//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针

		if (ucpBuffer == NULL) {
			uiLength = 0;
		} else if (uiBufferLength >= CSnmpConstDefine::uiConstStringMaxSize) {//超过预分配内存，需要动态申请空间
			ucpChangeString = new uint8[uiBufferLength];
			for (uint32 i = 0; i < uiBufferLength; i++) {
				ucpChangeString[i] = ucpBuffer[i];
			}
			uiLength = uiBufferLength;
		} else {
			for (uint32 i = 0; i < uiBufferLength; i++) {
				ucString[i] = ucpBuffer[i];
			}
			uiLength = uiBufferLength;
		}
	}
}
/**********************************************************************************************************************
 ** Function name:			CSnmpVariable
 ** Descriptions:			OID构造函数
 ** input parameters:		ucpBuffer:			OID Buffer
 ** 							uiBufferLength：		OID Buffer长度
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::CSnmpVariable(uint32* uipOID, uint32 uiOIDLength) {
	if (uipOID == NULL || uiOIDLength < 2
			|| uiOIDLength > CSnmpConstDefine::uiConstOidMaxSize) {
		ucSyntax = CSnmpConstDefine::ucConstNull;		//SNMP变量类型
		uiIntegerValue = 0;										//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针
	} else {
		ucSyntax = CSnmpConstDefine::ucConstOID;		//SNMP变量类型
		uiIntegerValue = 0;										//32位整型值对象
		uiIntegerValueLow = 0;									//64位整型值对象的低32位
		uiLength = 0;										//String或OID的有效长度
		ucpChangeString = NULL;								//超长String存放Buffer指针
		for (uint32 i = 0; i < uiOIDLength; i++) {
			uiOIDValue[i] = uipOID[i];
		}
		uiLength = uiOIDLength;
	}
}

/**********************************************************************************************************************
 ** Function name:			SetSyntax
 ** Descriptions:			设置变量类型
 ** input parameters:		ucType:			变量类型
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-09
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpVariable::SetSyntax(uint8 ucType) {
	ucSyntax = ucType;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			~CSnmpVariable
 ** Descriptions:			类析构函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-03
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CSnmpVariable::~CSnmpVariable() {

	if (ucpChangeString != NULL) {
		delete[] ucpChangeString;
	}
}

/**********************************************************************************************************************
 ** Function name:			Clone
 ** Descriptions:			复制SNMP变量数据
 ** input parameters:		objpVariable：			SNMP变量对象指针
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-05
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpVariable::Clone(CSnmpVariable* objpVariable) {
	if (objpVariable == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	ucSyntax = objpVariable->GetSyntax();
	objpVariable->GetInteger64Value(&uiIntegerValue, &uiIntegerValueLow);
	if (ucSyntax == CSnmpConstDefine::ucConstOID) {
		uint32 uiLen = 0;
		uint32* uiBuf = objpVariable->GetOIDValue(&uiLen);
		if (uiLen > CSnmpConstDefine::uiConstOidMaxSize) {
			uiLength = 0;
		} else {
			for (uint32 i = 0; i < uiLen; i++) {
				uiOIDValue[i] = uiBuf[i];
			}
			uiLength = uiLen;
		}
	} else {
		uint32 uiLen = 0;
		uint8* ucBuf = objpVariable->GetStringValue(&uiLen);
		if (ucBuf == NULL) {
			uiLength = 0;
			ucpChangeString = NULL;
			return CErrorValueDefine::uiConstReturnSuccess;
		}
		if (uiLen >= CSnmpConstDefine::uiConstStringMaxSize) {//超过预分配内存，需要动态申请空间
			ucpChangeString = new uint8[uiLen];
			for (uint32 i = 0; i < uiLen; i++) {
				ucpChangeString[i] = ucBuf[i];
			}
			uiLength = uiLen;
		} else {
			ucpChangeString = NULL;
			for (uint32 i = 0; i < uiLen; i++) {
				ucString[i] = ucBuf[i];
			}
			uiLength = uiLen;
		}
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			Decode
 ** Descriptions:			从数据Buffer中解码出对象
 ** input parameters:		ucpBuffer：			数据Buffer
 ** 							uiBufferLength：		数据Buffer长度
 ** output parameters:		uipOffset：			字段占用的字节数
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
uint32 CSnmpVariable::Decode(uint8* ucpBuffer, uint32 uiBufferLength,
		uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	if (uiBufferLength < 2) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	uint32 uiRet = CErrorValueDefine::uiConstReturnFailed;
	switch (ucpBuffer[0]) {
	case CSnmpConstDefine::ucConstInteger32:
		uiRet = CSnmpStatic::DecodeInteger32(ucpBuffer, uiBufferLength,
				&uiIntegerValue, uipOffset);
		break;
	case CSnmpConstDefine::ucConstGauge32:
	case CSnmpConstDefine::ucConstCounter32:
	case CSnmpConstDefine::ucConstTimeTicks:
		uiRet = CSnmpStatic::DecodeUnsignedInteger32(ucpBuffer, uiBufferLength,
				&uiIntegerValue, uipOffset);
		break;
	case CSnmpConstDefine::ucConstCounter64:
		uiRet = CSnmpStatic::DecodeInteger64(ucpBuffer, uiBufferLength,
				&uiIntegerValue, &uiIntegerValueLow, uipOffset);
		break;
	case CSnmpConstDefine::ucConstOctetString: {
		uint32 uiIntegerLen = 0;
		uint32 uiOffsettemp = 0;
		if (CSnmpStatic::DecodeLengthSection(&(ucpBuffer[1]),
				uiBufferLength - 1, &uiIntegerLen, &uiOffsettemp)
				!= CErrorValueDefine::uiConstReturnSuccess) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		if (uiBufferLength < (uiIntegerLen + uiOffsettemp + 1)) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		if (uiIntegerLen == 0) {
			uiLength = 0;
			*uipOffset = 2;
			uiRet = CErrorValueDefine::uiConstReturnSuccess;
		} else {
			if (uiIntegerLen >= CSnmpConstDefine::uiConstStringMaxSize) {//超过预分配内存，需要动态申请空间
				if (ucpChangeString != NULL) {
					delete[] ucpChangeString;
					ucpChangeString = NULL;
				}
				ucpChangeString = new uint8[uiIntegerLen];
				uint32 uiInLen = uiBufferLength;
				uiRet = CSnmpStatic::DecodeOctetString(ucpBuffer, &uiInLen,
						ucpChangeString, uipOffset);
				uiLength = uiInLen;
			} else {
				uint32 uiInLen = uiBufferLength;
				uiRet = CSnmpStatic::DecodeOctetString(ucpBuffer, &uiInLen,
						ucString, uipOffset);
				uiLength = uiInLen;
			}
		}
	}
		break;
	case CSnmpConstDefine::ucConstIPAddress: {
		if (ucpBuffer[1] == 4) {										//长度
			uint32 uiInLen = uiBufferLength;
			uiRet = CSnmpStatic::DecodeOctetString(ucpBuffer, &uiInLen,
					ucString, uipOffset);
			uiLength = uiInLen;
		}
	}
		break;
	case CSnmpConstDefine::ucConstOID: {
		uint32 uiInLen = uiBufferLength;
		uiRet = CSnmpStatic::DecodeOID(ucpBuffer, &uiInLen, uiOIDValue,
				uipOffset);
		uiLength = uiInLen;
	}
		break;
	case CSnmpConstDefine::ucConstNull:
	case CSnmpConstDefine::ucConstNoSuchObject:
	case CSnmpConstDefine::ucConstNoSuchInstance:
	case CSnmpConstDefine::ucConstEndofMibView: {
		if (ucpBuffer[1] == 0) {										//长度
			*uipOffset = 2;
			uiRet = CErrorValueDefine::uiConstReturnSuccess;
		}
	}
		break;
	default:
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiRet == CErrorValueDefine::uiConstReturnSuccess) {
		ucSyntax = ucpBuffer[0];
	}
	return uiRet;
}

/**********************************************************************************************************************
 ** Function name:			Encode
 ** Descriptions:			从对象中编码数据到Buffer
 ** input parameters:		ucpBuffer：			数据Buffer
 ** 							uiValidLength：		数据Buffer有效长度
 ** output parameters:		uipOffset：			字段占用的字节数
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
uint32 CSnmpVariable::Encode(uint8* ucpBuffer, uint32 uiValidLength,
		uint32* uipOffset) {
	if (ucpBuffer == NULL || uipOffset == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiRet = CErrorValueDefine::uiConstReturnFailed;
	switch (ucSyntax) {
	case CSnmpConstDefine::ucConstInteger32:
		uiRet = CSnmpStatic::EncodeInteger32(ucpBuffer, uiValidLength, this,
				uipOffset);
		break;
	case CSnmpConstDefine::ucConstGauge32:
	case CSnmpConstDefine::ucConstCounter32:
	case CSnmpConstDefine::ucConstTimeTicks:
		uiRet = CSnmpStatic::EncodeUnsignedInteger32(ucpBuffer, uiValidLength,
				this, uipOffset);
		break;
	case CSnmpConstDefine::ucConstCounter64:
		uiRet = CSnmpStatic::EncodeInteger64(ucpBuffer, uiValidLength, this,
				uipOffset);
		break;
	case CSnmpConstDefine::ucConstOctetString:
	case CSnmpConstDefine::ucConstIPAddress:
		uiRet = CSnmpStatic::EncodeOctetString(ucpBuffer, uiValidLength, this,
				uipOffset);
		break;
	case CSnmpConstDefine::ucConstOID:
		uiRet = CSnmpStatic::EncodeOID(ucpBuffer, uiValidLength, this,
				uipOffset);
		break;
	case CSnmpConstDefine::ucConstNull:
	case CSnmpConstDefine::ucConstNoSuchObject:
	case CSnmpConstDefine::ucConstNoSuchInstance:
	case CSnmpConstDefine::ucConstEndofMibView: {
		if (uiValidLength < 2) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
		ucpBuffer[uiValidLength - 1] = 0x00;
		ucpBuffer[uiValidLength - 2] = GetSyntax();
		*uipOffset = 2;
		uiRet = CErrorValueDefine::uiConstReturnSuccess;
	}
		break;
	default:
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return uiRet;

}

/**********************************************************************************************************************
 ** Function name:			GetSyntax
 ** Descriptions:			获得变量类型
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			变量类型
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8 CSnmpVariable::GetSyntax() {
	return ucSyntax;
}

/**********************************************************************************************************************
 ** Function name:			GetInteger32Value
 ** Descriptions:			获得32位整型值
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			32位整型值
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpVariable::GetInteger32Value() {
	return uiIntegerValue;
}

/**********************************************************************************************************************
 ** Function name:			GetInteger64Value
 ** Descriptions:			获得64位整型值
 ** input parameters:		None
 ** output parameters:		uipValueHigh：		64位整型值高位
 ** 							uipValueLow：		64位整型值低位
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpVariable::GetInteger64Value(uint32* uipValueHigh,
		uint32* uipValueLow) {
	if (uipValueHigh == NULL || uipValueLow == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	*uipValueHigh = uiIntegerValue;
	*uipValueLow = uiIntegerValueLow;
	return CErrorValueDefine::uiConstReturnSuccess;

}

/**********************************************************************************************************************
 ** Function name:			GetStringValue
 ** Descriptions:			获得字符串值
 ** input parameters:		None
 ** output parameters:		uipLength：		字符串长度
 ** Returned value:			字符串Buffer指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8* CSnmpVariable::GetStringValue(uint32* uipLength) {
	if (uiLength == 0) {
		if (uipLength != NULL) {
			*uipLength = uiLength;
		}
		return ucString;
	}
	if (uiLength >= CSnmpConstDefine::uiConstStringMaxSize) {
		if (uipLength != NULL) {
			*uipLength = uiLength;
		}
		return ucpChangeString;
	} else {
		if (uipLength != NULL) {
			*uipLength = uiLength;
		}
		return ucString;
	}
}

/**********************************************************************************************************************
 ** Function name:			GetOIDValue
 ** Descriptions:			获得OID值
 ** input parameters:		None
 ** output parameters:		uipLength：		OID长度
 ** Returned value:			OID Buffer指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-04
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32* CSnmpVariable::GetOIDValue(uint32* uipLength) {
	if (uiLength > CSnmpConstDefine::uiConstOidMaxSize) {
		if (uipLength != NULL) {
			*uipLength = 0;
		}
	} else {
		if (uipLength != NULL) {
			*uipLength = uiLength;
		}
	}
	return uiOIDValue;
}

/**********************************************************************************************************************
 ** Function name:			GetOIDValue
 ** Descriptions:			SNMP变量比较方法
 ** input parameters:		objpInVariable:		传入的比较对象
 ** output parameters:		None
 ** Returned value:			比较结果，	等于0表示相等；
 ** 										小于0表示小于传入的比较对象；
 ** 										大于0表示大于传入的比较对象；
 ** 										无法比较时默认返回大于0（1）
 ** Created by:				WangChangRong
 ** Created date:			2011-08-05
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
int CSnmpVariable::CompareTo(CSnmpVariable* objpInVariable) {
	if (objpInVariable == NULL) {
		return 1;
	}
	int iResult = 0;
	switch (ucSyntax) {
	case CSnmpConstDefine::ucConstOID: {
		if (objpInVariable->GetSyntax() != CSnmpConstDefine::ucConstOID) {
			return 1;
		}
		uint32 uiInOIDLen = 0;
		uint32* uipInOID = objpInVariable->GetOIDValue(&uiInOIDLen);
		if (uipInOID == NULL || uiInOIDLen == 0) {
			return 1;
		}
		//获得比较长度
		uint32 uiMin = uiInOIDLen;
		if (uiLength < uiMin) {
			uiMin = uiLength;
		}
		for (uint32 i = 0; i < uiMin; i++) {
			if (uiOIDValue[i] == uipInOID[i]) {
				continue;
			} else if ((uiOIDValue[i] & 0xFFFFFFFFL)
					< (uipInOID[i] & 0xFFFFFFFFL)) {
				iResult = -1;
				break;
			} else {
				iResult = 1;
				break;
			}
		}
		if (iResult == 0) {
			if (uiLength > uiInOIDLen) {
				return 1;
			} else if (uiLength == uiInOIDLen) {
				return 0;
			} else {
				return -1;
			}
		} else {
			return iResult;
		}
	}
//		break;
	default:
		iResult = 1;
		break;
	}
	return iResult;
}

/**********************************************************************************************************************
 ** Function name:			StartWith
 ** Descriptions:			OID是否以给定OID开始
 ** input parameters:		objpInVariable:		传入的比较对象
 ** output parameters:		None
 ** Returned value:			比较结果，	true表示以给定OID开始；false表示不是以给定OID开始
 ** Created by:				WangChangRong
 ** Created date:			2011-08-08
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CSnmpVariable::StartWith(CSnmpVariable* objpInVariable) {
	if (objpInVariable == NULL) {
		return false;
	}
	switch (ucSyntax) {
	case CSnmpConstDefine::ucConstOID:
		if (objpInVariable->GetSyntax() != CSnmpConstDefine::ucConstOID) {
			return false;
		}
		uint32 uiInOIDLen = 0;
		uint32* uipInOID = objpInVariable->GetOIDValue(&uiInOIDLen);
		if (uipInOID == NULL || uiInOIDLen == 0) {
			return false;
		}
		//比较长度
		if (uiInOIDLen > uiLength) {
			return false;
		}
		for (uint32 i = 0; i < uiInOIDLen; i++) {
			if (uiOIDValue[i] != uipInOID[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}
