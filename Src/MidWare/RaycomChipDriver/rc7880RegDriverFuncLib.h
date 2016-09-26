#ifndef  _RC7880REGDRIVERFUNCLIB_H_
#define   _RC7880REGDRIVERFUNCLIB_H_

#ifdef __cplusplus
extern "C"{
#endif 

#include <rtl.h>

/***************RC7880 REG DEFINE****************************************/

#define		RC7880_ADDR		0x00000000
/*******GLOBALE Module**********/
#define	RC7880REG_GLOBAL_CHIPID1			0x0000
#define	RC7880REG_GLOBAL_CHIPID2			0x0001
#define	RC7880REG_GLOBAL_CHIPVERSION	0x0002
#define	RC7880REG_GLOBAL_RPD				0x0005
#define	RC7880REG_GLOBAL_WRITELOCK		0x000F
#define	RC7880REG_GLOBAL_ALS				0x0012
#define	RC7880REG_GLOBAL_RPDENABLE		0x0013
#define	RC7880REG_GLOBAL_CONFIG			0x0014
#define	RC7880REG_GLOBAL_CONFIG2					0x0015
#define	RC7880REG_GLOBAL_INPUT0			0x0008
#define	RC7880REG_GLOBAL_INPUT1			0x0009
#define	RC7880REG_GLOBAL_OUTPUT0		0x000B
#define	RC7880REG_GLOBAL_OUTPUT1		0x000C
/*******EOW Module********/
#define	RC7880REG_EOW_ADDR				0x0300
#define	RC7880REG_EOW_XE1ALARM			0x0302
#define	RC7880REG_EOW_int			0x0304
#define	RC7880REG_EOW_RESET				0x0311
#define	RC7880REG_EOW_TONE				0x0312
#define	RC7880REG_EOW_HDLCEN			0x0314
#define	RC7880REG_EOW_USERCHANNEL		0x0315

/******OH DXC Module*****/
#define	RC7880REG_OHDXC_BASE				0x0200
/*EOW*/
#define	RC7880REG_E1_STM8M0A				0x00
#define	RC7880REG_E1_STM8M0B				0x20
#define	RC7880REG_TS5_SXE11					0x85
#define	RC7880REG_TS5_SXE12					0xA5
#define	RC7880REG_EOW_OH					0xC0

#define	RC7880REG_R2_STM8M0A				0x08
#define	RC7880REG_D4_STM8M0A				0x09
#define	RC7880REG_V1_STM8M0A				0x0A
#define	RC7880REG_V2_STM8M0A				0x0B
#define	RC7880REG_V3_STM8M0A				0x0D
#define	RC7880REG_V4_STM8M0A				0x0E
#define	RC7880REG_D4_STM8M0B				0x29
/*DCC*/
#define	RC7880REG_DCC1_ST2M0				0xC2
#define	RC7880REG_DCC2_ST2M0				0xC3
#define	RC7880REG_DCC3_ST2M0				0xC4
#define	RC7880REG_F1_ST2M0					0xC1

#define	RC7880REG_F1_STM8M0A				0x01
#define	RC7880REG_D1_STM8M0A				0x02
#define	RC7880REG_D2_STM8M0A				0x03
#define	RC7880REG_D3_STM8M0A				0x04
#define	RC7880REG_F2_STM8M0A				0x05
#define	RC7880REG_V5_STM8M0A				0x10
#define	RC7880REG_V6_STM8M0A				0x11
#define	RC7880REG_V7_STM8M0A				0x13
#define	RC7880REG_V8_STM8M0A				0x14
#define	RC7880REG_V9_STM8M0A				0x16

#define	RC7880REG_E2_STM8M0A				0x1F

#define	RC7880REG_TS1_SXE11				0x81
#define	RC7880REG_TS2_SXE11				0x82
#define	RC7880REG_TS3_SXE11				0x83
#define	RC7880REG_TS4_SXE11				0x84

#define	RC7880REG_TS1_SXE12				0xA1
#define	RC7880REG_TS2_SXE12				0xA2
#define	RC7880REG_TS3_SXE12				0xA3
#define	RC7880REG_TS4_SXE12				0xA4



#define	RC7880REG_F1_STM8M0B				0x21
#define	RC7880REG_D1_STM8M0B				0x22
#define	RC7880REG_D2_STM8M0B				0x23
#define	RC7880REG_D3_STM8M0B				0x24
#define	RC7880REG_F2_STM8M0B				0x25
#define	RC7880REG_R2_STM8M0B				0x28
#define	RC7880REG_V1_STM8M0B				0x2A
#define	RC7880REG_V2_STM8M0B				0x2B
#define	RC7880REG_V3_STM8M0B				0x2D
#define	RC7880REG_V4_STM8M0B				0x2E
#define	RC7880REG_V5_STM8M0B				0x30
#define	RC7880REG_V6_STM8M0B				0x31
#define	RC7880REG_V7_STM8M0B				0x33
#define	RC7880REG_V8_STM8M0B				0x34
#define	RC7880REG_V9_STM8M0B				0x36
#define	RC7880REG_E2_STM8M0B				0x3F


#define	RC7880REG_D6_STM8M0A				0x0F
#define	RC7880REG_D7_STM8M0A				0x12
#define	RC7880REG_D8_STM8M0A				0x15
#define	RC7880REG_D5_STM8M0A				0x0C

#define	RC7880REG_D6_STM8M0B				0x2F
#define	RC7880REG_D7_STM8M0B				0x32
#define	RC7880REG_D8_STM8M0B				0x35
#define	RC7880REG_D5_STM8M0B				0x2C


#define	RC7880REG_F2_ST8M1B				0x65
#define	RC7880REG_E2_ST8M1B				0x7F

#define	RC7880REG_F2_ST8M1A				0x45
#define	RC7880REG_D12_ST8M1A				0x4D
#define	RC7880REG_S1_ST8M1A				0x4E
#define	RC7880REG_E2_ST8M1A				0x5F

#define	RC7880REG_END_STM21				0xFF

/***  Line Interface Module ***/
#define		RC7880REG_LPORT_LOOP			0x012B
#define		RC7880REG_LPORTA_BASEADDR	0x0400
#define		RC7880REG_LPORTB_BASEADDR	0x0600
#define		RC7880REG_LPORT_BASEADDR(vc4Id)		(RC7880REG_LPORTA_BASEADDR + (vc4Id) * 0x0200)
#define 	RC7880REG_APS_UP_BASEADDR		0x06B0
#define 	RC7880REG_APS_DOWN_BASEADDR		0x06F0

/*VC4POH*/


/*alarm*/
#define		RC7880REG_ALARM_IA0			0xA0
#define		RC7880REG_ALARM_IA1			0xA1
#define		RC7880REG_ALARM_IA2			0xA2
#define		RC7880REG_ALARM_IA3			0xA3

/*alarm protect*/
#define		RC7880REG_ALMPROTECT_MS		0x40
#define		RC7880REG_ALMPROTECT_HP		0x68
#define		RC7880REG_ALMHPRDI_SEND		0x69
/*over head*/
#define		RC7880REG_J0_SEND				0x0B
#define		RC7880REG_OH_SRC				0x0A
#define		RC7880REG_NEWJ0_SEND			0x0530
#define		RC7880REG_K1_SEND				0x0C
#define		RC7880REG_K2_SEND				0x0D
#define		RC7880REG_S1_SEND				0x0E
#define		RC7880REG_X1_SEND				0x0F
#define		RC7880REG_X2_SEND				0x10
#define 	RC7880REG_AU4AIS_BUS_TYPE		0x20
#define		RC7880REG_J1_SEND				0x21
#define		RC7880REG_C2_SEND				0x31
#define		RC7880REG_K3_SEND				0x33
#define		RC7880REG_N1_SEND			0x34
#define		RC7880REG_J0_MODE				0x41
#define		RC7880REG_J0_EXCEPT			0x49
#define		RC7880REG_NEWJ0_EXCEPT		0x0540
#define		RC7880REG_C2_EXCEPT			0x71
#define		RC7880REG_J1_EXCEPT			0x72
#define		RC7880REG_J0_RCV				0x4A
#define		RC7880REG_K1_RCV				0x4B
#define		RC7880REG_K2_RCV				0x4C
#define		RC7880REG_S1_RCV				0x4D
#define		RC7880REG_X1_RCV				0x4E
#define		RC7880REG_X2_RCV				0x4F
#define		RC7880REG_J1_RCV				0x82
#define		RC7880REG_C2_RCV				0x92
#define		RC7880REG_K3_RCV				0x94
#define		RC7880REG_N1_RCV				0x95
#define		RC7880REG_POH_ALM			0x96
#define		RC7880REG_NEWJ0_RCV			0x0550
#define		RC7880REG_OVERHEAD_CFG		0x67

/*dxc*/
#define		RC7880REG_DXC_ADD_TU121		0x04B0
#define		RC7880REG_DXC_ADD_TU12(tu12Id)	(RC7880REG_DXC_ADD_TU121 + tu12Id)

/*perform*/
#define		RC7880REG_PERFORM_B1H		0x5D
#define		RC7880REG_PERFORM_B1L		0x5E
#define		RC7880REG_PERFORM_B2H		0x5F
#define		RC7880REG_PERFORM_B2L		0x60
#define		RC7880REG_PERFORM_M1H		0x61
#define		RC7880REG_PERFORM_M1L		0x62
#define		RC7880REG_PERFORM_PJE		0x97
#define		RC7880REG_PERFORM_NJE		0x98
#define		RC7880REG_PERFORM_B3H		0x9A
#define		RC7880REG_PERFORM_B3L		0x9B
#define		RC7880REG_PERFORM_G1H		0x9C
#define		RC7880REG_PERFORM_G1L		0x9D
/*Bus type*/
#define		RC7880REG_BUS_TYPE			0x0401
/*UNEQ*/
#define		RC7880REG_UNEQ_BASEADDR		0x38
#define		RC7880REG_UNEQ_ENDADDR		0x3F

/***  TU12  Module  *********/
#define		RC7880REG_TU12_BASEADDR		0x1000
#define		RC7880REG_ALMPROTECT_LP		0x1F85
#define		RC7880REG_TU12REG_BASEADDR(tu12Id)		(RC7880REG_TU12_BASEADDR + tu12Id * 0x80)
/*DXC*/
#define		RC7880REG_TS_PROTECT			0x00
#define		RC7880REG_RC7880E1_CONFIG	0x01
#define		RC7880REG_TS_SELECT			0x03
/*ALARM*/
#define		RC7880REG_ALARM_E1PORT		0x02
#define		RC7880REG_LPRDI_ENABLE		0x08
#define		RC7880REG_ALARM_DROPA		0x42
#define		RC7880REG_ALARM_BUSAV5EXPECT	0x44
#define		RC7880REG_ALARM_DROPB		0x62
#define		RC7880REG_ALARM_BUSBV5EXPECT	0x64
/*PERFORM*/
#define		RC7880REG_PERFORM_BIP2L_A	0x40
#define		RC7880REG_PERFORM_BIP2L(drop)	(RC7880REG_PERFORM_BIP2L_A + 0x20 * drop)
#define		RC7880REG_PERFORM_BIP2H_REIH_A	0x45
#define		RC7880REG_PERFORM_BIP2H_REIH(drop)	(RC7880REG_PERFORM_BIP2H_REIH_A + 0x20 * drop)
#define		RC7880REG_PERFORM_REIL_A		0x41
#define		RC7880REG_PERFORM_REIL(drop)		(RC7880REG_PERFORM_REIL_A + 0x20 * drop)
#define		RC7880REG_PERFORM_PJE_NJE_A		0x43
#define		RC7880REG_PERFORM_PJE_NJE(drop)	(RC7880REG_PERFORM_PJE_NJE_A + 0x20 * drop)
/******SEC Module*****************/
#define		RC7880REG_SEC_DPLL1				0x0100
#define		RC7880REG_SEC_FREQH				0x0101
#define		RC7880REG_SEC_FREQL				0x0102
#define		RC7880REG_SEC_T21QL				0x0103
#define		RC7880REG_SEC_T31QL				0x0104
#define		RC7880REG_SEC_REFLOST1			0x0105
#define		RC7880REG_SEC_REFLOST2T3			0x0106
#define		RC7880REG_SEC_FREQint		0x010F
#define		RC7880REG_SEC_A_SELCET	  		0x0110
#define		RC7880REG_SEC_T2T3T4				0x0113
#define		RC7880REG_SEC_T41SRC				0x0114
#define		RC7880REG_SEC_T0SOURCE			0x0115
#define		RC7880REG_SEC_T41SSM				0x0129
#define		RC7880REG_SEC_FREQ				0x012D
#define		RC7880REG_SEC_FREQ2CTRL			0x013F
#define		RC7780REG_SEC_T21SRC				0x0FAA
/*******BER Module*****************/
#define		RC7880REG_BER_SENDCFG			0x0FA0
#define		RC7880REG_BER_RCVCFG				0x0FA1
#define		RC7880REG_BER_ALARM				0x0FA2
#define		RC7880REG_BER_LCOUNTERH			0x0FA3
#define		RC7880REG_BER_LCOUNTERL			0x0FA4
#define		RC7880REG_BER_RCOUNTERH			0x0FA5
#define		RC7880REG_BER_RCOUNTERL			0x0FA6

/************XE1******************/
#define		RC7880REG_XE1_XE11CONFIG			0x0FAC
#define		RC7880REG_XE1_XE12CONFIG			0x0FAD


/***************END  RC7880 REG DEFINE****************************************/

/***************RC7880 MANAGE INTERFACE DEFINE********************************/
#define External_IO_Base	             		(0xE3000000 + 0x6000)	/*��48M��ʼ,�����CAECH��*/
#define EXTERNAL_IO_BYTE 	             		((volatile unsigned char*) (External_IO_Base))

#define	RC7880_OK		0
#define	RC7880_ERROR	-1
#define	RC7880_NULL	NULL

#define DCCMODE_STANDARD 1


//#ifndef int
//#define	int		int
//#endif

#ifndef BYTE
#define   BYTE		unsigned char	
#endif
#ifndef WORD
#define	WORD		unsigned short	
#endif
#ifndef DWORD
#define	DWORD		unsigned long	
#endif

#ifndef NULL
#define NULL  0
#endif


typedef struct
{
	BYTE 	los ;
	BYTE	lof ;
	BYTE	lom ;
	BYTE	ms_exc ;
	BYTE	ms_ais ;
	BYTE	ms_rdi ;
	BYTE	ms_deg ;
	BYTE	au_lop ;
	BYTE	au_ais ;
	BYTE	hp_ais ;
	BYTE	hp_rdi ;
	BYTE	hp_tim ;
	BYTE	hp_exc ;
	BYTE	hp_plm ;
}Vc4UnitAlarm_t ;



typedef struct
{
	BYTE	a_tu_lop ;
	BYTE	a_tu_ais ;
	BYTE	a_tu_rdi ;
	BYTE	a_tu_slm ;
	BYTE	b_tu_lop ;
	BYTE	b_tu_ais ;
	BYTE	b_tu_rdi ;
	BYTE	b_tu_slm ;
	BYTE	tLos ;
	BYTE	tCv ;
}Tu12UnitAlarm_t ;


typedef struct
{
	BYTE   	j0 ;
	BYTE	nj0[16] ;
	BYTE   	k1 ;
	BYTE   	k2 ;
	BYTE   	s1 ;
	BYTE   	x1 ;
	BYTE   	x2 ;
	BYTE   	j1[16] ;
	BYTE   	c2 ;
	BYTE   	k3 ;
	BYTE   	n1 ;
}Vc4UnitSendOverHead_t ;

typedef struct
{
	BYTE   	j0 ;
	BYTE	nj0[16] ;
	BYTE   	k1 ;
	BYTE   	k2 ;
	BYTE   	s1 ;
	BYTE   	x1 ;
	BYTE   	x2 ;
	BYTE   	j1[16] ;
	BYTE   	c2 ;
	BYTE   	k3 ;
	BYTE   	n1 ;
}Vc4UnitOverHead_t ;

typedef struct
{
	BYTE   	j0 ;
	BYTE	nj0[16] ;
	BYTE   	j1[16] ;
	BYTE   	c2 ;
}Vc4UnitExceptOverHead_t ;


typedef struct
{
	WORD	rsB1 ;
	WORD	msB2 ;
	WORD	msRei ;
	WORD	hovcB3 ;
	WORD	hovcRei ;
	WORD	hovcPje  ;
	WORD	hovcNje  ;
}VC4UnitPerform_t ;

typedef struct
{
	WORD	dropABIP2 ;
	WORD	dropAREI ;
	WORD	dropAPJE ;
	WORD	dropANJE ;
	WORD	dropBBIP2 ;
	WORD	dropBREI ;
	WORD	dropBPJE ;
	WORD	dropBNJE ;
	WORD	cv ;
}TU12UnitPerform_t ;


/***************END RC7880 MANAGE INTERFACE DEFINE********************************/


/***************RC7880 MACRO DEFINE**********************************************/

#define	RC7880_ID				0x7880
#define	RC7883_ID				0x7883
#define	RC7880_MAXTU12		24
#define	RC7880_MAXVC4			2

#define	SSM_ENABLE		0x0F 
#define	SSM_DISABLE	0

#define	MODE_SOC				0
#define	MODE_MAPPER			1


#define	VC4ID_A		0
#define	VC4ID_B			1

#define	AUTO_PROTECT		0
#define	MANUAL_PROTECT	1
#define	DISABLE_PROTECT	2

#define	USERCHANNEL_ENABLE	1
#define	USERCHANNEL_DISABLE	0

#define	ALS_ENABLE			1
#define	ALS_DISABLE		0
#define	ALS_SHORTMODE		1
#define	ALS_LONGMODE		0

#define	TONE_ENABLE	1
#define	TONE_DISABLE	0

#define	DXC_TRANSFER	1
#define	DXC_LOCAL		2
#define	DXC_LOOP		3
#define	DXC_CLOSE		4


#define	DXCBUSID_AB		1
#define	DXCBUSID_GH		2
#define	DXCBUSID_CD		4


#define	WORK_int	0
#define	ALARM_int	1

#define	BER_DISABLE	0
#define	BER_ENABLE		1
#define	DIRECT_BUS		1
#define	DIRECT_E1		0
#define	FRAME_MODE	1
#define	UNFRAME_MODE	0

#define	E1_MAPPER		0
#define	E1_CLOCK		1
#define	XE1_IN			2
#define	XE1_OUT		3

#define	BUS_VC4	1
#define	BUS_TUG3	2
#define	BUS_TU12	3

#define	HPRDI_ENABLE	1
#define	HPRDI_DISABLE	0
#define	LPRDI_ENABLE	1
#define	LPRDI_DISABLE	0
#define	MSAIS_ENABLE	1
#define	MSAIS_DISABLE	0
#define   HPAIS_ENABLE	1
#define	HPAIS_DISABLE	0

#define	LPORTLOOP_ENABLE	1
#define	LPORTLOOP_DISABLE	0

/***************END RC7880 MACRO DEFINE******************************************/

int writeRegByte(WORD addr , BYTE data) ;
int writeRc7880RegLock(void);
int writeRc7880RegUnlock(void);
int writeRc7880RegByte(WORD addr , BYTE data);
BYTE readRc7880RegByte(WORD addr);
int RC7880GlobalUnitChipInfoRead(WORD  *chipIdP , BYTE *chipVersionP);
int RC7880DrvEOWUnitAddrRead(BYTE	*eowAddrP);
int RC7880EOWUnitAlarmToneWrite(BYTE	 enable);
int RC7880EOWUnitUserChannelEnableWrite(BYTE	enable);
int RC7880EOWUnitUserChannelEnableRead(BYTE	*enableP);
int RC7880OHUnitLoopWrite(BYTE  startAddr , BYTE  endAddr) ;
int RC7880OHUnitOtherDxcWrite(BYTE  startAddr , BYTE  endAddr , BYTE	 startSrcAddr) ;
int RC7880OHUnitDxcWrite(BYTE  *regAddrP , BYTE  *dataP	) ;
int RC7880OHUnitStandardEowDxcWrite(
									BYTE  srcEow ,
									BYTE  srcAE1 ,
									BYTE  srcXe11Ts5 ,
									BYTE  srcBE1 , 
									BYTE  srcXe12Ts5);
int RC7880OHUnitStandardD1DxcWrite(
									BYTE  srcDcc1 ,
									BYTE  srcAD1 ,
									BYTE  srcXe11Ts2 ,
									BYTE  srcBD1 ,
									BYTE  srcXe12Ts2) ;
int RC7880OHUnitStandardD2DxcWrite(
									BYTE  srcDcc2 ,
									BYTE  srcAD2 ,
									BYTE  srcXe11Ts3 ,
									BYTE  srcBD2 ,
									BYTE  srcXe12Ts3 ) ;
int RC7880OHUnitStandardD3DxcWrite(
									BYTE  srcDcc3 ,
									BYTE  srcAD3 ,
									BYTE  srcXe11Ts4 ,
									BYTE  srcBD3 , 
									BYTE  srcXe12Ts4) ;
int RC7880OHUnitStandardF1DxcWrite(
									BYTE  srcF1 ,
									BYTE  srcAF1 ,
									BYTE  srcXe11Ts1 ,
									BYTE  srcBF1 ,
									BYTE  srcXe12Ts1) ;
int RC7880OHUnitUnstandardEowDxcWrite(
									BYTE  srcEow ,
									BYTE  srcAD4 ,
									BYTE  srcXe11Ts5 ,
									BYTE  srcBD4 ,
									BYTE  srcXe12Ts5) ;
int RC7880OHUnitUnstandardD6DxcWrite(
									BYTE  srcDcc1 ,
									BYTE  srcAD6 ,
									BYTE  srcXe11Ts2 ,
									BYTE  srcBD6 ,
									BYTE  srcXe12Ts2) ;
int RC7880OHUnitUnstandardD7DxcWrite(
									BYTE  srcDcc2 ,
									BYTE  srcAD7 ,
									BYTE  srcXe11Ts3 ,
									BYTE  srcBD7 ,
									BYTE  srcXe12Ts3) ;
int RC7880OHUnitUnstandardD8DxcWrite(
									BYTE  srcDcc3 ,
									BYTE  srcAD8 ,
									BYTE  srcXe11Ts4 ,
									BYTE  srcBD8 ,
									BYTE  srcXe12Ts4) ;
int RC7880OHUnitUnstandardF1DxcWrite(
									BYTE  srcF1 ,
									BYTE  srcAD5 ,
									BYTE  srcXe11Ts1 ,
									BYTE  srcBD5 ,
									BYTE  srcXe12Ts1) ;
int RC7880OHUnitDxcSelfLoopWrite(void);
void dccUnstandardModeOhCommFunc(BYTE dccint);
void dccStandardModeOhCommFunc(BYTE dccint);
void rc7880ManageDccOhCommFunc(BYTE	dccMode , BYTE dccint);
int	RC7880DrvVC4UnitAlarmRead (BYTE	vc4Id , BYTE *iA0P , BYTE *iA1P , BYTE *iA2P) ;
int	RC7880DrvVC4UnitOOMAlarmRead(BYTE	vc4Id , BYTE *oomAlmP);
int	RC7880DrvTU12UnitAlarmRead(BYTE	tu12Id , BYTE *e1P , BYTE *dropA , BYTE *DropB);
int RC7880DrvVC4UnitLportLoopWrite(BYTE vc4Id , BYTE inLoop , BYTE outLoop);
int RC7880DrvVC4UnitJ0ModeWrite(BYTE vc4Id , BYTE j0Mode);
BYTE RC7880DrvCRC7Func(const BYTE *pSrc , DWORD cnt);
void RC7880DrvReadNewJxBytes(BYTE *jxCharP , BYTE *jxByteP , BYTE jxLen) ;
void RC7880DrvWriteNewJxBytes(BYTE *jxCharP , BYTE *jxByteP , BYTE jxLen) ;

int RC7880DrvVC4UnitJ0SendWrite16( BYTE	vc4Id ,  BYTE* nj0, BYTE	j0CrcEnable);

int RC7880DrvVC4UnitSendOverHeadWrite(
							BYTE	vc4Id , 
							Vc4UnitOverHead_t *overHeadP ,
							BYTE	j0CrcEnable ,
							BYTE	j1CrcEnable);
int RC7880DrvVC4UnitRcvOverHeadRead(
							BYTE	vc4Id , 
							Vc4UnitOverHead_t *overHeadP);
int RC7880DrvVC4UnitSendS1Write(	BYTE	vc4Id , BYTE sendS1) ;
int RC7880DrvVC4Unit16BytsJ1Read(BYTE vc4Id , BYTE *sendJ1P , BYTE	*expectJ1P , BYTE *rcvJ1P);
int RC7880DrvVC4Unit16BytsJ0Read(BYTE vc4Id , BYTE *sendJ0P , BYTE	*expectJ0P , BYTE *rcvJ0P);
int RC7880DrvVC4UnitExceptOverHeadWrite(
							BYTE	vc4Id , 
							Vc4UnitExceptOverHead_t *overHeadP ,
							BYTE	j0CrcEnable ,
							BYTE	j1CrcEnable);
int RC7880DrvVC4UnitPerformRead(
							BYTE	vc4Id , 
							VC4UnitPerform_t *performP);
int RC7880DrvTU12UnitPerformRead(
							BYTE	tu12Id , 
							TU12UnitPerform_t *performP);
int RC7880DrvEOWUnitEOWReset(BYTE	enable);
int	RC7880EowUnitHdlcTxEnableWrite(BYTE	enable);

int RC7880AU4UnitForceAUAISSendWrite(BYTE vc4Id , BYTE sendAisEnable);
int RC7880Vc4UnitForceMSAISSendWrite(BYTE vc4Id , BYTE sendAisEnable);
int RC7880Vc4UnitHpRdiSendEnableWrite(BYTE vc4Id, BYTE force, BYTE hpPlm, BYTE hpLom, BYTE hpUneq, BYTE hpTim ,
						BYTE hpAis , BYTE hpExc , BYTE hpDeg);
int	RC7880Vc4UnitMsAisWrite(BYTE vc4Id ,BYTE msExc , BYTE msDeg);
int	RC7880Vc4UnitAlmProtectWrite(BYTE vc4Id ,BYTE msExc , BYTE  msDeg , BYTE hpPlm , BYTE hpExc , BYTE hpTim , BYTE hpUneq , BYTE hpDeg , BYTE hpAis);
int	RC7880Tu12UnitAlmProtectWrite(BYTE lpPlm , BYTE lpTim , BYTE lpUneq);
int	RC7880Vc4UnitBusTypeWrite(BYTE vc4Type ,BYTE tug1Type , BYTE tug2Type , BYTE tug3Type);
int	RC7880Vc4UnitUNEQInsWrite(BYTE vc4Id , BYTE offset , BYTE	inData);
int	RC7880SecUnitT2T3T4Write(BYTE t2t3t4Cfg) ;
int	RC7880SecUnitT41SrcWrite(BYTE t41Src) ;
int	RC7880SecUnitT41SSMEnableWrite(BYTE ssmEnable) ;
int	RC7880SecUnitDPLL1intRead(BYTE *modeP);
int	RC7880SecUnitFreqintRead(WORD *freqP);
int	RC7880SecUnitT0SourceRead(BYTE *sourceP);
int	RC7880SecUnitT0SourceWrite(BYTE mode , BYTE clockSrc);
int	RC7880SecUnitFreqWrite(BYTE cfgData);
int	RC7880SecUnitT21QLRead(BYTE *qlP);
int	RC7880SecUnitT31QLRead(BYTE *qlP);
int	RC7880SecUnitT2xSSMEnableRead(BYTE t2x , BYTE *enableP);
int	RC7880SecUnitT3xSSMEnableRead(BYTE t3x , BYTE *enableP);
int	RC7880SecUnitREFLOST1xRead(BYTE t1x , BYTE *losP);
int	RC7880SecUnitREFReg1LOSRead(BYTE *losP);
int	RC7880SecUnitREFLOST2T3Read(BYTE tx , BYTE *losP);
int	RC7880SecUnitREFReg2LOSRead(BYTE *losP);
int	RC7880SecUnitFreqErrintRead(BYTE clockSrc , BYTE *freqP);
int	RC7880Vc4UnitS1RcvRead(BYTE vc4Id , BYTE *rcvS1P);
int	RC7880Vc4UnitJ1TestEnableWrite(BYTE vc4Id , BYTE enable);
int	RC7880Tu12UnitTsSelectWrite(BYTE	tu12Id , BYTE select);
int	RC7880Tu12UnitTsSelectRead(BYTE	tu12Id , BYTE *selectP);
int	RC7880Tu12UnitTsSelectintRead(BYTE	tu12Id , BYTE *intP);
int	RC7880Tu12UnitTu12LoopWrite(BYTE  tu12Id , BYTE lineLoop , BYTE devLoop);
int	RC7880Tu12UnitTu12LoopRead(BYTE  tu12Id , BYTE *lineLoopP , BYTE *e1LoopP);
int	RC7880Tu12UnitProtectModeWrite(BYTE tu12Id , BYTE protectMode /*, BYTE startFlag*/);
int	RC7880Tu12UnitBusConfigWrite(BYTE tu12Id , BYTE busId);
int	RC7880Tu12UnitWorkBusRead(BYTE tu12Id , BYTE *busIdP);
int	RC7880Tu12UnitProtectToExceptBusWrite(BYTE tu12Id , BYTE protectMode , BYTE exceptBus);
int	RC7880Tu12UnitLPRDIEnableWrite(BYTE tu12Id , BYTE lpRdiEnable);
int	RC7880EOWUnitXE1AlarmRead(BYTE	*alarmP , BYTE xE1Id);
int	RC7880GlobalUnitAutoAlsEnableWrite(BYTE	vc4Id , BYTE	enable);
int	RC7880GlobalUnitAlsModeWrite(BYTE mode);
int	RC7880GlobalUnitManualAlsWrite(BYTE	vc4Id );
int RC7880GlobalUnitAlsCov(BYTE vc4ID, BYTE enable);
int	RC7880GlobalUnitAlsintRead(BYTE	*enableAP ,  BYTE *enableBP , BYTE *modeP);
int	RC7880GlobalUnitCommnWrite(WORD addr ,  BYTE	  cfgData);
int	RC7880GlobalUnitCommnRead(WORD addr ,  BYTE	  *intP);
int	RC7880Vc4UnitDxcConfigWrite(BYTE tu12Id , BYTE upSource);
int	Rc7880GlobalUnitRpdint(BYTE *rpdAP , BYTE *rpdBP);
int	RC7880BERUnitLocalErrCounterRead(WORD  *counterP);
int	RC7880BERUnitRemoteErrCounterRead(WORD  *counterP);
int	RC7880BERUnitAlarmintRead(BYTE  *alarmP);
int	RC7880BERUnitSendConfigWrite(BYTE  enable , BYTE direct , BYTE e1Id);
int	RC7880BERUnitSendConfigRead(BYTE  *enableP , BYTE *directP , BYTE *e1IdP);
int	RC7880BERUnitRcvConfigWrite(BYTE  enable , BYTE direct , BYTE frameMode ,BYTE e1Id);
int	RC7880BERUnitRcvConfigRead(BYTE  *enableP , BYTE *directP , BYTE *frameModeP ,BYTE *e1IdP);
int	RC7880BERUnitInsertErrCodeWrite(void);
int	RC7880XE1UnitXE1ConfigWrite(BYTE  xE1Id , BYTE  cfgData);
int	RC7880SecUnitT2T3T4Read(BYTE* t2t3t4ValueP) ;
int	RC7880SecUnitT32QLRead(BYTE *qlP);
int	RC7880SecUnitT41ASelectWrite(BYTE t41Source) ;
int	RC7880SecUnitT32QLRead(BYTE *qlP);
int	RC7880SecUnitT32QLRead(BYTE *qlP);


extern int writeRegByte(WORD addr , BYTE data);
extern OS_MUT mut_7880;


int RC7880GlobalUnitPortProtectWrite(BYTE enable);

#ifdef __cplusplus
}
#endif 

#endif 	/* _RC7880REGDRIVERFUNCLIB_H_ */
