/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			FVIdt821054Access.cpp
 ** File path:			/EMUX300M0/Src/HardwareDrivers/FVIdt821054Access.cpp
 ** Created by:          Shqp
 ** Created date:        2012-6-28
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

#include "FVIdt821054Access.h"
#include "IDT821054RegisterMap.h"
#include "Mid_SPI.h"
#include "ChipGluLogic.h"

#define DEF_IDCode 0x81
#define SelCPLD 3

static void SelectChip(uint8 value);		   //片选
static int IDTMPIReadCommand(int Command, int* RegValue);
static int IDTMPIWriteCommand(int Command, int NewValue);
static int IDTMPIRamReadBlock(uint8 block, uint16* data);
static int IDTMPIRamWriteBlock(uint8 block, uint16* data);
//int IDTReadLocalRegister(int channel, int RegAddr, int* RegValue);
//int IDTWriteLocalRegister(int channel, int RegAddr, int NewValue);
//static void CS_CPLD(uint8 value);
/*
 * 读全局寄存器，RegAddr 范围2x
 */
int ReadIdtChipGlbRegister(int ChipID, int RegAddr, int* RegValue) {
	int Rtn = 0;
	if( ChipID < DEF_Min_ChipID || ChipID > DEF_Max_ChipID || RegValue == NULL ) {
		return -1;
	}
	SelectChip(ChipID);
	Rtn = IDTMPIReadCommand(RegAddr, RegValue);
	SelectChip(SelCPLD);
	return Rtn;
}

/*
 * 写全局寄存器
 */
int WriteIdtChipGlbRegister(int ChipID, int RegAddr, int RegValue) {
	int Rtn;
	if( ChipID < DEF_Min_ChipID || ChipID > DEF_Max_ChipID ) {
		return -1;
	}
	SelectChip(ChipID);
	Rtn = IDTMPIWriteCommand(RegAddr, RegValue);
	SelectChip(SelCPLD);
	return Rtn;
}

/*
 * 读通道寄存器
 */
int ReadIdtChipLocRegister(int ChipID, int channel, int RegAddr, int* RegValue) {
	int channelMask	= 0;
	int Rtn = 0;
	if( ChipID 	 < DEF_Min_ChipID ||
		ChipID 	 > DEF_Max_ChipID ||
		RegValue == NULL ||
		channel  < DEF_Min_ChannelID ||
		channel  > DEF_Max_ChannelID ) {

		return -1;
	}
	channelMask = (1 << (channel-1));
	WriteIdtChipGlbRegister(ChipID, IDT_GREG_MCLK_Channel_Program, (channelMask<<4) | DEF_MCLK);

	SelectChip(ChipID);
	Rtn = IDTMPIReadCommand(RegAddr, RegValue);
	SelectChip(SelCPLD);
	return Rtn;
}

/*
 * 写通道寄存器
 */
int WriteIdtChipLocRegister(int ChipID, int channel, int RegAddr, int NewValue) {
	int channelMask, Rtn;

	if( ChipID 	 < DEF_Min_ChipID ||
		ChipID 	 > DEF_Max_ChipID ||
		channel  < DEF_Min_ChannelID ||
		channel  > DEF_Max_ChannelID ) {

		return -1;
	}
	channelMask = (1 << (channel-1));
	WriteIdtChipGlbRegister(ChipID, IDT_GREG_MCLK_Channel_Program, (channelMask<<4) | DEF_MCLK);
	SelectChip(ChipID);
	Rtn = IDTMPIWriteCommand(RegAddr, NewValue);
	SelectChip(SelCPLD);
	return Rtn;
}

/*
 * 读CoeRam 一次读取一个block 8words
 */
