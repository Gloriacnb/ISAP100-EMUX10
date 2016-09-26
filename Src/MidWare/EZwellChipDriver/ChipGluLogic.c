/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			ChipXO2640.cpp
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/EZwellChipDriver/ChipXO2640.cpp
 ** Created by:          Administrator
 ** Created date:        2012-12-8
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

#include "ChipGluLogic.h"

volatile GluLogic_REGS_T *glulogic;
GluLogic_CFG_T GluConfig;

uint8 GluLogic_ReadReg(uint32 regaddr) {
	uint32 realaddr = regaddr + GluLogic_BASE_ADDR;
	return *((uint8*)realaddr);
}

void GluLogic_WriteReg(uint32 regaddr, uint8 newdata) {
	uint32 realaddr = regaddr + GluLogic_BASE_ADDR;
	*((uint8*)realaddr) = newdata;
}

uint32 glulogic_open(GluLogic_CFG_T* config) {
	if( config == NULL ) {
		return FALSE;
	}
	if( config->chipRunning == TRUE ) {
		return TRUE;
	}
	glulogic = GluLogic_REGPTR;				//Init glulogic regisgers
	config->chipRunning = FALSE;
	if( glulogic->chipID != Glu_Hard_Code ) {
		return FALSE;
	}
	config->chipRunning = TRUE;

	glulogic->FPGA_CTRL = Glu_SPI_NORMAL;
	glulogic->SPI_SEL = SPI_IDLE_MAX;	//close SPI
	glulogic->EXT_WTD = 0;			//close WTD
	return TRUE;
}

uint16 getGluLogicVersion(void) {
	return glulogic->chip_ver;
}

