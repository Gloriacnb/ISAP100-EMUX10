/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_RC6400App.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/Mid_RC6400App.h
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


#ifndef MID_RC6400APP_H_
#define MID_RC6400APP_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"

#define MAX_TU12_NUM 	63
#define MAX_VCG_NUM		4

uint32 open_rc6400(void);
uint32 AddTu12ToVCGSimple(uint8 tsNum, uint8 vcgNum);
uint32 DeleteTu12FromVCGSimple(uint8 usNum);

uint32 AssignTu12Bus(uint8 tsNum, uint8 busID);

uint8 Rc6400_ReadReg(uint32 regaddr);
void Rc6400_WriteReg(uint32 regaddr, uint8 newdata);

#if defined (__cplusplus)
}
#endif
#endif /* MID_RC6400APP_H_ */
