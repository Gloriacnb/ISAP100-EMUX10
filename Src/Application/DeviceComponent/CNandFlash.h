/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ezwell-tech.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Liu Weifeng
** Created date:			2011-05-19
** Version:				    1.0
** Descriptions:			对NandFlash驱动的进一步封装
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:						
**
**********************************************************************************************************************/
#ifndef CNandFlash_H
#define CNandFlash_H

#include "EZ_types.h"

class CNandFlash
{
    public:
        CNandFlash();
        ~CNandFlash();
        uint32 EraseSector(uint32 uiSectorNum);                         //  擦除一个扇区(块)
        uint32 ReadFlash(uint8* ucpBuf,uint32 uiLen, uint32 uiAddr);    //  从地址uiAddr开始读uiLen个数据到ucpBuf中
        uint32 WriteFlash(uint8* ucpBuf,uint32 uiLen, uint32 uiAddr);   //  从地址uiAddr开始写uiLen个ucpBuf中的数据
        uint32 IsBadBlock(uint32 uiBlockNum);                           //  是否坏块
        uint32 SectorToAddr(uint32 uiSector);                           //  块转换为地址
        uint32 AddrToSector(uint32 uiAddr);                                    //  地址转换为块
        uint32 IsBusy();
};

#endif

