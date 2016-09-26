/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ezwell-tech.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Liu Weifeng
** Created date:			2011-06-07
** Version:				    1.0
** Descriptions:			对Flash主备双区的操作
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:						
**
**********************************************************************************************************************/
#include "CMSSave.h"
#include "CErrorValueDefine.h"
#include "CNandFlash.h"
#include "string.h"
#include "CCheckData.h"
/**********************************************************************************************************************
** Function name:			CMSSave
** Descriptions:			构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None                               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-06-07 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
CMSSave::CMSSave()
{
}

CMSSave::CMSSave(EZ_FLASH_DATA_T* stpInfo) {
	setInfo(*stpInfo);
}


/**********************************************************************************************************************
** Function name:			CMSSave
** Descriptions:			析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None                               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-06-07 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
CMSSave::~CMSSave()
{
}


/**********************************************************************************************************************
** Function name:			ReadData
** Descriptions:			读取数据函数
** input parameters:		uiLen:	读取数据长度
** output parameters:		ucpBuf: 读取数据的缓冲
** Returned value:			CErrorValueDefine::uiConstReturnFailed:  读失败
**							CErrorValueDefine::uiConstReturnSuccess: 读成功
**							CErrorValueDefine::uiConstReturnDeviceBusy:Flash正忙
**							读取数据的时候一定要判断返回值，以防读取失败
** Created by:				Liu Weifeng                                            
** Created Date:			2011-06-07 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CMSSave::ReadData(uint8* ucpBuf, uint32 uiLen)
{
    if( flash_data_load(&DataInfo) == TRUE ) {

    	return CErrorValueDefine::uiConstReturnSuccess;
    }

    return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
** Function name:			SaveData
** Descriptions:			开始保存数据
** input parameters:		uiDelayS: 延迟几秒进行保存开始
** output parameters:		None
** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 写数据成功
** Created by:				Liu Weifeng                                            
** Created Date:			2011-06-07 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CMSSave::SaveData(uint32 uiDelayS)
{
    if( flash_data_save(&DataInfo) == TRUE ) {
    	return CErrorValueDefine::uiConstReturnSuccess;
    }

    return CErrorValueDefine::uiConstReturnFailed;
}

bool CMSSave::ReadData(void) {
	if( flash_data_load(&DataInfo) ) {
		uint32 crcResult;
		CCheckData::CRCCheck1((uint8*)DataInfo.BufAddr, DataInfo.ByteNums-4, &crcResult);
		uint32* p = (uint32*)DataInfo.BufAddr;
		uint32 point = (DataInfo.ByteNums+3) >> 2;
		return crcResult == p[point-1];
	}
	return false;
}

bool CMSSave::SaveData(void) {
	uint32 crcResult;
	CCheckData::CRCCheck1((uint8*)DataInfo.BufAddr, DataInfo.ByteNums-4, &crcResult);
	uint32* p = (uint32*)DataInfo.BufAddr;
	uint32 point = (DataInfo.ByteNums+3) >> 2;
	p[point-1] = crcResult;
	return flash_data_save(&DataInfo);
}


/*
 * 设置存储信息
 */
void CMSSave::setInfo(EZ_FLASH_DATA_T& info) {
	memcpy(&DataInfo, &info, sizeof(EZ_FLASH_DATA_T));
}


