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
#ifndef CNandFlash_CPP
#define CNandFlash_CPP

#include "CNandflash.h"
#include "CNandFlashDef.h"
#include "CErrorValueDefine.h"
#include <string.h>
#include "Mid_Nandflash.h"
// extern "C" {
//     //#include "NAND_FLASH.h"
//     extern int32 nand_lb_slc_erase_block(uint32 block);
//     extern void  nand_lb_slc_mark_bad_block(uint32 block);
//     extern int32 nand_lb_slc_is_block_bad(uint32 block);
//     extern int32 nand_lb_slc_read_sector(uint32 sector, uint8 *readbuff, uint8 *spare);
//     extern int32 nand_lb_slc_write_sector(uint32 sector, uint8 *writebuff, uint8 *spare);
//     extern int32 nand_lb_slc_is_ready(void);
// }

/**********************************************************************************************************************
** Function name:			CNandFlash
** Descriptions:			���캯�� 
** input parameters:		None
** output parameters:		None
** Returned value:			None                                            
** Created Date:			2011-06-02 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
CNandFlash::CNandFlash() {

}

/**********************************************************************************************************************
** Function name:			~CNandFlash
** Descriptions:			�������� 
** input parameters:		None
** output parameters:		None
** Returned value:			None                                            
** Created Date:			2011-06-02 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
CNandFlash::~CNandFlash()
{
    return;
}

/**********************************************************************************************************************
** Function name:			EraseSector
** Descriptions:			����һ������(��) 
** input parameters:		uiSectorNum:��Ҫ����������(��)��(ȡָ��Χ0~2047)
** output parameters:		None
** Returned value:			CNandFlashDef::uiParaError  : ��������                                 
**							CNandFlashDef::uiBusy       : Flash��æ
**                          CNandFlashDef::uiBadBlock   : ����
**                          CErrorValueDefine::uiConstReturnSuccess    : �����ɹ�
**                          CErrorValueDefine::uiConstReturnFailed     : ����ʧ��
** Created by:				Liu Weifeng                                            
** Created Date:			2011-05-19 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::EraseSector(uint32 uiSectorNum)
{
    if( (uiSectorNum > CNandFlashDef::uiMaxBlock) || (uiSectorNum < CNandFlashDef::uiMinBlock) ) {
        return CNandFlashDef::uiParaError;      //  ��������
    }
    
    if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;           //  æ
    } 
    
    if( nand_lb_slc_erase_block(uiSectorNum) == 1 ) {
        if( nand_lb_slc_is_block_bad(uiSectorNum) == 1 ) {
            nand_lb_slc_mark_bad_block(uiSectorNum);
            return CNandFlashDef::uiBadBlock;   //  ����
        } else {
            return CErrorValueDefine::uiConstReturnSuccess;    //  �ɹ�
        }
    }
    return CErrorValueDefine::uiConstReturnFailed;         //  ʧ��
}

/**********************************************************************************************************************
** Function name:			ReadFlash
** Descriptions:			��ȡuiLen���ֽڵ����� 
** input parameters:		uiAddr:��Ҫ��ȡ���ݵĿ�ʼ��ַ
**                          uiLen :��Ҫ��ȡ���ݵ��ֽڸ��� 
** output parameters:		ucpBuf:��ȡ���ݵĻ���
** Returned value:			CNandFlashDef::uiParaError: ��������
**                          CNandFlashDef::uiBusy     : ��æ                                 
**							CErrorValueDefine::uiConstReturnSuccess  : ��ȡ�ɹ�
**                          CErrorValueDefine::uiConstReturnFailed   : ��ȡʧ��
**                          CNandFlashDef::uiBadBlock : ����
** Created by:				Liu Weifeng                                            
** Created Date:			2011-05-19 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::ReadFlash(uint8* ucpBuf,uint32 uiLen, uint32 uiAddr)
{
    uint32 uiLenght  = uiLen;
    uint8* ucpBuffer = ucpBuf;
    uint32 uiCount = 0;
    uint32 uiSectorNum = AddrToSector(uiAddr);
    if( (ucpBuf == NULL) 
     || (uiLen  == 0) 
     || (uiAddr >  CNandFlashDef::uiMaxAddr) 
     || (uiSectorNum < CNandFlashDef::uiMinBlock) ) {
        return CNandFlashDef::uiParaError;          //  ��������
     }
     
     if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;               //  æ
     } 
     
     uint32 uiSector = uiAddr  / CNandFlashDef::uiBytePerSector;
     uint32 uiBlock  = uiSector / CNandFlashDef::uiSectorPerBlock;
     if( nand_lb_slc_is_block_bad(uiBlock) == 1 ) {
            nand_lb_slc_mark_bad_block(uiBlock);
            return CNandFlashDef::uiBadBlock;       //  ����
     }
     uint32 i;
     
     uint32 uiTmpCount = uiAddr % CNandFlashDef::uiBytePerSector;
     uiTmpCount += uiLenght;
     uint32 uiUseSector = uiTmpCount / CNandFlashDef::uiBytePerSector;
     if( (uiTmpCount % CNandFlashDef::uiBytePerSector) != 0 )
     {
     	uiUseSector++;
     }
     
     uint8 ucTmpBuf[CNandFlashDef::uiBytePerSector];
     for( i = 0; i < uiUseSector; i++ ) {
        /*
        if( nand_lb_slc_read_sector(uiSector + i, ucTmpBuf, NULL) == -1) {
            return CErrorValueDefine::uiConstReturnFailed;         //  ��ȡʧ��
        }*/
        nand_lb_slc_read_sector(uiSector + i, ucTmpBuf, NULL);
        uint32 uiOffset;
        if( i == 0 ) {
            uiOffset = uiAddr % CNandFlashDef::uiBytePerSector;
        } else {
            uiOffset = 0;
        }
        for( uint32 j = uiOffset; 
             (j < CNandFlashDef::uiBytePerSector);
             j++ ) {
             ucpBuffer[uiCount] = ucTmpBuf[j];
             uiCount++;
             if(uiCount >= uiLenght) {
                break;
             }
        }
     }
     return CErrorValueDefine::uiConstReturnSuccess;               //  ��ȡ�ɹ�
}

