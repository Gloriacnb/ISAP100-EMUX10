/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			ChipSlotLogic.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/EZwellChipDriver/ChipSlotLogic.c
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

#include "ChipSlotLogic.h"
#include "Mid_SPI.h"
#include "lpc32xx_gpio_driver.h"
#include "ChipGluLogic.h"
#include <string.h>
#include "Mid_FlashData.h"
#include "Mid_Timer.h"
#include <rtl.h>

//#include "TerminalUart.h"


SlotLogic_REGS_T* slotlogic;
DCC_BUF_T* dcc_buf;
DCC_CTRL_T* dcc_ctrl;
DCC_BUF_T* dcn_buf;

uint32 checkFpgaFile(void) {
	return TRUE;
}

uint32 slotlogic_open(EZ_FLASH_DATA_T* file) {
	int i, j;
	uint32 errno = 0;
	int tryCount = 1;
	slotlogic = SlotLogic_REG_PTR;
	dcc_buf = DCC_BUF_REG_PTR;
	dcc_ctrl = DCC_CTRL_REG_PTR;
	dcn_buf = DCN_BUF_REG_PTR;
	while( tryCount-- ) {
		if( updata_fpga((uint8*)file->BufAddr,file->ByteNums) == TRUE ) {
			if( slotlogic->chipID != SlotLogic_Hard_Code ) {
				slotlogic = NULL;
				errno = 3;
				continue;
			}
			break;
		}
		else {
			errno = 2;
		}
	}
	if( errno != 0 ) {
		return errno;
	}

	for( i = 0; i < 16; i++ ) {
		for( j = 0; j < 32; j++ ) {
			SlotLogic_WriteReg( (i<<6) | (j<<1) | 1, 0x80 );
		}
	}

 	/* ���Ȱ�PCMʱ�ӹ̶�Ϊ��ʱ��  */
	setPCMClockSource(FREE_RUN);
	return 0;

}


uint32 updata_fpga(uint8* loadData, uint32 len ) {
	uint32 i = 0;
//	uint8* pdata;
//	uint32 sendBytes = 0;
	
	uint8 dump;
	//clear fifo
	SpiSend(&dump, 1);

	glulogic->FPGA_CTRL = Glu_SPI_LOADFPGA;
	while( (GPIO->p3_inp_state & P3_IN_STATE_GPI_08) != 0 );

	glulogic->FPGA_CTRL = Glu_SPI_LOADFPGA | 1;
	while( (GPIO->p3_inp_state & P3_IN_STATE_GPI_08) == 0 );



//	pdata = (uint8*)loadData;
//	for( i = 0; i < 2000; i++ );

	SpiSend(loadData, len);


	glulogic->FPGA_CTRL = Glu_SPI_NORMAL;
	i = 10000;
	while( i-- ) {
		if( (GPIO->p3_inp_state & P3_IN_STATE_GPI_19_U4RX) != 0 ) {
			return TRUE;
		}
	}

	return FALSE;
}

uint32 do_upe1_alarm_ais(uint8 id) {
	uint8 ais = slotlogic->UP_E1_AIS;
	return (ais & (1<<id)) != 0;
}

uint32 do_upe1_alarm_wrk(uint8 id) {
	uint8 los = slotlogic->UP_E1_LOS;
	return (los & (1<<id)) != 0;
}

uint32 do_upe1_alarm_lof(uint8 id) {
	uint8 alarm = 0;
	if( id == 2 ) {
		alarm = slotlogic->UP_E1_1_Alarm;
	}
	else if( id == 3 ) {
		alarm = slotlogic->UP_E1_2_Alarm;
	}
	return ((alarm >> 4) & 1) == 0;
}
uint32 do_upe1_alarm_lom(uint8 id) {
	uint8 alarm = 0;
	if( id == 2 ) {
		alarm = slotlogic->UP_E1_1_Alarm;
	}
	else if( id == 3 ) {
		alarm = slotlogic->UP_E1_2_Alarm;
	}
	return ((alarm >> 2) & 1);
}

uint8 SlotLogic_ReadReg(uint32 regaddr) {
	uint32 realaddr = regaddr + SlotLogic_Base_Addr;
	return *((uint8*)realaddr);
}
void SlotLogic_WriteReg(uint32 regaddr, uint8 newdata) {
	uint32 realaddr = regaddr + SlotLogic_Base_Addr;
	*((uint8*)realaddr) = newdata;
}

