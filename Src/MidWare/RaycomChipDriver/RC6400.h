/*********************************************************************************
**								Raycom company
**					ChuanXin Road 27# ,ChangPing Science Tech Park, Beijing
**
**						(c)Copyright 2008,Raycom,Changping,Beijing
** 								All Rights Reserved 
**________________________________________________________________________________
**
** FileName:RC6400.h
** Author:   xuezj
** Description:RC6400 DRIVER header file
**
*********************************************************************************/

#ifndef _RC6400_H_
#define _RC6400_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"

/*======== RC6400 寄存器定义==================================== */
#define RC6400_BASE_ADDR 				0
#define RC6400_REGS_FREE_CODE		0xAA
#define RC6400_REGS_PROTECT_CODE	(~RC6400_REGS_FREE_CODE)

/*================== 全局寄存器定义===========================*/
#define cGLOBAL_RESET 					0x1FC0
#define laGLOBAL_38MCLK_BYTE 			0x1FC4
	#define la38MCLK_LOSS 		0x80
 	#define la38MCLK_RECOVER 	0x40
#define sGLOBAL_ID_PARTNUMBERH 		0x1FCA
#define sGLOBAL_ID_PARTNUMBERL		0x1FCB
#define sGLOBAL_VERSION				0x1FCC

#define sGLOBAL_REGS_PROTECT		0x1FCF



/*----------------------- 虚级联发送全局寄存器------------------------ */
/*  配置*/
#define cGLOBAL_CVCT_CMD 	0x1FD7
/* 状态*/
#define sGLOBAL_CVCT_CMD 	0x1FD8
/* 告警*/
#define laGLOBAL_AVCT_DNU 	0x1FDA
/* ----------------------- 虚级联接收全局寄存器-------------------------*/
/*  配置*/
#define cGLOBAL_CVCR_CMD 			0x1FDB
/*  告警*/
#define laGLOBAL_LaVCR_BYTE 		0x1FDE
	#define LaVCR_LOSQM 		0x01
	#define LaVCR_LOCRCE 		0x02
	#define LaVCR_LOADDED 		0x04
	#define LaVCR_LOFAIL 		0x08
	#define LaVCR_LOREM 		0x10
#define laGLOBAL_LaVCR_VCAT_BYTE 	0x1FDF
	#define LaVCR_LOLOS 			0x01
	#define LaVCR_LOLOA 		0x02
	#define LaVCR_LOLCASGIDM 	0x04
	#define LaVCR_RXFIFO 		0x08



	
/*  映射全局寄存器*/
#define cGLOBAL_BIP2_BLOCK 0x1FE2



/*==========================  组寄存器定义    =============================*/

#define GROUP_ONE 		0x00<<9
#define GROUP_TEO 		0x01<<9
#define GROUP_THREE 	0x02<<9
#define GROUP_FOUR 		0x03<<9
/*------------------------- 以太网发送寄存器-----------------------------------------*/
#define cGROUP_ETHNET_SEND_PAUSEEN 	0x0000



/*----------------------------  GFP 封装寄存器 -------------------------------------------*/
/* 配置*/
#define cGROUP_GFP_SEND_CONFIG 		0x00A0
	#define CGT_PTI 					0xE0 
	#define CGT_PFI 					0x10
	#define CGT_EXI 					0x0F
/* 性能RC  */
#define rpcGROUP_GFP_FRAME_ALLPktH 	0x00B0
#define rpcGROUP_GFP_FRAME_ALLPktL 	0x00B1
#define rpcGROUP_GFP_FRAME_NetPkt		0x00B2
#define rpcGROUP_GFP_FRAME_ErrPkt 		0x00B3
#define rpcGROUP_GFP_FRAME_ALLByteH 	0x00B4
#define rpcGROUP_GFP_FRAME_AllByteM 	0x00B5
#define rpcGROUP_GFP_FRAME_AllByteL 	0x00B6
/* ----------------------------  GFP 解封装寄存器----------------------------------------*/
/* 状态RO */
#define sGROUP_GFP_DEFRAME_SYN 		0x00C9
#define sGROUP_GFP_DEFRAME_PTIPFIEXI 	0x00CA
	#define sGR_PTI 				0xE0
	#define sGR_PFI				0x10
	#define sGR_EXI				0x0F
