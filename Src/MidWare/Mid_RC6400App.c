/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_RC6400App.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_RC6400App.c
** Created by:          Administrator
** Created date:        2012-12-11
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

#include "Mid_RC6400App.h"
#include "RC6400.h"

void InitRC6400(void) {
	int i = 0;
	for(i = 0; i < MAX_TU12_NUM; i++) {
		RC6400_TU12_V5_Config_Tx_Set(i, 0x0a);
		RC6400_TU12_V5_Config_Rx_Set(i, 0x05);
		RC6400_TU12_K4_Config_Tx_Set(i, 0x0d);
		RC6400_TU12_K4_Config_Rx_Set(i, 0x0d);
	}
}



uint32 open_rc6400() {

	uint8 i = 3;

	while( i-- ) {
		if( RC6400_Check_FPGA_Ready() != TRUE ) {
			continue;
		}
		RC6400_Chip_Init();
		RC6400_Var_Init();
	
		for(i = 0; i < MAX_TU12_NUM; i++) {
	
			/* Set all tu12 work in multiplexer mode */
			RC6400_TU12_Bus_Sel_Mode_Rx_Set(i, 0);
			/* set all tu12 add disable */
			RC6400_TU12_En_Tx_Set(i, 0);
		}
	
		for(i = 0; i < MAX_VCG_NUM; i++) {

			/* enable LCAS */
			RC6400_LCAS_En_Rx_Set(i, ENABLE);
			RC6400_LCAS_En_Tx_Set(i, ENABLE);
		}
		InitRC6400();
		return TRUE;
	}
	return FALSE;
}


uint32 AddTu12ToVCGSimple(uint8 tsNum, uint8 vcgNum) {
	if( tsNum >= MAX_TU12_NUM || vcgNum >= MAX_VCG_NUM ) {
		return FALSE;
	}

	/* Set virtual connect group for vc12
	 * NOTE: must call first
	 */
	RC6400_VC12_GRP_Sel_Rx_Set(tsNum, vcgNum);
	RC6400_VC12_GRP_Sel_Tx_Set(tsNum, vcgNum);


	/* enable all mapping layer tu12
	 * NOTE: must call second
	 */
	RC6400_TU12_En_Rx_Set(tsNum, ENABLE);
	RC6400_TU12_En_Tx_Set(tsNum, ENABLE);

	/* enable VCAT layer vc12
	 * NOTE: must call latest
	 */
	RC6400_VC12_En_Rx_Set(tsNum, ENABLE);
	RC6400_VC12_En_Tx_Set(tsNum, ENABLE);

//	/* tu12 add enable */
	RC6400_TU12_En_Tx_Set(tsNum, ENABLE);

	return TRUE;
}

uint32 DeleteTu12FromVCGSimple(uint8 tsNum) {

	if( tsNum >= MAX_TU12_NUM ) {
		return FALSE;
	}


	/* disable VCAT layer vc12
	 * NOTE: must call first
	 */
	RC6400_VC12_En_Rx_Set(tsNum, DISABLE);
	RC6400_VC12_En_Tx_Set(tsNum, DISABLE);

	/* disable mapping layer tu12
	 * NOTE: must call second
	 */
	RC6400_TU12_En_Rx_Set(tsNum, DISABLE);
	RC6400_TU12_En_Tx_Set(tsNum, DISABLE);

	/* clear virtual connect group for vc12
	 * NOTE: must call latest
	 */
	RC6400_VC12_GRP_Sel_Rx_Set(tsNum, 0);
	RC6400_VC12_GRP_Sel_Tx_Set(tsNum, 0);

	/* tu12 add enable */
	RC6400_TU12_En_Tx_Set(tsNum, DISABLE);

	return TRUE;
}

uint32 AssignTu12Bus(uint8 tsNum, uint8 busID) {
	/* assign exp bus
	 *
	 */
	RC6400_TU12_Bus_Exp_Sel_Rx_Set(tsNum, busID); //下行方向A、B选择
	RC6400_TU12_Bus_Sel_Force_Rx_En_Set(tsNum, busID);		//上行方向A、B选择
	return TRUE;
}


uint8 Rc6400_ReadReg(uint32 regaddr) {
	uint32 realaddr = regaddr + RC6400_ADDR_BASE;
	return *((uint8*)realaddr);
}
void Rc6400_WriteReg(uint32 regaddr, uint8 newdata) {
	write(regaddr, newdata);
}

