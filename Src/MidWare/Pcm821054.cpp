

#include "Pcm821054.h"
#include "FVIdt821054Access.h"
#include "IDT821054RegisterMap.h"
#include <string.h>

#define DEFMakeAB(A,B) ( ((A) << 1) | (B))
#define DEFMakeSHK12(SHK1,SHK2) DEFMakeAB(SHK1, SHK2)
#define DEFGetA(v) (((v)>>1)&1)
#define DEFGetB(v) (((v)>>0)&1)
#define DEFGetSHK1(s) DEFGetA(s)
#define DEFGetSHK2(s) DEFGetB(s)

STVoiceChannel stVC[DEF_MAX_VF_NUM] = {0};
uint32 loopCounter = 0;
#define DEFStartVc	(loopCounter & 0x1f)

extern volatile uint32 timer32_1_counter;


/* 内部功能函数声明 */
void HardReset821054(uint8 slot);					//复位所有芯片
bool ChipOnBoard(int chipID);
void InitVoiceChannelStruct(STVoiceChannel stVC[]);
void InitVoiceChannelStructChipDes(int sn, int chipID, int channelID);
extern "C"  uint8 GetVoiceChannelType(int chipID, int channelID);
void InitChannal(int chipID);				//分配时隙
uint32 SelectClock(int chipID);				//设置MCLK
uint32 SetPowerUp(int chipID);					//禁能PowerDown
uint32 SetSb123Direction(int chipID);			//设置SB1输出，SB2、SB3为输入
void SetHardwareRingTripEnable(int chipID); //使能环回功能
void openDigitalGain(int chipID);

///*
// * 通过CPLD操作信令bit
// */
//int GetSignalA(int sn);
//int GetSignalB(int sn);
//void SetSignalA( int sn, uint8 newValue );
//void SetSignalB( int sn, uint8 newValue );
//
///*
// * 通过821054处理信令
// */
//int GetSHK1(int sn);
//int GetSHK2(int sn);
//void SetRC(int sn, int newValue);
//void SetFR(int sn, int newValue);
//
///*
// * 信令处理流程实现
// */
//void FXSSignalFromCpldToPcm(int sn, int SrcSignal);
//void FXSSignalFromPcmToCpld(int sn, int SrcSignal);
//void FXOSignalFromCpldToPcm(int sn, int SrcSignal);
//void FXOSignalFromPcmToCpld(int sn, int SrcSignal);

/*
 * 以芯片为单位初始化
 * 设置MCLK为2.048M
 * SB1为输出，SB2、SB3为输入
 * 使能硬件环回
 * 去能掉电模式
 * 为所有通道分配时隙
 * 为话路通道初始化数据结构
 */
void Init821054(uint8 slot) {				  //821054初始化
	int i;
	uint8 baseCh = slot << 2;
	InitVoiceChannelStruct(stVC);		//数据结构初始化
	HardReset821054(slot);				//821054硬件复位
//	readIDTChipCoeRamBlock(spichannel, channel, block, data);
    for( i = 1; i <= 2; i++ ) {
		if( ChipOnBoard(baseCh+i) ) {
			SelectClock(baseCh+i);
			SetSb123Direction(baseCh+i);	//SetSb123Direction
			SetHardwareRingTripEnable(baseCh+i);
			SetPowerUp(baseCh+i);
			InitChannal(baseCh+i);
			openDigitalGain(baseCh+i);
		}
	}
}

//void InitCPLDRegister() {
//	while(1) {
//		int ReadValue = 0;
//		int a = ReadCPLDRegister(0x0001, &ReadValue);
//		if( (a == 0) && (ReadValue== 0x9A) ) {
//			break;
//		}
//	}
//	for( int i = 0; i < 32; i++ ) {
//		WriteCPLDRegister(DEF_REGADDR_CPLD_UP_SIGNAL+i, 0x0a);
//	}
//}

