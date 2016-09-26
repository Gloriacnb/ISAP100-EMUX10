/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSlotCardConstDefine.h
 ** Created by:				WangChangRong
 ** Created date:			2011-7-14
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSLOTCARDCONSTDEFINE_H_
#define CSLOTCARDCONSTDEFINE_H_
//#include "config.h"
#include "EZ_types.h"
class CSlotCardConstDefine
{
public:
	static const uint32 uiConstCardStatusNo 				= 0;		//插卡状态未知
	static const uint32 uiConstCardStatusNormal 			= 1;		//插卡正常运行
	static const uint32 uiConstCardStatusBootMainLoss 		= 2;		//Boot中Main程序缺失
	static const uint32 uiConstCardStatusBootPrograming		= 3;		//Boot中程序加载中
	static const uint32 uiConstCardStatusBootProgramFailed	= 4;		//Boot中程序加载失败
	static const uint32 uiConstCardStatusBootNormal			= 5;		//Boot中运行
	static const uint32 uiConstCardStatusMainFPGALoss		= 6;		//Main中FPGA程序缺失
	static const uint32 uiConstCardStatusMainPrograming		= 7;		//Main中程序加载中
	static const uint32 uiConstCardStatusMainProgramFailed	= 8;		//Main中程序加载失败
	static const uint32 uiConstCardStatusMainLoadFPGAFailed	= 9;		//Main中程序写入FPGA失败
	static const uint32 uiConstCardStatusMainFPGARunFailed	= 10;		//Main中FPGA运行失败
	static const uint32 uiConstCardStatusMainHardWareFailed	= 11;		//Main中硬件失效
	static const uint32 uiConstCardStatusMainConfigLoss		= 11;		//Main中等待配置数据
	static const uint32 uiConstCardStatusMainConfigLoading	= 12;		//Main中正在下发配置数据
	static const uint32 uiConstCardStatusMainConfigFailed	= 13;		//Main中下发配置数据失败


	//板卡类型定义
	static const uint32 uiConstCardTypeNone					= 0;		//无插卡
	static const uint32 uiConstCardTypeMC					= 0x01;		//主控卡
	static const uint32 uiConstCardTypeEA					= 0x04;		//以太汇聚卡
	static const uint32 uiConstCardTypePWRFAN				= 0x0c;		//电源风扇卡
	static const uint32 uiConstCardTypeXCSTM4Line2			= 0x10;		//上联交叉卡STM4-2
	static const uint32 uiConstCardTypeXCSTM4Line4			= 0x14;		//上联交叉卡STM4-4
	static const uint32 uiConstCardTypeXCSTM16Line1			= 0x18;		//上联交叉卡STM16-1
	static const uint32 uiConstCardTypeLISTM1Line2			= 0x90;		//下联群路卡STM1-2
	static const uint32 uiConstCardTypeLISTM1Line4			= 0x94;		//下联群路卡STM1-4
	static const uint32 uiConstCardTypeTRSTM1Line4			= 0x98;		//下联支路卡STM1-4
	static const uint32 uiConstCardTypeTRSTM1Line8			= 0x9c;		//下联支路卡STM1-8
	static const uint32 uiConstCardType16E1					= 0x20;		//16E1卡
	static const uint32 uiConstCardType8E1					= 0x21;		//8E1卡
	static const uint32 uiConstCardType4E1					= 0x22;		//4E1卡
	static const uint32 uiConstCardType4V35					= 0x28;		//4V.35卡
	static const uint32 uiConstCardTypeFE88EOS				= 0x30;		//以太隔离卡8电口，EOS协议
	static const uint32 uiConstCardTypeFX88EOS				= 0x31;		//以太隔离卡8光口，EOS协议
	static const uint32 uiConstCardTypeFE88EOP				= 0x38;		//以太隔离卡8电口，EOP协议
	static const uint32 uiConstCardTypeFX88EOP				= 0x39;		//以太隔离卡8光口，EOP协议
	static const uint32 uiConstCardTypeGE8AEOS				= 0x40;		//以太交换卡，EOS协议
	static const uint32 uiConstCardTypeGE8AEOP				= 0x48;		//以太交换卡，EOP协议
	static const uint32 uiConstCardTypeGE24AEOS				= 0x50;		//以太交换卡，EOS协议，24VCG
	static const uint32 uiConstCardTypeGE24AEOP				= 0x58;		//以太交换卡，EOP协议，24VCG

	//检查是否是有效的插卡类型。添加新插卡类型时，需添加相应处理
	static uint32 IsValidCardType(uint32 uiType){
		if( uiType == uiConstCardTypeMC || uiType == uiConstCardTypeEA
		 || uiType == uiConstCardTypePWRFAN || uiType == uiConstCardTypeXCSTM4Line2
		 || uiType == uiConstCardTypeXCSTM4Line4 || uiType == uiConstCardTypeXCSTM16Line1
		 || uiType == uiConstCardTypeLISTM1Line2 || uiType == uiConstCardTypeLISTM1Line4
		 || uiType == uiConstCardTypeTRSTM1Line4 || uiType == uiConstCardTypeTRSTM1Line8
		 || uiType == uiConstCardType16E1 || uiType == uiConstCardType4V35
		 || uiType == uiConstCardTypeFE88EOS || uiType == uiConstCardTypeFX88EOS
		 || uiType == uiConstCardTypeFE88EOP || uiType == uiConstCardTypeFX88EOP
		 || uiType == uiConstCardTypeGE8AEOS || uiType == uiConstCardTypeGE8AEOP
		 || uiType == uiConstCardTypeGE24AEOS || uiType == uiConstCardTypeGE24AEOP
		 ){
			return true;
		}
		return false;
	};
};

#endif /* CSLOTCARDCONSTDEFINE_H_ */
