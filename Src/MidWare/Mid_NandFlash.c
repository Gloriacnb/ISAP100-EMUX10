/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_NandFlash.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_NandFlash.c
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

#include "Mid_NandFlash.h"
#include "lpc32xx_slcnand_driver.h"
#include "lpc_nandflash_params.h"

static INT_32 nand;


/* Timing parameter */
#define ISAP100_SLC_TIMING \
		SLCTAC_WDR(SLC_NAND_W_RDY) | \
		SLCTAC_WWIDTH(SLC_NAND_W_WIDTH) | \
		SLCTAC_WHOLD(SLC_NAND_W_HOLD) | \
		SLCTAC_WSETUP(SLC_NAND_W_SETUP) | \
		SLCTAC_RDR(SLC_NAND_R_RDY) | \
		SLCTAC_RWIDTH(SLC_NAND_R_WIDTH) | \
		SLCTAC_RHOLD(SLC_NAND_R_HOLD) | \
		SLCTAC_RSETUP(SLC_NAND_R_SETUP)

/* TODO: Change this timing as given in Datasheet */
/* Timings for MICRON Flash */
#define SLCNAND_MICRON_DA_TIMING ISAP100_SLC_TIMING
/* Timings for SAMSUNG flash */
#define SLCNAND_SAMSUNG_F1_TIMING ISAP100_SLC_TIMING

/* List of all types of NAND flash that could be mounted
 * in an EA3250 Board
 */
static struct nand_ids ISAP100_nand_ids[] =
{
  /* SAMSUNG Flash */
  {
    LPCNAND_VENDOR_SAMSUNG,
    0xDA, /* Device ID */
    2048, /* Page size */
    64, /* Pages per block */
    2048, /* Total blocks */
	{SLCNAND_SAMSUNG_F1_TIMING}/* Timing */
  },
};

static struct nand_devinfo_list ISAP100_nand_list =
{
  sizeof(ISAP100_nand_ids)/sizeof(ISAP100_nand_ids[0]),
  ISAP100_nand_ids,
  NULL
};



uint32 InitNandFlash(void) {
	static NAND_GEOM_T geom;
	nand = slcnand_open(SLCNAND, (INT_32)&ISAP100_nand_list);
	if (!nand)
	  return NULL;

	if (slcnand_get_geom(nand, &geom))
	  return NULL;

	return (uint32)&geom;

}

/***********************************************************************
 *
 * Function: flash_read_sector
 *
 * Purpose: Read a NAND sector, will skip bad blocks
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns:
 *     Returns >0 on success, -1 on fail, or -2 if the block
 *     associated with the sector is bad
 *
 * Notes:
 *     The block is read regardless of whether the block is bad or not.
 *
 **********************************************************************/
int flash_read_sector(UNS_32 sector, void *buff, void *extra)
{

	UNS_32 block;
	static UNS_32 lastblock = 0xffffffff;
	static int lastblockgood = 0;
	int ret;

	block = slcnand_get_block(nand, sector);

	if (lastblock != block)
	{
		if (slcnand_is_block_bad(nand, block))
		{
			lastblockgood = 0;
		}
		else
		{
			lastblockgood = 1;
		}

		lastblock = block;
	}

	/* We get 0 on success */
	ret = slcnand_read_sector(nand, sector, (UNS_8 *) buff,
		(UNS_8 *) extra);

	if (lastblockgood == 0)
	{
		return -2;
	}

	/* Caller considers > 0 as success */
	return ret != _ERROR;


}

/***********************************************************************
 *
 * Function: flash_write_sector
 *
 * Purpose: Writes a NAND sector, will skip bad blocks
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns:
 *     Returns >0 on success, -1 on fail, or -2 if the block
 *     associated with the sector is bad
 *
 * Notes: The block will not be written if it is bad.
 *
 **********************************************************************/
int flash_write_sector(UNS_32 sector, void *buff, void *extra)
{

	UNS_32 block;
	static UNS_32 lastblock = 0xffffffff;
	static int lastblockgood = 0;

	block = slcnand_get_block(nand, sector);
	if (lastblock != block)
	{
		if (slcnand_is_block_bad(nand, block))
		{
			lastblockgood = 0;
		}
		else
		{
			lastblockgood = 1;
		}

		lastblock = block;
	}

	if (lastblockgood == 0)
	{
		return -2;
	}

	return slcnand_write_sector(nand, sector, (UNS_8 *) buff,
		(UNS_8 *) extra) != _ERROR;

}


/***********************************************************************
 *
 * Function: flash_erase_block
 *
 * Purpose: Erase a block
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     block: Block number
 *
 * Outputs: None
 *
 * Returns: TRUE on good erase, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 flash_erase_block(UNS_32 block)
{
	/* Don't allow erasure of bad blocks in S1L */
	if (!(slcnand_is_block_bad(nand, block)) )
	{
		if (slcnand_erase_block(nand, block) != _ERROR)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/***********************************************************************
 *
 * Function: flash_is_bad_block
 *
 * Purpose: Erase a block
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     block: Block number
 *
 * Outputs: None
 *
 * Returns: TRUE if the block is bad, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 flash_is_bad_block(UNS_32 block)
{
	if (slcnand_is_block_bad(nand, block))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL_32 nand_lb_slc_erase_block(UNS_32 block)
{
	return flash_erase_block(block);
}

void  nand_lb_slc_mark_bad_block(UNS_32 block) {
	slcnand_mark_block_bad(nand, block);
}
BOOL_32 nand_lb_slc_is_block_bad(UNS_32 block) {
	return flash_is_bad_block(block);
}
BOOL_32 nand_lb_slc_read_sector(UNS_32 sector, UNS_8 *readbuff, UNS_8 *spare) {
	return flash_read_sector(sector, readbuff, spare);
}
BOOL_32 nand_lb_slc_write_sector(UNS_32 sector, UNS_8 *writebuff, UNS_8 *spare) {
	return flash_read_sector(sector, writebuff, spare);
}
//static void slcnand_wait_ready(const SLCNAND_DEV_T *dev)
BOOL_32 nand_lb_slc_is_ready(void) {
//	slcnand_wait_ready(nand);
	return 1;
}
