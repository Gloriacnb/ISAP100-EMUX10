/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpCommand.cpp
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

#include "CSnmpCommand.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CClassPointer.h"
#include "CSnmpStatic.h"
#include "CSnmpDataInOut.h"

#include <string.h>
#include <rtl.h>
#include "TerminalUart.h"
extern uint8 udp_soc;

//#include "CUDPInterface.h"
//extern CClassPointer objGlbClassPointer;
/**********************************************************************************************************************
** Function name:			CSnmpCommand
** Descriptions:			类构造函数
** input parameters:		objpIn：		SNMP数据接收对象
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

CSnmpCommand::CSnmpCommand(CSnmpDataInOut* objpIn)
{
	objpSnmpDataInOut = objpIn;				//SNMP数据接收对象
//	objpUDPInterface = NULL;				//UDP数据包来源对象
	uiRequestID = 0;								//SNMP请求ID
	ucCurrentVersion = CSnmpConstDefine::ucConstVersion2c;							//版本
	ucCurrentType = CSnmpConstDefine::ucConstGet;							//SNMP请求类型
	uiCurrentErrorStatus = 0;							//SNMP差错状态
	uiCurrentErrorIndex = 0;							//SNMP差错索引
}
/**********************************************************************************************************************
** Function name:			~CSnmpCommand
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

CSnmpCommand::~CSnmpCommand()
{
}


/**********************************************************************************************************************
** Function name:			GetCurrentRequestType
** Descriptions:			获得SNMP请求类型
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP请求类型
** Created by:				WangChangRong
** Created date:			2011-08-04
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::GetCurrentRequestType()
{
	return ucCurrentType;
}

/**********************************************************************************************************************
** Function name:			SetCurrentRequestType
** Descriptions:			设置SNMP请求类型
** input parameters:		ucType:	SNMP请求类型
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SetCurrentRequestType(uint8 ucType)
{
	ucCurrentType = ucType;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetCurrentRequestID
** Descriptions:			获得SNMP请求ID
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP请求ID
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::GetCurrentRequestID()
{
	return uiRequestID;
}

/**********************************************************************************************************************
** Function name:			SetCurrentRequestID
** Descriptions:			设置SNMP请求ID
** input parameters:		uiID:	SNMP请求ID
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SetCurrentRequestID(uint32 uiID)
{
	uiRequestID = uiID;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetCurrentRequestVersion
** Descriptions:			获得SNMP版本
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP版本
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::GetCurrentRequestVersion()
{
	return ucCurrentVersion;
}

/**********************************************************************************************************************
** Function name:			SetCurrentRequestVersion
** Descriptions:			设置SNMP版本
** input parameters:		ucVersion:	SNMP版本
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SetCurrentRequestVersion(uint8 ucVersion)
{
	ucCurrentVersion = ucVersion;
	return CErrorValueDefine::uiConstReturnSuccess;
}



/**********************************************************************************************************************
** Function name:			GetCurrentRequestErrorStatus
** Descriptions:			获得SNMP差错状态
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP差错状态
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::GetCurrentRequestErrorStatus()
{
	return uiCurrentErrorStatus;
}

/**********************************************************************************************************************
** Function name:			SetCurrentRequestErrorStatus
** Descriptions:			设置SNMP差错状态
** input parameters:		ucVersion:	SNMP差错状态
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SetCurrentRequestErrorStatus(uint32 uiStatus)
{
	uiCurrentErrorStatus = uiStatus;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetCurrentRequestErrorIndex
** Descriptions:			获得SNMP差错索引
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP差错索引
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::GetCurrentRequestErrorIndex()
{
	return uiCurrentErrorIndex;
}

/**********************************************************************************************************************
** Function name:			SetCurrentRequestErrorIndex
** Descriptions:			设置SNMP差错索引
** input parameters:		ucVersion:	SNMP差错索引
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SetCurrentRequestErrorIndex(uint32 uiIndex)
{
	uiCurrentErrorIndex = uiIndex;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			GetUDPData
** Descriptions:			获得UDP数据包对象
** input parameters:		None
** output parameters:		None
** Returned value:			UDP数据包对象
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CUDPData* CSnmpCommand::GetUDPData()
{
	return &objData;
}

/**********************************************************************************************************************
** Function name:			SetUDPData
** Descriptions:			设置UDP数据包对象
** input parameters:		objpData:	UDP数据包对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SetUDPData(CUDPData* objpData)
{
	if( objpData == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	return  objData.Clone(objpData);
}


/**********************************************************************************************************************
** Function name:			GetUDPInterface
** Descriptions:			获得UDP数据包来源对象
** input parameters:		None
** output parameters:		None
** Returned value:			UDP数据包来源对象
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//CUDPInterface* CSnmpCommand::GetUDPInterface()
//{
//	return objpUDPInterface;
//}

/**********************************************************************************************************************
** Function name:			SetUDPInterface
** Descriptions:			设置UDP数据包来源对象
** input parameters:		objpData:	UDP数据包来源对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CSnmpCommand::SetUDPInterface(CUDPInterface* objpData)
//{
//	objpUDPInterface = objpData;
//	return  CErrorValueDefine::uiConstReturnSuccess;
//}


/**********************************************************************************************************************
** Function name:			InitialObject
** Descriptions:			初始化对象
** input parameters:		objpIn：			UDP数据包来源对象
** 							objpData：				UDP数据包对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-08-02
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
/*uint32 CSnmpCommand::InitialObject(CUDPInterface* objpIn,CUDPData* objpData)
{
	if( objpData == NULL || objpIn == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	objpUDPInterface = objpIn;
	if( objData.Clone(objpData) != CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiDataLength = 0;
	uint8* ucpBuffer = objData.GetData(&uiDataLength);
	if( ucpBuffer == NULL || uiDataLength == 0 ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//解码
	if( Decode(ucpBuffer,uiDataLength) != CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( GetCurrentRequestType() != CSnmpConstDefine::ucConstGet
		&& GetCurrentRequestType() != CSnmpConstDefine::ucConstSet
		&& GetCurrentRequestType() != CSnmpConstDefine::ucConstGetNext ){
		return CErrorValueDefine::uiConstReturnFailed;
	}

	//注册任务
	CTaskScheduling* objpTaskScheduling = objGlbClassPointer.GetTaskSchedulingPointer();
	if( objpTaskScheduling == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpCell* objpCell = (CSnmpCell*)GetFirstDownLink();
	while(objpCell!=NULL){
		objpTaskScheduling->RegisterTask((COneTask*)objpCell,0);
		objpCell = (CSnmpCell*)GetNextDownLink((CEventTask*)objpCell);
	}
	//启动查询MIB库
	objpCell = (CSnmpCell*)GetFirstDownLink();
	while(objpCell!=NULL){
		objpCell->StartMibSearch();
		objpCell = (CSnmpCell*)GetNextDownLink(objpCell);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
*/
/**********************************************************************************************************************
** Function name:			Decode
** Descriptions:			从数据Buffer中解码
** input parameters:		ucpData：			UDP数据静负荷Buffer
** 							uiLength：			UDP数据静负荷Buffer长度
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-08-02
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::Decode(uint8* ucpData,uint32 uiLength)
{
	if( ucpData == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	if( ucpData[0] != 0x30 ){//不是SNMP协议头
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiOffset = 0;
	uint32 uiValue = 0;
	//获得数据包长度
	if( CSnmpStatic::DecodeLengthSection( &ucpData[1],uiLength-1,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//长度不正确
	if( uiValue == 0 || uiValue != (uiLength-1-uiOffset)){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiPoint = uiOffset+1;//解码位置计数
	//获取版本
	if( CSnmpStatic::DecodeInteger32( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//只解析v1和v2c的snmp数据包
	if( uiValue == CSnmpConstDefine::ucConstVersion1 || uiValue == CSnmpConstDefine::ucConstVersion2c ){
		ucCurrentVersion = uiValue;
	}
	else{
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiPoint += uiOffset;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//判断Community字段，此处默认判断是否是public
	{
		if( ucpData[uiPoint] != CSnmpConstDefine::ucConstOctetString 	//octetstring 类型
		 && ucpData[uiPoint+1] != 6										//长度
		 && ucpData[uiPoint+2] != 'p'										//p
		 && ucpData[uiPoint+3] != 'u'										//u
		 && ucpData[uiPoint+4] != 'b'										//b
		 && ucpData[uiPoint+5] != 'l'										//l
		 && ucpData[uiPoint+6] != 'i'										//i
		 && ucpData[uiPoint+7] != 'c' ){									//c
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiPoint += 8;
	}
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//SNMP请求类型判断
	if( ucpData[uiPoint] == CSnmpConstDefine::ucConstGet
	 || ucpData[uiPoint] == CSnmpConstDefine::ucConstSet
	 || ucpData[uiPoint] == CSnmpConstDefine::ucConstGetNext
	 || ucpData[uiPoint] == CSnmpConstDefine::ucConstResponse
	 || ucpData[uiPoint] == CSnmpConstDefine::ucConstTrap ){
		ucCurrentType = ucpData[uiPoint];
	}
	else{
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiPoint ++;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//获得数据包长度
	if( CSnmpStatic::DecodeLengthSection( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//长度不正确
	if( uiValue == 0 || uiValue != (uiLength-uiPoint-uiOffset)){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiPoint += uiOffset;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//请求ID
	if( CSnmpStatic::DecodeInteger32( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiRequestID = uiValue;
	uiPoint += uiOffset;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//Error Status字段
	if( CSnmpStatic::DecodeInteger32( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiCurrentErrorStatus = uiValue;
	uiPoint += uiOffset;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//Error Index字段
	if( CSnmpStatic::DecodeInteger32( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiCurrentErrorIndex = uiValue;
	uiPoint += uiOffset;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//变量绑定列表头字段
	if( ucpData[uiPoint] != 0x30 ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiPoint ++;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( CSnmpStatic::DecodeLengthSection( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
		!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//长度不正确
	if( uiValue == 0 || uiValue != (uiLength-uiPoint-uiOffset)){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiPoint += uiOffset;
	//长度判断
	if( uiPoint >= uiLength ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//变量绑定的解析
	while(true){
		//变量绑定列表头字段
		if( ucpData[uiPoint] != 0x30 ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiPoint ++;
		//长度判断
		if( uiPoint >= uiLength ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		if( CSnmpStatic::DecodeLengthSection( &ucpData[uiPoint],uiLength-uiPoint,&uiValue,&uiOffset)
			!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		//长度不正确
		if( uiValue == 0 ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiPoint += uiOffset;
		//长度判断
		if( uiPoint >= uiLength ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		//OID类型判断，必须是OID
		if( ucpData[uiPoint] != CSnmpConstDefine::ucConstOID ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		CSnmpCell* objpCell = new CSnmpCell(this);
		InsertDownLinkThreadTask(objpCell);
		if( objpCell->GetRequestVB()->GetOIDObject()->Decode(&ucpData[uiPoint],uiLength-uiPoint,&uiOffset)
			!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiPoint += uiOffset;
		//长度判断
		if( uiPoint >= uiLength ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		if( objpCell->GetRequestVB()->GetValueObject()->Decode(&ucpData[uiPoint],uiLength-uiPoint,&uiOffset)
			!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiPoint += uiOffset;
		//长度判断,VB解析结束
		if( uiPoint >= uiLength ){
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	}
//	return CErrorValueDefine::uiConstReturnSuccess;
}


/**********************************************************************************************************************
** Function name:			Encode
** Descriptions:			从对象中编码到CSnmpDataInOut的响应数据Buffer
** input parameters:		None
** output parameters:		uipDataLength：	数据的有效长度
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
uint32 CSnmpCommand::Encode(uint32* uipDataLength)
{
	if( uipDataLength == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpCell* objpCell = (CSnmpCell*)GetEndDownLink();
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiMaxSize = CSnmpDataInOut::uiConstResponseBufferSize;
	uint8* ucpBuffer = objpSnmpDataInOut->GetResponseBuffer();
	uint32 uiLength = 0;
	uint32 uiOffsetTemp = 0;
	uint32 uiCellNumber = 0;
	uint8 ucErrorStatus = CSnmpConstDefine::ucConstSnmpErrorSuccess;
	uint32 uiErrorIndex = 0;
	while(objpCell!=NULL){
		CSnmpVariableBinding* objpVB = objpCell->GetResponseVB();
		if( CSnmpStatic::EncodeVariableBinding(ucpBuffer,uiMaxSize-uiLength,
				objpVB,&uiOffsetTemp)
			!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiLength+=uiOffsetTemp;
		uint8 ucTemp =  objpCell->GetErrorStatus() ;
		if( ucTemp != CSnmpConstDefine::ucConstSnmpErrorSuccess ){
			ucErrorStatus = ucTemp;
			uiErrorIndex = uiCellNumber;
		}
		uiCellNumber++;
		objpCell = (CSnmpCell*)GetPrevDownLink(objpCell);
	}
	//编码长度
	if( CSnmpStatic::EncodeLengthSection(ucpBuffer,uiMaxSize-uiLength,uiLength,&uiOffsetTemp)
	!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiLength+=uiOffsetTemp;
	//长度判断
	if( uiMaxSize <= uiLength){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//头部0x30
	ucpBuffer[uiMaxSize-uiLength-1] = 0x30;
	uiLength ++;
	//长度判断
	if( uiMaxSize <= uiLength){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( ucErrorStatus != CSnmpConstDefine::ucConstSnmpErrorSuccess ){
		uiErrorIndex = uiCellNumber - uiErrorIndex;
	}
	//编码Error Index字段
	{
		CSnmpVariable objIntegerValue(uiErrorIndex);
		if( CSnmpStatic::EncodeInteger32(ucpBuffer,uiMaxSize-uiLength,&objIntegerValue,&uiOffsetTemp)
		!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiLength+=uiOffsetTemp;
		//长度判断
		if( uiMaxSize <= uiLength){
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	//编码Error status字段
	{
		CSnmpVariable objIntegerValue(ucErrorStatus);
		if( CSnmpStatic::EncodeInteger32(ucpBuffer,uiMaxSize-uiLength,&objIntegerValue,&uiOffsetTemp)
		!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiLength+=uiOffsetTemp;
		//长度判断
		if( uiMaxSize <= uiLength){
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	//编码RequestID字段
	{
		CSnmpVariable objIntegerValue(uiRequestID);
		if( CSnmpStatic::EncodeInteger32(ucpBuffer,uiMaxSize-uiLength,&objIntegerValue,&uiOffsetTemp)
		!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiLength+=uiOffsetTemp;
		//长度判断
		if( uiMaxSize <= uiLength){
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	//编码长度
	if( CSnmpStatic::EncodeLengthSection(ucpBuffer,uiMaxSize-uiLength,uiLength,&uiOffsetTemp)
	!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiLength+=uiOffsetTemp;
	//长度判断
	if( uiMaxSize <= uiLength){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//响应类型
//	if( ucCurrentType == CSnmpConstDefine::ucConstTrap){
//		ucpBuffer[uiMaxSize-uiLength-1] = CSnmpConstDefine::ucConstTrap;
//	}
//	else{
//		ucpBuffer[uiMaxSize-uiLength-1] = CSnmpConstDefine::ucConstResponse;
//	}
	ucpBuffer[uiMaxSize-uiLength-1] =  ucCurrentType;

	uiLength ++;
	//长度判断
	if( uiMaxSize <= uiLength){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//编码Community，这里默认为public
	uiLength += 8;
	//长度判断
	if( uiMaxSize <= uiLength){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	ucpBuffer[uiMaxSize-uiLength] = CSnmpConstDefine::ucConstOctetString;
	ucpBuffer[uiMaxSize-uiLength+1] = 6;
	ucpBuffer[uiMaxSize-uiLength+2] = 'p';
	ucpBuffer[uiMaxSize-uiLength+3] = 'u';
	ucpBuffer[uiMaxSize-uiLength+4] = 'b';
	ucpBuffer[uiMaxSize-uiLength+5] = 'l';
	ucpBuffer[uiMaxSize-uiLength+6] = 'i';
	ucpBuffer[uiMaxSize-uiLength+7] = 'c';
	//编码版本字段
	{
		CSnmpVariable objIntegerValue(ucCurrentVersion);
		if( CSnmpStatic::EncodeInteger32(ucpBuffer,uiMaxSize-uiLength,&objIntegerValue,&uiOffsetTemp)
		!= CErrorValueDefine::uiConstReturnSuccess){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uiLength+=uiOffsetTemp;
		//长度判断
		if( uiMaxSize <= uiLength){
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	//编码长度
	if( CSnmpStatic::EncodeLengthSection(ucpBuffer,uiMaxSize-uiLength,uiLength,&uiOffsetTemp)
	!= CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uiLength+=uiOffsetTemp;
	//长度判断
	if( uiMaxSize <= uiLength){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//SNMP头0x30
	ucpBuffer[uiMaxSize-uiLength-1] = 0x30;
	uiLength ++;
	*uipDataLength = uiLength;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			EventCompleted
** Descriptions:			事件完成动作虚方法
** input parameters:		None
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
/*uint32 CSnmpCommand::EventCompleted()
{
	uint32 uiLength = 0;
	//编码
	if( Encode(&uiLength) != CErrorValueDefine::uiConstReturnSuccess ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//交换源和目的
	objData.Switch();
	uint8* ucpBuffer = objpSnmpDataInOut->GetResponseBuffer();

	if( objData.SetData( &ucpBuffer[CSnmpDataInOut::uiConstResponseBufferSize-uiLength],uiLength)
			!= CErrorValueDefine::uiConstReturnSuccess ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//发送数据响应
	if( objpUDPInterface != NULL ){
		objpUDPInterface->TransmitUDPPackage(&objData);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
*/



