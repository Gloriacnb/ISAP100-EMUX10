/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    LPC32_EMAC.C
 *      Purpose: Driver for NXP LPC3250 EMAC Ethernet Controller
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2012 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include "LPC32_EMAC.h"
#include <LPC325x.H>                    /* LPC325x definitions               */
#include "MidoptDCC.h"
#include "EthMemory.h"

#ifdef EZ_Debug
#include "TraceCounter.h"
#endif

/* The following macro definitions may be used to select the speed
 of the physical link:

 _10MBIT_   - connect at 10 MBit only
 _100MBIT_  - connect at 100 MBit only

 By default an autonegotiation of the link speed is used. This may take
 longer to connect, but it works for 10MBit and 100MBit physical links.     */

/* Net_Config.c */
extern U8 own_hw_adr[];
extern OS_TID t_tcpTask;
extern OS_TID t_eth_rcv;

/* Local variables */

/* EMAC local DMA Descriptors. */
static RX_Desc Rx_Desc[NUM_RX_FRAG];
static __align(8) RX_Stat Rx_Stat[NUM_RX_FRAG]; /* Must be 8-Byte alligned   */
static TX_Desc Tx_Desc[NUM_TX_FRAG];
static TX_Stat Tx_Stat[NUM_TX_FRAG];

/* EMAC local DMA buffers. */
static U32 rx_buf[NUM_RX_FRAG][ETH_FRAG_SIZE >> 2];
static U32 tx_buf[NUM_TX_FRAG][ETH_FRAG_SIZE >> 2];

/*----------------------------------------------------------------------------
 *      EMAC Ethernet Driver Functions
 *----------------------------------------------------------------------------
 *  Required functions for Ethernet driver module:
 *  a. Polling mode: - void init_ethernet ()
 *                   - void send_frame (LAYER2FRAME *frame)
 *                   - void poll_ethernet (void)
 *  b. Interrupt mode: - void init_ethernet ()
 *                     - void send_frame (LAYER2FRAME *frame)
 *                     - void int_enable_eth ()
 *                     - void int_disable_eth ()
 *                     - interrupt function 
 *---------------------------------------------------------------------------*/

/* Local Function Prototypes */
static void rx_descr_init(void);
static void tx_descr_init(void);
static void write_PHY(U32 PhyReg, U16 Value);
static U16 read_PHY(U32 PhyReg);

/*--------------------------- init_ethernet ---------------------------------*/