//void SignalProcess(int chNumber) {
//	for( int i = DEFStartVc; i < DEFStartVc+chNumber; i++ ) {
//		if( stVC[i].State != 0 ) { //只处理有效通道
//
//			/*先采集下行*/
//			int Abit = GetSignalA(i);
////			stVC[i].led = Abit;
//			int Bbit = GetSignalB(i);
//			int tempSignal = DEFMakeAB(Abit, Bbit);
//			if( (tempSignal != stVC[i].BakAB) || (stVC[i].mode != 0 && stVC[i].Type == DEF_VFType_FXS) ) {
////				if( Abit == 0 ) {
////					SetVFLED(i, DEF_LED_ON);
////				}
////				else {
////					SetVFLED(i, DEF_LED_OFF);
////				}
//				stVC[i].BakAB = tempSignal;
//				/* 处理下行信令*/
//				if( stVC[i].Type == DEF_VFType_FXS ) {
//					FXSSignalFromCpldToPcm(i, tempSignal);
//				}
//				else if( stVC[i].Type == DEF_VFType_FXO ) {
//					FXOSignalFromCpldToPcm(i, tempSignal);
//				}
//				else {
//					// the other type
//				}
//			}
//
//			/*再采集上行*/
//			int SHK1 = GetSHK1(i);
//			int SHK2 = GetSHK2(i);
//			tempSignal = DEFMakeSHK12(SHK1, SHK2);
//			if( tempSignal != stVC[i].BakSHK ) {
//				stVC[i].BakSHK = tempSignal;
//				/* 处理上行信令 */
//				if( stVC[i].Type == DEF_VFType_FXS ) {
//					FXSSignalFromPcmToCpld(i, tempSignal);
////					stVC[i].led &= SHK2;
////					if( SHK2 == 0 ) {
////						SetVFLED(i, DEF_LED_ON);
////					}
////					else {
////						SetVFLED(i, DEF_LED_OFF);
////					}
//				}
//				else if( stVC[i].Type == DEF_VFType_FXO ) {
//					FXOSignalFromPcmToCpld(i, tempSignal);
////					if( tempSignal != 1 ) {
////						stVC[i].led = 0;
////					}
//				}
//				else {
//					// the other type
//				}
//			}
//			int tempLED = 1;
//			tempLED &= Abit;
//			if( stVC[i].Type == DEF_VFType_FXS ) {
//				tempLED &= SHK2;
//			}
//			else if( stVC[i].Type == DEF_VFType_FXO ) {
//				tempLED &= (tempSignal == 1);
//			}
//			if( tempLED != stVC[i].led) {
//				stVC[i].led = tempLED;
//				SetVFLED(i, stVC[i].led);
//			}
//		}
//	}
//	loopCounter += chNumber;
//}



/*
 * 通过CPLD寄存器复位所有821054
 */
void HardReset821054(uint8 slot) {  //821054的硬件复位
	WriteCPLDRegister(slot,1,0);
	for(int i = 0; i < 200000 ; i++);
	WriteCPLDRegister(slot,1,1);
	for(int i = 0; i < 200000; i++);
}

/*
 * 设置为single clock  cs = 011
 */
uint32 SelectClock(int chipID) {
	if( WriteIdtChipGlbRegister(chipID, IDT_GREG_CODEC_Parameter, Bin(00011000)) < 0 ) {
		return FALSE;
	}
	return TRUE;
}

/*
 * 4路SB1用做4路话路的LED指示，设置为输出（低点灯）
 * SB2-1、SB3-1、SB2-2 用做第一个话路模块类型识别，设置为输入
 * SB2-3、SB3-3、SB2-4 用做第二个话路模块类型识别，设置为输入
 * 剩余的 SB3-2、SB3-4保留，设置为输入
 */
uint32 SetSb123Direction(int chipID) {
	if( WriteIdtChipGlbRegister(chipID, IDT_GREG_SB1_Control_Status, 0xff) < 0 ) {
		return FALSE;
	}
	if( WriteIdtChipGlbRegister(chipID, IDT_GREG_SB2_Control_Status, 0) < 0 ) {
		return FALSE;
	}
	if( WriteIdtChipGlbRegister(chipID, IDT_GREG_SB3_Control_Status, 0) < 0 ) {
		return FALSE;
	}
	return TRUE;
}

void SetHardwareRingTripEnable(int chipID) {
	int ucTemp = 0;
	if( ReadIdtChipGlbRegister(chipID, IDT_GREG_Ring_Trip, &ucTemp) < 0 ) {
		return ;
	}
	ucTemp |= (1 << 3);
	WriteIdtChipGlbRegister(chipID, IDT_GREG_Ring_Trip, ucTemp);     //1为使能 0为关闭
}