/**********************************************************************************************************************
** Function name:			StartMibSearch
** Descriptions:			根据设置的CUDPData值，进行MIB库搜索
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
**							正在执行任务，不能立即获得结果，正在处理中CErrorValueDefine::uiConstReturnProcessing
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::StartMibSearch()
{
	uint32 uiDataLength = 0;
	uint8* ucpBuffer = objData.GetData(&uiDataLength);
	if( ucpBuffer == NULL || uiDataLength == 0 ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//解码
	if( Decode(ucpBuffer,uiDataLength) != CErrorValueDefine::uiConstReturnSuccess){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if( GetCurrentRequestType() != CSnmpConstDefine::ucConstGet
		&& GetCurrentRequestType() != CSnmpConstDefine::ucConstSet
		&& GetCurrentRequestType() != CSnmpConstDefine::ucConstGetNext ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	//启动查询MIB库
	CSnmpCell* objpCell = (CSnmpCell*)GetFirstDownLink();
	uint32 uiRet = 0;
	while(objpCell!=NULL){
		if(  objpCell->StartMibSearch() == CErrorValueDefine::uiConstReturnProcessing){//如果正在处理中，需要注册等待任务
			//等待，可以不用
//			if(uiRet == 0){
//				Wait(0);
//			}
			uiRet = 1;
		}
		objpCell = (CSnmpCell*)GetNextDownLink(objpCell);
	}
	if(uiRet == 0){// 处理完成
		//设置类型为响应类型
		ucCurrentType = CSnmpConstDefine::ucConstResponse;
		//交换源和目的
//		objData.Switch();
		SendSnmpCommand();
		ThreadTaskDestory();
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			SendSnmpCommand
** Descriptions:			发送命令
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
**							正在执行任务，不能立即获得结果，正在处理中CErrorValueDefine::uiConstReturnProcessing
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-13
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::SendSnmpCommand()
{
	uint32 uiLength = 0;
	//编码
	if( Encode(&uiLength) != CErrorValueDefine::uiConstReturnSuccess ){
		return CErrorValueDefine::uiConstReturnFailed;
	}

	uint8* ucpBuffer = objpSnmpDataInOut->GetResponseBuffer();

	//发送数据响应
	uint8* sendbuf = udp_get_buf (uiLength);
	memcpy (sendbuf, &ucpBuffer[CSnmpDataInOut::uiConstResponseBufferSize-uiLength], uiLength);
	  /* Send 'Hello World!' to remote peer */
	udp_send (udp_soc, objData.GetSourceIP(), objData.GetSourcePort(), sendbuf, uiLength);

