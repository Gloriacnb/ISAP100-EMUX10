/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_FlashData.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_FlashData.c
** Created by:          Administrator
** Created date:        2012-12-14
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

#include "Mid_FlashData.h"
#include "Mid_NandFlash.h"
//#include "lpc_nandflash_params.h"
#include <string.h>

ISAP100_SAVE_T sysConfig;

//ISAP100_SAVE_T* sysConfig;
Board_Slot_CFG_T board_slot_config;

UNS_8 secdat[2048 + 64];

void config_load_default(ISAP100_SAVE_T* cfgData);
uint32 SaveISAP100Config(ISAP100_SAVE_T* saveData);
ISAP100_SAVE_T* RestoreISAP100Config(void);


uint32 Init_data_storage(void) {

	RestoreISAP100Config();
	return TRUE;
}


/***********************************************************************
 *
 * Function: conv_to_sector
 *
 * Purpose: Converts a block/page to a sector number
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     block : Block number
 *     page  : Page number
 *
 * Outputs: None
 *
 * Returns: The sector number for the passed block and page
 *
 * Notes: None
 *
 **********************************************************************/
UNS_32 conv_to_sector(UNS_32 block,
					  UNS_32 page)
{
	uint32 sector = (sysConfig.nandgeom->pages_per_block) * block;
	return (page + sector);
}

/***********************************************************************
 *
 * Function: mem_to_nand
 *
 * Purpose: Moves data from memory to FLASH
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     starting_sector : Starting sector for write
 *     buff            : Pointer to buffer to write
 *     bytes           : Number of bytes to write
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 mem_to_nand(UNS_32 starting_sector,
					void *buff,
					UNS_32 bytes)
{
	BOOL_32 blkchk;
	UNS_32 block, page, sector, wbytes;
	UNS_8 *p8 = (UNS_8 *) buff;

	if (sysConfig.nandgeom == NULL)
	{
#ifdef EZ_DEBUG
		term_dat_out_crlf(noflash_msg);
#endif
		return FALSE;
	}

	/* Get block and page for passed sector */
	block = starting_sector / sysConfig.nandgeom->pages_per_block;
	page = starting_sector -
		(block * sysConfig.nandgeom->pages_per_block);

	/* Align bytes to a sector boundary */
	wbytes = bytes & ~(sysConfig.nandgeom->data_bytes_per_page - 1);
	if (wbytes < bytes)
	{
		bytes = wbytes + sysConfig.nandgeom->data_bytes_per_page;
	}

	/* Write data */
	blkchk = TRUE;
	while (bytes > 0)
	{
		/* Is a block check needed? */
		if ((page == 0) && (blkchk == TRUE))
		{
			if (flash_is_bad_block(block) != FALSE)
			{
				/* Goto next block */
#ifdef EZ_DEBUG
				term_dat_out(bskip_msg);
				str_makedec(str, block);
				term_dat_out_crlf(str);
#endif
				block++;
				page = 0;
			}
			else
			{
				/* Block is good */
				blkchk = FALSE;
			}
		}
		else
		{
			/* Convert to sector */
			sector = conv_to_sector(block, page);

			/* Write sector data */
			if (flash_write_sector(sector, p8, NULL) == FALSE)
			{
#ifdef EZ_DEBUG
				term_dat_out(writeerr_msg);
				str_makedec(str, sector);
				term_dat_out_crlf(str);
#endif
				bytes = 0;
				return FALSE;
			}
			else
			{
				p8 += sysConfig.nandgeom->data_bytes_per_page;
				bytes -= sysConfig.nandgeom->data_bytes_per_page;
			}

			/* Next page and block */
			page++;
			if (page >= sysConfig.nandgeom->pages_per_block)
			{
				page = 0;
				block++;
				blkchk = TRUE;
			}
		}
	}

	return TRUE;
}