void openDigitalGain(int chipID) {
	int ucTemp = 0;
	for(int i = 0; i < 4; i++ ) {
		ucTemp = GetVoiceChannelType(chipID, i+1);
		if( ucTemp == DEF_VFType_4W || ucTemp == DEF_VFType_2W ) {
			ReadIdtChipLocRegister(chipID, i+1, 0, &ucTemp);
			ucTemp |= 0xa0;
			WriteIdtChipLocRegister(chipID, i+1, 0, ucTemp);
		}
	}
}

void InitChannal(int chipID) {
	int TransmitReceiveTSBase = 0;
	switch( chipID & 3 ) {
	case 1:
		TransmitReceiveTSBase = 1;
		break;
	case 2:
		TransmitReceiveTSBase = 17;
		break;
//	case 3:
//		TransmitReceiveTSBase = 8;
//		break;
//	case 4:
//		TransmitReceiveTSBase = 9;
//		break;
//	case 5:
//		TransmitReceiveTSBase = 16;
//		break;
//	case 6:
//		TransmitReceiveTSBase = 17;
//		break;
//	case 7:
//		TransmitReceiveTSBase = 24;
//		break;
//	case 8:
//		TransmitReceiveTSBase = 25;
//		break;
	}

	for( int i = DEF_Min_ChannelID; i <= DEF_Max_ChannelID; i++ ) {
		WriteIdtChipLocRegister(chipID, i, IDT_LREG_Transmit_Timeslot, TransmitReceiveTSBase);
		WriteIdtChipLocRegister(chipID, i, IDT_LREG_Recieve_Timeslot, TransmitReceiveTSBase);
		WriteIdtChipLocRegister(chipID, i, IDT_LREG_DSH_GK_Debounce, 0x0a); //SI1 去抖20ms
		InitVoiceChannelStructChipDes(TransmitReceiveTSBase, chipID, i);
		TransmitReceiveTSBase++;//TransmitReceiveTSBase += 2;
	}
}


uint32 SetPowerUp(int chipID) {					  //设置PD为正常模式
	for(int i = DEF_Min_ChannelID; i <= DEF_Max_ChannelID; i++ ) {
		if( WriteIdtChipLocRegister(chipID, i, IDT_LREG_Gain_Powerdown_Cutoff, 0) < 0 ) {
			return FALSE;
		}
	}
	return TRUE;	
}

bool ChipOnBoard(int chipID) {
	int VersionNumber = 0;
	if( ReadIdtChipGlbRegister(chipID, IDT_GREG_Version_Number, &VersionNumber) == 0 ) {
		if( VersionNumber == 1 ) {
			return true;
		}
	}
	return false;
}

/* 固定配置 ，运行中不需要改变 ， 所有VC一起配置 */
void InitVoiceChannelStruct(STVoiceChannel pVc[]) {
	memset(pVc, 0 , sizeof(stVC));
	for( int i = 0; i < DEF_MAX_VF_NUM; i++ ) {
		pVc[i].UpSignalAddr = DEF_REGADDR_CPLD_UP_SIGNAL + i;
		pVc[i].DownSignalAddr = DEF_REGADDR_CPLD_DOWN_SIGNAL + i;
		pVc[i].led = DEF_LED_OFF;
	}
}

/*
 * 运行时，以话路为单位检测模块类型并记录
 */
void InitVoiceChannelStructChipDes(int sn, int chipID, int channelID) {
	stVC[sn].ChipID = chipID;
	stVC[sn].ChannelID = channelID;
	stVC[sn].Type = GetVoiceChannelType(chipID, channelID);
	if( stVC[sn].Type != 0 ) {
		stVC[sn].State = 1;
	}
	stVC[sn].mode = 0;
}

uint8 GetVoiceChannelType(int chipID, int channelID) {
	if( channelID == 1 || channelID == 2 ) {
		channelID = 1;
	}
	else if( channelID == 3 || channelID == 4 ) {
		channelID = 3;
	}
	else {
		return 0;
	}
	int typeCode = 0;	//bit2--test1 bit1--test2 bit0--test3
	int tempValue = 0;
	ReadIdtChipLocRegister(chipID, channelID, IDT_LREG_Channel_IOData, &tempValue);
	typeCode |= (((tempValue>>3) & 1) << 2); //取SB2为Test1
	typeCode |= (((tempValue>>4) & 1) << 1); //取SB3为Test2
	ReadIdtChipLocRegister(chipID, channelID+1, IDT_LREG_Channel_IOData, &tempValue);
	typeCode |= (((tempValue>>3) & 1) << 0); //取SB2为Test3
	return typeCode;
}