//	term_dat_out_len(sendbuf, uiLength);

	return CErrorValueDefine::uiConstReturnSuccess;

}

/**********************************************************************************************************************
** Function name:			GetSnmpDataInOut
** Descriptions:			获得SNMP数据接收对象
** input parameters:		None
** output parameters:		None
** Returned value:			SNMP数据接收对象
** Created by:				WangChangRong
** Created date:			2012-03-16
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CSnmpDataInOut* CSnmpCommand::GetSnmpDataInOut()
{
	return objpSnmpDataInOut;
}


/**********************************************************************************************************************
** Function name:			GetSnmpDataInOut
** Descriptions:			清除下联SNMPCell
** input parameters:		None
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-03-16
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::Clear()
{
	//销毁下联伪线程任务对象
	if( GetFirstDownLink() !=NULL ){
		CThreadTask* obipThreadTask = GetFirstDownLink();
		CThreadTask* obipTmp = NULL;
		while( obipThreadTask != NULL ){
			obipTmp = obipThreadTask->GetThreadTaskNext();
			obipThreadTask->ThreadTaskDestory();
			obipThreadTask = obipTmp;
		}
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			Notify
** Descriptions:			任务唤醒
** 							只对伪线程任务有效，对定时任务、高优先级任务和低优先级任务无效
** input parameters:		uiNotifyType:	唤醒类型
** 							objpSourceTask:	唤醒的源伪线程任务对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-16
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
//uint32 CSnmpCommand::Notify(uint32 uiNotifyType,CThreadTask* objpSourceTask)
//{
//	//设置类型为响应类型
//	ucCurrentType = CSnmpConstDefine::ucConstResponse;
//	//交换源和目的
//	objData.Switch();
//	//发送返回命令
//	SendSnmpCommand();
//	//销毁对象
//	ThreadTaskDestory();
//
//	return CErrorValueDefine::uiConstReturnSuccess;
//}

/**********************************************************************************************************************
** Function name:			Notify
** Descriptions:			对象克隆
** input parameters:		objpSnmp:	克隆对象
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
** 							输入空指针返回CErrorValueDefine::uiConstReturnInputNULLPointer
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2012-3-18
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CSnmpCommand::Clone(CSnmpCommand* objpSnmp)
{
	if(objpSnmp == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
//	objpUDPInterface = objpSnmp->GetUDPInterface();				//UDP数据包来源对象
	objData.Clone(objpSnmp->GetUDPData());								//UDP数据包对象
	uiRequestID = objpSnmp->GetCurrentRequestID();								//SNMP请求ID
	ucCurrentVersion = objpSnmp->GetCurrentRequestVersion();							//版本
	ucCurrentType = objpSnmp->GetCurrentRequestType();							//SNMP请求类型
	uiCurrentErrorStatus = objpSnmp->GetCurrentRequestErrorStatus();							//SNMP差错状态
	uiCurrentErrorIndex = objpSnmp->GetCurrentRequestErrorIndex();							//SNMP差错索引

	CSnmpCell* objTempTask = (CSnmpCell*)objpSnmp->GetFirstDownLink();
	while(objTempTask != NULL){
		CSnmpCell* objpCell = new CSnmpCell(this);
		objpCell->Clone(objTempTask);
		InsertDownLinkThreadTask(objpCell);
		objTempTask =  (CSnmpCell*)objTempTask->GetThreadTaskNext();
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
