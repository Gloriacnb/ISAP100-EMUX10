/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CUDPData.cpp
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

#include "CUDPData.h"
#include "string.h"
#include "CErrorValueDefine.h"
/**********************************************************************************************************************
 ** Function name:			CUDPData
 ** Descriptions:			类构造函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-8-2
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/

CUDPData::CUDPData() {

	memset(ucSourceMAC, 0x00, 6);						//源MAC
	memset(ucDestinationMAC, 0x00, 6);					//目的MAC
	memset(ucSourceIP, 0x00, 4);						//源IP
	memset(ucDestinationIP, 0x00, 6);					//目的IP
	usSourcePort = 0;						//源端口
	usDestinationPort = 0;					//目的端口
	ucpUDPData = NULL;							//UDP数据Buffer
	uiDataLength = 0;						//UDP数据长度
}

CUDPData::CUDPData(uint8* remip, uint16 remport, uint8* pdata, uint16 len) {
	usSourcePort = remport;
	memcpy(ucSourceIP, remip, 4);
	ucpUDPData = pdata;
	uiDataLength = len;
}

/**********************************************************************************************************************
 ** Function name:			~CUDPData
 ** Descriptions:			类析构函数
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
CUDPData::~CUDPData() {
}

/**********************************************************************************************************************
 ** Function name:			Decode
 ** Descriptions:			从UDP数据包中解码出UDP数据
 ** input parameters:		ucpBuffer：			二层MAC以太包数据Buffer
 ** 							uiLength：			二层MAC以太包数据长度
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							数据参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CUDPData::Decode(uint8* ucpBuffer, uint32 uiLength) {
	if (ucpBuffer == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	if (uiLength < 42) {				//MAC数据包长度小于14(MAC头部)+20(IP头部)+8(UDP头部)
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if (ucpBuffer[12] != 0x80 && ucpBuffer[13] != 0x00) {			//校验是否是IP数据包
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if (ucpBuffer[23] != 0x11) {						//校验是否是UDP协议
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	memcpy(ucDestinationMAC, ucpBuffer, 6);		//目的MAC
	memcpy(ucSourceMAC, &ucpBuffer[6], 6);		//源MAC
	memcpy(ucSourceIP, &ucpBuffer[26], 4);		//源IP
	memcpy(ucDestinationIP, &ucpBuffer[30], 4);	//目的IP
	usSourcePort = (uint16) ((ucpBuffer[34] << 8) | ucpBuffer[35]);	//源端口
	usDestinationPort = (uint16) ((ucpBuffer[36] << 8) | ucpBuffer[37]);//目的端口

	ucpUDPData = &ucpBuffer[42];							//UDP数据Buffer
	//uiDataLength = ((ucpBuffer[38] << 8) |ucpBuffer[39]);	//UDP数据长度
	uiDataLength = uiLength - 46;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			DecodeFromIPPackage
 ** Descriptions:			从IP包中解码出UDP数据，没有MAC地址
 ** input parameters:		ucpBuffer：			IP包数据Buffer
 ** 							uiLength：			IP包数据长度
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							数据参数错误返回CErrorValueDefine::uiConstReturnInputDataInvalid;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-26
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CUDPData::DecodeFromIPPackage(uint8* ucpBuffer, uint32 uiLength) {
	if (ucpBuffer == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	if (uiLength < 28) {	//IP包长度小于20(IP头部)+8(UDP头部)
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if (ucpBuffer[9] != 0x11) {	//校验是否是UDP协议
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	memcpy(ucSourceIP, &ucpBuffer[12], 4);		//源IP
	memcpy(ucDestinationIP, &ucpBuffer[16], 4);	//目的IP
	usSourcePort = (uint16) ((ucpBuffer[20] << 8) | ucpBuffer[21]);	//源端口
	usDestinationPort = (uint16) ((ucpBuffer[22] << 8) | ucpBuffer[23]);//目的端口

	ucpUDPData = &ucpBuffer[28];							//UDP数据Buffer
	//uiDataLength = ((ucpBuffer[38] << 8) |ucpBuffer[39]);	//UDP数据长度
	uiDataLength = uiLength - 28;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			Switch
 ** Descriptions:			交换源和目的
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CUDPData::Switch() {
	uint8 ucTemp[6];
	memcpy(ucTemp, ucSourceMAC, 6);
	memcpy(ucSourceMAC, ucDestinationMAC, 6);
	memcpy(ucDestinationMAC, ucTemp, 6);

	memcpy(ucTemp, ucSourceIP, 4);
	memcpy(ucSourceIP, ucDestinationIP, 4);
	memcpy(ucDestinationIP, ucTemp, 4);

	uint16 usTemp = usSourcePort;
	usSourcePort = usDestinationPort;
	usDestinationPort = usTemp;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			Clone
 ** Descriptions:			克隆UDP数据对象
 ** input parameters:		objpData：			UDP数据对象
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** 							空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CUDPData::Clone(CUDPData* objpData) {
	if (objpData == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	memcpy(ucDestinationMAC, objpData->GetDestinationMAC(), 6);		//目的MAC
	memcpy(ucSourceMAC, objpData->GetSourceMAC(), 6);		//源MAC
	memcpy(ucSourceIP, objpData->GetSourceIP(), 4);		//源IP
	memcpy(ucDestinationIP, objpData->GetDestinationIP(), 4);	//目的IP
	usSourcePort = objpData->GetSourcePort();	//源端口
	usDestinationPort = objpData->GetDestinationPort();	//目的端口

	ucpUDPData = objpData->GetData(&uiDataLength);	//UDP数据Buffer,UDP数据长度
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetSourceMAC
 ** Descriptions:			获得源MAC
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			源MAC的Buffer地址指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8* CUDPData::GetSourceMAC() {
	return ucSourceMAC;
}
/**********************************************************************************************************************
 ** Function name:			GetDestinationMAC
 ** Descriptions:			获得目的MAC
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			目的MAC的Buffer地址指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8* CUDPData::GetDestinationMAC() {
	return ucDestinationMAC;
}

/**********************************************************************************************************************
 ** Function name:			GetSourceIP
 ** Descriptions:			获得源IP
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			源IP的Buffer地址指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8* CUDPData::GetSourceIP() {
	return ucSourceIP;
}

/**********************************************************************************************************************
 ** Function name:			GetDestinationIP
 ** Descriptions:			获得目的IP
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			目的IP的Buffer地址指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8* CUDPData::GetDestinationIP() {
	return ucDestinationIP;
}

/**********************************************************************************************************************
 ** Function name:			GetSourcePort
 ** Descriptions:			获得源端口
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			源端口值
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint16 CUDPData::GetSourcePort() {
	return usSourcePort;
}

/**********************************************************************************************************************
 ** Function name:			GetDestinationPort
 ** Descriptions:			获得目的端口
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			目的端口值
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint16 CUDPData::GetDestinationPort() {
	return usDestinationPort;
}

/**********************************************************************************************************************
 ** Function name:			GetData
 ** Descriptions:			获得数据
 ** input parameters:		uipDataLength：	数据长度
 ** output parameters:		None
 ** Returned value:			数据的Buffer地址指针
 ** Created by:				WangChangRong
 ** Created date:			2011-08-02
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint8* CUDPData::GetData(uint32* uipDataLength) {
	if (uipDataLength != NULL) {
		*uipDataLength = uiDataLength;
	}
	return ucpUDPData;
}

/**********************************************************************************************************************
 ** Function name:			SetData
 ** Descriptions:			设置数据
 ** input parameters:		ucpBuffer：	数据Buffer地址
 ** 							uiLength：	数据长度
 ** output parameters:		None
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
uint32 CUDPData::SetData(uint8* ucpBuffer, uint32 uiLength) {
	if (ucpBuffer == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	ucpUDPData = ucpBuffer;
	uiDataLength = uiLength;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			SetDestinationMAC
 ** Descriptions:			设置目的MAC地址
 ** input parameters:		ucpDestMAC: 目的MAC地址指针
 ** output parameters:		None
 ** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
 **							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
 ** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
 ** Created by:				Liu Weifeng
 ** Created date:			2011-12-20
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 CUDPData::SetDestinationMAC(uint8* ucpDestMAC) {
	if (ucpDestMAC == NULL) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	memcpy(ucDestinationMAC, ucpDestMAC, 6);
	return CErrorValueDefine::uiConstReturnSUCCESS;
}