uint32 CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs) {
	uint16 uiRegAddr = (toCh << 5) | toTs;
	if( toCh > 15 || fromCh > 15 || toTs > 31 || fromTs > 31 ) {
		return FALSE;
	}
	SlotLogic_WriteReg( uiRegAddr << 1, fromTs);
	SlotLogic_WriteReg( (uiRegAddr << 1) | 1, fromCh );
	return TRUE;
}


uint32 RemoveCrossConnection(uint32 Ch, uint32 Ts) {
	uint16 uiRegAddr = (Ch << 5) | Ts;
	if( Ch > 15 || Ts > 31 ) {
		return FALSE;
	}
	SlotLogic_WriteReg( (uiRegAddr << 1) | 1, 0x80 );
	return TRUE;
}

#define DEF_TEST_MODE 0xEB


void configXC(SlotLogic_CFG_T* cf) {
	int i = 0;
	for( i = 0; i < cf->count; i++ ) {
		if( cf->conn[i].option == creat ) {
			CreatCrossConnection( 	cf->conn[i].part_A_CH,
									cf->conn[i].part_A_TS,
									cf->conn[i].part_B_CH,
									cf->conn[i].part_B_TS   );

			CreatCrossConnection( 	cf->conn[i].part_B_CH,
									cf->conn[i].part_B_TS,
									cf->conn[i].part_A_CH,
									cf->conn[i].part_A_TS   );
		}
		else if( cf->conn[i].option == removeXC ) {
			RemoveCrossConnection( 	cf->conn[i].part_A_CH,
									cf->conn[i].part_A_TS);

			RemoveCrossConnection( 	cf->conn[i].part_B_CH,
									cf->conn[i].part_B_TS);
		}
	}
}

void SetTempWorkMode(uint8 mode) {
	int i = 0;
	SlotLogic_CFG_T config;
	memset(&config, 0, sizeof(config));
	if( mode == DEF_TEST_MODE ) {
		config.count = 8;
		for( i = 0; i < 8; i++ ) {
			config.conn[i].option = creat;
			config.conn[i].part_A_CH = 8;
			config.conn[i].part_B_CH = 9;
			if(i < 4) {
				config.conn[i].part_A_TS = i+1;
				config.conn[i].part_B_TS = i+1;
			}
			else {
				config.conn[i].part_A_TS = i+13;
				config.conn[i].part_B_TS = i+13;
			}
		}
	}
	else {
		config.count = 30;
		/*
		 *	VF	E1	STB 8
		 *	1	1	1
		 *	2	2	2
		 *	3	3	3
		 *	4	4	4
		 *	5	5	17
		 *	6	6	18
		 *	7	7	19
		 *	8	8	20
		 */
		for( i = 0; i < 8; i++ ) {
			config.conn[i].option = creat;
			config.conn[i].part_A_CH = 2;
			config.conn[i].part_B_CH = 8;
			if(i < 4) {
				config.conn[i].part_A_TS = i+1;
				config.conn[i].part_B_TS = i+1;
			}
			else {
				config.conn[i].part_A_TS = i+1;
				config.conn[i].part_B_TS = i+13;
			}
		}
		/*
		 *	VF	E1	STB 9
		 *	1	9	1
		 *	2	10	2
		 *	3	11	3
		 *	4	12	4
		 *	5	13	17
		 *	6	14	18
		 *	7	15	19
		 *	8	17	20
		 */
		for( i = 0; i < 8; i++ ) {
			config.conn[i+8].option = creat;
			config.conn[i+8].part_A_CH = 2;
			config.conn[i+8].part_B_CH = 9;
			if(i < 4) {
				config.conn[i+8].part_A_TS = i+1+8;
				config.conn[i+8].part_B_TS = i+1;
			}
			else if( i < 7 ){
				config.conn[i+8].part_A_TS = i+1+8;
				config.conn[i+8].part_B_TS = i+13;
			}
			else {
				config.conn[i+8].part_A_TS = i+2+8;
				config.conn[i+8].part_B_TS = i+13;
			}
		}
		/*
		 *	VF	E1	STB 10
		 *	1	18	1
		 *	2	19	2
		 *	3	20	3
		 *	4	21	4
		 *	5	22	17
		 *	6	23	18
		 *	7	24	19
		 *	8	25	20
		 */
		for( i = 0; i < 8; i++ ) {
			config.conn[i+16].option = creat;
			config.conn[i+16].part_A_CH = 2;
			config.conn[i+16].part_B_CH = 10;
			if(i < 4) {
				config.conn[i+16].part_A_TS = i+2+16;
				config.conn[i+16].part_B_TS = i+1;
			}
			else {
				config.conn[i+16].part_A_TS = i+2+16;
				config.conn[i+16].part_B_TS = i+13;
			}
		}
		/*
		 *	VF	E1	STB 11
		 *	1	26	1
		 *	2	27	2
		 *	3	28	3
		 *	4	29	4
		 *	5	30	17
		 *	6	31	18
		 */
		for( i = 0; i < 6; i++ ) {
			config.conn[i+24].option = creat;
			config.conn[i+24].part_A_CH = 2;
			config.conn[i+24].part_B_CH = 11;
			if(i < 4) {
				config.conn[i+24].part_A_TS = i+2+24;
				config.conn[i+24].part_B_TS = i+1;
			}
			else {
				config.conn[i+24].part_A_TS = i+2+24;
				config.conn[i+24].part_B_TS = i+13;
			}
		}
	}
	configXC(&config);
}


