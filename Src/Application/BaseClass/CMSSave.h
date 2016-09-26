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
**                          使用此模块请注意：1) 使用前必须初始化InitialClass()函数
**                                            2) 要保存数据的后6个字节必须为"EZWell"
**                                            3) 当有数据修改后，需要调用SaveData函数
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:						
**
**********************************************************************************************************************/

#ifndef  CMSSave_H
#define  CMSSave_H

#include "EZ_types.h"
#include "CNandFlashDef.h"
#include "CNandFlash.h"
#include "Mid_FlashData.h"

//class CNandFlash;
class  CMSSave//: public CNandFlash//, public COneTask
{
    private:
        EZ_FLASH_DATA_T DataInfo;
    public:
        
        CMSSave();
        CMSSave(EZ_FLASH_DATA_T* stpInfo);
        virtual ~CMSSave();
        void setInfo(EZ_FLASH_DATA_T& info);
        EZ_FLASH_DATA_T* getInfo(void) {
        	return &DataInfo;
        };
        uint32 ReadData(uint8* ucpBuf, uint32 uiLen);                                   //  读取uiLen个字节的数据
        bool ReadData(void);
        uint32 SaveData(uint32 uiDelayS);                                               //  保存数据
        bool SaveData(void);
};


#endif
