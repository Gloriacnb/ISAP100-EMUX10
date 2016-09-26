/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** Created by:				Wang Ying
 ** Created date:			2011-1-4
 ** Version:					1.0
 ** Descriptions:			RTL8306E交换芯片接口功能实现方法
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
 ** Descriptions:			构造函数
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
 ** Descriptions:			析构函数
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
 ** Descriptions:			芯片开电初始化
 ** input parameters:		uiConfig：		是否需要配置芯片标志,可取值为
 **											CSwitchBaseImpl::uiConstNeedConfigChip：需要配置芯片寄存器
 **											CSwitchBaseImpl::uiConstDontConfigChip：不需要配置芯片寄存器
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 				函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed:  				函数执行失败
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
//			 rtl8306e_mib_reset(i);										    //重启WAN口计数
//			 rtl8306e_mibUnit_set(i,RTL8306_MIB_CNT1,RTL8306_MIB_BYTE);		//设置WAN口发方向 字节计数
//			 rtl8306e_mibUnit_set(i,RTL8306_MIB_CNT2,RTL8306_MIB_BYTE);		//设置WAN口收方向 字节计数
//		}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/**********************************************************************************************************************
 ** Function name:			GetSwitchChipID
 ** Descriptions:			获得交换芯片ID
 ** input parameters:		None
 ** output parameters:		uipChipID：		交换芯片的ID
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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

