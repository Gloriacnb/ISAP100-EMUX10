/*
 * CExtCard4E1_define.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CEXTCARD4E1_DEFINE_H_
#define CEXTCARD4E1_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "CUnframeE1_define.h"

#define TYPE_4E1  0x50

typedef struct {
	uint8 pwm;
	UE1_Config_Data_T e1[4];
	uint32 crc;
}Card_4E1_Config_T;

enum {
	ext4E1VersionPCB = 1,
	ext4E1VersionChip,
	ext4E1VersionSize=2
};

#if defined (__cplusplus)
}
#endif
#endif /* CEXTCARD4E1_DEFINE_H_ */
