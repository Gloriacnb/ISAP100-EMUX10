#ifndef RTL8306ESWITCH_H
#define RTL8306ESWITCH_H

#include "rtk_api_ext.h"
#include "CSwitchBaseImpl.h"

#define BandWitchMaxNum  1526
#define MaxPriInPrioritySelection   5
#define MinPriInPrioritySelection   1

#define RTL8306eMaxPacketLength     3     

#ifndef FALSE
/* FALSE macro */
#define FALSE (0==1)
#endif
#ifndef TRUE
/* TRUE macro */
#define TRUE (!(FALSE))
#endif

class RTL8306ESwitch : public CSwitchBaseImpl
{	
public:


	RTL8306ESwitch();
	virtual ~RTL8306ESwitch();	
	
	virtual uint32 InitializeSwitch(uint32 uiConfig);	 //оƬ�����ʼ��		
	virtual uint32 GetSwitchChipID(uint32* uipChipID );  //��ý���оƬID	

	/*   ����ģʽ����  */
	virtual uint32 InitializeFullSwitchMode(void); 	     //ȫ����ģʽ��ʼ��
	virtual uint32 InitializeAggregationMode(void); 	 //���ģʽ(����)��ʼ��	
	virtual uint32 InitializeTagAwareMode(void);         //802.1Qģʽ��ʼ��
	
	/*   ����оƬȫ������  */	
	virtual uint32 SetSwitchMaxPacketLength(uint32 uiLength); //���������� 	
	virtual uint32 SetSwitchBroadcastFilter(uint32 uiEnabled); //���ù㲥�籩����ʹ��	
	virtual uint32 SetSwitchFlowControl(uint32 port, uint32 uiEnabled); 		//������������ʹ��
	
	/*   VLAN����  */
	virtual uint32 CreateVLANGroup(uint32 uiVID); 	//����VLAN��
	virtual uint32 DeleteVLANGroup(uint32 uiVID);  	//ɾ��VLAN��	
	virtual uint32 AddPortMemberToVLANGroup(uint32 uiVID, uint32 uiPort); //���VLAN���Ա
	
	virtual uint32 DeletePortMemberFromVLANGroup(uint32 uiVID, uint32 uiPort); 	  //ɾ��VLAN���Ա
	virtual uint32 SetPortVID(uint32 uiPort,uint32 uiPVID);  	//���ö˿ڵ�PVID
	virtual uint32 SetVLANTaggingMode(uint32 uiVid,uint32 uiPort,uint32 uiMode);  	//���ö˿ڶ�Tag�Ĵ���ģʽ�����롢�Ƴ�Tag�ȣ�
	virtual uint32 SetPortAcceptFrameType(uint32 uiPort, uint32 uiMode);
	
	/*   �˿�ͳ�Ƽ���   */
	virtual uint32 SetCounterMode(uint32 uiMode);		//������̫�����ֽ�/��������ʽ	
	virtual uint32 GetRxCounter(uint32 uiPort, uint32 *uipValue); //��ö˿���̫���ݽ��ռ���
	virtual uint32 GetTxCounter(uint32 uiPort, uint32 *uipValue);  	//��ö˿���̫���ݷ��ͼ���
	virtual uint32 GetDropCounter(uint32 uiPort, uint32 *uipValue); 	//��ö˿���̫���ݶ�������
	virtual uint32 GetRxCounterNoClear(uint32 uiPort, uint32 *uipValue);  	//��ö˿���̫���ݽ��ռ�����������
	virtual uint32 GetTxCounterNoClear(uint32 uiPort, uint32 *uipValue);  	//��ö˿���̫���ݷ��ͼ�����������
	virtual uint32 GetDropCounterNoClear(uint32 uiPort, uint32 *uipValue);		//��ö˿���̫���ݶ���������������
	virtual	uint32 getCrcErrorCounterNoClear(uint32 port, uint32* value);
	
	/*   �˿�ģʽ����  */
	virtual uint32 SetEthernetPHY(uint32 uiPort, stPortEthernetPHY* stpPHYMode);   	//���ö˿�ģʽ 
	virtual uint32 GetPortAlarmStatus(uint32 uiPort,stPortAlarmStatus *stpStatus); 	 	//��ö˿ڸ澯״̬
	virtual uint32 SetPortPowerDown(uint32 uiPort,uint32 uiEnabled);  	//���ö˿ڹض�ʹ��
	
	/*   QoS����   */
	virtual uint32 InitializeQoS(uint32 uiQueueNumber);    	//QoS��ʼ�����������ȼ����и���
	virtual uint32 SetPortRxBandWidth(uint32 uiPort,uint32 uiBandWidth); 	//�˿��շ����������
	virtual uint32 SetPortTxBandWidth(uint32 uiPort,uint32 uiBandWidth); 		//�˿ڷ������������
	virtual uint32 SetQoSPrioritySelection(stQosPrioritySelection* stpSelection); 	 	//����QoS�Ĳ�ͬ�������ȼ��ȽϹ�ϵ
	virtual uint32 SetPortPriority(uint32 uiPort,uint32 uiPriority);	   	//���ö˿����ȼ�
	virtual uint32 SetDSCPPriority(uint32 uiDSCPType,uint32 uiPriority); 		//����DSCP���ȼ� 
	virtual uint32 SetDot1QPriority(uint32 uiDot1QType,uint32 uiPriority); 			//����802.1Q���ȼ�	
	
	virtual uint32 SetQosWrr(uint8 mode);	
};

#endif