/*   交换模式设置  */
/**********************************************************************************************************************
 ** Function name:			InitializeFullSwitchMode
 ** Descriptions:			全交换模式初始化
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
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
 ** Descriptions:			汇聚模式(隔离)初始化
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
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
		rtl8306e_portLearningAbility_set(i, 0); //关闭所有端口的学习功能，实现物理隔离
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			InitializeTagAwareMode
 ** Descriptions:			802.1Q模式初始化
 ** input parameters:		None
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
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
	rtl8306e_vlan_IgrFilterEnable_set(1); //设置入口过滤使能
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   交换芯片全局设置  */
/**********************************************************************************************************************
 ** Function name:			SetSwitchMaxPacketLength
 ** Descriptions:			设置最大包长
 ** input parameters:		uiLength：		最大包长配置，可取值为
 **											CSwitchBaseImpl::uiConstMaxPacketLength1518：最大包长1518
 **											CSwitchBaseImpl::uiConstMaxPacketLength1536：最大包长1536
 **											CSwitchBaseImpl::uiConstMaxPacketLength1552：最大包长1552
 **											CSwitchBaseImpl::uiConstMaxPacketLength1916：最大包长1916
 **											CSwitchBaseImpl::uiConstMaxPacketLength2047：最大包长2047

 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
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
 ** Descriptions:			设置广播风暴抑制使能
 ** input parameters:		uiEnabled：		广播风暴使能配置，可取值为
 **											CSwitchBaseImpl::uiConstEnabled：	使能 1
 **											CSwitchBaseImpl::uiConstDisabled：	不使能 0
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
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
 ** Descriptions:			设置流量控制使能
 ** input parameters:		uiEnabled：		流量控制使能配置，可取值为
 **											CSwitchBaseImpl::uiConstEnabled：	使能
 **											CSwitchBaseImpl::uiConstDisabled：	不使能
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 				函数执行成功
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
	//流量控制 为全局寄存器
//	for( uint32 i = 0; i < 6; i++){
	rtl8306e_qos_portFlcMode_set(port, uiEnabled);
//	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   VLAN设置  */
/**********************************************************************************************************************
 ** Function name:			CreateVLANGroup
 ** Descriptions:			创建VLAN组
 ** input parameters:		uiVID：		需要创建的VLAN组的ID，取值范围为0---4095
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstRuturnInputDataNotSupported:	不支持的输入参数值
 **							CErrorValueDefine::uiConstRuturnVLANGroupAlreadyExist:	VLAN组已经存在
 **							CErrorValueDefine::uiConstRuturnVLANGroupTableFULL:		VLAN组已经满，不能创建
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
 ** Descriptions:			删除VLAN组
 ** input parameters:		uiVID：		需要删除的VLAN组的ID，取值范围为0---4095
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  			参数输入错误
 **							CErrorValueDefine::uiConstRuturnVLANGroupInvalid:			VLAN组不存在
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
 ** Descriptions:			添加VLAN组成员
 ** input parameters:		uiVID：		VLAN组的ID，取值范围为0---4095
 **							uiPort：	VLAN组成员端口的ID
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstRuturnInputDataNotSupported:	不支持的输入参数值
 **							CErrorValueDefine::uiConstRuturnVLANGroupInvalid:			VLAN组不存在
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
		mbrmsk_val.bits[0] |= (1 << uiPort);	//指定端口加入指定组
		mbrmsk_val.bits[0] |= (1 << 5);			//WAN口同时加入指定组
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
 ** Descriptions:			删除VLAN组成员
 ** input parameters:		uiVID：		VLAN组的ID，取值范围为0---4095
 **							uiPort：	VLAN组成员端口的ID
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
		return CErrorValueDefine::uiConstReturnInputDataInvalid;//输入参数越界，则返回FAILED
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
 ** Descriptions:			设置端口的PVID
 ** input parameters:		uiPort：	端口的ID
 **							uiPVID：	端口的PVID，取值范围为0---4095
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 				函数执行成功
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
		return CErrorValueDefine::uiConstReturnInputDataInvalid;//输入参数越界，则返回FAILED
	}
//	rtk_vlan_portPvid_set(uiPort, 0, 0);
	rtk_vlan_portPvid_set(uiPort, uiPVID, 0);		   //rtk_pri_t priority
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
 ** Function name:			SetVLANTaggingMode
 ** Descriptions:			设置端口对Tag的处理模式（插入、移除Tag等）
 ** input parameters:		uiPort：	端口的ID
 **							uiMode：	端口对Tag的处理模式参数，可取值为
 **										CSwitchBaseImpl::uiConstTaggingModeNone				不插入且不移除Tag包
 **										CSwitchBaseImpl::uiConstTaggingModeInsert			只插入且不移除Tag包
 **										CSwitchBaseImpl::uiConstTaggingModeRemove			不插入且只移除Tag包
 **										CSwitchBaseImpl::uiConstTaggingModeInsertAndRemove	即插入且又移除Tag包
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstRuturnInputDataNotSupported:	不支持的输入参数值
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
 ** Descriptions:			设置端口允许通过的格式
 ** input parameters:		uiPort：	端口的ID
 **							uiMode：	端口模式 1为 带Tag和不带Tag都允许通过
 2为 带Tag允许通过
 **												 3为 不带Tag允许通过
 ** output parameters:		None
 ** Returned value:
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 CErrorValueDefine::uiConstReturnSuccess                     函数执行成功
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
	case 1:	//带Tag和不带Tag都允许通过
		rtk_vlan_portAcceptFrameType_set(uiPort, ACCEPT_FRAME_TYPE_ALL);
		break;
	case 2:		//带Tag允许通过
		rtk_vlan_portAcceptFrameType_set(uiPort, ACCEPT_FRAME_TYPE_TAG_ONLY);
		break;
	case 3:	  	//不带Tag允许通过
		rtk_vlan_portAcceptFrameType_set(uiPort, ACCEPT_FRAME_TYPE_UNTAG_ONLY);
		break;
	default:
		return CErrorValueDefine::uiConstReturnFailed;
	}
	return CErrorValueDefine::uiConstReturnSuccess;
}

/*   端口统计计数   */
/**********************************************************************************************************************
 ** Function name:			SetCounterMode
 ** Descriptions:			设置以太数据字节/包计数方式	(仅支持字节方式和包方式)
 ** input parameters:		uiByte：	字节/包计数方式，可取值为
 **										CSwitchBaseImpl::uiConstCounterModeByte		统计计数采用字节方式
 **										CSwitchBaseImpl::uiConstCounterModePackage	统计计数采用包方式
 **										CSwitchBaseImpl::uiConstCounterModeBit		统计计数采用比特方式
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
 ** Descriptions:			获得端口以太数据接收计数
 ** input parameters:		uiPort：	端口的ID
 ** output parameters:		uipValue：		计数值
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			获得端口以太数据发送计数
 ** input parameters:		uiPort：	端口的ID
 ** output parameters:		uipValue：		计数值
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			获得端口以太数据丢弃计数
 ** input parameters:		uiPort：	端口的ID
 ** output parameters:		uipValue：		计数值
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			获得端口以太数据接收计数，不清零
 ** input parameters:		uiPort：	端口的ID
 ** output parameters:		uipValue：		计数值
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			获得端口以太数据发送计数，不清零
 ** input parameters:		uiPort：	端口的ID
 ** output parameters:		uipValue：		计数值
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			获得端口以太数据丢弃计数，不清零
 ** input parameters:		uiPort：	端口的ID
 ** output parameters:		uipValue：		计数值
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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

/*   端口模式设置  */
/**********************************************************************************************************************
 ** Function name:			SetEthernetPHY
 ** Descriptions:			设置端口模式
 ** input parameters:		uiPort：		端口的ID
 **							stpPHYMode：	端口的工作模式配置
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			获得端口告警状态
 ** input parameters:		uiPort：		端口的ID
 ** output parameters:		stpStatus：		端口状态
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			设置端口关断使能
 ** input parameters:		uiPort：		端口的ID
 **							uiEnabled：		端口关断参数，，可取值为
 **											CSwitchBaseImpl::uiConstEnabled：	使能
 **											CSwitchBaseImpl::uiConstDisabled：	不使能
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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

/*   QoS配置   */
/**********************************************************************************************************************
 ** Function name:			InitializeQoS
 ** Descriptions:			QoS初始化，设置优先级队列个数
 ** input parameters:		uiQueueNumber：		Qos优先级队列个数
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
 ** Descriptions:			端口收方向带宽配置
 ** input parameters:		uiPort：				端口的ID
 **							uiBandWidth：			端口的带宽配置，每个1代表64Kbps。如值10代表640Kbps带宽
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
	if (uiBandWidth == 0) {						  //0为 最大带宽100M
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
 ** Descriptions:			端口发方向带宽配置
 ** input parameters:		uiPort：				端口的ID
 **							uiBandWidth：			端口的带宽配置，每个1代表64Kbps。如值10代表640Kbps带宽
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
		return CErrorValueDefine::uiConstReturnFailed;		   //0为 最大带宽100M
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
 ** Descriptions:			设置QoS的不同类型优先级比较关系
 ** input parameters:		stpSelection：		QoS不同类型优先级的关系配置
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  			参数输入错误
 **							CErrorValueDefine::uiConstReturnInputNULLPointer:			参数空指针错误
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
 ** Descriptions:			设置端口优先级
 ** input parameters:		uiPort：				端口的ID
 **							uiPriority：			端口的优先级配置
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
 ** Descriptions:			设置DSCP优先级
 ** input parameters:		uiDSCPType：			DSCP优先级类型值
 **							uiPriority：			优先级配置
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
 ** Descriptions:			设置802.1Q优先级
 ** input parameters:		uiDot1QType：			802.1Q优先级类型值
 **							uiPriority：			优先级配置
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
 ** Descriptions:			设置优先级权重
 ** input parameters:		mode  模式（0 严格优先级，1 1:1， 2 1:4，3 1:8）
 ** output parameters:		None
 ** Returned value:			CErrorValueDefine::uiConstReturnSuccess: 					函数执行成功
 **							CErrorValueDefine::uiConstReturnFailed: 					函数执行失败
 **							CErrorValueDefine::uiConstRuturnNotSupported:				不支持的功能
 **							CErrorValueDefine::uiConstReturnInputDataInvalid:  		参数输入错误
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
