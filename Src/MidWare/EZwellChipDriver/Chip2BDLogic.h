/*
 * Chip2BDLogic.h
 *
 *  Created on: 2013-8-1
 *      Author: Administrator
 */

#ifndef CHIP2BDLOGIC_H_
#define CHIP2BDLOGIC_H_

#include "EZ_types.h"

uint16 get2BDChipVersion(uint8 slot);

void resetMC145572(uint8 slot, uint8 chip);
void selectNTLT(uint8 slot, uint8 chip, uint8 mode);
void setLinkLED(uint8 slot, uint8 chip, uint8 s);
void setModeLED(uint8 slot, uint8 chip, uint8 mode);


/* Regs define */
#define MC145572_reset 0x0024 //bit0 chip1 bit1 chip2
#define NTLT_SEL_0 0x0020 //0 LT, 1 NT
#define NTLT_SEL_1 0x0021
#define LED_2BD_0  0x0022	//bit0 link, bit1 LT(0)NT(1)
#define LED_2BD_1  0x0023
#define Chip_2BD_VER  0x000f

#endif /* CHIP2BDLOGIC_H_ */
