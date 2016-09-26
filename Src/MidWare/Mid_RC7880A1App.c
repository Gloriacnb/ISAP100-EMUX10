/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			RC7880A1App.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/RC7880A1App.c
** Created by:          Administrator
** Created date:        2012-11-23
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

#include "Mid_RC7880A1App.h"
#include "rc7880RegDriverFuncLib.h"
#include "EZ_types.h"
#include <rtl.h>
//#include "Mid_flashData.h"

BYTE	gVc4OhJ0Send[2] = {0};
BYTE	gVc4OhJ0Expect[2] = {0};
BYTE	gVc4OhJ1Send[2] = {0};
BYTE	gVc4OhJ1Expect[2] = {0};

uint32 SetClockMode(uint8 mode);

static int GlbRc7880Mode = 0;

/*
 * 设置7880A1为初始的已知状态
 * 1. 24路E1都为自动保护
 * 2. 配置全局ADM工作参数
 * 3. 为光DCC通道选择开销,为DCN通道选择开销
 * 4. 所有VC12 bypass，所有E1 无mapping。
 * mode = 1 ADM; mode = 2 TM
 */
void InitRc7880A1(uint8 mode) {
	enum {
		D1 = 0x02, D2, D3,
		D4 = 0x09, D5 = 0x0C, D6 = 0x0f,
		D7 = 0x12, D8 = 0x15, D9 = 0x18,
		D10 = 0x1B, D11, D12,
		SO8MBase = 0x40,
		Boffset = 0x20
	};
	uint8 SO8M[] = {D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12};

	int i = 0;
	uint8 e1ID = 0;
	uint8 vc12ID = 0;
	for( e1ID = 0; e1ID < MAX_E1_Number; e1ID++ ) {
		if( mode == 2 ) { //TM 下，默认使能所有VC12的SNCP功能
			RC7880Tu12UnitProtectModeWrite(e1ID, AUTO_PROTECT);
		}

		/*
		 * delete all default mapping
		 */
		RC7880Tu12UnitTsSelectWrite(e1ID, mapping_Idle);

		/*
		 * INIT V5 "010"
		 */
		RC7880Tu12UnitV5SendWrite(e1ID, 0x04);
		RC7880Tu12V5ExpectWrite(e1ID, 0x04);
	}

	/* F1 connect OH-DXC; DCC from OH-DXC;
	 * STB_C/D open
	 * working in ADM
	 */
	writeRc7880RegByte( RC7880REG_GLOBAL_CONFIG, 0x04 );


	/*
	 * 配置DCC通道为标准DCC，使用D1~D12传送HDLC，双光口DCC使能
	 */
	//rc7880ManageDccOhCommFunc(0, 5);
	for( i = 0; i < sizeof(SO8M); i++ ) {
		RC7880OHUnitOtherDxcWrite( SO8M[i], SO8M[i], SO8MBase+i);
		RC7880OHUnitOtherDxcWrite( SO8MBase+i, SO8MBase+i, SO8M[i] );

		RC7880OHUnitOtherDxcWrite( SO8M[i]+Boffset, SO8M[i]+Boffset, SO8MBase+i+Boffset);
		RC7880OHUnitOtherDxcWrite( SO8MBase+i+Boffset, SO8MBase+i+Boffset, SO8M[i]+Boffset );
	}

	for (i = 0; i < 2; ++i) {
		RC7880XE1UnitXE1ConfigWrite(i, XE1_OUT); //设置23组E1连接XE1，且向E1管脚方向连接

	}
	RC7880OHUnitOtherDxcWrite(0x40 + 12, 0x40 + 23, 0x81);//xe1-1(1~12) ---> SO8MA(12~23)
	RC7880OHUnitOtherDxcWrite(0x81, 0x81 + 11, 0x40+12);  //SO8MA(12~23)---> xe1-1(1~12)

	RC7880OHUnitOtherDxcWrite(0x60 + 12, 0x60 + 23, 0xA1);//xe1-2(1~12) ---> SO8MB(12~23)
	RC7880OHUnitOtherDxcWrite(0xA1, 0xA1 + 11, 0x60+12);  //SO8MB(12~23)---> xe1-2(1~12)
	/*
	 * SET all vc12 bypass
	 */
	for( vc12ID = 0; vc12ID < MAX_VC12_Number; vc12ID++ ) {
		RC7880Vc4UnitDxcConfigWrite(vc12ID, direct_AB);
	}

	/*
	 * set j0 16bytes mode
	 */
	writeRc7880RegByte( 0x0441, 0x01);
	writeRc7880RegByte( 0x0641, 0x01);
	os_mut_init(mut_7880);


}

/*
 * mode = 1 ADM; mode = 2 TM
 */