/***********************************************************************
 *
 * Function: nand_to_mem
 *
 * Purpose: Moves data from FLASH to memory
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     starting_sector : Starting sector for read operation
 *     buff            : Buffer to place read data
 *     bytes           : Number of bytyes to read
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 nand_to_mem(UNS_32 starting_sector,
					void *buff,
					UNS_32 bytes)
{
	BOOL_32 blkchk;
	UNS_32 block, page, sector, toread;
	UNS_8 *p8 = (UNS_8 *) buff;

	if (sysConfig.nandgeom == NULL)
	{
#ifdef EZ_DEBUG
		term_dat_out_crlf(noflash_msg);
#endif
		return FALSE;
	}

	/* Get block and page for passed sector */
	block = starting_sector / sysConfig.nandgeom->pages_per_block;
	page = starting_sector -
		(block * sysConfig.nandgeom->pages_per_block);
	/* Read data */
	blkchk = TRUE;
	while (bytes > 0)
	{
		/* Is a block check needed? */
		if ((page == 0) && (blkchk == TRUE))
		{
			if (flash_is_bad_block(block) != FALSE)
			{
				/* Goto next block */
#ifdef EZ_DEBUG
				term_dat_out(bskip_msg);
				str_makedec(str, block);
				term_dat_out_crlf(str);
#endif
				block++;
				page = 0;
				blkchk = TRUE;
			}
			else
			{
				blkchk = FALSE;
			}
		}
		else
		{
			/* Convert to sector */
			sector = conv_to_sector(block, page);

			toread = bytes;
			if (toread > sysConfig.nandgeom->data_bytes_per_page)
			{
				toread = sysConfig.nandgeom->data_bytes_per_page;
			}

			/* Read sector data */
			if (flash_read_sector(sector, secdat, NULL) <= 0)
			{
#ifdef EZ_DEBUG
				term_dat_out(readerr_msg);
				str_makedec(str, sector);
				term_dat_out_crlf(str);
#endif
			}

			memcpy(p8, secdat, toread);
			p8 += toread;
			bytes -= toread;

			/* Next page and block */
			page++;
			if (page >= sysConfig.nandgeom->pages_per_block)
			{
				page = 0;
				block++;
				blkchk = TRUE;
			}
		}
	}

	return TRUE;
}



/***********************************************************************
 *
 * Function: flash_data_save
 *
 * Purpose: Moves image in memory to FLASH application load region
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Always returns TRUE.
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 flash_data_save(EZ_FLASH_DATA_T* fdata)
{
	UNS_32 fblock, ffblock;
	INT_32 sector, numsecs, nblks;
//	FLASH_SAVE_T flashsavdat;

	/* Set first block pat boot loader */
	ffblock = fblock = fdata->BlockFirst;

	/* Save programmed FLASH data */
//	flashsavdat.block_first = fblock;
//	flashsavdat.num_bytes = fdata->ByteNums;
//	flashsavdat.loadaddr = DEF_LARGE_BUF_ADDR;
//	fdata->valid = TRUE;

	/* Get starting sector and number of sectors to program */
	numsecs = fdata->ByteNums /
			sysConfig.nandgeom->data_bytes_per_page;
	if ((numsecs * sysConfig.nandgeom->data_bytes_per_page) <
		fdata->ByteNums)
	{
		numsecs++;
	}
	fdata->SecsUsed = numsecs;
	nblks = numsecs / sysConfig.nandgeom->pages_per_block;
	if ((nblks * sysConfig.nandgeom->pages_per_block) < numsecs)
	{
		nblks++;
	}
	fdata->BlockUsed = nblks;

	/* Erase necessary blocks first */
	while (nblks > 0)
	{
		if (flash_is_bad_block(ffblock) == FALSE)
		{
			flash_erase_block(ffblock);
			nblks--;
		}

		ffblock++;
	}

	/* Burn image into FLASH */
	sector = conv_to_sector(fblock, 0);

	return mem_to_nand(sector, (UNS_8 *)fdata->BufAddr,
					(numsecs * sysConfig.nandgeom->data_bytes_per_page));
//	if (mem_to_nand(sector, (UNS_8 *) DEF_LARGE_BUF_ADDR,
//		(numsecs * nandgeom->data_bytes_per_page)) == FALSE)
//	{
//		term_dat_out_crlf(nsaeerr_msg);
//	}
//	else
//	{
//		/* Update saved NAND configuration */
//		syscfg.fsave = flashsavdat;
//		cfg_save(&syscfg);
//	}

