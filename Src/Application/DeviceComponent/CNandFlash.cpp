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
** Descriptions:			构造函数 
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
** Descriptions:			析构函数 
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
** Descriptions:			擦除一个扇区(块) 
** input parameters:		uiSectorNum:所要擦除的扇区(块)号(取指范围0~2047)
** output parameters:		None
** Returned value:			CNandFlashDef::uiParaError  : 参数错误                                 
**							CNandFlashDef::uiBusy       : Flash正忙
**                          CNandFlashDef::uiBadBlock   : 坏块
**                          CErrorValueDefine::uiConstReturnSuccess    : 擦除成功
**                          CErrorValueDefine::uiConstReturnFailed     : 擦除失败
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
        return CNandFlashDef::uiParaError;      //  参数错误
    }
    
    if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;           //  忙
    } 
    
    if( nand_lb_slc_erase_block(uiSectorNum) == 1 ) {
        if( nand_lb_slc_is_block_bad(uiSectorNum) == 1 ) {
            nand_lb_slc_mark_bad_block(uiSectorNum);
            return CNandFlashDef::uiBadBlock;   //  坏块
        } else {
            return CErrorValueDefine::uiConstReturnSuccess;    //  成功
        }
    }
    return CErrorValueDefine::uiConstReturnFailed;         //  失败
}

/**********************************************************************************************************************
** Function name:			ReadFlash
** Descriptions:			读取uiLen个字节的数据 
** input parameters:		uiAddr:所要读取数据的开始地址
**                          uiLen :所要读取数据的字节个数 
** output parameters:		ucpBuf:读取数据的缓冲
** Returned value:			CNandFlashDef::uiParaError: 参数错误
**                          CNandFlashDef::uiBusy     : 正忙                                 
**							CErrorValueDefine::uiConstReturnSuccess  : 读取成功
**                          CErrorValueDefine::uiConstReturnFailed   : 读取失败
**                          CNandFlashDef::uiBadBlock : 坏块
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
        return CNandFlashDef::uiParaError;          //  参数错误
     }
     
     if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;               //  忙
     } 
     
     uint32 uiSector = uiAddr  / CNandFlashDef::uiBytePerSector;
     uint32 uiBlock  = uiSector / CNandFlashDef::uiSectorPerBlock;
     if( nand_lb_slc_is_block_bad(uiBlock) == 1 ) {
            nand_lb_slc_mark_bad_block(uiBlock);
            return CNandFlashDef::uiBadBlock;       //  坏块
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
            return CErrorValueDefine::uiConstReturnFailed;         //  读取失败
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
     return CErrorValueDefine::uiConstReturnSuccess;               //  读取成功
}

/**********************************************************************************************************************
** Function name:			WriteFlash
** Descriptions:			写uiLen个字节的数据
** input parameters:		ucpBuf:要写入数据的缓冲
**                          uiLen :要写入数据的个数
**                          uiAddr:要写入数据的首地址
** output parameters:		None
** Returned value:			CNandFlashDef::uiParaError: 参数错误
**                          CNandFlashDef::uiBusy     : 正忙                                 
**							CErrorValueDefine::uiConstReturnSuccess  : 写成功
**                          CErrorValueDefine::uiConstReturnFailed   : 写失败
**                          CNandFlashDef::uiBadBlock : 坏块                               
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
        return CNandFlashDef::uiParaError;          //  参数错误
    }
     
    if( nand_lb_slc_is_ready() != 1 ) {
        return CNandFlashDef::uiBusy;               //  忙
    } 
     
    uint32 uiSector = uiAddr  / CNandFlashDef::uiBytePerSector;
    uint32 uiBlock  = uiSector / CNandFlashDef::uiSectorPerBlock;
    if( nand_lb_slc_is_block_bad(uiBlock) == 1 ) {
        nand_lb_slc_mark_bad_block(uiBlock);
        return CNandFlashDef::uiBadBlock;       //  坏块
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
            return CErrorValueDefine::uiConstReturnFailed;         //  写失败
        }
     }
     return CErrorValueDefine::uiConstReturnSuccess;               //  写成功
}

/**********************************************************************************************************************
** Function name:			IsBadBlock
** Descriptions:			判断是否是坏块
** input parameters:		uiBlockNum：块号
** output parameters:		None
** Returned value:			CNandFlashDef::uiBusy     : 正忙                                 
**							CErrorValueDefine::uiConstReturnSuccess  : 不是坏块
**                          CErrorValueDefine::uiConstReturnFailed   : 写失败
**                          CNandFlashDef::uiBadBlock : 坏块                               
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
        return CNandFlashDef::uiBusy;               //  忙
    }
    
    if( nand_lb_slc_is_block_bad(uiBlockNum) == 1 ) {
        nand_lb_slc_mark_bad_block(uiBlockNum);
        return CNandFlashDef::uiBadBlock;       //  坏块
    }
    return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
** Function name:			SectorToAddr
** Descriptions:			块转换为地址
** input parameters:		uiSector：块号
** output parameters:		None
** Returned value:			地址                              
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
** Descriptions:			地址转换为块
** input parameters:		uiAddr：地址
** output parameters:		None
** Returned value:			块                      
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
** Descriptions:			Flash是否正忙
** input parameters:		None
** output parameters:		None
** Returned value:			CNandFlashDef::uiBusy: Flash正忙
**                          CNandFlashDef::uiReady： Flash不忙               
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
        return CNandFlashDef::uiBusy;           //  忙
    }
    return CNandFlashDef::uiReady;
}

#endif