void init_ethernet(void) {
	/* Initialize the EMAC ethernet controller. */
	U32 regv, tout,id1,id2;

	/* Enable PIN MUX for Ethernet. */
	MACCLK_CTRL = 0x001F; //bit4~3 11 RMII connect
	MAC_MCFG = 0x001C;

	/* Reset all EMAC internal modules. */
	MAC_MAC1 = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX | MAC1_RES_MCS_RX |
	MAC1_SIM_RES | MAC1_SOFT_RES;
	MAC_COMMAND = CR_REG_RES | CR_TX_RES | CR_RX_RES;

	/* A short delay after reset. */
	for (tout = 100; tout; tout--)
		;

	/* Initialize MAC control registers. */
	MAC_MAC1 = MAC1_PASS_ALL;
	MAC_MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
	MAC_MAXF = ETH_MAX_FLEN;
	MAC_CLRT = CLRT_DEF;
	MAC_IPGR = IPGR_DEF;

	/* Enable Reduced MII interface. */
	MAC_COMMAND = CR_RMII | CR_PASS_RUNT_FRM;

	/* Reset Reduced MII Logic. */
	MAC_SUPP = SUPP_RES_RMII;
	for (tout = 100; tout; tout--)
		;
	MAC_SUPP = 0;

	/* Put the LAN8700 in reset mode */
	write_PHY(PHY_REG_BCR, 0x8000);

	/* Wait for hardware reset to end. */
	for (tout = 0; tout < 0x100000; tout++) {
		regv = read_PHY(PHY_REG_BCR);
		if (!(regv & 0x8000)) {
			/* Reset complete */
			break;
		}
	}

   /* Check if this is a IP101A PHY. */
   id1 = read_PHY (PHY_REG_PID1);
   id2 = read_PHY (PHY_REG_PID2);

	if (((id1 << 16) | (id2 & 0xFFF0)) == LAN8700_ID) {
		/* Use autonegotiation about the link speed. */
		write_PHY(PHY_REG_BCR, PHY_AUTO_NEG);
		/* Wait to complete Auto_Negotiation. */
		for (tout = 0; tout < 0x100000; tout++) {
			regv = read_PHY(PHY_REG_BSR);
			if (regv & 0x0020) {
				/* Autonegotiation Complete. */
				break;
			}
		}
	}

//   /* Check the link status. */
//   for (tout = 0; tout < 0x10000; tout++) {
//     regv = read_PHY (PHY_REG_BSR);
//     if (regv & 0x0004) {
//       /* Link is on. */
//       break;
//     }
//   }

	/* Configure Full/Half Duplex mode. */
	regv = read_PHY (PHY_REG_BCR);
	if (regv & (1<<8)) {
		/* Full duplex is enabled. */
		MAC_MAC2 |= MAC2_FULL_DUP;
		MAC_COMMAND |= CR_FULL_DUP;
		MAC_IPGT = IPGT_FULL_DUP;
	} else {
		/* Half duplex mode. */
		MAC_IPGT = IPGT_HALF_DUP;
	}

	/* Configure 100MBit/10MBit mode. */
	if (regv & (1<<13)) {
		/* 100MBit mode. */
		MAC_SUPP = SUPP_SPEED;
	} else {
		/* 10MBit mode. */
		MAC_SUPP = 0;
	}

	/* Set the Ethernet MAC Address registers */
	MAC_SA0 = ((U32) own_hw_adr[5] << 8) | (U32) own_hw_adr[4];
	MAC_SA1 = ((U32) own_hw_adr[3] << 8) | (U32) own_hw_adr[2];
	MAC_SA2 = ((U32) own_hw_adr[1] << 8) | (U32) own_hw_adr[0];

	/* Initialize Tx and Rx DMA Descriptors */
	rx_descr_init();
	tx_descr_init();

	/* Receive Broadcast, Multicast and Perfect Match Packets */
	MAC_RXFILTERCTRL = RFC_BCAST_EN | RFC_UCAST_EN; //RFC_MCAST_EN | RFC_BCAST_EN | RFC_PERFECT_EN;

	/* Enable EMAC interrupts. */
	MAC_INTENABLE = INT_RX_DONE | INT_TX_DONE;

	/* Reset all interrupts */
	MAC_INTCLEAR = 0xFFFF;

	/* Enable receive and transmit mode of MAC Ethernet core */
	MAC_COMMAND |= (CR_RX_EN | CR_TX_EN);
	MAC_MAC1 |= MAC1_REC_EN;

	/* Configure MIC for EMAC interrupt. */
	MIC_APR |= (1 << 29);
	MIC_ATR &= ~(1 << 29);
	MIC_ITR &= ~(1 << 29);
}

/*--------------------------- int_enable_eth --------------------------------*/
void int_enable_eth_real(void) {
	/* Ethernet Interrupt Enable function. */
	MIC_ER |= (1 << 29);
}

void int_enable_eth(void) {
//  /* Ethernet Interrupt Enable function. */
//  MIC_ER |=  (1 << 29);
	int_enable_eth_real();
	Dcc_interrupt_enable();

}

/*--------------------------- int_disable_eth -------------------------------*/

void int_disable_eth_real(void) {
	/* Ethernet Interrupt Disable function. */
	MIC_ER &= ~(1 << 29);
}
void int_disable_eth(void) {
//  /* Ethernet Interrupt Disable function. */
//  MIC_ER &= ~(1 << 29);
	int_disable_eth_real();
	Dcc_interrupt_disable();

}