/* 性能RC */
#define rpcGROUP_GFP_DEFRAME_ALLPktH 	0x00E0
#define rpcGROUP_GFP_DEFRAME_ALLPktL	0x00E1
#define rpcGROUP_GFP_DEFRAME_ERRPktH	0x00E2
#define rpcGROUP_GFP_DEFRAME_ERRPktL 	0x00E3
#define rpcGROUP_GFP_DEFRAME_NETPKT 	0x00E4
#define rpcGROUP_GFP_DEFRAME_ALLBytesH	0x00E5
#define rpcGROUP_GFP_DEFRAME_ALLBytesM	0x00E6
#define rpcGROUP_GFP_DEFRAME_ALLBytesL	0x00E7
/*告警*/
#define LaGR_Alarm_Byte 0x00DC
	#define LaGR_SYNLOSS 0x02
	#define LaGR_Siglecsf  0x01



/* ----------------------------- 虚级联发送组寄存器----------------------------------*/
/* 配置*/
#define cGROUP_VCAT_SEND_CONFIG		0x0180
	#define cTVCAT 		0x01
	#define cTLCAS 		0x02
	#define cTFCRST		0x04
	#define cTVCG_SRST 	0x08
	#define cTFAIL_DEAL 	0x30
/*  告警RC */
#define laGROUP_VCAT_SEND_TLOPRD2 	0x0191
/* ---------------------------- 虚级联接收组寄存器----------------------------------*/
#define cGROUP_VCAT_RECV_CONFIG 		0x01C0
	#define cRVCT 		0x01
	#define cRLCAS 		0x02
	#define cRLCCRCRST 	0x04
	#define cRmaxdelvcg 0x38
/* 告警*/
#define laGROUP_VCAT_RECV_ALARM 		0x01D1
	#define laLOLOS_AIIVT 	0x01
	#define laLOLOA_AIIVT 	0x02
	#define laRLOLCASGIDM 	0x04
	#define laRXFIFO 			0x08
/* ========================== 支路寄存器定义================================*/
#define VC12_BASE_ADDR 0x1000
/*----------------------------  虚级联支路发送寄存器--------------------------------*/
#define cVC12_SEND_CONFIG 				0x00
	#define cVC12_SEND_LOVCG		0x07
	#define cTLOUSE 					0x08
	#define cTLOK4VCEN				0x10
	#define cTLOCRCERO				0x20
#define cVC12_SEND_LOSQ				0x01  	/*bit 5:0*/
/* 状态*/
#define sVC12_SEND_STATUS 				0x02
	#define sVC12_SEND_LOVCG		0x07
	#define sVC12_SEND_LOUSE		0x08
	#define sVC12_SEND_INGRP		0x10
	#define sVC12_SEND_ADD_END 	0x20
#define sVC12_SEND_LOSQ				0x03 	/*bit 5:0*/
#define sVC12_SEND_LOCTRL				0x04	/*bit 3:0*/
/*  告警*/
#define laVC12_SEND_LCAS_DNU 			0x09
/* --------------------------------- 虚级联支路接收寄存器-----------------------------*/
#define cVC12_RECV_CONFIG				0x0B
	#define cVC12_RECV_LOVCG 		0x07
	#define cRLOUSE					0x08
	#define cRMSTFAIL				0x10
#define cVC12_RECV_LOSQ			0x0C	/*bit 5:0*/
/* 状态*/
#define sVC12_RECV_STATUS 				0x0D
	#define sVC12_RECV_LOVCG		0x07
	#define sVC12_RECV_LOUSE 		0x08
	#define sVC12_RECV_INGRP		0x10
#define sVC12_RECV_LOSQ			0x0E		/*bit 5:0*/
#define sVC12_RECV_LOCTRL			0x0F		/*bit 4:0*/
/* 告警*/
#define laVC12_RECV_ALARM				0x14
	#define laVC12_RECV_LOSQM		0x01
	#define laVC12_RECV_LCASCRCE	0x02
	#define laVC12_RECV_LCASADDED	0x04
	#define laVC12_RECV_LCASFAIL	0x08
	#define laVC12_RECV_LCASREM 	0x10
	#define laVC12_RECV_K4BIT1_LOF 	0x20
	#define laVC12_RECV_MFI_LOF	0x40
	#define laVC12_RECV_TSF			0x80

