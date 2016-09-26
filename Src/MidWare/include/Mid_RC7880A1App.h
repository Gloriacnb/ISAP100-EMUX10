/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			RC7880A1App.h
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/RC7880A1App.h
 ** Created by:          Administrator
 ** Created date:        2012-11-23
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

#ifndef MID_RC7880A1APP_H_
#define MID_RC7880A1APP_H_

#if defined (__cplusplus)
extern "C" {
#endif

#include "EZ_types.h"
#include "rc7880RegDriverFuncLib.h"
#include "ClockSourceDefine.h"

//#define MAP_TU12_PROTECT_MODE_AUTO 0
#define CHIP_RC7880A1_ID 0x7880
#define MAX_E1_Number	24
#define MAX_VC12_Number	63

typedef enum {
	direct_AB = 1, direct_GH, direct_Loop, direct_CD, mapping_Idle = 63
} CROSS_DIRECT_E;
uint32 open_rc7880a1(uint8 mode);
void InitRc7880A1(uint8 mode);

void OpticalTXOff(uint8 vc4, uint8 en);
void OpticalAlsEnable(uint8 vc4, uint8 en);
void OpticalAlsMode(uint8 mode);

uint32 SetClockMode(CLOCK_SOURCE_OP_E mode);
uint8 GetClockMode(void);

uint32 do_vc4_alarm(uint8 vc4ID);
//uint32 do_E1_alm(uint8 e1ID);

uint32 do_E1_alm_wrk(uint8 slot, uint8 e1ID);
uint32 do_E1_alm_ais(uint8 slot, uint8 e1ID);

int opt_is_los(uint8 vc4ID);

uint8 Rc7880_ReadReg(uint32 regaddr);
void Rc7880_WriteReg(uint32 regaddr, uint8 newdata);

#if defined (__cplusplus)
}
#endif /*__cplusplus */
#endif /* RC7880A1APP_H_ */
