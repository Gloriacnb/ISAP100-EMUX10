/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			ChipSlotLogic.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/EZwellChipDriver/ChipSlotLogic.h
** Created by:          Administrator
** Created date:        2012-12-19
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


#ifndef CHIPSLOTLOGIC_H_
#define CHIPSLOTLOGIC_H_

#include "EZ_types.h"
#include "Mid_FlashData.h"
#include "ClockSourceDefine.h"

#if defined (__cplusplus)
extern "C"
{
#endif

#define DEF_MAX_Connection 120

typedef enum {
	invalid,
	creat,
	removeXC
}OPT_MODE_E;

typedef struct {
	OPT_MODE_E option;
	uint8 part_A_CH;
	uint8 part_A_TS;
	uint8 part_B_CH;
	uint8 part_B_TS;

}Connection_T;

typedef struct {
	Connection_T conn[DEF_MAX_Connection];
	uint8 count;
	uint8 src_clk_mode;
	uint8 rcv_src_clk;
}SlotLogic_CFG_T;

typedef struct {
	uint8 reserve1[0x40F];
	uint8 reserve11;
	uint8 reserve12;
	uint8 UP_E1_1_Alarm;//bit2 lom, bit4 ~lof
	uint8 UP_E1_2_Alarm;//bit2 lom, bit4 ~lof
	uint8 reserve3[0x450-0x40F-4];
	volatile uint8 E1_buff_deep;
	uint8 reserve[15];
	volatile uint8 UP_E1_LOS;	//los
	volatile uint8 UP_E1_AIS;	//ais
	uint8 reseve2[3];
	uint8 loopIn;			//0x465
	uint8 loopOut;			//0x466
	uint8 portEN;			//0x467
	uint8 chipID;			//0x468
	uint8 chip_ver;			//0x469
	uint8 E1_Buff_change;   //0x46a
	uint8 reserve4[0x800-0x46a-1];
	uint8 CLK_SEL;			//bit7 freerun(1) recover(0) ; bit2~0 recover ch
	uint8 reseve3[4];
	uint8 CLK_Start;
//	uint8 NM_SND_CTRL; //bit 1 WEN, bit0 WDONE
//	uint8 ocup;
//	uint8 NM_RCV_CTRL; //bit1 REN, bit0 RDONE
//	uint8 ocup1[0x900-0x803-1];
//	uint8 NM_SND_PKG;
//	uint8 ocup2[0xA00-0x900-1];
//	uint8 NM_RCV_PKG;

}SlotLogic_REGS_T;

typedef struct {

	uint8 dcc_a_send_len[2];
	uint8 dcc_a_send_buf[0x400-2];
	uint8 dcc_b_send_len[2];
	uint8 dcc_b_send_buf[0x400-2];
	uint8 dcc_a_rcv_len[2];
	uint8 dcc_a_rcv_buf[0x400-2];
	uint8 dcc_b_rcv_len[2];
	uint8 dcc_b_rcv_buf[0x400-2];

}DCC_BUF_T;

typedef struct {
	uint8 reserv1;
	uint8 dcc_a_send_ctrl; // bit0 WDONE bit1 WEN
	uint8 reserv2;
	uint8 dcc_b_send_ctrl; // bit0 WDONE bit1 WEN
	uint8 reserv3[3];
	uint8 dcc_a_rcv_ctrl;  // bit0 RDONE bit1 REN
	uint8 reserv4[3];
	uint8 dcc_b_rcv_ctrl;  // bit0 RDONE bit1 REN

	uint8 reserv5[0x100-12];

	uint8 reserv6;
	uint8 xe1_a_send_ctrl; // bit0 WDONE bit1 WEN
	uint8 reserv7;
	uint8 xe1_b_send_ctrl; // bit0 WDONE bit1 WEN
	uint8 reserv8[3];
	uint8 xe1_a_rcv_ctrl;  // bit0 RDONE bit1 REN
	uint8 reserv9[3];
	uint8 xe1_b_rcv_ctrl;  // bit0 RDONE bit1 REN


}DCC_CTRL_T;

uint32 slotlogic_open(EZ_FLASH_DATA_T*);
uint32 updata_fpga(uint8* loadData, uint32 len );

void SetTempWorkMode(uint8 mode);

uint32 do_upe1_alarm_ais(uint8 id);
uint32 do_upe1_alarm_wrk(uint8 id);
uint32 do_upe1_alarm_lof(uint8 id);
uint32 do_upe1_alarm_lom(uint8 id);

uint32 get_e1_buff_deepth(uint8 id);
void change_e1_buff_deep(uint8 id);

uint16 getSlotLogicVersion(void);

/*
 * for crossconnect
 */
uint32 CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs);
uint32 RemoveCrossConnection(uint32 Ch, uint32 Ts);