extern void SendFrameBySwitch(LAYER2FRAME* frame);
/*--------------------------- send_frame ------------------------------------*/

void send_frame(OS_FRAME *f) {
	U32 len;
	U32 *sp, *dp;

	LAYER2FRAME* frame = alloc_Eth_mem(f->length);
	sp = (U32 *) &f->data[0];
	dp = (U32 *) frame->frame;

	/* Copy frame data to EMAC packet buffers. */
	for (len = (frame->length + 3) >> 2; len; len--) {
		*dp++ = *sp++;
	}
	SendFrameBySwitch(frame);
	free_Eth_mem(frame);
}

//void SendFrameDirect(LAYER2FRAME* frame) {
//	  /* Send frame to EMAC ethernet controller */
//	  U32 idx,len;
//	  U32 *sp,*dp;
//
//	  idx = MAC_TXPRODUCEINDEX;
//	  sp  = (U32 *)frame->frame;
//	  dp  = (U32 *)Tx_Desc[idx].Packet;
//
//	  /* Copy frame data to EMAC packet buffers. */
//	  for (len = (frame->length + 3) >> 2; len; len--) {
//	    *dp++ = *sp++;
//	  }
//	  Tx_Desc[idx].Ctrl = (frame->length-1) | (TCTRL_INT | TCTRL_LAST);
//
//	  /* Start frame transmission. */
//	  if (++idx == NUM_TX_FRAG) idx = 0;
//	  MAC_TXPRODUCEINDEX = idx;
//}

void SendPacketDirect(U8* pkt, U32 pktlen) {
	U32 idx, len;
	U32 *sp, *dp;
	idx = MAC_TXPRODUCEINDEX;
	sp = (U32 *) pkt;
	dp = (U32 *) Tx_Desc[idx].Packet;

	/* Copy frame data to EMAC packet buffers. */
	for (len = (pktlen + 3) >> 2; len; len--) {
		*dp++ = *sp++;
	}
	Tx_Desc[idx].Ctrl = (pktlen - 1) | (TCTRL_INT | TCTRL_LAST);

	/* Start frame transmission. */
	if (++idx == NUM_TX_FRAG)
		idx = 0;
	MAC_TXPRODUCEINDEX = idx;
}

/*--------------------------- interrupt_ethernet ----------------------------*/
extern void insertEthList(LAYER2FRAME* frame);

void interrupt_ethernet(void)
__irq {
	/* EMAC Ethernet Controller Interrupt function. */
	LAYER2FRAME *frame;
	U32 idx,int_stat,RxLen,info;
	U32 *sp,*dp;
	U8* p;
	U8 flagRcv = 0;
	U16 frameType = 0;

#ifdef EZ_Debug
	eth_trace.interrupt++;
#endif

	while ((int_stat = (MAC_INTSTATUS & MAC_INTENABLE)) != 0) {
		MAC_INTCLEAR = int_stat;
		if (int_stat & INT_RX_DONE) {
			/* Packet received, check if packet is valid. */
			idx = MAC_RXCONSUMEINDEX;
			while (idx != MAC_RXPRODUCEINDEX) {
				info = Rx_Stat[idx].Info;
				if (!(info & RINFO_LAST_FLAG)) {
					goto rel;
				}

				RxLen = (info & RINFO_SIZE) - 3;
				if ( (RxLen > DEF_DCN_MTU) || (info & RINFO_ERR_MASK)) {
					/* Invalid frame, ignore it and free buffer. */
					goto rel;
				}

#ifdef EZ_Debug
				eth_trace.rcv++; //////////////////////////////////////////
#endif
				p = (U8 *)Rx_Desc[idx].Packet;
				frameType = ((p[12] << 8) | p[13]);
				if( frameType != 0x0800 && frameType != 0x0806) {
					goto rel;
				}
				/* Flag 0x80000000 to skip sys_error() call when out of memory. */
				frame = alloc_Eth_mem (RxLen);
				/* if 'alloc_mem()' has failed, ignore this packet. */
				if (frame != NULL) {
					dp = (U32 *)frame->frame;
					sp = (U32 *)Rx_Desc[idx].Packet;
					for (RxLen = (RxLen + 3) >> 2; RxLen; RxLen--) {
						*dp++ = *sp++;
					}
					insertEthList(frame);
					flagRcv = 1;
#ifdef EZ_Debug
					eth_trace.rcv_valid++; //////////////////////////////////////////
#endif
				}
				else {

				}
				rel: if (++idx == NUM_RX_FRAG) idx = 0;
				/* Release frame from EMAC buffer. */
				MAC_RXCONSUMEINDEX = idx;
			}
		}
		if (int_stat & INT_TX_DONE) {
			/* Frame transmit completed. */
		}
	}
	if( flagRcv ) {
		isr_evt_set(0x0001, t_eth_rcv);
	}
}