/* ----------------------------   映射支路发送寄存器------------------------------------*/
#define TU12_BASE_ADDR 				0x1000

/* 配置*/
#define cTU12_SEND_K4					0x18
#define cTU12_V5_BYTE					0x19
	#define cTU12_V5				0xC0
	#define cTU12_REI				0x20
	#define cFIX_BIT					0x0E		/*bit3:1 = 101*/
	#define cTU12_RDI				0x01
#define cTU12_SEND_K4_B1			0x1A
#define cTU12_SEND_N2					0x1B
/* ------------------------------- 映射支路接收寄存器------------------------------------*/
/* 配置*/
#define cTU12_RECV_TSL_EXP				0x1C 	/*bit2:0*/
#define cTU12_RECV_K4_B1_ESL_EXP		0x1D
#define cTU12_RECV_ADD_DROP_BYTE		0x1E
	#define cTU12_RECV_ADDEN		0x80
	#define cTU12_RECV_DROPEN		0x40
	#define cTU12_RECV_DEG			0x20
	#define cTU12_RECV_SEL_MOD		0x18
	#define cTU12_RECV_SEL_FORCE 	0x04
	#define cTU12_RECV_SEL_CONFIG	0x02
	#define sTU12_RECV_SEL_ACTUAL 	0x01
/*告警*/
#define laTU12_RECV_A_ALARM			0x20
	#define TU_AIS					0x80
	#define TU_LOP					0x40
	#define TU_UNEQ					0x20
	#define VC_AIS					0x10
	#define PLM						0x08
	#define RDI						0x04
	#define K4_B1_LOM				0x02
	#define K4_B1_PLM				0x01
#define rpcTU12_RECV_A_PJE_CNT			0x22	/*bit6:0*/
#define rpcTU12_RECV_A_NJE_CNT			0x23	/*bit6:0*/
#define rpcTU12_RECV_A_BIP2_CNTL 		0x24
#define rpcTU12_RECV_A_BIP2_CNTH 		0x25	/*bit3:0*/
#define rpcTU12_RECV_A_REI_CNTL		0x26
#define rpcTU12_RECV_A_REI_CNTH		0x27	/*bit3:0*/



#define laTU12_RECV_B_ALARM			0x30
#define rpcTU12_RECV_B_PJE_CNT			0x32	/*bit6:0*/
#define rpcTU12_RECV_B_NJE_CNT			0x33	/*bit6:0*/
#define rpcTU12_RECV_B_BIP2_CNTL		0x34
#define rpcTU12_RECV_B_BIP2_CNTH		0x35	/*bit3:0*/
#define rpcTU12_RECV_B_REI_CNTL		0x36
#define rpcTU12_RECV_B_REI_CNTH		0x37	/*bit3:0*/
/*========================================================================*/


//typedef unsigned char BOOL;
//typedef unsigned char uint8;
//typedef unsigned short int uint16;
//typedef unsigned long int uint32;
#define CURRENT_CARD_VCG_NUMBER 4      /*虚级联组  个数*/
#define MAX_CARD_E1_NUMBER 63              /*板卡E1 的数量*/




// typedef struct
// {
// 	uint32 high32;
// 	uint32 low32;
// }U64;


extern uint8 MarkTableNew[CURRENT_CARD_VCG_NUMBER][MAX_CARD_E1_NUMBER];
extern uint8 MarkTableOld[CURRENT_CARD_VCG_NUMBER][MAX_CARD_E1_NUMBER];
extern uint8 LcasFlagNew[CURRENT_CARD_VCG_NUMBER];
extern uint8 LcasFlagOld[CURRENT_CARD_VCG_NUMBER];




#ifndef TRUE
#define TRUE (!FALSE)
#endif
#ifndef FALSE
#define FALSE (1==0)
#endif

#ifndef ENABLE
#define ENABLE 1
#endif
#ifndef DISABLE 
#define DISABLE 0
#endif


#define BUS_A 1
#define BUS_B 2
#define VCAT_VALID 1
#define VCAT_INVALID 0
#define LCAS_ENABLE 1
#define LCAS_DISABLE 0
#define VCAT_ENABLE 1
#define VCAT_DISABLE 0


