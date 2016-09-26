/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** Created by:				Wang Ying
 ** Created date:			2011-1-4
 ** Version:					1.0
 ** Descriptions:			RTL8306E����оƬ�ӿڹ���ʵ�ַ���
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Version:
 ** Descriptions:
 **
 **********************************************************************************************************************/
#ifndef RTL8306ESWITCH_CPP
#define RTL8306ESWITCH_CPP

#include "RTL8306ESwitch.h"
#include "CErrorValueDefine.h"

uint32 ClearRxCountValue = 0;
uint32 ClearTxCountValue = 0;
uint32 ClearDropCountValue = 0;

/**********************************************************************************************************************
 ** Function name:			RTL8306ESwitch
 ** Descriptions:			���캯��
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				Wang Ying
 ** Created date:			2011-1-4
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
RTL8306ESwitch::RTL8306ESwitch() {
}
/**********************************************************************************************************************
 ** Function name:			~RTL8306ESwitch
 ** Descriptions:			��������
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			None
 ** Created by:				Wang Ying
 ** Created date:			2011-1-4
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
RTL8306ESwitch::~RTL8306ESwitch() {
}

/**********************************************************************************************************************
 ** Function name:			InitializeSwitch
 ** Descriptions:			оƬ�����ʼ��
 ** input parameters:		uiConfig��		�Ƿ���Ҫ����оƬ��־,��ȡֵΪ
 **											CSwitchBaseImpl::uiConstNeedConfigChip����Ҫ����оƬ�Ĵ���
 **											CSwitchBaseImpl::uiConstDontConfigChip������Ҫ����оƬ�Ĵ���
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 				����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed:  				����ִ��ʧ��
 ** Created by:				Wang ying
 ** Created date:			2011-12-27
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::InitializeSwitch(uint32 uiConfig) {

	rtk_switch_init();
	rtk_qos_init(1);
	rtk_cpu_enable_set(DISABLED);
	rtk_filter_igrAcl_init();
	rtk_port_mac_ability_t info = { 0 };
	info.forcemode = 1;
	info.nway = 0;
	info.speed = PORT_SPEED_100M;
	info.duplex = PORT_FULL_DUPLEX;
	info.rxpause = 1;
	info.txpause = 1;
	info.link = 1;
	rtk_port_macForceLinkExt0_set(MODE_EXT_RMII, &info);

//	     for (int i = 0; i < 6; ++i) {
//			 rtl8306e_mib_reset(i);										    //����WAN�ڼ���
//			 rtl8306e_mibUnit_set(i,RTL8306_MIB_CNT1,RTL8306_MIB_BYTE);		//����WAN�ڷ����� �ֽڼ���
//			 rtl8306e_mibUnit_set(i,RTL8306_MIB_CNT2,RTL8306_MIB_BYTE);		//����WAN���շ��� �ֽڼ���
//		}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			GetSwitchChipID
 ** Descriptions:			��ý���оƬID
 ** input parameters:		None
 ** output parameters:		uipChipID��		����оƬ��ID
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang Ying
 ** Created date:			2011-1-5
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetSwitchChipID(uint32* uipChipID) {
	if (uipChipID == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint16 chipID = 0;
	if (rtk_getOUIID(0, &chipID) != TRUE) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	*uipChipID = chipID;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   ����ģʽ����  */
