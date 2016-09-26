/*
 * CExtCard8VF_define.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CEXTCARD8VF_DEFINE_H_
#define CEXTCARD8VF_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"
	

#define TYPE_8VF 0x51

typedef struct {
	uint8 enable;
	uint8 work_mode;
	uint8 polar_turn;
	uint8 rcv_gain;//[2];
	uint8 snd_gain;
	uint8 desclen;
	char desc[32];

}VF_Port_Config_T;

typedef struct {
	uint8 rcv_gain;
	uint8 snd_gain;
}VF_Group_Config_T;

typedef struct {
	VF_Port_Config_T port[8];
	VF_Group_Config_T group[2];
	uint32 crc;
}Card_8VF_Config_T;

typedef struct {
	uint8 portSn;
	uint8 hid;
}VF_port_channel_map_T;

enum {
	ext8VFVersionPCB = 1,
	ext8VFVersionChip,
	ext8VFVersionSize=2
};

#if defined (__cplusplus)
}
#endif
#endif /* CEXTCARD8VF_DEFINE_H_ */