/*--------------------------- rx_descr_init ---------------------------------*/

static void rx_descr_init(void) {
	/* Initialize Receive Descriptor and Status array. */
	U32 i;

	for (i = 0; i < NUM_RX_FRAG; i++) {
		Rx_Desc[i].Packet = (U32) & rx_buf[i];
		Rx_Desc[i].Ctrl = RCTRL_INT | (ETH_FRAG_SIZE - 1);
		Rx_Stat[i].Info = 0;
		Rx_Stat[i].HashCRC = 0;
	}

	/* Set EMAC Receive Descriptor Registers. */
	MAC_RXDESCRIPTOR = (U32) & Rx_Desc[0];
	MAC_RXSTATUS = (U32) & Rx_Stat[0];
	MAC_RXDESCRIPTORNUM = NUM_RX_FRAG - 1;

	/* Rx Descriptors Point to 0 */
	MAC_RXCONSUMEINDEX = 0;
}

/*--------------------------- tx_descr_init ---- ----------------------------*/

static void tx_descr_init(void) {
	/* Initialize Transmit Descriptor and Status array. */
	U32 i;

	for (i = 0; i < NUM_TX_FRAG; i++) {
		Tx_Desc[i].Packet = (U32) & tx_buf[i];
		Tx_Desc[i].Ctrl = 0;
		Tx_Stat[i].Info = 0;
	}

	/* Set EMAC Transmit Descriptor Registers. */
	MAC_TXDESCRIPTOR = (U32) & Tx_Desc[0];
	MAC_TXSTATUS = (U32) & Tx_Stat[0];
	MAC_TXDESCRIPTORNUM = NUM_TX_FRAG - 1;

	/* Tx Descriptors Point to 0 */
	MAC_TXPRODUCEINDEX = 0;
}

/*--------------------------- write_PHY -------------------------------------*/
static void writePhy(uint16 phyadd, int PhyReg, int Value) {
	unsigned int tout;

	MAC_MADR = (phyadd << 8) | PhyReg;
	MAC_MWTD = Value;

	/* Wait utill operation completed */
	tout = 0;
	for (tout = 0; tout < 50000; tout++) {
		if ((MAC_MIND & 1) == 0) {
			break;
		}
	}

}
static void write_PHY(U32 PhyReg, U16 Value) {
	writePhy(9, PhyReg, Value);
}

/*--------------------------- read_PHY --------------------------------------*/
static U16 readPhy(uint16 phyadd, int PhyReg) {
	unsigned int tout;

	MAC_MADR = (uint32)((phyadd << 8) | PhyReg);
	MAC_MCMD = 1;

	/* Wait until operation completed */
	for (tout = 0; tout < 500000; tout++) {
		if ((MAC_MIND & 1) == 0) {
			break;
		}
	}
	MAC_MCMD = 0;
	return ((uint16) MAC_MRDD);

}
static U16 read_PHY(U32 PhyReg) {
	return readPhy(9, PhyReg);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