/**********************************************************************************************************************
 ** Function name:			InitializeFullSwitchMode
 ** Descriptions:			ȫ����ģʽ��ʼ��
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 ** Created by:				Wang Ying
 ** Created date:			2011-1-5
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::InitializeFullSwitchMode(void) {
	rtk_portmask_t isolate;
	isolate.bits[0] = 0x3f;

	rtl_VLANEnable_set(FALSE);
	for (uint32 i = 0; i < 6; i++) {
		rtk_port_isolation_set(i, isolate);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			InitializeAggregationMode
 ** Descriptions:			���ģʽ(����)��ʼ��
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 ** Created by:				Wang ying
 ** Created date:			2011-1-5
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::InitializeAggregationMode(void) {
//	rtk_portmask_t isolate;
//	isolate.bits[0] = 0;
//	isolate.bits[0] |= (1 << 5);
//	rtl8306e_vlan_transparentEnable_set(1);

	rtk_portmask_t iso[6] = { 0 };
	iso[0].bits[0] = (1 << 4); //~(1 << 4) & 0x3f;
	iso[1].bits[0] = (1 << 5); //~(1 << 4) & 0x3f;
	iso[2].bits[0] = (1 << 4); //~(1 << 5) & 0x3f;
	iso[3].bits[0] = (1 << 5); //~(1 << 5) & 0x3f;
	iso[4].bits[0] = (1 << 0) | (1 << 2); //~((1 << 0) | (1 << 2)) & 0x3f;
	iso[5].bits[0] = (1 << 1) | (1 << 3); //~((1 << 1) | (1 << 3)) & 0x3f;
	rtl_VLANEnable_set(FALSE);
//	rtl8306e_regbit_set(0, 18, 8, 0, 1);
	for (uint32 i = 0; i < 6/*GetEthernetPortNumber()*/; i++) {
//		IP175_setAsicPortLUT(i, 0x0);
		rtk_port_isolation_set(i, iso[i]);
		rtl8306e_portLearningAbility_set(i, 0); //�ر����ж˿ڵ�ѧϰ���ܣ�ʵ���������
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			InitializeTagAwareMode
 ** Descriptions:			802.1Qģʽ��ʼ��
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 ** Created by:				Wang ying
 ** Created date:			2011-1-5
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::InitializeTagAwareMode(void) {
	rtk_vlan_init();
	rtl_VLANEnable_set(1);
	rtl8306e_vlan_IgrFilterEnable_set(1); //������ڹ���ʹ��
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   ����оƬȫ������  */
/**********************************************************************************************************************
 ** Function name:			SetSwitchMaxPacketLength
 ** Descriptions:			����������
 ** input parameters:		uiLength��		���������ã���ȡֵΪ
 **											CSwitchBaseImpl::uiConstMaxPacketLength1518��������1518
 **											CSwitchBaseImpl::uiConstMaxPacketLength1536��������1536
 **											CSwitchBaseImpl::uiConstMaxPacketLength1552��������1552
 **											CSwitchBaseImpl::uiConstMaxPacketLength1916��������1916
 **											CSwitchBaseImpl::uiConstMaxPacketLength2047��������2047

 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 ** Created by:				Wang ying
 ** Created date:			2011-1-5
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetSwitchMaxPacketLength(uint32 uiLength) {
	if (uiLength != uiConstMaxPacketLength2047
			&& uiLength != uiConstMaxPacketLength1518
			&& uiLength != uiConstMaxPacketLength1536
			&& uiLength != uiConstMaxPacketLength1552) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if (uiLength == uiConstMaxPacketLength2047) {
		uiLength = RTL8306eMaxPacketLength;
	}

	rtk_switch_maxPktLen_set(uiLength);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			SetSwitchBroadcastFilter
 ** Descriptions:			���ù㲥�籩����ʹ��
 ** input parameters:		uiEnabled��		�㲥�籩ʹ�����ã���ȡֵΪ
 **											CSwitchBaseImpl::uiConstEnabled��	ʹ�� 1
 **											CSwitchBaseImpl::uiConstDisabled��	��ʹ�� 0
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 ** Created by:				Wang ying
 ** Created date:			2011-1-6
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetSwitchBroadcastFilter(uint32 uiEnabled) {
	if (rtl8306e_storm_filterEnable_set(RTL8306_BROADCASTPKT, uiEnabled) != TRUE) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (rtl8306e_storm_filter_set(RTL8306_STM_FILNUM64, RTL8306_STM_FIL800MS,
			1) != TRUE) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			SetSwitchFlowControl
 ** Descriptions:			������������ʹ��
 ** input parameters:		uiEnabled��		��������ʹ�����ã���ȡֵΪ
 **											CSwitchBaseImpl::uiConstEnabled��	ʹ��
 **											CSwitchBaseImpl::uiConstDisabled��	��ʹ��
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 				����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-6
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetSwitchFlowControl(uint32 port, uint32 uiEnabled) {
	if (uiEnabled > CSwitchBaseImpl::uiConstEnabled) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	//�������� Ϊȫ�ּĴ���
//	for( uint32 i = 0; i < 6; i++){
	rtl8306e_qos_portFlcMode_set(port, uiEnabled);
//	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   VLAN����  */
/**********************************************************************************************************************
 ** Function name:			CreateVLANGroup
 ** Descriptions:			����VLAN��
 ** input parameters:		uiVID��		��Ҫ������VLAN���ID��ȡֵ��ΧΪ0---4095
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstRuturnInputDataNotSupported:	��֧�ֵ��������ֵ
 **							CErrorValueDefine::uiConstRuturnVLANGroupAlreadyExist:	VLAN���Ѿ�����
 **							CErrorValueDefine::uiConstRuturnVLANGroupTableFULL:		VLAN���Ѿ��������ܴ���
 ** Created by:				Wang changrong
 ** Created date:			2010-12-27
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::CreateVLANGroup(uint32 uiVID) {
//	rtl8306e_vlan_entry_set(0, 1, 0x3F, 0);
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			DeleteVLANGroup
 ** Descriptions:			ɾ��VLAN��
 ** input parameters:		uiVID��		��Ҫɾ����VLAN���ID��ȡֵ��ΧΪ0---4095
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  			�����������
 **							CErrorValueDefine::uiConstRuturnVLANGroupInvalid:			VLAN�鲻����
 ** Created by:				Wang ying
 ** Created date:			2011-1-7
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::DeleteVLANGroup(uint32 uiVID) {
	if (uiVID > 4095) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	rtk_vlan_destroy(uiVID);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			AddPortMemberToVLANGroup
 ** Descriptions:			���VLAN���Ա
 ** input parameters:		uiVID��		VLAN���ID��ȡֵ��ΧΪ0---4095
 **							uiPort��	VLAN���Ա�˿ڵ�ID
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstRuturnInputDataNotSupported:	��֧�ֵ��������ֵ
 **							CErrorValueDefine::uiConstRuturnVLANGroupInvalid:			VLAN�鲻����
 ** Created by:				Wang ying
 ** Created date:			2011-1-7
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::AddPortMemberToVLANGroup(uint32 uiVID, uint32 uiPort) {
	if (uiVID > RTL8306E_VLAN_MAXID || uiPort > 5) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}

	rtk_portmask_t mbrmsk_val;
	mbrmsk_val.bits[0] = 0;
	rtk_portmask_t untagmsk_val;
	untagmsk_val.bits[0] = 0;
	uint32 fid_val = 0;
	if (rtk_vlan_get(uiVID, &mbrmsk_val, &untagmsk_val, &fid_val)
			== RT_ERR_OK) {
		mbrmsk_val.bits[0] |= (1 << uiPort);	//ָ���˿ڼ���ָ����
		mbrmsk_val.bits[0] |= (1 << 5);			//WAN��ͬʱ����ָ����
		if (rtk_vlan_set(uiVID, mbrmsk_val, untagmsk_val, fid_val)
				!= RT_ERR_OK) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
	} else {
		mbrmsk_val.bits[0] |= (1 << uiPort);
		mbrmsk_val.bits[0] |= (1 << 5);
		untagmsk_val.bits[0] = 0;
		if (rtk_vlan_set(uiVID, mbrmsk_val, untagmsk_val, fid_val)
				!= RT_ERR_OK) {
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}

	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			DeletePortMemberFromVLANGroup
 ** Descriptions:			ɾ��VLAN���Ա
 ** input parameters:		uiVID��		VLAN���ID��ȡֵ��ΧΪ0---4095
 **							uiPort��	VLAN���Ա�˿ڵ�ID
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				zhangcong
 ** Created date:			2011-11-7
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::DeletePortMemberFromVLANGroup(uint32 uiVID,
		uint32 uiPort) {
	if ((uiVID > RTL8306E_VLAN_MAXID) || (uiPort > RTL8306E_Port_MAXID)) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;//�������Խ�磬�򷵻�FAILED
	}

	rtk_portmask_t mbrmsk_val;
	rtk_portmask_t untagmsk_val;
	uint32 fid_val;

	rtk_vlan_get(uiVID, &mbrmsk_val, &untagmsk_val, &fid_val);
	mbrmsk_val.bits[0] &= ~(1 << uiPort);
	rtk_vlan_set(uiVID, mbrmsk_val, untagmsk_val, fid_val);
	if ((mbrmsk_val.bits[0] & 0x0F) == 0) {
		rtk_vlan_destroy(uiVID);
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetPortVID
 ** Descriptions:			���ö˿ڵ�PVID
 ** input parameters:		uiPort��	�˿ڵ�ID
 **							uiPVID��	�˿ڵ�PVID��ȡֵ��ΧΪ0---4095
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 				����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-7
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetPortVID(uint32 uiPort, uint32 uiPVID) {
	if ((uiPVID > RTL8306E_VLAN_MAXID) || (uiPort > RTL8306E_Port_MAXID)) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;//�������Խ�磬�򷵻�FAILED
	}
//	rtk_vlan_portPvid_set(uiPort, 0, 0);
	rtk_vlan_portPvid_set(uiPort, uiPVID, 0);		   //rtk_pri_t priority
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetVLANTaggingMode
 ** Descriptions:			���ö˿ڶ�Tag�Ĵ���ģʽ�����롢�Ƴ�Tag�ȣ�
 ** input parameters:		uiPort��	�˿ڵ�ID
 **							uiMode��	�˿ڶ�Tag�Ĵ���ģʽ��������ȡֵΪ
 **										CSwitchBaseImpl::uiConstTaggingModeNone				�������Ҳ��Ƴ�Tag��
 **										CSwitchBaseImpl::uiConstTaggingModeInsert			ֻ�����Ҳ��Ƴ�Tag��
 **										CSwitchBaseImpl::uiConstTaggingModeRemove			��������ֻ�Ƴ�Tag��
 **										CSwitchBaseImpl::uiConstTaggingModeInsertAndRemove	�����������Ƴ�Tag��
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstRuturnInputDataNotSupported:	��֧�ֵ��������ֵ
 ** Created by:				zhangcong
 ** Created date:			2011-11-7
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetVLANTaggingMode(uint32 uiVid, uint32 uiPort,
		uint32 uiMode) {
	rtk_portmask_t mbrmsk_val;
	rtk_portmask_t untagmsk_val;
	uint32 fid_val;
	switch (uiMode) {
	case CSwitchBaseImpl::uiConstTaggingModeNone: {
		rtl8306e_vlan_tagInsert_set(uiPort, 0x00);
		if (rtk_vlan_get(uiVid, &mbrmsk_val, &untagmsk_val, &fid_val)
				== RT_ERR_OK) {
			untagmsk_val.bits[0] &= ~(1 << uiPort);
			if (rtk_vlan_set(uiVid, mbrmsk_val, untagmsk_val, fid_val)
					== RT_ERR_OK) {
				return CErrorValueDefine::uiConstReturnSuccess;
			}
		}
		break;
	}
	case CSwitchBaseImpl::uiConstTaggingModeInsert: {
		rtl8306e_vlan_tagInsert_set(uiPort, 0x3F);
		if (rtk_vlan_get(uiVid, &mbrmsk_val, &untagmsk_val, &fid_val)
				== RT_ERR_OK) {
			untagmsk_val.bits[0] &= ~(1 << uiPort);
			if (rtk_vlan_set(uiVid, mbrmsk_val, untagmsk_val, fid_val)
					== RT_ERR_OK) {
				return CErrorValueDefine::uiConstReturnSuccess;
			}
		}
		break;
	}
	case CSwitchBaseImpl::uiConstTaggingModeRemove: {
		rtl8306e_vlan_tagInsert_set(uiPort, 0x00);
		if (rtk_vlan_get(uiVid, &mbrmsk_val, &untagmsk_val, &fid_val)
				== RT_ERR_OK) {
			untagmsk_val.bits[0] |= (1 << uiPort);
			if (rtk_vlan_set(uiVid, mbrmsk_val, untagmsk_val, fid_val)
					== RT_ERR_OK) {
				return CErrorValueDefine::uiConstReturnSuccess;
			}
		}
		break;
	}
	case CSwitchBaseImpl::uiConstTaggingModeInsertAndRemove: {
		rtl8306e_vlan_tagInsert_set(uiPort, 0x3F);
		if (rtk_vlan_get(uiVid, &mbrmsk_val, &untagmsk_val, &fid_val)
				== RT_ERR_OK) {
			untagmsk_val.bits[0] |= (1 << uiPort);
			if (rtk_vlan_set(uiVid, mbrmsk_val, untagmsk_val, fid_val)
					== RT_ERR_OK) {
				return CErrorValueDefine::uiConstReturnSuccess;
			}
		}
		break;
	}
	default:
		return CErrorValueDefine::uiConstReturnFailed;

	}

	return CErrorValueDefine::uiConstReturnFailed;
}

/**********************************************************************************************************************
 ** Function name:			SetPortAcceptFrameType
 ** Descriptions:			���ö˿�����ͨ���ĸ�ʽ
 ** input parameters:		uiPort��	�˿ڵ�ID
 **							uiMode��	�˿�ģʽ 1Ϊ ��Tag�Ͳ���Tag������ͨ��
 2Ϊ ��Tag����ͨ��
 **												 3Ϊ ����Tag����ͨ��
 ** output parameters:		None
 ** Returned value:
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 CErrorValueDefine::uiConstReturnSuccess                     ����ִ�гɹ�
 ** Created by:				zhangcong
 ** Created date:			2011-11-7
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetPortAcceptFrameType(uint32 uiPort, uint32 uiMode) {
	switch (uiMode) {
	case 1:	//��Tag�Ͳ���Tag������ͨ��
		rtk_vlan_portAcceptFrameType_set(uiPort, ACCEPT_FRAME_TYPE_ALL);
		break;
	case 2:		//��Tag����ͨ��
		rtk_vlan_portAcceptFrameType_set(uiPort, ACCEPT_FRAME_TYPE_TAG_ONLY);
		break;
	case 3:	  	//����Tag����ͨ��
		rtk_vlan_portAcceptFrameType_set(uiPort, ACCEPT_FRAME_TYPE_UNTAG_ONLY);
		break;
	default:
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   �˿�ͳ�Ƽ���   */
/**********************************************************************************************************************
 ** Function name:			SetCounterMode
 ** Descriptions:			������̫�����ֽ�/��������ʽ	(��֧���ֽڷ�ʽ�Ͱ���ʽ)
 ** input parameters:		uiByte��	�ֽ�/��������ʽ����ȡֵΪ
 **										CSwitchBaseImpl::uiConstCounterModeByte		ͳ�Ƽ��������ֽڷ�ʽ
 **										CSwitchBaseImpl::uiConstCounterModePackage	ͳ�Ƽ������ð���ʽ
 **										CSwitchBaseImpl::uiConstCounterModeBit		ͳ�Ƽ������ñ��ط�ʽ
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetCounterMode(uint32 uiMode) {
	if (uiMode > uiConstCounterModeBit) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	for (uint32 i = 0; i < 6/*GetEthernetPortNumber()*/; i++) {
		for (uint32 j = 0; j <= RTL8306_MIB_CNT5; j++) {
			rtl8306e_mibUnit_set(i, j, uiMode);
		}
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetRxCounter
 ** Descriptions:			��ö˿���̫���ݽ��ռ���
 ** input parameters:		uiPort��	�˿ڵ�ID
 ** output parameters:		uipValue��		����ֵ
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetRxCounter(uint32 uiPort, uint32 *uipValue) {
	if (uipValue == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 RxCounterValue = 0;
	rtl8306e_mib_get(uiPort, RTL8306_MIB_CNT2, &RxCounterValue);

	*uipValue = RxCounterValue - ClearRxCountValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetTxCounter
 ** Descriptions:			��ö˿���̫���ݷ��ͼ���
 ** input parameters:		uiPort��	�˿ڵ�ID
 ** output parameters:		uipValue��		����ֵ
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetTxCounter(uint32 uiPort, uint32 *uipValue) {
	if (uipValue == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 TxCounterValue = 0;
	rtl8306e_mib_get(uiPort, RTL8306_MIB_CNT1, &TxCounterValue);
	*uipValue = TxCounterValue - ClearTxCountValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetDropCounter
 ** Descriptions:			��ö˿���̫���ݶ�������
 ** input parameters:		uiPort��	�˿ڵ�ID
 ** output parameters:		uipValue��		����ֵ
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetDropCounter(uint32 uiPort, uint32 *uipValue) {
	if (uipValue == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 DropCounterValue = 0;
	rtl8306e_mib_get(uiPort, RTL8306_MIB_CNT3, &DropCounterValue);
	*uipValue = DropCounterValue - ClearDropCountValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetRxCounterNoClear
 ** Descriptions:			��ö˿���̫���ݽ��ռ�����������
 ** input parameters:		uiPort��	�˿ڵ�ID
 ** output parameters:		uipValue��		����ֵ
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetRxCounterNoClear(uint32 uiPort, uint32 *uipValue) {
	if (uipValue == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 RxCounerNoClearValue = 0;
	rtl8306e_mib_get(uiPort, RTL8306_MIB_CNT2, &RxCounerNoClearValue);
	*uipValue = RxCounerNoClearValue;
	ClearRxCountValue = RxCounerNoClearValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetTxCounterNoClear
 ** Descriptions:			��ö˿���̫���ݷ��ͼ�����������
 ** input parameters:		uiPort��	�˿ڵ�ID
 ** output parameters:		uipValue��		����ֵ
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetTxCounterNoClear(uint32 uiPort, uint32 *uipValue) {
	if (uipValue == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 TxCounerNoClearValue = 0;
	rtl8306e_mib_get(uiPort, RTL8306_MIB_CNT1, &TxCounerNoClearValue);
	*uipValue = TxCounerNoClearValue;
	ClearTxCountValue = TxCounerNoClearValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetDropCounterNoClear
 ** Descriptions:			��ö˿���̫���ݶ���������������
 ** input parameters:		uiPort��	�˿ڵ�ID
 ** output parameters:		uipValue��		����ֵ
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetDropCounterNoClear(uint32 uiPort, uint32 *uipValue) {
	if (uipValue == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 DropCounterNoClearValue = 0;
	rtl8306e_mib_get(uiPort, RTL8306_MIB_CNT3, &DropCounterNoClearValue);
	*uipValue = DropCounterNoClearValue;
	ClearDropCountValue = DropCounterNoClearValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}

uint32 RTL8306ESwitch::getCrcErrorCounterNoClear(uint32 port, uint32* value) {
	if (value == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 DropCounterNoClearValue = 0;
	rtl8306e_mib_get(port, RTL8306_MIB_CNT4, &DropCounterNoClearValue);
	*value = DropCounterNoClearValue;
	ClearDropCountValue = DropCounterNoClearValue;
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   �˿�ģʽ����  */
/**********************************************************************************************************************
 ** Function name:			SetEthernetPHY
 ** Descriptions:			���ö˿�ģʽ
 ** input parameters:		uiPort��		�˿ڵ�ID
 **							stpPHYMode��	�˿ڵĹ���ģʽ����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetEthernetPHY(uint32 uiPort,
		stPortEthernetPHY* stpPHYMode) {
	if (stpPHYMode == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	if (stpPHYMode->ucLinkSpeed == 0x01) {
		stpPHYMode->ucLinkSpeed = 100;
	} else if (stpPHYMode->ucLinkSpeed == 0) {
		stpPHYMode->ucLinkSpeed = 10;
	} else {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (rtl8306e_setEtherPhy(uiPort, stpPHYMode->ucANEnabled,
			stpPHYMode->ucCapability, stpPHYMode->ucLinkSpeed,
			stpPHYMode->ucFullDuplex) != TRUE) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetPortAlarmStatus
 ** Descriptions:			��ö˿ڸ澯״̬
 ** input parameters:		uiPort��		�˿ڵ�ID
 ** output parameters:		stpStatus��		�˿�״̬
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::GetPortAlarmStatus(uint32 uiPort,
		stPortAlarmStatus *stpStatus) {
	if (stpStatus == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	rtk_port_linkStatus_t LinkStat;
	rtk_port_speed_t SpeedStat;
	rtk_port_duplex_t DuplexStat;
	rtk_port_phyStatus_get(uiPort, &LinkStat, &SpeedStat, &DuplexStat);
	stpStatus->ucLinkDown = LinkStat;
	stpStatus->ucSpeedLow = !SpeedStat;
	stpStatus->ucHalfDuplex = !DuplexStat;

	uint32 AnDone = 0;
	uint32 LoopBack = 0;
	rtl8306e_getPhyAutoNegotiationDone(uiPort, &AnDone);
	stpStatus->ucANFailure = AnDone;
	rtl8306e_getPhyLoopback(uiPort, &LoopBack);
	stpStatus->ucLoopback = LoopBack;
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetPortPowerDown
 ** Descriptions:			���ö˿ڹض�ʹ��
 ** input parameters:		uiPort��		�˿ڵ�ID
 **							uiEnabled��		�˿ڹضϲ���������ȡֵΪ
 **											CSwitchBaseImpl::uiConstEnabled��	ʹ��
 **											CSwitchBaseImpl::uiConstDisabled��	��ʹ��
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetPortPowerDown(uint32 uiPort, uint32 uiEnabled) {
	if (uiPort > 4/*GetEthernetPortNumber()-1*/) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	RTL8306E_setPowerDown(uiPort, uiEnabled);
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   QoS����   */
/**********************************************************************************************************************
 ** Function name:			InitializeQoS
 ** Descriptions:			QoS��ʼ�����������ȼ����и���
 ** input parameters:		uiQueueNumber��		Qos���ȼ����и���
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::InitializeQoS(uint32 uiQueueNumber) {
	if (uiQueueNumber > 4) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	return rtk_qos_init(uiQueueNumber);
//	        rtl8306e_qos_priToQueMap_set(0, 0);
//            rtl8306e_qos_priToQueMap_set(1, 3);       
//            rtl8306e_qos_priToQueMap_set(2, 3);                   
//            rtl8306e_qos_priToQueMap_set(3, 3);                                           
//
//	rtk_qos_pri2queue_t PriToQueueId;
//	switch (uiQueueNumber)
//	{
//		case 1:			
//			PriToQueueId.pri2queue[0] = 0; 
//			PriToQueueId.pri2queue[1] = 0; 
//			PriToQueueId.pri2queue[2] = 0; 
//			PriToQueueId.pri2queue[3] = 0; 
//			break;
//		case 2:
//			PriToQueueId.pri2queue[0] = 0; 
//			PriToQueueId.pri2queue[1] = 1; 
//			PriToQueueId.pri2queue[2] = 1; 
//			PriToQueueId.pri2queue[3] = 1; 
//			break;
//		case 3:
//			PriToQueueId.pri2queue[0] = 0; 
//			PriToQueueId.pri2queue[1] = 1; 
//			PriToQueueId.pri2queue[2] = 1; 
//			PriToQueueId.pri2queue[3] = 2; 
//			break;
//		case 4:
//			PriToQueueId.pri2queue[0] = 0; 
//			PriToQueueId.pri2queue[1] = 1; 
//			PriToQueueId.pri2queue[2] = 2; 
//			PriToQueueId.pri2queue[3] = 3; 
//			break;
//		default:
//			break;
//	}    
//	rtk_qos_priMap_set(uiQueueNumber, &PriToQueueId);
//	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetPortRxBandWidth
 ** Descriptions:			�˿��շ����������
 ** input parameters:		uiPort��				�˿ڵ�ID
 **							uiBandWidth��			�˿ڵĴ������ã�ÿ��1����64Kbps����ֵ10����640Kbps����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				zhangcong
 ** Created date:			2011-11-14
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetPortRxBandWidth(uint32 uiPort, uint32 uiBandWidth) {
	if (uiBandWidth > BandWitchMaxNum) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	if (uiBandWidth == 0) {						  //0Ϊ ������100M
		uiBandWidth = RTL8306_QOS_RATE_INPUT_MAX;
	}
	if (rtk_rate_igrBandwidthCtrlRate_set(uiPort, uiBandWidth, DISABLED)
			!= RT_ERR_OK) {
		return CErrorValueDefine::uiConstReturnFailed;
	}	//enabled 
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetPortTxBandWidth
 ** Descriptions:			�˿ڷ������������
 ** input parameters:		uiPort��				�˿ڵ�ID
 **							uiBandWidth��			�˿ڵĴ������ã�ÿ��1����64Kbps����ֵ10����640Kbps����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				zhangcong
 ** Created date:			2011-11-14
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetPortTxBandWidth(uint32 uiPort, uint32 uiBandWidth) {
	if (uiBandWidth > BandWitchMaxNum) {
		return CErrorValueDefine::uiConstReturnFailed;		   //0Ϊ ������100M
	}
	if (uiBandWidth == 0) {
		uiBandWidth = RTL8306_QOS_RATE_INPUT_MAX;
	}
	if (rtk_rate_egrBandwidthCtrlRate_set(uiPort, uiBandWidth, DISABLED)
			!= RT_ERR_OK) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetQoSPrioritySelection
 ** Descriptions:			����QoS�Ĳ�ͬ�������ȼ��ȽϹ�ϵ
 ** input parameters:		stpSelection��		QoS��ͬ�������ȼ��Ĺ�ϵ����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  			�����������
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			������ָ�����
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetQoSPrioritySelection(
		stQosPrioritySelection* stpSelection) {
	if (stpSelection == 0) {
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	rtk_priority_select_t PrioritySelection = { 0 };
	PrioritySelection.dot1q_pri = MinPriInPrioritySelection;
	PrioritySelection.dscp_pri = MinPriInPrioritySelection;
	PrioritySelection.port_pri = MinPriInPrioritySelection;
	PrioritySelection.vid_pri = MinPriInPrioritySelection;
	if (stpSelection->ucDot1QEnabled != 0) {
		PrioritySelection.dot1q_pri = MaxPriInPrioritySelection;
		for (uint32 i = 0; i < 6; i++) {
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_1QBP_PRIO, 1);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_DSCP_PRIO, 0);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_PBP_PRIO, 0);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_CPUTAG_PRIO, 0);

			rtl8306e_qos_1pRemarkEnable_set(i, DISABLED);
		}
	}
	if (stpSelection->ucDSCPEnabled != 0) {
		PrioritySelection.dscp_pri = MaxPriInPrioritySelection;
		for (uint32 i = 0; i < 6; i++) {
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_DSCP_PRIO, 1);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_1QBP_PRIO, 0);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_PBP_PRIO, 0);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_CPUTAG_PRIO, 0);

			rtl8306e_qos_1pRemarkEnable_set(i, DISABLED);
		}
	}
	if (stpSelection->ucPortEnabled != 0) {
		PrioritySelection.port_pri = MaxPriInPrioritySelection;
		for (uint32 i = 0; i < 6; i++) {
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_PBP_PRIO, 1);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_DSCP_PRIO, 0);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_1QBP_PRIO, 0);
			rtl8306e_qos_priSrcEnable_set(i, RTL8306_CPUTAG_PRIO, 0);

			rtl8306e_qos_1pRemarkEnable_set(i, DISABLED);
		}
	}
	if (stpSelection->ucVIDEnabled != 0) {
		PrioritySelection.vid_pri = MaxPriInPrioritySelection;
	}

	if (rtk_qos_priSel_set(&PrioritySelection) != RT_ERR_OK) {
		return CErrorValueDefine::uiConstReturnFailed;
	}

	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetPortPriority
 ** Descriptions:			���ö˿����ȼ�
 ** input parameters:		uiPort��				�˿ڵ�ID
 **							uiPriority��			�˿ڵ����ȼ�����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetPortPriority(uint32 uiPort, uint32 uiPriority) {
	if (uiPriority > 3) {
		return CErrorValueDefine::uiConstReturnInputDataInvalid;
	}
	if (rtk_qos_portPri_set(uiPort, uiPriority) != RT_ERR_OK) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetDSCPPriority
 ** Descriptions:			����DSCP���ȼ�
 ** input parameters:		uiDSCPType��			DSCP���ȼ�����ֵ
 **							uiPriority��			���ȼ�����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-1-11
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetDSCPPriority(uint32 uiDSCPType, uint32 uiPriority) {
	if (rtk_qos_dscpPriRemap_set(uiDSCPType, uiPriority) != TRUE) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			GetSwitchChipID
 ** Descriptions:			����802.1Q���ȼ�
 ** input parameters:		uiDot1QType��			802.1Q���ȼ�����ֵ
 **							uiPriority��			���ȼ�����
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang changrong
 ** Created date:			2010-12-27
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetDot1QPriority(uint32 uiDot1QType, uint32 uiPriority) {
	if (rtk_qos_1pPriRemap_set(uiDot1QType, uiPriority) != RT_ERR_OK) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			SetQosWrr
 ** Descriptions:			�������ȼ�Ȩ��
 ** input parameters:		mode  ģʽ��0 �ϸ����ȼ���1 1:1�� 2 1:4��3 1:8��
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					����ִ�гɹ�
 **							CErrorValueDefine::uiConstReturnFailed: 					����ִ��ʧ��
 **							CErrorValueDefine::uiConstRuturnNotSupported:				��֧�ֵĹ���
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		�����������
 ** Created by:				Wang ying
 ** Created date:			2011-3-2
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Descriptions:
 **
 **********************************************************************************************************************/
uint32 RTL8306ESwitch::SetQosWrr(uint8 mode) {
	rtl8306e_qosSchPara_t WRRQuConfig;
	rtl8306e_qos_schedulingPara_get(1, &WRRQuConfig);
	switch (mode) {
	case 0:
		WRRQuConfig.q0_wt = 1;
		WRRQuConfig.q1_wt = 1;
		WRRQuConfig.q2_wt = 1;
		WRRQuConfig.q3_wt = 1;
		break;
	case 1:
		WRRQuConfig.q0_wt = 1;
		WRRQuConfig.q1_wt = 1;
		WRRQuConfig.q2_wt = 1;
		WRRQuConfig.q3_wt = 1;
		break;
	case 2:
		WRRQuConfig.q0_wt = 1;
		WRRQuConfig.q1_wt = 4;
		WRRQuConfig.q2_wt = 1;
		WRRQuConfig.q3_wt = 1;
		break;
	case 3:
		WRRQuConfig.q0_wt = 1;
		WRRQuConfig.q1_wt = 8;
		WRRQuConfig.q2_wt = 1;
		WRRQuConfig.q3_wt = 1;
		break;
	default:
		break;
	}
//	WRRQuConfig.q2_n64Kbps = BandWitchMaxNum;
//    WRRQuConfig.q3_n64Kbps = BandWitchMaxNum; 
	if (RTL8306EWRRConfig(WRRQuConfig) != TRUE) {
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

#endif
