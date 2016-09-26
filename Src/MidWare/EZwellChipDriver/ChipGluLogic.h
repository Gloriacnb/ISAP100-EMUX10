/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			ChipXO2640.h
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/EZwellChipDriver/ChipXO2640.h
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

#ifndef CHIPGLULOGIC_H_
#define CHIPGLULOGIC_H_

#include "EZ_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* data struct in glulogic*/
typedef struct {

	/* 0x000~0x00F */
	uint8 SPI_SEL;		//| slot1   | slot2   | slot3   | slot4   | idle
						//| spi_1~4 | spi_1~4 | spi_1~4 | spi_1~4 | noSPI selected
						//| 0~3     | 4~7     | 8~11    | 12~15   | 16~MAX

	uint8 I2C_SEL;		//| SMI1 | SMI2 | SFP1 | SFP2
						//| 0    | 1    | 2    | 3

	uint8 FPGA_CTRL;	//| load        | program
						//| bit7~4      | bit0
						//| 1010 load   | 1 PROG PIN high
						//| 0101 normal | 0 PROG PIN LOW

	uint8 EXT_WTD;		//| enalbe WTD    | clear
						//| bit7~4		  | other
						//| 0101 enable   | write clear WTD counter
						//| other disable
	uint8 reserve1[11];
	uint8 chip_ver;	//0x00f;

	/* 0x010~0x01F */
	uint8 bytebuf;
	uint8 chipID;		//always 0xA9
	uint8 reserve2[14];

	/* 0x020~0x02F */
	volatile uint8 SMI_DL;
	volatile uint8 SMI_DH;
	volatile uint8 SMI_REGAD;
	volatile uint8 SMI_PHYAD;
	uint8 reserve3[12];

	/* 0x30~0x11F*/
	uint8 reserve4[0x120-0x30];

	/* 0x120~0x13F */
	uint8 i2c_ctrlDataBytes;
	uint8 i2c_ctrlAddrBytes;
	uint8 reserve5[6];
	uint8 i2c_RegAddr;
	uint8 reserve6[3];
	uint8 i2c_SlaveAddr;
	uint8 reserve7;
	volatile uint8 i2c_Start;
	uint8 reserve8;
	volatile uint8 i2c_Data;


}GluLogic_REGS_T;

typedef struct {
	uint32 chipRunning;
}GluLogic_CFG_T;

/* base function for read/write register debug */
uint8 GluLogic_ReadReg(uint32 regaddr);
void GluLogic_WriteReg(uint32 regaddr, uint8 newdata);


/* fuctions in glulogic chip */
uint32 glulogic_open(GluLogic_CFG_T* config);
uint16 getGluLogicVersion(void);



typedef enum {
	SLOT_1_SPI_1, SLOT_1_SPI_2, SLOT_1_SPI_3, SLOT_1_SPI_4,
	SLOT_2_SPI_1, SLOT_2_SPI_2, SLOT_2_SPI_3, SLOT_2_SPI_4,
	SLOT_3_SPI_1, SLOT_3_SPI_2, SLOT_3_SPI_3, SLOT_3_SPI_4,
	SLOT_4_SPI_1, SLOT_4_SPI_2, SLOT_4_SPI_3, SLOT_4_SPI_4,
	SPI_IDLE_MAX
}SPI_CH_E;

#define GluLogic_BASE_ADDR (0xe3000000)
#define GluLogic_REGPTR ((volatile GluLogic_REGS_T*)(GluLogic_BASE_ADDR))

#define Glu_Hard_Code 0xa9
#define Glu_SPI_NORMAL (5 << 4)
#define Glu_SPI_LOADFPGA (0xa << 4)

#define I2C_SEL_Base  2
extern GluLogic_CFG_T GluConfig;
extern volatile GluLogic_REGS_T* glulogic;

#ifdef __cplusplus
}
#endif

#endif /* CHIPXO2640_H_ */
