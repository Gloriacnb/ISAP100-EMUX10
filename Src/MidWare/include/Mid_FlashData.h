/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_FlashData.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/Mid_FlashData.h
** Created by:          Administrator
** Created date:        2012-12-14
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


#ifndef MID_FLASHDATA_H_
#define MID_FLASHDATA_H_

#include "lpc_nandflash_params.h"

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"


typedef enum {
	DXC_config_data,
	E1_map_data,
	CFG_NUMS
}ISAP100_Config_E;

typedef struct {
	uint32 BlockFirst;
	uint32 ByteNums;
	uint32 BufAddr;
	uint32 SecsUsed;
//	uint32 BytesNum;
	uint32 valid;
	uint32 BlockUsed;
}EZ_FLASH_DATA_T;

typedef struct {
	NAND_GEOM_T* nandgeom;
	EZ_FLASH_DATA_T FpgaFile;
	EZ_FLASH_DATA_T DeviceConfig;
	uint32 valid;
}ISAP100_SAVE_T;

typedef struct {
	uint8 DevicType;	//0 ADM; 1 PCM
	uint8 StmClockSrc;	//0 ��ʱ��; 1 ��ʱ��
	uint8 UpE1ClockSrc; //0 ��ʱ��; 1 �ָ�ʱ��
}Board_Slot_CFG_T;



uint32 Init_data_storage(void);
BOOL_32 flash_data_load(EZ_FLASH_DATA_T* fdata);
BOOL_32 flash_data_save(EZ_FLASH_DATA_T* fdata);

uint32 SaveISAP100Config(ISAP100_SAVE_T* saveData);

void config_load_default(ISAP100_SAVE_T* cfgData);

UNS_32 conv_to_sector(UNS_32 block,
					  UNS_32 page);



#define FPGA_FILE_BLOCK_START  	200
#define CFG_DATA_BLOCK_START	208
#define SYS_INFO_BLOCK_START	300

#define Base					100
#define size_Base				1
#define Reserve					2
#define Data_Part(n)		(Base+(n)*(size_Base+Reserve))
#define SYS_Attribut_Block_Start 	Data_Part(0)
#define Slot1_Config_Block_start	Data_Part(1)
#define Slot2_Config_Block_start	Data_Part(2)
#define Slot3_Config_Block_start	Data_Part(3)
#define Slot4_Config_Block_start	Data_Part(4)
#define SYS_Vc12_Cross_Block_Start	Data_Part(5)
#define MB_VCG_Config_Block_Start	Data_Part(6)
#define MB_SDH_Config_Block_Start	Data_Part(7)
#define SYS_TS_Cross_Block_Start	Data_Part(8)
//#define SYS_InnerDCC_Block_Start	Data_Part(9)
#define MB_ETH_Config_Block_Start	Data_Part(10)
#define MB_FE1_Config_Block_Start	Data_Part(9)
#define SYS_InnerDCC_Block_Start	Data_Part(12)

extern Board_Slot_CFG_T board_slot_config;
extern ISAP100_SAVE_T sysConfig;
extern UNS_8 secdat[];

#if defined (__cplusplus)
}
#endif
#endif /* MID_FLASHDATA_H_ */
