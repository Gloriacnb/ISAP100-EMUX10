/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ebbnetwork.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Wang changrong
** Created date:			2010-12-27
** Version:					1.0
** Descriptions:			��̫������оƬ����ͨ��ʵ�ֽӿڣ�������̫������оƬӦ��ʵ�ֵĻ�������
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**
**********************************************************************************************************************/
#ifndef CSwitchBaseImpl_H
#define CSwitchBaseImpl_H

#include "EZ_types.h"


/**********************************************************************************************************************
** name:					stPortAlarmStatus
** Descriptions:			�˿ڸ澯�ṹ
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
** Varialble��				ucLinkDown��	����״̬�澯����ȡֵ
**											CCommonValueDefine::uiConstAlarmHasAlarm:					�и澯
**											CCommonValueDefine::uiConstAlarmNoAlarm:					û�и澯
**							ucANFailure��	�Զ�Э�̸澯����ȡֵ
**											CCommonValueDefine::uiConstAlarmHasAlarm:					�и澯
**											CCommonValueDefine::uiConstAlarmNoAlarm:					û�и澯
**							ucHalfDuplex��	�������Զ�Э��״̬ʱ��Э�̳ɰ�˫��״̬�澯����ȡֵ
**											CCommonValueDefine::uiConstAlarmHasAlarm:					�и澯
**											CCommonValueDefine::uiConstAlarmNoAlarm:					û�и澯
**							ucSpeedLow��	�������Զ�Э��״̬ʱ��Э�̳ɵ�����״̬�澯�����������¿�ȡֵ
**											CCommonValueDefine::uiConstAlarmHasAlarm:					�и澯
**											CCommonValueDefine::uiConstAlarmNoAlarm:					û�и澯
**											���˿�Ϊǧ����̫��ʱ����ȡֵ
**											CCommonValueDefine::uiConstAlarmNoAlarm:					û�и澯
**											CCommonValueDefine::uiConstAlarmHasAlarmSpeedLow100M:		100M�澯
**											CCommonValueDefine::uiConstAlarmHasAlarmSpeedLow10M:		10M�澯
**							ucLoopback��	�Զ�Э�̸澯����ȡֵ
**											CCommonValueDefine::uiConstAlarmHasAlarm:					�и澯
**											CCommonValueDefine::uiConstAlarmNoAlarm:					û�и澯
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**
**********************************************************************************************************************/
typedef struct{
	uint8 ucLinkDown;
	uint8 ucANFailure;
	uint8 ucHalfDuplex;
	uint8 ucSpeedLow;
	uint8 ucLoopback;
}stPortAlarmStatus;

/**********************************************************************************************************************
** name:					stPortEthernetPHY
** Descriptions:			�˿����ýṹ
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
** Varialble��				ucANEnabled��	�Զ�Э��ʹ�ܣ���ȡֵ
**											CSwitchBaseImpl::uiConstEnabled:			ʹ��
**											CSwitchBaseImpl::uiConstDisabled:			��ʹ��
**							ucLinkSpeed��	ǿ��ģʽ�µĶ˿����ʲ�������ȡֵ
**											CSwitchBaseImpl::uiConstLinkSpeed10M:		10M
**											CSwitchBaseImpl::uiConstLinkSpeed100M:		100M
**											CSwitchBaseImpl::uiConstLinkSpeed1000M:		1000M
**							ucFullDuplex��	ǿ��ģʽ�µĶ˿�˫��ģʽ��������ȡֵ
**											CSwitchBaseImpl::uiConstHalfDuplex:			��˫��
**											CSwitchBaseImpl::uiConstFullDuplex:			ȫ˫��
**							ucCapability��	�Զ�Э��ʱ�ܹ�֧�ֵ����Э��������������ȡֵ
**											CSwitchBaseImpl::uiConstCapabilit10MHalf	�Զ�Э��������10M��˫��
**											CSwitchBaseImpl::uiConstCapabilit10MFULL	�Զ�Э��������10Mȫ˫��
**											CSwitchBaseImpl::uiConstCapabilit100MHalf	�Զ�Э��������100M��˫��
**											CSwitchBaseImpl::uiConstCapabilit100MFULL	�Զ�Э��������100Mȫ˫��
**											CSwitchBaseImpl::uiConstCapabilit1000MHalf	�Զ�Э��������1000M��˫��
**											CSwitchBaseImpl::uiConstCapabilit1000MFULL	�Զ�Э��������1000Mȫ˫��
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**
**********************************************************************************************************************/
typedef struct{
	uint8 ucANEnabled;
	uint8 ucLinkSpeed;
	uint8 ucFullDuplex;
	uint8 ucCapability;
}stPortEthernetPHY;