uint32 open_rc7880a1(uint8 mode) {
	uint16 chipID = 0;
	uint8 trycnt = 3;

	GlbRc7880Mode = mode;
	while( trycnt-- ) {
		RC7880GlobalUnitChipInfoRead(&chipID, 0);
		if( chipID != CHIP_RC7880A1_ID ) {
			continue;
		}
		else {
			InitRc7880A1(mode);
			return TRUE;
		}
	
	}
	return FALSE;
}

/*
 * 设置STM口时钟模式
 * 		mode = 0 主时钟
 * 		mode != 0 恢复时钟
 */
uint32 SetClockMode(CLOCK_SOURCE_OP_E mode) {

	RC7880SecUnitT0SourceWrite(0, mode);
	return TRUE;
}

uint8 GetClockMode(void) {
	uint8 src;
	RC7880SecUnitT0SourceRead(&src);
	return src;
}


uint32 do_vc4_alarm(uint8 vc4ID) {
			    //|bit7 |bit6 |bit5 |bit4 |bit3 |bit2  |bit1 |bit0 |
	uint8 alm1;	//|los  |lof  |lom  |aulop|rstim|hpuneq|hptim|hpplm|
	uint8 alm2; //|msexc|msdeg|hpexc|hpdeg|-    |-     |-    |-    |
	uint8 alm3; //|msais|auais|hpais|hprdi|msrdi|-     |-    |-    |
	RC7880DrvVC4UnitAlarmRead(vc4ID, &alm1, &alm2, &alm3);
	if( alm1 & 0x80 ) {
		return FALSE;
	}
//	return ((alm1 & 0x40) | (alm3 & 0xC0)) != 0;
	return (alm3 & 0x08) != 0;
}

int opt_is_los(uint8 vc4ID) {
	uint8 alm1;	//los,lof,lom,aulop,rstim,hpuneq,hptim hpplm
	uint8 alm2; //msexc,msdeg,hpexc,hpdeg,-,-,-,-
	uint8 alm3; //msais,auais,hpais,hprdi,msrdi,-,-,-
	RC7880DrvVC4UnitAlarmRead(vc4ID, &alm1, &alm2, &alm3);
	if( (alm1 & 0x80) == 0 ) {
		return 0;
	}
	return 1;
}
// uint32 do_E1_alm(uint8 e1ID) {
// 	uint8 e1los;
// 	uint8 stbais;
// 	uint8 temp;
// 	RC7880DrvTU12UnitAlarmRead(e1ID, &e1los, &stbais, &temp);
// 	return ((e1los & 0x80) | (stbais & 0x80)) != 0;
// }

uint32 do_E1_alm_wrk(uint8 slot, uint8 e1ID) {
	uint8 e1los;
	uint8 stbais;
	uint8 temp;
	RC7880DrvTU12UnitAlarmRead(slot*4+e1ID, &e1los, &stbais, &temp);
	return (e1los & 0x80) == 0;
}
uint32 do_E1_alm_ais(uint8 slot, uint8 e1ID) {
	return FALSE;
// 	uint8 e1los;
// 	uint8 stbais;
// 	uint8 temp;
// 	uint8 alm1;	//los,lof,lom,aulop,rstim,hpuneq,hptim hpplm
// 	uint8 alm2; //msexc,msdeg,hpexc,hpdeg,-,-,-,-
// 	uint8 alm3; //msais,auais,hpais,hprdi,msrdi,-,-,-
// 	RC7880DrvVC4UnitAlarmRead(0, &alm1, &alm2, &alm3);
// 	if( alm1 & 0x80 ) {
// 		RC7880DrvVC4UnitAlarmRead(1, &alm1, &alm2, &alm3);
// 		if( alm1 & 0x80 ) {
// 			return FALSE;
// 		}
// 		else {
// 			RC7880DrvTU12UnitAlarmRead(slot*4+e1ID, &e1los, &stbais, &temp);
// 			return (temp & 0x80) != 0;
// 		}
// 	}
// 	else {
// 		RC7880DrvTU12UnitAlarmRead(slot*4+e1ID, &e1los, &stbais, &temp);
// 		return (stbais & 0x80) != 0;
// 	}

}

void OpticalTXOff(uint8 vc4, uint8 en) {
	RC7880GlobalUnitAlsCov(vc4, en);
}

void OpticalAlsEnable(uint8 vc4, uint8 en) {
	RC7880GlobalUnitAutoAlsEnableWrite(vc4, en);
}

void OpticalAlsMode( uint8 mode) {
	RC7880GlobalUnitAlsModeWrite(mode);

}


uint8 Rc7880_ReadReg(uint32 regaddr) {
	uint32 realaddr = regaddr + External_IO_Base;
	return *((uint8*)realaddr);
}
void Rc7880_WriteReg(uint32 regaddr, uint8 newdata) {
	writeRc7880RegByte(regaddr, newdata);
}