/***************RC6400 MANAGE INTERFACE DEFINE********************************/
#define RC6400_ADDR_BASE	             		(0xE3000000 + 0x8000)	/*从48M开始,放入非CAECH区*/
#define RC6400_REGS_PTR		 	             	((unsigned char volatile *) (RC6400_ADDR_BASE))

/*===============================================================================*/
/*===============================================================================*/
/*===============================================================================*/

extern void RC6400_Var_Init(void);							/*RC6400 模块相关变量的初始化*/
extern void RC6400_Chip_Init(void);							/*RC6400 模块芯片初始化*/
extern BOOL RC6400_Check_FPGA_Ready(void);			/*检测FPGA  程序是否下载完毕*/
extern void RC6400_Reset(void);							/*芯片复位接口*/
/*============================ 保护倒换配置接口===============================*/
#if 0
extern void RC6400_E1_Manual_Switch(void);				/*保护倒换接口*/
#endif
/*============================上下支路使能配置=================================
EnableFlag =	ENABLE;
			DISABLE;
--------------------------------------------------------------------------------------------------------*/
#if 0
extern void RC6400_Add_Drop_En(uint8 EnabledFlag);			/*映射支路使能接口*/
#endif
/* ============================= GFP 配置接口=====================================*/
extern void RC6400_PTI_Set(uint8 VCGNum,uint8 SetValue);
extern uint8 RC6400_PTI_Read(uint8 VCGNum);
extern void RC6400_PFI_Set(uint8 VCGNum,uint8 SetValue);
extern uint8 RC6400_PFI_Read(uint8 VCGNum);
extern void RC6400_EXI_Set(uint8 VCGNum,uint8 SetValue);
extern uint8 RC6400_EXI_Read(uint8 VCGNum);
/*============================== VCG 配置接口=====================================
LcasFlag = 	NON_LCAS;
			LCAS;
--------------------------------------------------------------------------------------------------------*/
/*一级函数，虚级联组*/
extern void RC6400_LCAS_En_Rx_Set(uint8 VCGNum,uint8 flag);			/*某组LCAS  接收端使能设置*/
extern BOOL RC6400_LCAS_En_Rx_Read(uint8 VCGNum);
extern void RC6400_LCAS_En_Tx_Set(uint8 VCGNum, uint8 flag);			/*某组LCAS  发送端使能设置*/
extern BOOL RC6400_LCAS_En_Tx_Read(uint8 VCGNum);
extern void RC6400_VCAT_En_Tx_Set(uint8 VCGNum, uint8 flag);
extern BOOL RC6400_VCAT_En_Tx_Read(uint8 VCGNum);
extern void RC6400_VCAT_En_Rx_Set(uint8 VCGNum, uint8 flag);
extern BOOL RC6400_VCAT_En_Rx_Read(uint8 VCGNum);
/*一级函数，虚级联支路*/
extern void RC6400_VC12_GRP_Sel_Rx_Set(uint8 TsNum,uint8 VCGNum);
extern uint8 RC6400_VC12_GRP_Sel_Rx_Read(uint8 TsNum);
extern void RC6400_VC12_GRP_Sel_Tx_Set(uint8 TsNum,uint8 VCGNum);
extern uint8 RC6400_VC12_GRP_Sel_Tx_Read(uint8 TsNum);
extern void RC6400_VC12_En_Tx_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_VC12_En_Tx_Read(uint8 TsNum);
extern void RC6400_VC12_En_Rx_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_VC12_En_Rx_Read(uint8 TsNum);
extern void RC6400_VC12_SQ_Rx_Set(uint8 TsNum,uint8 SQNum);
extern uint8 RC6400_VC12_SQ_Rx_Read(uint8 TsNum);
extern void RC6400_VC12_SQ_Tx_Set(uint8 TsNum, uint8 SQNum);
extern uint8 RC6400_VC12_SQ_Tx_Read(uint8 TsNum);
extern void RC6400_VC12_K4B2_En_Tx_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_VC12_K4B2_En_Tx_Read(uint8 TsNum);
extern void RC6400_VC12_MST_En_Rx_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_VC12_MST_En_Rx_Read(uint8 TsNum);
/*一级函数，映射层*/
extern void RC6400_TU12_En_Rx_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_TU12_En_Rx_Read(uint8 TsNum);
extern void RC6400_TU12_En_Tx_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_TU12_En_Tx_Read(uint8 TsNum);
extern void RC6400_TU12_V5_Config_Rx_Set(uint8 TsNum,uint8 val);		/*bit2:0, TSL,advice:0x0a*/
extern uint8 RC6400_TU12_V5_Config_Rx_Read(uint8 TsNum);
extern void RC6400_TU12_V5_Config_Tx_Set(uint8 TsNum,uint8 val);		/*One Byte, advice:0x0a*/
extern uint8 RC6400_TU12_V5_Config_Tx_Read(uint8 TsNum);
extern void RC6400_TU12_K4_Config_Rx_Set(uint8 TsNum,uint8 val);		/*One Byte, advice:0x0d*/
extern uint8 RC6400_TU12_K4_Config_Rx_Read(uint8 TsNum);
extern void RC6400_TU12_K4_Config_Tx_Set(uint8 TsNum, uint8 val);		/*bit5:0, advice:0x0d*/
extern uint8 RC6400_TU12_K4_Config_Tx_Read(uint8 TsNum);
extern void RC6400_TU12_Bus_Sel_Mode_Rx_Set(uint8 TsNum,uint8 flag);	/*00,01,10,11*/
extern uint8 RC6400_TU12_Bus_Sel_Mode_Rx_Read(uint8 TsNum);
extern void RC6400_TU12_Bus_Sel_Force_Rx_En_Set(uint8 TsNum,uint8 flag);
extern BOOL RC6400_TU12_Bus_Sel_Force_Rx_En_Read(uint8 TsNum);
extern void RC6400_TU12_Bus_Exp_Sel_Rx_Set(uint8 TsNum,uint8 flag);
extern uint8 RC6400_TU12_Bus_Exp_Sel_Rx_Read(uint8 TsNum);
extern void RC6400_TU12_Bus_Actual_Sel_Rx_Read(uint8 TsNum,uint8* flag);

