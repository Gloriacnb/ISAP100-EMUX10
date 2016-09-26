/*
 * Chip8VFLogic.h
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#ifndef CHIP8VFLOGIC_H_
#define CHIP8VFLOGIC_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"
#include "CExtCard8VF_define.h"

//typedef struct {
//	uint8 slot;
//	uint8 Hot_Line;
//
//}ExtChip8VF_CFG_T;

uint32 InitExt8VFChip(uint8 slot, Card_8VF_Config_T* cfg);

uint8 getVFType(uint8 slot, uint8 port);
uint8 get8VFVersion(uint8 slot);
uint8 setHotLine(uint8 slot, uint8 port, uint8 en);
uint8 getHookState(uint8 slot, uint8 port);
uint8 setRC(uint8 slot, uint8 port, uint8 rc); //rc 1 ring
uint8 setMTMode(uint8 slot, uint8 port, uint8 mode);
uint8 setPolarDisable(uint8 slot, uint8 port, uint8 dis);

#define Reset_IDT821054 0x0001
#define Chip_8VF_VER	0x000f

#define Hot_Line_Ctrl   0x0100  //bit0~7  VF1~8
#define Hook_State      0x0111  //0 is off hook
#define Polar_DIS       0x0120  //bit0~7 1 disable
#define MT_MODE         0x0121
#define RC_Ctrl         0x0122  //1 is ring
#define DEF_TSch_Type_Base	0x0101

#if defined (__cplusplus)
}
#endif
#endif /* CHIP8VFLOGIC_H_ */