int readIDTChipCoeRamBlock(const int ChipID, const int channel, const int block, uint16* dataBuff) {
	int channelMask, Rtn;

	if( ChipID 	 < DEF_Min_ChipID ||
		ChipID 	 > DEF_Max_ChipID ||
		channel  < DEF_Min_ChannelID ||
		channel  > DEF_Max_ChannelID ) {

		return -1;
	}
	channelMask = (1 << (channel-1));
	WriteIdtChipGlbRegister(ChipID, IDT_GREG_MCLK_Channel_Program, (channelMask<<4) | DEF_MCLK);
	SelectChip(ChipID);
	//printf("\ndataff = %x\n", dataBuff[0]);
	Rtn = IDTMPIRamReadBlock(block, dataBuff);
	SelectChip(SelCPLD);
//	printf("\ndataff = %x\n", dataBuff[0]);
	return Rtn;
}
/*
 * 写CoeRam 一次写一个block 8words
 */
int writeIDTChipCoeRamBlock(const int ChipID, const int channel, const uint8 block, uint16* data, uint8 dataLen) {
	int channelMask, Rtn;
    uint8 i;
    uint16 coeramdata[8];
    for(i=0;i<8;i++){
    		coeramdata[i]=0;
    	}
	if( ChipID 	 < DEF_Min_ChipID ||
		ChipID 	 > DEF_Max_ChipID ||
		channel  < DEF_Min_ChannelID ||
		channel  > DEF_Max_ChannelID ) {

		return -1;
	}
	channelMask = (1 << (channel-1));
	WriteIdtChipGlbRegister(ChipID, IDT_GREG_MCLK_Channel_Program, (channelMask<<4) | DEF_MCLK);
	SelectChip(ChipID);
	IDTMPIRamReadBlock(block, coeramdata);
	for (i = 0; i < dataLen; ++i) {
		coeramdata[i]=data[i];//暂时省略后七位
	}
	SelectChip(SelCPLD);//0h0011,close all
	SelectChip(ChipID);
	Rtn = IDTMPIRamWriteBlock(block, coeramdata);
	SelectChip(SelCPLD);
//	printf("\ncoeramdata = %x\n", coeramdata[0]);
//	SelectChip(ChipID);
//	IDTMPIRamReadBlock(block, coeramdata);
//	printf("\ncoeramdata = %x\n", coeramdata[0]);
//	SelectChip(SelCPLD);
	return Rtn;
}

/*
 * 读写CPLD寄存器
 */
int ReadCPLDRegister(int cID, int RegAddr, int* RegValue) {
	ExtCPLDRegReadByte(cID<<2, (uint16)RegAddr, (uint8*)RegValue);
	return 0;

}

int WriteCPLDRegister(int cID, int RegAddr, int RegValue) {
	ExtCPLDRegWriteByte(cID<<2, (uint16)RegAddr, (uint8)RegValue);
	return 0;
}


/* 以下均为本地功能函数 */

static void SelectChip(uint8 value) {						  //共有8个821054 选择其中一个
	glulogic->SPI_SEL = value;
}

//static void CS_CPLD(uint8 value) {
//	glulogic->SPI_SEL = value << 2;
//}


static int IDTMPIReadCommand(int Command, int* ReadData) {
	uint8 addr = (uint8)(Command & 0x7f);
	uint16 result = 0;
	result = SpiChipRead(addr, 1, 2);
	if( (result>>8) != DEF_IDCode ) {
		return -1;
	}
	*ReadData = result & 0xff;
	return 0;
}

static int IDTMPIWriteCommand(int Command, int NewValue) {
	uint8 Sendbuf[2];
	Sendbuf[0] = (uint8)(Command | 0x80);
	Sendbuf[1] = (uint8)NewValue;
	SpiChipWrite(Sendbuf[0], Sendbuf[1], 1, 1);
	return 0;
}
static int IDTMPIRamReadBlock(uint8 block, uint16* data) {
	if(block  > DEF_Max_Block) {
			return -1;
		}
		SpiChipRamRead(block,data);
		//读取块中的8个字，每个字16位，14位有效
		//result = SpiChipRead(block, 1, 2);//缓冲最大8帧， 每帧16位
	return 0;
}

static int IDTMPIRamWriteBlock(uint8 block, uint16* data) {
	//int i;
	if( block < DEF_Min_Block ||block  > DEF_Max_Block) {
				return -1;
			}

//	for ( i = 0; i < 8; ++i) {
//		printf("\ndata[%d] = %x\n", i, data[i]);
//	}
	SpiChipRamWrite(block,data);
	return 0;
}

