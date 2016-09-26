/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			Mid_SPI.h
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_SPI.h
 ** Created by:          Administrator
 ** Created date:        2012-12-7
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

#ifndef MID_SPI_H_
#define MID_SPI_H_

#include "EZ_Types.h"
#include <rtl.h>

#if defined (__cplusplus)
extern "C" {
#endif

int InitSPI(void);
int InitSPIforFPGA(void);

uint32 ExtCPLDRegReadByte(uint8 spiCh, uint16 regAddr, uint8* value);
uint32 ExtCPLDRegWriteByte(uint8 spiCh, uint16 regAddr, uint8 value);
uint32 ExtCPLDRegWriteBit(uint8 spiCh, uint16 regAddr, uint8 bitpos,
		uint8 value);

uint32 ExtIDTRegReadByte(uint8 spiCh, uint8 regAddr, uint8* value);
uint32 ExtIDTRegWriteByte(uint8 spiCh, uint16 regAddr, uint8 value);

//uint32 ExtIDTRegReadByte()

//int SpiChipRead(uint16 addr, uint8 addrWidth, uint8 dataWidth);
//void SpiChipWrite(uint16 addr, uint16 data, uint8 addrWidth, uint8 dataWidth);
int SpiChipRead(uint16 addr, uint8 addrWidth, uint8 dataWidth);
void SpiChipWrite(uint16 addr, uint16 data, uint8 addrWidth, uint8 dataWidth);

int SpiChipRamRead(uint16 addr, uint16* data);
void SpiChipRamWrite(uint8 addr, uint16* data);
uint32 SpiSend(uint8* buff, uint32 len);
uint32 SpiReceive(uint8* buff, uint32 len);

int SpiMCRead(uint8 addr, uint8 addrBits, uint8 dataBits);
int SpiMCWrite(uint8 addr, uint16 data, uint8 addrBits, uint8 dataBits);

extern OS_MUT mut_spi;

#if defined (__cplusplus)
}
#endif /*__cplusplus */

#endif /* MID_SPI_H_ */