/**********************************************************************************************************************
** name:					stQosPrioritySelection
** Descriptions:			���ȼ�ѡ��ṹ
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
** Varialble��				ucDot1QEnabled��	802.1Q���ȼ�ʹ�ܲ���
**							ucDSCPEnabled��		DSCP���ȼ�ʹ�ܲ���
**							ucPortEnabled��		�˿����ȼ�ʹ�ܲ���
**							ucVIDEnabled��		VLANID���ȼ�ʹ�ܲ���
**												���ǵ�ȡֵ��Χ����
**												CSwitchBaseImpl::uiConstEnabled:			ʹ��
**												CSwitchBaseImpl::uiConstDisabled:			��ʹ��
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**
**********************************************************************************************************************/
typedef struct{
	uint8 ucDot1QEnabled;
	uint8 ucDSCPEnabled;
	uint8 ucPortEnabled;
	uint8 ucVIDEnabled;
}stQosPrioritySelection;

/**********************************************************************************************************************
** name:					CSwitchBaseImpl
** Descriptions:			��̫������оƬ����ͨ��ʵ�ֽӿ���
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**
**********************************************************************************************************************/
class CSwitchBaseImpl
{	
public:
	static const uint32 uiConstDisabled 					= 0;	//��ʹ��
	static const uint32 uiConstEnabled 						= 1;	//ʹ��

//	static const uint32 uiConstDontConfigChip 				= 0;	//����Ҫ����оƬ�Ĵ���
//	static const uint32 uiConstNeedConfigChip 				= 1;	//��Ҫ����оƬ�Ĵ���
	
	static const uint32 uiConstMaxPacketLength1518 			= 0;	//������ѡ��----1518
	static const uint32 uiConstMaxPacketLength1536 			= 1;	//������ѡ��----1536
	static const uint32 uiConstMaxPacketLength1552 			= 2;	//������ѡ��----1552
	static const uint32 uiConstMaxPacketLength1916 			= 3;	//������ѡ��----1916
	static const uint32 uiConstMaxPacketLength2047 			= 4;	//������ѡ��----2047
	
	static const uint32 uiConstTaggingModeNone				= 0;	//�������Ҳ��Ƴ�Tag��
	static const uint32 uiConstTaggingModeInsert			= 1;	//ֻ�����Ҳ��Ƴ�Tag��
	static const uint32 uiConstTaggingModeRemove			= 2;	//��������ֻ�Ƴ�Tag��
	static const uint32 uiConstTaggingModeInsertAndRemove	= 3;	//�����������Ƴ�Tag��
	
	static const uint32 uiConstCounterModeByte				= 0;	//ͳ�Ƽ��������ֽڷ�ʽ
	static const uint32 uiConstCounterModePackage			= 1;	//ͳ�Ƽ������ð���ʽ
	static const uint32 uiConstCounterModeBit				= 2;	//ͳ�Ƽ������ñ��ط�ʽ
	
	static const uint32 uiConstLinkSpeed10M					= 0;	//ʮ������	
	static const uint32 uiConstLinkSpeed100M				= 1;	//��������
	static const uint32 uiConstLinkSpeed1000M				= 2;	//ǧ������	
	
	static const uint32 uiConstHalfDuplex					= 0;	//��˫��ģʽ	
	static const uint32 uiConstFullDuplex					= 1;	//ȫ˫��ģʽ
	
	static const uint32 uiConstCapabilit10MHalf				= 0;	//�Զ�Э��������10M��˫��
	static const uint32 uiConstCapabilit10MFULL				= 1;	//�Զ�Э��������10Mȫ˫��
	static const uint32 uiConstCapabilit100MHalf			= 2;	//�Զ�Э��������100M��˫��
	static const uint32 uiConstCapabilit100MFULL			= 3;	//�Զ�Э��������100Mȫ˫��
	static const uint32 uiConstCapabilit1000MHalf			= 4;	//�Զ�Э��������1000M��˫��
	static const uint32 uiConstCapabilit1000MFULL			= 5;	//�Զ�Э��������1000Mȫ˫��

	static const uint32 uiConstPriorityLevelHigh            = 1;	//�����ȼ�
	static const uint32 uiConstPriorityLevelLow             = 0;	//�����ȼ�
	
public:
	CSwitchBaseImpl();
	virtual ~CSwitchBaseImpl();
	
	/*   ���¹�����������ʵ��ʵ�ʹ���  */
	//оƬ�����ʼ��
	virtual uint32 InitializeSwitch(uint32 uiConfig) = 0;
	//��ý���оƬID
	virtual uint32 GetSwitchChipID(uint32* uipChipID ) = 0;
	
	/*   ����ģʽ����  */
	//ȫ����ģʽ��ʼ��
	virtual uint32 InitializeFullSwitchMode(void) = 0;
	//���ģʽ(����)��ʼ��
	virtual uint32 InitializeAggregationMode(void) = 0;
	//802.1Qģʽ��ʼ��
	virtual uint32 InitializeTagAwareMode(void) = 0;
	
