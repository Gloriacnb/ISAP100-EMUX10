/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			ChipOptLogic.cpp
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/EZwellChipDriver/ChipOptLogic.cpp
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

#include "ChipOptLogic.h"

OptLogic_REGS_T* optlogic;

uint32 optlogic_open(OptLogic_REGS_T* regs) {

	int i = 0;
	int trycnt = 3;
	if( regs == NULL ) {
		return FALSE;
	}
	optlogic = regs;

	while( trycnt-- ) {
		if( optlogic->chipID != Opt_Hard_Code ) {
			continue;
		}
	
		optlogic->RC7880_RST_CTRL = Opt_Rst_Precede_Code;
		optlogic->RC6400_RST_CTRL = Opt_Rst_Precede_Code;
	
		for( i = 0; i < 10000; i++);
		optlogic->RC7880_RST_CTRL = Opt_Rst_Precede_Code | 1;
		optlogic->RC6400_RST_CTRL = Opt_Rst_Precede_Code | 1;
		for( i = 0; i < 10000; i++);
	
		return TRUE;
	}
	return FALSE;
}


uint8 OptLogic_ReadReg(uint32 regaddr) {
	uint32 realaddr = regaddr + OptLogic_BASE_ADDR;
	return *((uint8*)realaddr);
}
void OptLogic_WriteReg(uint32 regaddr, uint8 newdata) {
	uint32 realaddr = regaddr + OptLogic_BASE_ADDR;
	*((uint8*)realaddr) = newdata;
}

void ResetRemote(uint8 sn) {
	if(sn == 1) {
		optlogic->Remote_RST ^= 1;
	}
	else {
		optlogic->Remote_RST ^= 2;
	}
}


/*
 * 设置重启模式，并重启设备
 */
void Rst_MCU(RST_MODE_E mode) {
	uint8 bak;
	bak = optlogic->mcu_RST_CTRL;
	bak &= 0x0f;
	bak |= (mode<<4);
	bak |= Opt_Mcu_Rst_fix;
	bak ^= 1;
	optlogic->mcu_RST_CTRL = bak;
}

/*
 * 返回当前启动模式，并清启动模式为up_new
 */
RST_MODE_E Rst_Mode(void) {
	RST_MODE_E rtn = (RST_MODE_E)(optlogic->mcu_RST_CTRL >> 4);
	optlogic->mcu_RST_CTRL &= 0x0f;
	return rtn;
}


uint16 getOptLogicVersion(void) {
	return optlogic->chip_ver;
}

uint8 getRealPCBVersion(void) {
	uint8 ver = optlogic->pcbVersion;
	if( ver == 0  || ver > 0xf ) {
		return 16;
	}
	return ver+16;
}