int setPowerDown(uint8 chipID, uint8 ch, uint8 pd) {
//	if( WriteIdtChipLocRegister(chipID, ch, IDT_LREG_Gain_Powerdown_Cutoff, pd) < 0 ) {
//		return FALSE;
//	}
//	return TRUE;
	int data;
	ReadIdtChipLocRegister(chipID, ch, IDT_LREG_Gain_Powerdown_Cutoff, &data);
	data &= ~(1<<7);
	data |= pd<<7;
	return WriteIdtChipLocRegister(chipID, ch, IDT_LREG_Gain_Powerdown_Cutoff, data);
}

int setLoopBackAnalogOnebit(uint8 chipID, uint8 ch, uint8 loop) {
	int data;
	ReadIdtChipLocRegister(chipID, ch, IDT_LREG_LocalLoop_SLICInterrupt, &data);
	data &= ~(1<<1);
	data |= loop<<1;
	return WriteIdtChipLocRegister(chipID, ch, IDT_LREG_LocalLoop_SLICInterrupt, data);
}

int setLoopBackDigitalOnebit(uint8 chipID, uint8 ch, uint8 loop) {
	int data;
	ReadIdtChipLocRegister(chipID, ch, IDT_LREG_LocalLoop_SLICInterrupt, &data);
	data &= ~(1<<0);
	data |= loop<<0;
	return WriteIdtChipLocRegister(chipID, ch, IDT_LREG_LocalLoop_SLICInterrupt, data);

}

//int GetSignalA(int sn) {
//	int temp = 0;
//	ReadCPLDRegister(stVC[sn].DownSignalAddr, &temp);
//	return (temp >> 3) & 1;
//}
//int GetSignalB(int sn) {
//	int temp = 0;
//	ReadCPLDRegister(stVC[sn].DownSignalAddr, &temp);
//	return (temp >> 2) & 1;
//}
//void SetSignalA( int sn, uint8 newValue ) {
//	if( newValue > 1 ) {
//		newValue = 1;
//	}
//	int temp = 0;
//	ReadCPLDRegister(stVC[sn].UpSignalAddr, &temp);
//	temp &= ~(1<<3);
//	temp |= (newValue << 3);
//	WriteCPLDRegister(stVC[sn].UpSignalAddr, (uint8)temp);
//}
//void SetSignalB( int sn, uint8 newValue ) {
//	if( newValue > 1 ) {
//		newValue = 1;
//	}
//	int temp = 0;
//	ReadCPLDRegister(stVC[sn].UpSignalAddr, &temp);
//	temp &= ~(1<<2);
//	temp |= (newValue << 2);
//	WriteCPLDRegister(stVC[sn].UpSignalAddr, (uint8)temp);
//}
int GetSHK1(int sn) {
	int temp = 0;
	ReadIdtChipLocRegister(stVC[sn].ChipID, stVC[sn].ChannelID, IDT_LREG_Channel_IOData, &temp);
	return (temp>>0) & 1;	//si1
}
int GetSHK2(int sn) {
	int temp = 0;
	ReadIdtChipLocRegister(stVC[sn].ChipID, stVC[sn].ChannelID, IDT_LREG_Channel_IOData, &temp);
	return (temp>>1) & 1;	//si2
}
void SetRC(int sn, int newValue) {
	if( newValue > 1 ) {
		newValue = 1;
	}
	int temp = 0;
	ReadIdtChipLocRegister(stVC[sn].ChipID, stVC[sn].ChannelID, IDT_LREG_Channel_IOData, &temp);
	temp &= ~(1<<5);
	temp |= (newValue << 5);
	WriteIdtChipLocRegister(stVC[sn].ChipID, stVC[sn].ChannelID, IDT_LREG_Channel_IOData, temp);
}
void SetFR(int sn, int newValue) {
	if( newValue > 1 ) {
		newValue = 1;
	}
	int temp = 0;
	ReadIdtChipLocRegister(stVC[sn].ChipID, stVC[sn].ChannelID, IDT_LREG_Channel_IOData, &temp);
	temp &= ~(1<<6);
	temp |= (newValue << 6);
	WriteIdtChipLocRegister(stVC[sn].ChipID, stVC[sn].ChannelID, IDT_LREG_Channel_IOData, temp);
}

