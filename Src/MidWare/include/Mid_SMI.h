/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_SMI.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/Mid_SMI.h
** Created by:          Administrator
** Created date:        2012-12-17
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


#ifndef MID_SMI_H_
#define MID_SMI_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"

uint32 EthnetPHYRead(uint8 chipID, uint8 phyAddr, uint8 RegAddr, uint16* newData);
uint32 EthnetPHYWrite(uint8 chipID, uint8 phyAddr, uint8 RegAddr, uint16 newData);

uint32 RTL8306EPHYWrite( uint32 PHYID, uint32 REGAddr, uint16 PHYData );
uint32 RTL8306EPHYRead( uint32 PHYID, uint32 REGAddr, uint16* PHYData );
uint32 RTL8306EPHYWriteBit( uint32 PHY_ID, uint32 register_address, uint32 bit_position, uint32 value );
uint32 RTL8306EPHYReadBit( uint32 PHY_ID, uint32 register_address, uint32 bit_position, uint32 *value );





#define SMI_CMD_READ  0
#define SMI_CMD_WRITE 0x80
#define SMI_PHY_PRE	  0x00
#if defined (__cplusplus)
}
#endif
#endif /* MID_SMI_H_ */