uint32 get_e1_buff_deepth(uint8 id) {
	volatile uint8* p = &slotlogic->E1_buff_deep;
	p += id;
	return *p;
}
void change_e1_buff_deep(uint8 id) {
	uint8 temp = slotlogic->E1_Buff_change;
	temp ^= (1<<id);
	slotlogic->E1_Buff_change = temp;
}

uint32 ifHavePacket(uint8 ch) {
	uint8 ctrl;
	switch( ch ) {
	case 0:
		ctrl = dcc_ctrl->dcc_a_rcv_ctrl & (1<<1);
		break;
	case 1:
		ctrl = dcc_ctrl->dcc_b_rcv_ctrl & (1<<1);
		break;
	case 2:
		ctrl = dcc_ctrl->xe1_a_rcv_ctrl & (1<<1);
		break;
	case 3:
		ctrl = dcc_ctrl->xe1_b_rcv_ctrl & (1<<1);
		break;
	}
	if( ctrl == 0 ) {
		return FALSE;
	}
	return TRUE;
}
uint16 getPacketLen(uint8 ch) {
	uint8* p;
	if( ifHavePacket(ch) != TRUE ) {
		return 0;
	}
	switch( ch ) {
	case 0:
		p = dcc_buf->dcc_a_rcv_len;
		break;
	case 1:
		p = dcc_buf->dcc_b_rcv_len;
		break;
	case 2:
		p = dcn_buf->dcc_a_rcv_len;
		break;
	case 3:
		p = dcn_buf->dcc_b_rcv_len;
		break;
	default:
		return 0;
	}
	return ((p[0]<<8) | p[1])-2;
}
uint32 GetDCCPacket(uint8 ch, uint8* buff) {

	uint8* buf;
//	uint8* rcvCtrl;
	uint16 len = getPacketLen(ch);
	int i;
	if( len == 0 ) {
		return 0;
	}
	switch( ch ) {
	case 0:
		buf = dcc_buf->dcc_a_rcv_buf;
		break;
	case 1:
		buf = dcc_buf->dcc_b_rcv_buf;
		break;
	case 2:
		buf = dcn_buf->dcc_a_rcv_buf;
		break;
	case 3:
		buf = dcn_buf->dcc_b_rcv_buf;
		break;
	default:
		return 0;
	}
	for( i = 0; i < len; i++ ) {
		*buff++ = *buf++;
	}
	clearDccRdBufForce(ch);
	return len;
}

void clearDccRdBufSafety(uint8 ch) {
	if( ifHavePacket(ch) == TRUE ) {
		clearDccRdBufForce(ch);
	}
}

void clearDccRdBufForce(uint8 ch) {
	uint8* rcvCtrl;
	switch( ch ) {
	case 0:
		rcvCtrl = &dcc_ctrl->dcc_a_rcv_ctrl;
		break;
	case 1:
		rcvCtrl = &dcc_ctrl->dcc_b_rcv_ctrl;
		break;
	case 2:
		rcvCtrl = &dcc_ctrl->xe1_a_rcv_ctrl;
		break;
	case 3:
		rcvCtrl = &dcc_ctrl->xe1_b_rcv_ctrl;
		break;
	default:
		return;
	}
	*rcvCtrl ^= 1;

}