/*二级函数*/
extern void RC6400_LCAS_Single_Ts_Remove_Tx(uint8 TsNum);
extern void RC6400_LCAS_Single_Ts_Remove_Rx(uint8 TsNum);
extern void RC6400_NLCAS_Single_Ts_Remove_Tx(uint8 TsNum);
extern void RC6400_NLCAS_Single_Ts_Remove_Rx(uint8 TsNum);
extern void RC6400_LCAS_Single_Ts_Add_Tx(uint8 TsNum,uint8 VCGNum);
extern void RC6400_LCAS_Single_Ts_Add_Rx(uint8 TsNum,uint8 VCGNum);
extern void RC6400_NLCAS_Single_Ts_Add_Tx(uint8 TsNum,uint8 VCGNum);
extern void RC6400_NLCAS_Single_Ts_Add_Rx(uint8 TsNum,uint8 VCGNum);

/*三级函数,涉及到方案*/
extern void RC6400_LCAS_VCAT_GRP_Remove(uint8 VCGNum);
extern void RC6400_LCAS_VCAT_GRP_Add(uint8 VCGNum);
extern void RC6400_NLCAS_VCAT_GRP_Remove(uint8 VCGNum);
extern void RC6400_NLCAS_VCAT_GRP_Add(uint8 VCGNum);

/*四级函数, 涉及到 方案*/
#if 0
extern void VCG_Config_One(uint8 VCGNum);
#endif
extern void RC6400_VCG_Config_One_Remove(uint8 VCGNum);
extern void RC6400_VCG_Config_One_Add(uint8 VCGNum);
/*虚级联配置前更新函数*/
extern void Update_MarkTable_New_One(uint8 VCGNum,uint8* pTsArr, uint8 TsLen);
extern void Update_MarkTable_Old_One(uint8 VCGNum);
extern void Update_LCASTable_New_One(uint8 VCGNum,uint8 LcasFlag);
extern void Update_LCASTable_Old_One(uint8 VCGNum);

