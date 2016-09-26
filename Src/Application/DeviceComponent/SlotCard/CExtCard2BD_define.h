/*
 * CExtCard2BD_define.h
 *
 *  Created on: 2013-7-29
 *      Author: Administrator
 */

#ifndef CEXTCARD2BD_DEFINE_H_
#define CEXTCARD2BD_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "CUInterface_define.h"

#define TYPE_2BD  0x53

typedef struct {
	UInterface_config_data port[2];
	uint32 crc;
}Card_2BD_Config_T;

enum {
	ext2BDVersionPCB = 1,
	ext2BDVersionChip,
	ext2BDVersionSize=2
};


#if defined (__cplusplus)
}
#endif
#endif /* CEXTCARD2BD_DEFINE_H_ */