	/*   ����оƬȫ������  */
	//���������� 
	virtual uint32 SetSwitchMaxPacketLength(uint32 uiLength) = 0;
	//���ù㲥�籩����ʹ��
	virtual uint32 SetSwitchBroadcastFilter(uint32 uiEnabled) = 0;
	//������������ʹ��
	virtual uint32 SetSwitchFlowControl(uint32 port, uint32 uiEnabled) = 0;
	
	/*   VLAN����  */
	//����VLAN��
	virtual uint32 CreateVLANGroup(uint32 uiVID) = 0;
	//ɾ��VLAN��
	virtual uint32 DeleteVLANGroup(uint32 uiVID) = 0;
	//���VLAN���Ա
	virtual uint32 AddPortMemberToVLANGroup(uint32 uiVID, uint32 uiPort) = 0;
	//ɾ��VLAN���Ա
	virtual uint32 DeletePortMemberFromVLANGroup(uint32 uiVID, uint32 uiPort) = 0;
	//���ö˿ڵ�PVID
	virtual uint32 SetPortVID(uint32 uiPort,uint32 uiPVID) = 0;
	//���ö˿ڶ�Tag�Ĵ���ģʽ�����롢�Ƴ�Tag�ȣ�
	virtual uint32 SetVLANTaggingMode(uint32 uiVid,uint32 uiPort,uint32 uiMode) = 0;
	//���ý���˿�ʱ �Ƿ���Դ�Tag
	virtual uint32 SetPortAcceptFrameType(uint32 uiPort, uint32 uiMode) = 0;
	
	/*   �˿�ͳ�Ƽ���   */
	//������̫�����ֽ�/��������ʽ
	virtual uint32 SetCounterMode(uint32 uiMode) = 0;
	//��ö˿���̫���ݽ��ռ���
	virtual uint32 GetRxCounter(uint32 uiPort, uint32 *uipValue) = 0;
	//��ö˿���̫���ݷ��ͼ���
	virtual uint32 GetTxCounter(uint32 uiPort, uint32 *uipValue) = 0;
	//��ö˿���̫���ݶ�������
	virtual uint32 GetDropCounter(uint32 uiPort, uint32 *uipValue) = 0;
	//��ö˿���̫���ݽ��ռ�����������
	virtual uint32 GetRxCounterNoClear(uint32 uiPort, uint32 *uipValue) = 0;
	//��ö˿���̫���ݷ��ͼ�����������
	virtual uint32 GetTxCounterNoClear(uint32 uiPort, uint32 *uipValue) = 0;
	//��ö˿���̫���ݶ���������������
	virtual uint32 GetDropCounterNoClear(uint32 uiPort, uint32 *uipValue) = 0;

	virtual	uint32 getCrcErrorCounterNoClear(uint32 port, uint32* value) = 0;

	/*   �˿�ģʽ����  */
	//���ö˿�ģʽ 
	virtual uint32 SetEthernetPHY(uint32 uiPort, stPortEthernetPHY* stpPHYMode) = 0;
	//��ö˿ڸ澯״̬
	virtual uint32 GetPortAlarmStatus(uint32 uiPort,stPortAlarmStatus *stpStatus) = 0;
	//���ö˿ڹض�ʹ��
	virtual uint32 SetPortPowerDown(uint32 uiPort,uint32 uiEnabled) = 0;
	
	/*   QoS����   */
	//QoS��ʼ�����������ȼ����и���
	virtual uint32 InitializeQoS(uint32 uiQueueNumber) = 0;
	//�˿��շ����������
	virtual uint32 SetPortRxBandWidth(uint32 uiPort,uint32 uiBandWidth) = 0;
	//�˿ڷ������������
	virtual uint32 SetPortTxBandWidth(uint32 uiPort,uint32 uiBandWidth) = 0;
	//����QoS�Ĳ�ͬ�������ȼ��ȽϹ�ϵ
	virtual uint32 SetQosWrr(uint8 mode) = 0;
	//���ö˿ڶ���Ȩ��
	virtual uint32 SetQoSPrioritySelection(stQosPrioritySelection* stpSelection) = 0;
	//���ö˿����ȼ�
	virtual uint32 SetPortPriority(uint32 uiPort,uint32 uiPriority) = 0;
	//����DSCP���ȼ� 
	virtual uint32 SetDSCPPriority(uint32 uiDSCPType,uint32 uiPriority) = 0;
	//����802.1Q���ȼ�
	virtual uint32 SetDot1QPriority(uint32 uiDot1QType,uint32 uiPriority) = 0;
	//�������������	
};
#endif