void Delay32ms(void);
extern void RC6400_SQ_Realing(uint8 VCGNum);
/*=================================== PAUSE  控制==================================*/
extern void RC6400_Pause_Config(uint8 VCGNum,uint8 flag);/*future reserved*/
/*==================================  告警接口===================================*/
extern void RC6400_TU12_LockAlarmR_Read_Multi(uint8 busSel,uint8 TsNums,uint8* pTsIndex,uint8* pTsAlarms);
extern uint8 RC6400_TU12_LockAlarmR_Read_Single(uint8 busSel, uint8 TsNum);
extern void RC6400_VC12_AlarmR_Read_Multi(uint8 TsNums,uint8* pTsIndex,uint8* pTsAlarms);
extern uint8 RC6400_VC12_AlarmR_Read_Single(uint8 TsNum);
extern void RC6400_VC12_AlarmT_Read_Multi(uint8 TsNums,uint8* pTsIndex,uint8* pTsAlarms);
extern uint8 RC6400_VC12_AlarmT_Read_Single(uint8 TsNum);
extern void RC6400_VCAT_AlarmT_Read(uint8 VCGNum,uint8* pVCGAlarm);
extern uint8 RC6400_VCAT_AlarmT_Read_V2(uint8 VCGNum);
extern void RC6400_VCAT_AlarmR_Read(uint8 VCGNum,uint8* pVCGAlarm);
extern void RC6400_38MClk_Alarm_Read(uint8* pAlarmByte);
extern void RC6400_VCAT_GLOBAL_AlarmR_Read(uint8* pAlarmByte1,uint8* pAlarmByte2);
extern void RC6400_VCAT_GLOBAL_AlarmT_Read(uint8* pAlarmByte);
extern BOOL RC6400_DeFrame_Syn_Alarm_Read(uint8 VCGNum);
extern void RC6400_Alarm_Clear_All_Init(void);
/*=================================== 状态接口===================================*/
extern uint8 RC6400_VC12R_SQ_Status_Read(uint8 TsNum);
extern uint8 RC6400_VC12T_SQ_Status_Read(uint8 TsNum);
extern uint8 RC6400_VC12R_CTRL_Status_Read(uint8 TsNum);
extern uint8 RC6400_VC12T_CTRL_Status_Read(uint8 TsNum);
extern uint8 RC6400_VC12R_UseInfos_Status_Read(uint8 TsNum);
extern uint8 RC6400_VC12T_UseInfos_Status_Read(uint8 TsNum);
extern BOOL RC6400_GFP_DeFrame_Syn_Status_Read(uint8 VCGNum);
extern uint8 RC6400_GFP_DeFrame_PTI_Status_Read(uint8 VCGNum);
extern uint8 RC6400_GFP_DeFrame_PFI_Status_Read(uint8 VCGNum);
extern uint8 RC6400_GFP_DeFrame_EXI_Status_Read(uint8 VCGNum);
/*=================================== 性能接口====================================

--------------------------------------------------------------------------------------------------------*/
extern uint16 RC6400_TU12_BIP2_Perform_Read(uint8 BusSel,uint8 TsNum);
extern uint8 RC6400_TU12_PJE_Perform_Read(uint8 BusSel,uint8 TsNum);
extern uint8 RC6400_TU12_NJE_Perform_Read(uint8 BusSel,uint8 TsNum);
extern uint16 RC6400_TU12_REI_Perform_Read(uint8 BusSel,uint8 TsNum);

extern uint16 RC6400_GFP_Frame_AllPkts_Perform_Read(uint8 VCGNum);
extern uint8  RC6400_GFP_Frame_ErrPkts_Perform_Read(uint8 VCGNum);
extern uint32  RC6400_GFP_Frame_AllBytes_Perform_Read(uint8 VCGNum);
extern uint16  RC6400_GFP_DeFrame_AllPkts_Perform_Read(uint8 VCGNum);
extern uint16  RC6400_GFP_DeFrame_ErrPkts_Perform_Read(uint8 VCGNum);
extern uint32  RC6400_GFP_DeFrame_AllBytes_Perform_Read(uint8 VCGNum);

/*=============================== 38M 时钟信号监测===============================*/
extern void RC6400_38MClk_Los_Check(void);							/*38M 时钟信号消失监测*/
/*===============================  软件升级支持==================================*/

extern uint8 get_drv_pkt_info(void);											/*获取软件版本号*/
extern uint8  get_IC_info(void);												/*获取芯片版本号*/
extern void write(uint16 addr , uint8 data);

#if defined (__cplusplus)
}
#endif

#endif

