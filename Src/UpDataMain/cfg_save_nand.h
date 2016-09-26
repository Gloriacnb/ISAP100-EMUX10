/*
 * cfg_save_nand.h
 *
 *  Created on: 2013-3-16
 *      Author: Administrator
 */

#ifndef CFG_SAVE_NAND_H_
#define CFG_SAVE_NAND_H_


#if defined (__cplusplus)
extern "C"
{
#endif

#include "lpc_types.h"
#include "s1l_cfg.h"
#include "s1l_sys.h"

BOOL_32 cfg_save(S1L_CFG_T *pCfg);
BOOL_32 cfg_load(S1L_CFG_T *pCfg);


#if defined (__cplusplus)
}
#endif
#endif /* CFG_SAVE_NAND_H_ */
