/***********************************************************************
 * $Id:: cfg_save_nand.c 8088 2011-09-14 06:28:22Z ing03005            $
 *
 * Project: S1L config save/restore functions (common)
 *
 * Description:
 *     Implements the following functions required for the S1L API
 *         cfg_save
 *         cfg_load
 *         cfg_override
 *         cfg_user_reset
 *
 * Note:
 *     These functions need to be developed for the board they will be
 *     executed on. Examples of how these functions work can be seen
 *     in the Phytec and Embedded Artists versions fo S1L. For this
 *     generic package, these functions are stubs.
 *
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#include "lpc_string.h"
//#include "sys.h"
#include "s1l_cfg.h"
#include "s1l_sys.h"
//#include "s1l_sys_inf.h"
//#include "startup.h"
#include "Mid_FlashData.h"
#include "Mid_NandFlash.h"

#define CHECK_KEY 0x1352EADB

extern ISAP100_SAVE_T sysConfig;
extern void *memcpy(void *dst, const void *src, int sz);
S1L_BOARD_CFG_T s1l_board_cfg;
UNS_32 adjusted_num_blocks = 2;

static BOOL_32 cfg_size_check(void)
{
	BOOL_32 sts = TRUE;
	UNS_32 pg_sz = sysConfig.nandgeom->data_bytes_per_page *
			sysConfig.nandgeom->pages_per_block;

	if ( pg_sz < (sizeof(S1L_CFG_T) + sizeof(S1L_BOARD_CFG_T) +
		sizeof(UNS_32)))
	{
		sts = FALSE;
	}

	return sts;
}

/***********************************************************************
 *
 * Function: cfg_save
 *
 * Purpose: Save a S1L configuration
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     pCfg : Pointer to config structure to save
 *
 * Outputs: None
 *
 * Returns: Always returns FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 cfg_save(S1L_CFG_T *pCfg)
{
	UNS_32 sector, blk = adjusted_num_blocks - 1;
	const UNS_32 cfg_check_data = CHECK_KEY;
	UNS_32 pg_sz = sysConfig.nandgeom->data_bytes_per_page;

	if (cfg_size_check() == FALSE)
		return FALSE;

	while (blk < adjusted_num_blocks)
	{
		/* This won't erase bad blocks */
		if (flash_erase_block(blk) == TRUE)
		{
			INT_32 offset = 0, page = 0;
			INT_32 sz_bcfg = sizeof(s1l_board_cfg);
			INT_32 sz_cfg = sizeof(*pCfg);
			UNS_8 *ptr_cfg = (UNS_8 *)pCfg;
			UNS_8 *ptr_bcfg = (UNS_8 *)&s1l_board_cfg;

			memcpy(secdat, &cfg_check_data, sizeof(cfg_check_data));
			offset += sizeof(cfg_check_data);

			/* Copy structure by structure */
			while (sz_bcfg > 0 || sz_cfg > 0)
			{
				/* Copy S1l Configuration structure */
				if (sz_cfg > 0)
				{
					UNS_32 tmp = sz_cfg > (pg_sz - offset) ? pg_sz - offset : sz_cfg;
					memcpy((UNS_8 *)secdat + offset, ptr_cfg, tmp);
					sz_cfg -= tmp;
					offset += tmp;
					ptr_cfg += tmp;
				}

				/* Copy Board configuration structure */
				if (sz_bcfg > 0 && offset < pg_sz)
				{
					UNS_32 tmp = sz_bcfg > (pg_sz - offset) ? pg_sz - offset : sz_bcfg;
					memcpy((UNS_8 *)secdat + offset, ptr_bcfg, tmp);
					sz_bcfg -= tmp;
					offset += tmp;
					ptr_bcfg += tmp;
				}

				if (offset >= pg_sz || (sz_bcfg <= 0 && sz_cfg <= 0))
				{
					sector = conv_to_sector(blk, page);
					if(flash_write_sector(sector, secdat, NULL) < 0)
						return FALSE;
					page ++;
					offset = 0;
				}
			}
			return TRUE;
		} else {
			adjusted_num_blocks ++;
//			sysinfo.sysrtcfg.bl_num_blks = adjusted_num_blocks;
		}
		blk ++;
	}

	return FALSE;
}

/***********************************************************************
 *
 * Function: cfg_load
 *
 * Purpose: Load an S1L configuariton
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     pCfg : Pointer to config structure to populate
 *
 * Outputs: None
 *
 * Returns: FALSE if the structure wasn't loaded, otherwise TRUE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 cfg_load(S1L_CFG_T *pCfg)
{
	UNS_32 sector, blk = adjusted_num_blocks - 1;
	UNS_32 cfg_check_data;
	UNS_32 pg_sz = sysConfig.nandgeom->data_bytes_per_page;

	if (cfg_size_check() == FALSE)
		return FALSE;

	while (blk < adjusted_num_blocks)
	{
		/* If bad block skip-it */
		if (flash_is_bad_block(blk) != TRUE)
		{
			INT_32 offset = 0, page = 0;
			INT_32 sz_bcfg = sizeof(s1l_board_cfg);
			INT_32 sz_cfg = sizeof(*pCfg);
			UNS_8 *ptr_cfg = (UNS_8 *)pCfg;
			UNS_8 *ptr_bcfg = (UNS_8 *)&s1l_board_cfg;

			/* Read first page of sector */
			sector = conv_to_sector(blk, page);
			if(flash_read_sector(sector, secdat, NULL) < 0)
				return FALSE;

			/* Check for the signature */
			memcpy(&cfg_check_data, secdat, sizeof(cfg_check_data));
			offset += sizeof(cfg_check_data);
			if (cfg_check_data != CHECK_KEY)
				return FALSE;
			page ++;

			/* Copy structure by structure */
			while (sz_bcfg > 0 || sz_cfg > 0)
			{
				/* Copy S1l Configuration structure */
				if (sz_cfg > 0)
				{
					UNS_32 tmp = sz_cfg > (pg_sz - offset) ? pg_sz - offset : sz_cfg;
					memcpy(ptr_cfg, (UNS_8 *)secdat + offset, tmp);
					sz_cfg -= tmp;
					offset += tmp;
					ptr_cfg += tmp;
				}

				/* Copy Board configuration structure */
				if (sz_bcfg > 0 && offset < pg_sz)
				{
					UNS_32 tmp = sz_bcfg > (pg_sz - offset) ? pg_sz - offset : sz_bcfg;
					memcpy(ptr_bcfg, (UNS_8 *)secdat + offset, tmp);
					sz_bcfg -= tmp;
					offset += tmp;
					ptr_bcfg += tmp;
				}

				if (sz_bcfg > 0 || sz_cfg > 0)
				{
					sector = conv_to_sector(blk, page);
					if(flash_read_sector(sector, secdat, NULL) < 0)
						return FALSE;
					page ++;
					offset = 0;
				}
			}
#ifdef ENABLE_CKLSWITCHING
			clock_adjust();
#endif
			return TRUE;
		} else {
			adjusted_num_blocks ++;
//			sysinfo.sysrtcfg.bl_num_blks = adjusted_num_blocks;
		}
		blk ++;
	}

	return FALSE;
}

/***********************************************************************
 *
 * Function: cfg_override
 *
 * Purpose: Return override state for saved config
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Always returns FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 cfg_override(void)
{
	return FALSE;
}

