/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_NandFlash.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/Mid_NandFlash.h
** Created by:          Administrator
** Created date:        2012-12-12
** Version:             V0.1
** Descriptions:        
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:				
** Descriptions:        
**
** Rechecked by:        
***********************************************************************************************************************/


#ifndef MID_NANDFLASH_H_
#define MID_NANDFLASH_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"
#include "lpc_types.h"

uint32 InitNandFlash(void);
int flash_read_sector(UNS_32 sector, void *buff, void *extra);
int flash_write_sector(UNS_32 sector, void *buff, void *extra);
BOOL_32 flash_erase_block(UNS_32 block);
BOOL_32 flash_is_bad_block(UNS_32 block);



/* Timing setup for the NAND SLC controller timing registers. On
   systems using NAND, these values effect how fast the kickstart
   loader loads the stage 1 application or how fast the S1L
   application handles NAND operations. See the 32x0 user's guide for
   info on these values. These should be programmed to work with the
   selected bus (HCLK) speed. */
#define SLC_NAND_W_RDY    0xf
#define SLC_NAND_W_WIDTH  0xf
#define SLC_NAND_W_HOLD   0xf
#define SLC_NAND_W_SETUP  0xf
#define SLC_NAND_R_RDY    0xf
#define SLC_NAND_R_WIDTH  0xf
#define SLC_NAND_R_HOLD   0xf
#define SLC_NAND_R_SETUP  0xf


int32 nand_lb_slc_erase_block(uint32 block);
void  nand_lb_slc_mark_bad_block(uint32 block);
int32 nand_lb_slc_is_block_bad(uint32 block);
int32 nand_lb_slc_read_sector(uint32 sector, uint8 *readbuff, uint8 *spare);
int32 nand_lb_slc_write_sector(uint32 sector, uint8 *writebuff, uint8 *spare);
int32 nand_lb_slc_is_ready(void);

#if defined (__cplusplus)
}
#endif
#endif /* MID_NANDFLASH_H_ */
