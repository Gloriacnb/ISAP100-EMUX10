/*
 * Chip8DataLogic.h
 *
 *  Created on: 2013-6-17
 *      Author: Administrator
 */

#ifndef CHIP8DATALOGIC_H_
#define CHIP8DATALOGIC_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"

uint8 getDPtype(uint8 slot, uint8 port);
uint8 get8DataVersion(uint8 slot);

void setPortEnable(uint8 slot, uint8 port, uint8 en);

void setPortLoopOut(uint8 slot, uint8 port, uint8 loop);
void setPortLoopIn(uint8 slot, uint8 port, uint8 loop);

typedef enum {
	type_RS485 = 5,
	type_RS422,
	type_RS232,
}Data_Port_E;
/* spi channel 0 */
#define Chip_8DT_Type	0x00
#define Chip_8DT_VER	0x0f
/* spi channel 1 & 2 */
#define Chip_8DT_ChType 0x01
#define Chip_8DT_ChEnable 0x02 // bit7 ~ 4 -> RS232/485 1~4;
								//bit3 ~ 0 -> RS422 1~4;
#define Chip_8DT_LoopOut 0x03
#define Chip_8DT_LoopIn	 0x04

#if defined (__cplusplus)
}
#endif
#endif /* CHIP8DATALOGIC_H_ */