void DccSendPacket(uint8 ch, uint8* data, uint16 len) {
	uint8* sendBuf;
	uint8* pSendLen;
	uint8* sendCtrl;
	uint16 glen = len+2;
	int i;
	switch( ch ) {
	case 0:
		sendBuf = dcc_buf->dcc_a_send_buf;
		pSendLen = dcc_buf->dcc_a_send_len;
		sendCtrl = &dcc_ctrl->dcc_a_send_ctrl;
		break;
	case 1:
		sendBuf = dcc_buf->dcc_b_send_buf;
		pSendLen = dcc_buf->dcc_b_send_len;
		sendCtrl = &dcc_ctrl->dcc_b_send_ctrl;
		break;
	case 2:
		sendBuf = dcn_buf->dcc_a_send_buf;
		pSendLen = dcn_buf->dcc_a_send_len;
		sendCtrl = &dcc_ctrl->xe1_a_send_ctrl;
		break;
	case 3:
		sendBuf = dcn_buf->dcc_b_send_buf;
		pSendLen = dcn_buf->dcc_b_send_len;
		sendCtrl = &dcc_ctrl->xe1_b_send_ctrl;
		break;
	default:
		return;
	}
	while( (*sendCtrl & (1<<1)) == 0 );
	pSendLen[0] = glen >> 8;
	pSendLen[1] = glen & 0xff;

	for( i = 0; i < len; i++ ) {
		sendBuf[i] = data[i];
	}
	*sendCtrl ^= 1;
}


uint16 getSlotLogicVersion(void) {
	return slotlogic->chip_ver;
}


void setLoopin(uint8 ch, uint8 loop) {
	uint8 temp = slotlogic->loopIn;
	temp &= ~(1 << ch);
	temp |= loop << ch;
	slotlogic->loopIn = temp;
}

void setLoopout(uint8 ch, uint8 loop) {
	uint8 temp = slotlogic->loopOut;
	temp &= ~(1 << ch);
	temp |= loop << ch;
	slotlogic->loopOut = temp;
}

void setPCMClockSource(CLOCK_SOURCE_OP_E mode) {

	switch( mode ) {
	case FREE_RUN:
		slotlogic->CLK_SEL = 0x80;
		break;
	case RECOVER_A:
		slotlogic->CLK_SEL = 0;
		break;
	case RECOVER_B:
		slotlogic->CLK_SEL = 1;
		break;
	case RECOVER_C:
		slotlogic->CLK_SEL = 2;
		break;
	case RECOVER_D:
		slotlogic->CLK_SEL = 3;
		break;
	}

	slotlogic->CLK_Start = 1;
}

CLOCK_SOURCE_OP_E getPCMClockSource(void) {
	uint8 temp = slotlogic->CLK_SEL;
	if( (temp & 0x80) != 0 ) {
		return FREE_RUN;
	}
	else if( temp == 0x02 ) {
		return RECOVER_A;
	}
	else if( temp == 0x03 ) {
		return RECOVER_B;
	}
	return HOLD_OVER;
}

void setDccInterruptEnable(uint8 ch, uint8 en) {
	uint8 regvalue = SlotLogic_ReadReg(REG_DCC_INTRR_EN);
	regvalue &= ~(1 << ch);
	regvalue |= (en << ch);
	SlotLogic_WriteReg(REG_DCC_INTRR_EN, regvalue);

}

void setDcnInterruptEnable(uint8 ch, uint8 en) {
	uint8 regvalue = SlotLogic_ReadReg(REG_DCN_INTRR_EN);
	regvalue &= ~(1 << ch);
	regvalue |= (en << ch);
	SlotLogic_WriteReg(REG_DCN_INTRR_EN, regvalue);
}

void selectDcnTs(uint8 ch, uint32 tsmap) {
	SlotLogic_WriteReg(REG_DCN_TS_SEL_Base(ch), tsmap & 0xff);
	SlotLogic_WriteReg(REG_DCN_TS_SEL_Base(ch)+1, (tsmap>>8) & 0xff);
	SlotLogic_WriteReg(REG_DCN_TS_SEL_Base(ch)+2, (tsmap>>16) & 0xff);
	SlotLogic_WriteReg(REG_DCN_TS_SEL_Base(ch)+3, (tsmap>>24) & 0xff);

}

uint32 getDcnTsMap(uint8 ch) {
	return SlotLogic_ReadReg(REG_DCN_TS_SEL_Base(ch))
			| (SlotLogic_ReadReg(REG_DCN_TS_SEL_Base(ch)+1) << 8)
			| (SlotLogic_ReadReg(REG_DCN_TS_SEL_Base(ch)+2) << 16)
			| (SlotLogic_ReadReg(REG_DCN_TS_SEL_Base(ch)+3) << 24);
}

