/*
 * Chip4E1Logic.h
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#ifndef CHIP4E1LOGIC_H_
#define CHIP4E1LOGIC_H_

#if defined (__cplusplus)
extern "C"
{
#endif


#include "EZ_types.h"
#include "CExtCard4E1_define.h"

//typedef struct {
//	uint8 slotNumber;
//	uint8 PWM_Para;
//}ExtChip4E1_CFG_T;

uint32 InitExtChip4E1(uint8 slot, Card_4E1_Config_T* cfgData);

void led_e1wrk_on(uint8 slot, uint8 e1);
void led_e1wrk_off(uint8 slot, uint8 e1);
void led_e1ais_on(uint8 slot, uint8 e1);
void led_e1ais_off(uint8 slot, uint8 e1);
uint16 get4E1ChipVersion(uint8 slot);

/* Regs define */

#define PWM_PARA  0x0001
#define E1_LED	  0x0002	//bit0~3 ais bit 4~7 work
#define Chip_4E1_VER  0x000f


#if defined (__cplusplus)
}
#endif
#endif /* CHIP4E1LOGIC_H_ */
