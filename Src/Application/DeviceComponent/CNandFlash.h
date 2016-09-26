/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ezwell-tech.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Liu Weifeng
** Created date:			2011-05-19
** Version:				    1.0
** Descriptions:			��NandFlash�����Ľ�һ����װ
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
        uint32 EraseSector(uint32 uiSectorNum);                         //  ����һ������(��)
        uint32 ReadFlash(uint8* ucpBuf,uint32 uiLen, uint32 uiAddr);    //  �ӵ�ַuiAddr��ʼ��uiLen�����ݵ�ucpBuf��
        uint32 WriteFlash(uint8* ucpBuf,uint32 uiLen, uint32 uiAddr);   //  �ӵ�ַuiAddr��ʼдuiLen��ucpBuf�е�����
        uint32 IsBadBlock(uint32 uiBlockNum);                           //  �Ƿ񻵿�
        uint32 SectorToAddr(uint32 uiSector);                           //  ��ת��Ϊ��ַ
        uint32 AddrToSector(uint32 uiAddr);                                    //  ��ַת��Ϊ��
        uint32 IsBusy();
};

#endif

