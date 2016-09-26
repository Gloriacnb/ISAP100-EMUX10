/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			FVIdt821054Access.h
 ** File path:			/EMUX300M0/Src/HardwareDrivers/FVIdt821054Access.h
 ** Created by:          Shqp
 ** Created date:        2012-6-28
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

#ifndef FVIDT821054ACCESS_H_
#define FVIDT821054ACCESS_H_

#include "EZ_types.h"

#if defined (__cplusplus)
extern "C"
{
#endif

#define DEF_MCLK	2		//MCLK = 2.048M
#define DEF_Max_ChipID	15
#define DEF_Min_ChipID	1
#define DEF_Max_ChannelID	4
#define DEF_Min_ChannelID	1
#define DEF_Max_Block	4
#define DEF_Min_Block	0

int ReadIdtChipGlbRegister(int ChipID, int RegAddr, int* RegValue);
int WriteIdtChipGlbRegister(int ChipID, int RegAddr, int RegValue);

int ReadIdtChipLocRegister(int ChipID, int channel, int RegAddr, int* RegValue);
int WriteIdtChipLocRegister(int ChipID, int channel, int RegAddr, int NewValue);

int readIDTChipCoeRamBlock(const int chipID, const int channel, const int block, uint16* dataBuff);
int writeIDTChipCoeRamBlock(const int chipID, const int channel, const uint8 block, uint16* data, uint8 dataLen);

int ReadCPLDRegister(int id,int RegAddr, int* RegValue);
int WriteCPLDRegister(int id,int RegAddr, int RegValue);

#if defined (__cplusplus)
}
#endif
#endif /* FVIDT821054ACCESS_H_ */