/**********************************************************************************************************************
** Function name:			WriteFlash
** Descriptions:			дuiLen���ֽڵ�����
** input parameters:		ucpBuf:Ҫд�����ݵĻ���
**                          uiLen :Ҫд�����ݵĸ���
**                          uiAddr:Ҫд�����ݵ��׵�ַ
** output parameters:		None
** Returned value:			CNandFlashDef::uiParaError: ��������
**                          CNandFlashDef::uiBusy     : ��æ                                 
**							CErrorValueDefine::uiConstReturnSuccess  : д�ɹ�
**                          CErrorValueDefine::uiConstReturnFailed   : дʧ��
**                          CNandFlashDef::uiBadBlock : ����                               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-05-19 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::WriteFlash(uint8* ucpBuf,uint32 uiLen, uint32 uiAddr)
{
    uint32 uiLenght  = uiLen;
    uint8* ucpBuffer = ucpBuf;
    uint32 uiCount = 0;
     uint32 uiSectorNum = AddrToSector(uiAddr);
    if( (ucpBuf == NULL) 
     || (uiLen  == 0) 
     || (uiAddr >  CNandFlashDef::uiMaxAddr) 
     || (uiSectorNum < CNandFlashDef::uiMinBlock) ) {
        return CNandFlashDef::uiParaError;          //  ��������
    }
     
    if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;               //  æ
    } 
     
    uint32 uiSector = uiAddr  / CNandFlashDef::uiBytePerSector;
    uint32 uiBlock  = uiSector / CNandFlashDef::uiSectorPerBlock;
    if( nand_lb_slc_is_block_bad(uiBlock) == 1 ) {
        nand_lb_slc_mark_bad_block(uiBlock);
        return CNandFlashDef::uiBadBlock;       //  ����
    }
     uint32 i;
     uint8 ucTmpBuf[CNandFlashDef::uiBytePerSector];
     
     uint32 uiTmpCount = uiAddr % CNandFlashDef::uiBytePerSector;
     uiTmpCount += uiLenght;
     uint32 uiUseSector = uiTmpCount / CNandFlashDef::uiBytePerSector;
     if( (uiTmpCount % CNandFlashDef::uiBytePerSector) != 0 )
     {
     	uiUseSector++;
     }
     
     for( i = 0; i < uiUseSector; i++ ) {
        memset(ucTmpBuf, 0xFF, CNandFlashDef::uiBytePerSector);
        //nand_lb_slc_read_sector(uiSector + i, ucTmpBuf, NULL);
        uint32 uiOffset;
        if( i == 0 ) {
            uiOffset = uiAddr % CNandFlashDef::uiBytePerSector;
        } else {
            uiOffset = 0;
        }
        for( uint32 j = uiOffset; 
             (j < CNandFlashDef::uiBytePerSector);
             j++ ) {
             ucTmpBuf[j] = ucpBuffer[uiCount];
             uiCount++;
             if( uiCount >= uiLenght ) {
                break;
             }
        }
        
        if( nand_lb_slc_write_sector(uiSector + i, ucTmpBuf, NULL) == -1) {
            return CErrorValueDefine::uiConstReturnFailed;         //  дʧ��
        }
     }
     return CErrorValueDefine::uiConstReturnSuccess;               //  д�ɹ�
}

/**********************************************************************************************************************
** Function name:			IsBadBlock
** Descriptions:			�ж��Ƿ��ǻ���
** input parameters:		uiBlockNum�����
** output parameters:		None
** Returned value:			CNandFlashDef::uiBusy     : ��æ                                 
**							CErrorValueDefine::uiConstReturnSuccess  : ���ǻ���
**                          CErrorValueDefine::uiConstReturnFailed   : дʧ��
**                          CNandFlashDef::uiBadBlock : ����                               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-05-19 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::IsBadBlock(uint32 uiBlockNum)
{
    if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;               //  æ
    }
    
    if( nand_lb_slc_is_block_bad(uiBlockNum) == 1 ) {
        nand_lb_slc_mark_bad_block(uiBlockNum);
        return CNandFlashDef::uiBadBlock;       //  ����
    }
    return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			SectorToAddr
** Descriptions:			��ת��Ϊ��ַ
** input parameters:		uiSector�����
** output parameters:		None
** Returned value:			��ַ                              
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-05 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::SectorToAddr(uint32 uiSector)
{
    return (uiSector * CNandFlashDef::uiSectorPerBlock * CNandFlashDef::uiBytePerSector);
}

/**********************************************************************************************************************
** Function name:			AddrToSector
** Descriptions:			��ַת��Ϊ��
** input parameters:		uiAddr����ַ
** output parameters:		None
** Returned value:			��                      
** Created by:				Liu Weifeng                                            
** Created Date:			2011-07-05 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::AddrToSector(uint32 uiAddr)
{
    return (uiAddr / CNandFlashDef::uiSectorPerBlock / CNandFlashDef::uiBytePerSector);
}

/**********************************************************************************************************************
** Function name:			IsBusy
** Descriptions:			Flash�Ƿ���æ
** input parameters:		None
** output parameters:		None
** Returned value:			CNandFlashDef::uiBusy: Flash��æ
**                          CNandFlashDef::uiReady�� Flash��æ               
** Created by:				Liu Weifeng                                            
** Created Date:			2011-11-22 
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Descriptions:			
**
**********************************************************************************************************************/
uint32 CNandFlash::IsBusy()
{
    if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;           //  æ
    }
    return CNandFlashDef::uiReady;
}

#endif
