/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ezwell-tech.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Zhou Houzhen
** Created date:			2011-07-07
** Version:				    1.0
** Descriptions:			数据加校验和检测校验
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:						
**
**********************************************************************************************************************/
#include "CCheckData.h"
#include "CErrorValueDefine.h"
//#include "config.h"
/**********************************************************************************************************************
** Function name:			AddrCheckSum
** Descriptions:			数据加校验和
** input parameters:		ucbuffer:	加校验和的数据
							uilen:		数据长度
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnSuccess:成功
** Created by:				Zhou Houzhen
** Created date:			2011-07-07
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CCheckData::AddCheckSum(uint8* ucbuff,uint32 uiLength)
{
	uint8 suma;
	uint8 sumx;
	CalculateSum(&ucbuff[1],ucbuff[2],&suma,&sumx);
	ucbuff[uiLength-2] = suma;
	ucbuff[uiLength-1] = sumx;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			CalculateSum
** Descriptions:			数据计算校验和
** input parameters:		ucbuffer:	计算校验和的数据
							uilen:		数据长度
							ucsuma:		校验和地址
							ucsumx:		校验和地址
** output parameters:		None
** Returned value:			None
** Created by:				Zhou Houzhen
** Created date:			2011-07-04
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CCheckData::CalculateSum(uint8* ucbuffer, uint32 uilen, uint8* ucsuma, uint8* ucsumx)
{
	if( (ucbuffer == NULL) || (ucsuma == NULL) || (ucsumx == NULL) )
		 return CErrorValueDefine::uiConstReturnFailed;
	
	*ucsuma = ucbuffer[0];
	*ucsumx = ucbuffer[0];
	for( uint32 i = 1; i < uilen; i++ )
	{
		*ucsuma = (uint8)(*ucsuma + ucbuffer[i]);
		*ucsumx = (uint8)(*ucsumx ^ ucbuffer[i]);	
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			CheckSum
** Descriptions:			数据检查校验和
** input parameters:		ucbuff:		检验的数据
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnFailed;失败
							CErrorValueDefine::uiConstReturnSuccess;成功
** Created by:				Zhou Houzhen
** Created date:			2011-07-04
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CCheckData::CheckSum(uint8* ucpbuff)
{
	if( (ucpbuff[0] != 0x7E) || (ucpbuff[1] != 0x0F) )
	{
		return CErrorValueDefine::uiConstReturnFailed;
	}
	uint32 uiCklen  = ucpbuff[2];
	uint8 uiSuma = ucpbuff[1];
	uint8 uiSumx = ucpbuff[1];
	for( int i=1; i < uiCklen; i++ )
	{
		uiSuma =(uint8)(uiSuma + ucpbuff[1+i]);
		uiSumx = (uint8)(uiSumx ^ ucpbuff[1+i]);	
	}
	if(uiSuma != ucpbuff[uiCklen+1]) 
	{
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if(uiSumx != ucpbuff[uiCklen+2])
	{
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			CRCCheck1
** Descriptions:			数据CRC检查
** input parameters:		ucBuf: 需要校验的数据的首地址
							uiLen: 需要校验的数据长度
** output parameters:		uipCRCResult: CRC校验的结果
** Returned value:			CErrorValueDefine::uiConstReturnSuccess:	成功
							CErrorValueDefine::uiConstReturnFailed:	失败
** Created by:				Zhou Houzhen
** Created date:			2011-07-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

uint32 CCheckData::CRCCheck1(uint8 *ucBuf, uint32 uiLen, uint32 *uipCRCResult)
{
	/*ulPolynomial = 0x04c11db7*/
	
    uint32 i = 0;
    uint32 uiCRC32 = 0;
    uint32 uiTabitem;
    
    if ((ucBuf == NULL) || (uiLen == 0) || (uipCRCResult == NULL)) {
	    return CErrorValueDefine::uiConstReturnFailed;
	}
	
    while(i < uiLen) {
		uiTabitem = ( uiCRC32 >> 24 ) ^ *(ucBuf + i);
        uiCRC32   = ( uiCRC32 << 8  ) ^ uiCRCTable[uiTabitem];
        i++;
    }
    *uipCRCResult = uiCRC32;
    return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			CRCCheck2
** Descriptions:			带初值的CRC校验
** input parameters:		ucBuf: 需要校验的数据的首地址
							uiLen: 需要校验的数据长度
							uiInitailValue: CRC校验的初值
** output parameters:		uipCRCResult: CRC校验的结果
** Returned value:			CErrorValueDefine::uiConstReturnSuccess:	成功
							CErrorValueDefine::uiConstReturnFailed:	失败
** Created by:				Zhou Houzhen
** Created date:			2011-07-05
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CCheckData::CRCCheck2(uint8 *ucBuf, uint32 uiLen, uint32 uiInitailValue, uint32 *uipCRCResult)
{
	/*ulPolynomial = 0x04c11db7*/
	
    uint32 i = 0;
    uint32 uiCRC32 = uiInitailValue;
    uint32 uiTabitem;
    
    if ((ucBuf == NULL) || (uiLen == 0) || (uipCRCResult == NULL)) {
	    return CErrorValueDefine::uiConstReturnFailed;
	}
	
    while(i < uiLen) {
		uiTabitem = ( uiCRC32 >> 24 ) ^ *(ucBuf + i);
        uiCRC32   = ( uiCRC32 << 8  ) ^ uiCRCTable[uiTabitem];
        i++;
    }
    *uipCRCResult = uiCRC32;
    return CErrorValueDefine::uiConstReturnSuccess;
}
