/*
 * CExtCard8Data_define.h
 *
 *  Created on: 2013-6-14
 *      Author: Administrator
 */

#ifndef CEXTCARD8DATA_DEFINE_H_
#define CEXTCARD8DATA_DEFINE_H_

#include "EZ_types.h"
#define TYPE_8Data 0x52

typedef struct {
	uint8 enable;
	uint8 desclen;
	char desc[32];

}Data_Port_Config_T;

typedef struct {
	Data_Port_Config_T port[8];
	uint32 crc;
}Card_8Data_Config_T;

enum {
	ext8DtVersionPCB = 1,
	ext8DtVersionChip,
	ext8DtVersionSize=2
};


#endif /* CEXTCARD8DATA_DEFINE_H_ */
