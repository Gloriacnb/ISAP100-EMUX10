/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			ChipOptLogic.h
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/EZwellChipDriver/ChipOptLogic.h
 ** Created by:          Administrator
 ** Created date:        2012-12-10
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#ifndef CHIPOPTLOGIC_H_
#define CHIPOPTLOGIC_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"

typedef struct {
	uint8 Remote_RST; //bit0 a bit1 b
	uint8 RC7880_RST_CTRL;
	uint8 RC6400_RST_CTRL;
	uint8 mcu_RST_CTRL;
	uint8 reserv1[11];
	uint8 chip_ver;
	uint8 reserv[1];
	uint8 chipID; 				//always 0xa9
	uint8 reserv2[13];
	uint8 pcbVersion;

}OptLogic_REGS_T;

typedef enum {
	up_new,
	up_main = 0x0a,
	up_fpga
}RST_MODE_E;

uint32 optlogic_open(OptLogic_REGS_T*);

void ResetRemote(uint8 sn);
uint16 getOptLogicVersion(void);

/* only for debug */
uint8 OptLogic_ReadReg(uint32 regaddr);
void OptLogic_WriteReg(uint32 regaddr, uint8 newdata);

void Rst_MCU(RST_MODE_E mode);

RST_MODE_E Rst_Mode(void);

uint8 getRealPCBVersion(void);

#define OptLogic_BASE_ADDR (0xe3002000)
#define OptLogic_REGPTR ((OptLogic_REGS_T *)(OptLogic_BASE_ADDR))

#define Opt_Hard_Code 0xa9
#define Opt_Rst_Precede_Code (0xa << 4)
#define Opt_Mcu_Rst_fix	(5 << 1)


extern OptLogic_REGS_T* optlogic;

#if defined (__cplusplus)
}
#endif
#endif /* CHIPOPTLOGIC_H_ */