//	return TRUE;
}

/***********************************************************************
 *
 * Function: flash_data_load
 *
 * Purpose: Moves FLASH application in load region to memory
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Always returns TRUE.
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 flash_data_load(EZ_FLASH_DATA_T* fdata)
{
	UNS_32 fblock;
	INT_32 sector;

	/* Find starting block of burned image */
	fblock = fdata->BlockFirst;//sysrtcfg.bl_num_blks;

	/* Read data into memory */
	sector = conv_to_sector(fblock, 0);
	return (nand_to_mem(sector, (UNS_8 *) fdata->BufAddr, fdata->ByteNums) );
		//(fdata->SecsUsed *
		//		sysConfig.nandgeom->data_bytes_per_page)) == FALSE)
// 	{
// 		return FALSE;
// 	}
//	else
//	{
//		/* Load image */
//		fdata->ByteNums = syscfg.fsave.num_bytes;
//		fdata->startaddr = (PFV) syscfg.fsave.startaddr;
//		fdata->loadaddr = syscfg.fsave.loadaddr;
//		fdata->flt = FLT_RAW;
//		fdata->contiguous = TRUE;
//		fdata->loaded = TRUE;
//	}

// 	return TRUE;
}


void config_load_default(ISAP100_SAVE_T* cfgData) {

	board_slot_config.DevicType = 0;
	board_slot_config.StmClockSrc = 0;
	board_slot_config.UpE1ClockSrc = 0;

	cfgData->FpgaFile.BlockFirst = 200;
	cfgData->FpgaFile.BufAddr = 0x87000000;
	cfgData->FpgaFile.ByteNums = 0x053300;
	cfgData->FpgaFile.SecsUsed = 167;
	cfgData->FpgaFile.valid = FALSE;

	cfgData->DeviceConfig.BlockFirst = 210;
	cfgData->DeviceConfig.ByteNums = 0;
	cfgData->DeviceConfig.BufAddr = 0;
	cfgData->DeviceConfig.SecsUsed = 1;
	cfgData->DeviceConfig.valid = FALSE;
	cfgData->valid = TRUE;
	flash_data_save(&cfgData->DeviceConfig);
	SaveISAP100Config(cfgData);

}

#define DEF_ISAP_DEV_CFG_Block   300
#define DEF_DEV_CFG_MAX_Block	310

ISAP100_SAVE_T* RestoreISAP100Config(void) {
// 	uint32 block = DEF_ISAP_DEV_CFG_Block;
// 	uint32 sector = 0;
// 	static uint8 buff[2048+64];

	sysConfig.nandgeom = (NAND_GEOM_T*)InitNandFlash();
	if( sysConfig.nandgeom == NULL ) {
		return (ISAP100_SAVE_T*)NULL;
	}

//	while( flash_is_bad_block(block) == TRUE ) {
//		++block;
//	}
//
//	sector = conv_to_sector(block, 0);
//	if( nand_to_mem(sector, buff, sizeof(ISAP100_SAVE_T)) == TRUE ) {
//		memcpy( ((uint8*)&sysConfig) + 4, buff+4, sizeof(ISAP100_SAVE_T)-4);
//		if( sysConfig.valid != TRUE ) {
//			config_load_default(&sysConfig);
//		}
//		else if( sysConfig.DeviceConfig.valid == TRUE ) {
//			sysConfig.DeviceConfig.BufAddr = (uint32)buff;
//			flash_data_load(&(sysConfig.DeviceConfig));
//			memcpy(&board_slot_config, buff, sizeof(board_slot_config));
//		}
//	}
//	else {
//		config_load_default(&sysConfig);
//	}
	return &sysConfig;
}

uint32 SaveISAP100Config(ISAP100_SAVE_T* saveData) {
	uint32 block = DEF_ISAP_DEV_CFG_Block;
	uint32 sector;
	while( flash_is_bad_block(block) == TRUE ) {
		++block;
	}
	flash_erase_block(block);
	sector = conv_to_sector(block, 0);
	return mem_to_nand(sector, saveData, sizeof(ISAP100_SAVE_T) );
}