//void FXSSignalFromCpldToPcm(int sn, int SrcSignal) {
//	int Abit = DEFGetA(SrcSignal);
//	int Bbit = DEFGetB(SrcSignal);
//	if( stVC[sn].mode == 0 ) {
//		/* 自动电话 */
//		if( Abit == 0 ) {
//			SetRC(sn, 1);
//			SetFR(sn, 1);
//		}
//		else {
//			SetRC(sn, 0);
//			SetFR(sn, !Bbit);
//		}
//	}
//	else {
//		/* 热线 */
//		if( Abit == 0 ) {
//			switch( stVC[sn].RCFlag ) {
//			case 0:
//			/* 第一次进入热线RC处理程序 */
//				stVC[sn].startTime = timer32_1_counter;
//				SetRC(sn, 1);
//				stVC[sn].RCFlag = 1;
//				break;
//			case 1: {
//				/* 1s 响铃时间 */
//				uint32 t = (timer32_1_counter - stVC[sn].startTime) % 50;
//				if( t >= 10 ) {
//					SetRC(sn, 0);
//					stVC[sn].RCFlag = 2;
//				}
//			}
//				break;
//			case 2: {
//				/* 4s 停止响铃时间 */
//				uint32 t = (timer32_1_counter - stVC[sn].startTime) % 50;
//				if( t < 10 ) {
//					SetRC(sn, 1);
//					stVC[sn].RCFlag = 1;
//				}
//			}
//				break;
//			default:
//				stVC[sn].RCFlag = 0;
//				break;
//			}
//			SetFR(sn, 1);
//
//		}
//		else {
//			SetRC(sn, 0);
//			SetFR(sn, !Bbit);
//			stVC[sn].RCFlag = 0;
//		}
//	}
//}
//void FXSSignalFromPcmToCpld(int sn, int SrcSignal) {
//	int SHK2 = DEFGetSHK2(SrcSignal);
//	SetSignalA(sn, SHK2);
//}
//void FXOSignalFromCpldToPcm(int sn, int SrcSignal) {
//	int Abit = DEFGetA(SrcSignal);
//	if( Abit == 0 ) {
//		SetRC(sn, 1);
//	}
//	else {
//		SetRC(sn, 0);
//	}
//}
//void FXOSignalFromPcmToCpld(int sn, int SrcSignal) {
//	switch( SrcSignal & 0x3 ) {
//	case 0:
//		SetSignalA(sn, 0);
//		break;
//	case 1:
//		SetSignalA(sn, 1);
//		break;
//	case 2:
//		SetSignalA(sn, 1);
//		SetSignalB(sn, 1);
//		break;
//	case 3:
//		SetSignalA(sn, 1);
//		SetSignalB(sn, 0);
//		break;
//	}
//}

int GetValidVF(int StartSN, int* FirstValidType) {
	for( int i = StartSN; i < DEF_MAX_VF_NUM; i++ ) {
		if( stVC[i].Type != 0 ) {
			*FirstValidType = stVC[i].Type;
			return i;
		}
	}
	return -1;
}

int CountValidVoiceChannel() {
	int count = 0;
	for( int i = 0; i < DEF_MAX_VF_NUM; i++ ) {
		if( stVC[i].Type != 0 ) {
			++count;
		}
	}
	return count;
}

int GetVfMode(int vfSn) {
	return stVC[vfSn].mode;
}
void SetVfMode(int vfSn, int newMode) {
	stVC[vfSn].mode = newMode;
}

void SetVFLED(int vfSn, int mode) {
	if( vfSn >= DEF_MAX_VF_NUM || stVC[vfSn].State == 0 || mode < 0 || mode > 1) {
		return;
	}
	int chipID = stVC[vfSn].ChipID;
	int channelID = stVC[vfSn].ChannelID;
	int Temp = 0;
	ReadIdtChipGlbRegister(chipID,IDT_GREG_SB1_Control_Status, &Temp);
	Temp &= ~(1 << (channelID-1));
	Temp |= mode << (channelID-1);
	WriteIdtChipGlbRegister(chipID,IDT_GREG_SB1_Control_Status, Temp);
}
