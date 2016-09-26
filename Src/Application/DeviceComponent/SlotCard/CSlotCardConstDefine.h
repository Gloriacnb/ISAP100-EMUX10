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
	static const uint32 uiConstCardStatusNo 				= 0;		//�忨״̬δ֪
	static const uint32 uiConstCardStatusNormal 			= 1;		//�忨��������
	static const uint32 uiConstCardStatusBootMainLoss 		= 2;		//Boot��Main����ȱʧ
	static const uint32 uiConstCardStatusBootPrograming		= 3;		//Boot�г��������
	static const uint32 uiConstCardStatusBootProgramFailed	= 4;		//Boot�г������ʧ��
	static const uint32 uiConstCardStatusBootNormal			= 5;		//Boot������
	static const uint32 uiConstCardStatusMainFPGALoss		= 6;		//Main��FPGA����ȱʧ
	static const uint32 uiConstCardStatusMainPrograming		= 7;		//Main�г��������
	static const uint32 uiConstCardStatusMainProgramFailed	= 8;		//Main�г������ʧ��
	static const uint32 uiConstCardStatusMainLoadFPGAFailed	= 9;		//Main�г���д��FPGAʧ��
	static const uint32 uiConstCardStatusMainFPGARunFailed	= 10;		//Main��FPGA����ʧ��
	static const uint32 uiConstCardStatusMainHardWareFailed	= 11;		//Main��Ӳ��ʧЧ
	static const uint32 uiConstCardStatusMainConfigLoss		= 11;		//Main�еȴ���������
	static const uint32 uiConstCardStatusMainConfigLoading	= 12;		//Main�������·���������
	static const uint32 uiConstCardStatusMainConfigFailed	= 13;		//Main���·���������ʧ��


	//�忨���Ͷ���
	static const uint32 uiConstCardTypeNone					= 0;		//�޲忨
	static const uint32 uiConstCardTypeMC					= 0x01;		//���ؿ�
	static const uint32 uiConstCardTypeEA					= 0x04;		//��̫��ۿ�
	static const uint32 uiConstCardTypePWRFAN				= 0x0c;		//��Դ���ȿ�
	static const uint32 uiConstCardTypeXCSTM4Line2			= 0x10;		//�������濨STM4-2
	static const uint32 uiConstCardTypeXCSTM4Line4			= 0x14;		//�������濨STM4-4
	static const uint32 uiConstCardTypeXCSTM16Line1			= 0x18;		//�������濨STM16-1
	static const uint32 uiConstCardTypeLISTM1Line2			= 0x90;		//����Ⱥ·��STM1-2
	static const uint32 uiConstCardTypeLISTM1Line4			= 0x94;		//����Ⱥ·��STM1-4
	static const uint32 uiConstCardTypeTRSTM1Line4			= 0x98;		//����֧·��STM1-4
	static const uint32 uiConstCardTypeTRSTM1Line8			= 0x9c;		//����֧·��STM1-8
	static const uint32 uiConstCardType16E1					= 0x20;		//16E1��
	static const uint32 uiConstCardType8E1					= 0x21;		//8E1��
	static const uint32 uiConstCardType4E1					= 0x22;		//4E1��
	static const uint32 uiConstCardType4V35					= 0x28;		//4V.35��
	static const uint32 uiConstCardTypeFE88EOS				= 0x30;		//��̫���뿨8��ڣ�EOSЭ��
	static const uint32 uiConstCardTypeFX88EOS				= 0x31;		//��̫���뿨8��ڣ�EOSЭ��
	static const uint32 uiConstCardTypeFE88EOP				= 0x38;		//��̫���뿨8��ڣ�EOPЭ��
	static const uint32 uiConstCardTypeFX88EOP				= 0x39;		//��̫���뿨8��ڣ�EOPЭ��
	static const uint32 uiConstCardTypeGE8AEOS				= 0x40;		//��̫��������EOSЭ��
	static const uint32 uiConstCardTypeGE8AEOP				= 0x48;		//��̫��������EOPЭ��
	static const uint32 uiConstCardTypeGE24AEOS				= 0x50;		//��̫��������EOSЭ�飬24VCG
	static const uint32 uiConstCardTypeGE24AEOP				= 0x58;		//��̫��������EOPЭ�飬24VCG

	//����Ƿ�����Ч�Ĳ忨���͡�����²忨����ʱ���������Ӧ����
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
