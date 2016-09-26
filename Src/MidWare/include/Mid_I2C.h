/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_I2C.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_I2C.h
** Created by:          Administrator
** Created date:        2012-12-21
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


#ifndef MID_I2C_H_
#define MID_I2C_H_

#include "EZ_types.h"

#if defined (__cplusplus)
extern "C"
{
#endif

uint8 I2C_read_byte(uint8 ch, uint8 slaveDev, uint8 regAddr);
void I2C_write_byte(uint8 ch, uint8 slaveDev, uint8 regAddr, uint8 newData);


#if defined (__cplusplus)
}
#endif
#endif /* MID_I2C_H_ */