uint8 ifDcnHavePacket(uint8 ch) {
	uint8 regv = SlotLogic_ReadReg(REG_DCN_R_STA);
	regv &= (1 << ch);
	return regv;
}

int getDcnPacketLen(uint8 ch) {
	uint8 regv[2];
	regv[1] = SlotLogic_ReadReg(REG_DCN_R_LEN_BASE(ch));
	regv[0] = SlotLogic_ReadReg(REG_DCN_R_LEN_BASE(ch)+1);
	return ((regv[1] << 8) | regv[0])-2;
}

uint8 getDcnPacket(uint8 ch, uint8* buff, uint16 len) {
	int i;
    for (i = 0; i < 2; ++i) {
        //gap length bytes
    	SlotLogic_ReadReg(REG_DCN_R_BUF(ch));
    }
    for (i = 0; i < len; ++i) {
        buff[i] = SlotLogic_ReadReg(REG_DCN_R_BUF(ch));
    }
    readDcnPacketOver(ch);
    return 1;
}

void readDcnPacketOver(uint8 ch) {
	uint8 regv = SlotLogic_ReadReg(REG_DCN_R_OVER);
	regv ^= (1 << ch);
	SlotLogic_WriteReg(REG_DCN_R_OVER, regv);
}

void sendDcnPacket(uint8 ch, uint8* data, uint16 len) {
    uint8 retryNum = 200;
    int i;
    uint16 regV;
    while( retryNum-- ) {
        uint16 sta = SlotLogic_ReadReg(REG_DCN_T_STA);
        if( ((sta >> ch) & 1) != 0 ) {
        	SlotLogic_WriteReg(REG_DCN_T_BUF(ch), (len+2) >> 8);
        	SlotLogic_WriteReg(REG_DCN_T_BUF(ch), (len+2) & 0xff);
            for (i = 0; i < len; ++i) {
            	SlotLogic_WriteReg(REG_DCN_T_BUF(ch), data[i]);
            }
            regV = SlotLogic_ReadReg(REG_DCN_T_OVER);
            regV ^= (1 << ch);
            SlotLogic_WriteReg(REG_DCN_T_OVER, regV);
            return;
        }
        os_dly_wait(1);
    }

}

uint16 REG_DCN_TS_SEL_Base(uint8 ch) {
    return 0x490 + (ch<<2);
}

uint16 REG_DCN_T_BUF(uint8 ch) {
    return 0x4a0 + ch;
}

uint16 REG_DCN_R_BUF(uint8 ch) {
    return 0x4b0 + ch;
}

uint16 REG_DCN_R_LEN_BASE(uint8 ch) {
    return 0x4b4 + (ch<<1);
}

uint8 ifSabitHavePacket(uint8 ch) {
    uint16 temp = SlotLogic_ReadReg(REG_SABIT_R_STA);
    if( temp & 1 ) {
    	temp = SlotLogic_ReadReg(REG_SABIT_R_CH);
    	if( temp == ch ) {
    		return 1;
    	}
    }
    return 0;

}
uint16 getSabitPacketLen(uint8 ch) {
    return SlotLogic_ReadReg(REG_SABIT_R_LEN);
}
uint8 getSabitPacket(uint8 ch, uint8* buff, uint16 len) {
	int i;
    for (i = 0; i < len; ++i) {
        buff[i] = (uint8)SlotLogic_ReadReg(REG_SABIT_R_BUF+i);
    }
    readSabitPacketOver(ch);
    return 1;

}

void readSabitPacketOver(uint8 ch) {
	SlotLogic_WriteReg(REG_SABIT_R_OVER, 0x46);
}
void sendSabitPacket(uint8 ch, uint8* data, uint16 len) {
    uint8 chmask = 1 << ch;
    int i;
    for (i = 0; i < 200; ++i) {
		if( (SlotLogic_ReadReg(REG_SABIT_T_CH_STA) & chmask) != 0 ) {
			break;
		}
        os_dly_wait(1);
        if( i == 199 ) {
            return;
        }
    }
    SlotLogic_WriteReg(REG_SABIT_T_CH, ch);
    SlotLogic_WriteReg(REG_SABIT_T_LEN, len);
    for (i = 0; i < len; ++i) {
    	SlotLogic_WriteReg(REG_SABIT_T_BUF+i, data[i]);
    }
    SlotLogic_WriteReg(REG_SABIT_T_OVER, 0x46);
}