/*
 * for loop
 */
void setLoopin(uint8 ch, uint8 loop);
void setLoopout(uint8 ch, uint8 loop);

/*
 * for vc12 DCC & dcn
 */
uint32 ifHavePacket(uint8 ch);
uint16 getPacketLen(uint8 ch);
uint32 GetDCCPacket(uint8 ch, uint8* buff);
void DccSendPacket(uint8 ch, uint8* data, uint16 len);
void clearDccRdBufSafety(uint8 ch);
void clearDccRdBufForce(uint8 ch);

/*
 * for sabit
 */
void setDccInterruptEnable(uint8 ch, uint8 en);
uint8 ifSabitHavePacket(uint8 ch);
uint16 getSabitPacketLen(uint8 ch);
uint8 getSabitPacket(uint8 ch, uint8* buff, uint16 len);
void readSabitPacketOver(uint8 ch);
void sendSabitPacket(uint8 ch, uint8* data, uint16 len);

/*
 * for DCN
 */
void setDcnInterruptEnable(uint8 ch, uint8 en);
void selectDcnTs(uint8 ch, uint32 tsmap);
uint32 getDcnTsMap(uint8 ch);
uint8 ifDcnHavePacket(uint8 ch);
int getDcnPacketLen(uint8 ch);
uint8 getDcnPacket(uint8 ch, uint8* buff, uint16 len);
void readDcnPacketOver(uint8 ch);
void sendDcnPacket(uint8 ch, uint8* data, uint16 len);


/* only for debug */
uint8 SlotLogic_ReadReg(uint32 regaddr);
void SlotLogic_WriteReg(uint32 regaddr, uint8 newdata);


/*
 * for ClockSource
 */
void setPCMClockSource(CLOCK_SOURCE_OP_E mode);
CLOCK_SOURCE_OP_E getPCMClockSource(void);

#define SlotLogic_Base_Addr (0xe3004000)
#define SlotLogic_REG_PTR 	((SlotLogic_REGS_T*)SlotLogic_Base_Addr)

#define DCC_CTRL_Base_Addr 	(0xe3005000)
#define DCC_CTRL_REG_PTR	((DCC_CTRL_T*)DCC_CTRL_Base_Addr)

#define DCC_BUF_Base_Addr 	(0xe300e000)
#define DCC_BUF_REG_PTR		((DCC_BUF_T*)DCC_BUF_Base_Addr)

#define DCN_BUF_Base_Addr   (0xe300f000)
#define DCN_BUF_REG_PTR		((DCC_BUF_T*)DCN_BUF_Base_Addr)

#define SlotLogic_Hard_Code 0xA9


static const uint16 REG_DCN_INTRR_EN = 0x484;
static const uint16 REG_DCC_INTRR_EN = 0x486;

//for sabit
//for sabit 0x6100
static const uint16 REG_SABIT_R_STA = 0x403; //bit0 rcv ready
static const uint16 REG_SABIT_R_CH  = 0x404; //RCV channal sn
static const uint16 REG_SABIT_R_LEN = 0x405; //RCV len
static const uint16 REG_SABIT_R_BUF = 0x600; //RCV Data
static const uint16 REG_SABIT_R_OVER= 0x40f; //RCV Over

//    static const uint16 REG_SABIT_T_STA = 0x8400;
static const uint16 REG_SABIT_T_BUF = 0x500; //SND Data
static const uint16 REG_SABIT_T_CH  = 0x401; //SND channal sn
static const uint16 REG_SABIT_T_LEN = 0x402; //SND len
static const uint16 REG_SABIT_T_OVER= 0x40c; //SND OVER 0x46 fix
static const uint16 REG_SABIT_T_BROAD = 0x40d; //bit7 1
static const uint16 REG_SABIT_T_CH_STA= 0x46c;

//for dcn
uint16 REG_DCN_TS_SEL_Base(uint8 ch);

static const uint16 REG_DCN_T_STA = 0x480;
static const uint16 REG_DCN_T_OVER = 0x481;
uint16 REG_DCN_T_BUF(uint8 ch);

static const uint16 REG_DCN_R_STA = 0x482;
static const uint16 REG_DCN_R_OVER = 0x483;
uint16 REG_DCN_R_BUF(uint8 ch);
uint16 REG_DCN_R_LEN_BASE(uint8 ch);

extern SlotLogic_REGS_T* slotlogic;
extern DCC_BUF_T* dcc_buf;
extern DCC_CTRL_T* dcc_ctrl;
extern DCC_BUF_T* dcn_buf;

#if defined (__cplusplus)
}
#endif
#endif /* CHIPSLOTLOGIC_H_ */
