/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_Timer.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/Mid_Timer.h
** Created by:          Administrator
** Created date:        2012-12-6
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


#ifndef MID_TIMER_H_
#define MID_TIMER_H_

#include "EZ_types.h"

#if defined (__cplusplus)
extern "C"
{
#endif

void InitTimer(void);

void WaitNms(uint32 ms);

extern uint32 volatile MicroSeconds;

#if defined (__cplusplus)
}
#endif /*__cplusplus */
#endif /* MID_TIMER_H_ */
