#ifndef __RTK_API_EXT_H__
#define __RTK_API_EXT_H__

#ifdef __cplusplus
   extern "C" {
#endif

#include <rtk_api.h>

   #define RTL8306E_VLAN_MAXID    4095
#define RTL8306E_Port_MAXID    5



uint32 rtk_getOUIID (uint8 Phy, uint16 *oui );
void RTL8306E_HardWareReset(void);
/*******************************函数说明******************************************/
uint32 rtk_switch_init(void);
uint32 rtk_switch_maxPktLen_set(uint32 len); 
uint32 rtk_switch_maxPktLen_get(rtk_switch_maxPktLen_t *pLen);
int32 rtk_port_phyReg_set(rtk_port_t port, rtk_port_phy_reg_t reg, uint32 value);
int32 rtk_port_phyReg_get(rtk_port_t port, rtk_port_phy_reg_t reg, uint16 *pData); 
uint32 rtk_port_phyAutoNegoAbility_set(rtk_port_t port, rtk_port_phy_ability_t *pAbility);
uint32 rtk_port_phyAutoNegoAbility_get(rtk_port_t port, rtk_port_phy_ability_t *pAbility);
uint32 rtk_port_phyForceModeAbility_set(rtk_port_t port, rtk_port_phy_ability_t *pAbility);
uint32 rtk_port_phyForceModeAbility_get(rtk_port_t port, rtk_port_phy_ability_t *pAbility);
uint32 rtk_port_phyStatus_get(rtk_port_t port, rtk_port_linkStatus_t *pLinkStatus, rtk_port_speed_t *pSpeed, rtk_port_duplex_t *pDuplex);
uint32 rtk_port_macForceLinkExt0_set(rtk_mode_ext_t mode, rtk_port_mac_ability_t *pPortability);
uint32 rtk_port_macForceLinkExt0_get(rtk_mode_ext_t *pMode, rtk_port_mac_ability_t *pPortability);
uint32 rtk_port_isolation_set(rtk_port_t port, rtk_portmask_t portmask);
uint32 rtk_port_isolation_get(rtk_port_t port, rtk_portmask_t *pPortmask);
uint32 rtk_stat_port_reset(rtk_port_t port);
uint32 rtk_rate_igrBandwidthCtrlRate_set( rtk_port_t port, rtk_rate_t rate,  rtk_enable_t ifg_include);
uint32 rtk_rate_igrBandwidthCtrlRate_get(rtk_port_t port, rtk_rate_t *pRate, rtk_enable_t *pIfg_include);
uint32 rtk_rate_egrBandwidthCtrlRate_set(rtk_port_t port, rtk_rate_t rate,  rtk_enable_t ifg_include);
uint32 rtk_rate_egrBandwidthCtrlRate_get(rtk_port_t port, rtk_rate_t *pRate, rtk_enable_t *pIfg_include);


uint32 rtl8306e_setEtherPhy(uint32 phy, uint32 autoNegotiation, uint32 advCapability, uint32 speed, uint32 fullDuplex);
uint32 rtl8306e_getPhyLoopback(uint32 phy, uint32 *pEnabled);
uint32 rtl8306e_getPhyAutoNegotiationDone(uint32 phy, uint32 *pDone);

/****************************  QOS  *********************************************/
/*	  QoS（Quality of Service）服务质量，是网络的一种安全机制, 是用来解决网络延迟和阻塞等问题的一种技术。 
  在正常情况下，如果网络只用于特定的无时间限制的应用系统，并不需要QoS，比如Web应用，或E-mail设置等。
  但是对关键应用和多媒体应用就十分必要。当网络过载或拥塞时，QoS 能确保重要业务量不受延迟或丢弃，同时保证网络的高效运行。

*/
uint32 rtk_qos_init(rtk_queue_num_t queueNum);
uint32 rtk_qos_1pPriRemap_set(rtk_pri_t dot1p_pri, rtk_pri_t int_pri);
uint32 rtk_qos_priSel_set(rtk_priority_select_t *pPriDec);
uint32 rtk_qos_priSel_get(rtk_priority_select_t *pPriDec);
uint32 rtk_qos_1pPriRemap_get(rtk_pri_t dot1p_pri, rtk_pri_t *pInt_pri);
int32 rtk_qos_dscpPriRemap_set(uint32 dscp, rtk_pri_t int_pri);
int32 rtk_qos_dscpPriRemap_get(uint32 dscp, rtk_pri_t *pInt_pri);
uint32 rtk_qos_portPri_set(rtk_port_t port, rtk_pri_t int_pri) ;
uint32 rtk_qos_portPri_get(rtk_port_t port, rtk_pri_t *pInt_pri) ;
int32 rtk_qos_priMap_set(rtk_queue_num_t queue_num, rtk_qos_pri2queue_t *pPri2qid);
int32 rtk_qos_priMap_get(rtk_queue_num_t queue_num, rtk_qos_pri2queue_t *pPri2qid);
int32 rtk_qos_1pRemarkEnable_set(rtk_port_t port, rtk_enable_t enable); 
int32 rtk_qos_1pRemarkEnable_get(rtk_port_t port, rtk_enable_t *pEnable);
int32 rtk_qos_1pRemark_set(rtk_pri_t int_pri, rtk_pri_t dot1p_pri);
int32 rtk_qos_1pRemark_get(rtk_pri_t int_pri, rtk_pri_t *pDot1p_pri);
int32 rtk_trap_unknownMcastPktAction_set(rtk_port_t port, rtk_mcast_type_t type, rtk_trap_mcast_action_t mcast_action);
int32 rtk_trap_unknownMcastPktAction_get(rtk_port_t port, rtk_mcast_type_t type, rtk_trap_mcast_action_t *pMcast_action);
int32 rtk_trap_igmpCtrlPktAction_set(rtk_igmp_type_t type, rtk_trap_igmp_action_t igmp_action);
int32 rtk_trap_igmpCtrlPktAction_get(rtk_igmp_type_t type, rtk_trap_igmp_action_t *pIgmp_action);


/***************************  VLAN  ***********************************************/
uint32 rtl_VLANEnable_set(uint32 enabled);

uint32 rtk_vlan_init(void);
uint32 rtk_vlan_set(rtk_vlan_t vid, rtk_portmask_t mbrmsk, rtk_portmask_t untagmsk, uint32 fid);
uint32 rtk_vlan_get(rtk_vlan_t vid, rtk_portmask_t *pMbrmsk, rtk_portmask_t *pUntagmsk, uint32 *pFid);
uint32 rtk_vlan_destroy(rtk_vlan_t vid);	  //delete vid
uint32 rtk_vlan_portPvid_set(rtk_port_t port, rtk_vlan_t pvid, rtk_pri_t priority);
int32 rtk_vlan_portPvid_get(rtk_port_t port, rtk_vlan_t *pPvid, rtk_pri_t *pPriority);
int32 rtk_vlan_portIgrFilterEnable_set(rtk_port_t port, rtk_enable_t igr_filter);
int32 rtk_vlan_portIgrFilterEnable_get(rtk_port_t port, rtk_enable_t *pIgr_filter);
uint32 rtk_vlan_portAcceptFrameType_set(rtk_port_t port, rtk_vlan_acceptFrameType_t accept_frame_type);
uint32 rtk_vlan_portAcceptFrameType_get(rtk_port_t port, rtk_vlan_acceptFrameType_t *pAccept_frame_type);
uint32 rtk_vlan_vlanBasedPriority_set(rtk_vlan_t vid, rtk_pri_t priority);
uint32 rtk_vlan_vlanBasedPriority_get(rtk_vlan_t vid, rtk_pri_t *pPriority);
uint32 rtk_vlan_vidTranslation_set(rtk_vlan_t vid, rtk_vlan_t nvid);
uint32 rtk_vlan_vidTranslation_get(rtk_vlan_t vid, rtk_vlan_t *pNvid);
uint32 rtk_vlan_vidTranslationEnable_set(rtk_enable_t enable, rtk_portmask_t nniMask);
uint32 rtk_vlan_vidTranslationEnable_get(rtk_enable_t *pEnable, rtk_portmask_t *pNniMask);
uint32 rtk_vlan_tagSrc_set(rtk_port_t port, rtk_vidSrc_t vidSrc, rtk_priSrc_t priSrc);
uint32 rtk_vlan_tagSrc_get(rtk_port_t port, rtk_vidSrc_t *pVidSrc, rtk_priSrc_t *pPriSrc);    



/******************************  Spanning Tree  ****************************************/
/*    Spanning Tree Group (STG)会检测并清除桥接或交换网络中的逻辑回路。
      STG会强制冗余数据路径进入standby (blocked)状态。当存在多路径时，Spanning Tree会让switch只用最快捷的路径。
  若那条路径失败，则自动切换到另一条路径。
	 由于Spanning Tree的监听，学习，和转发或封锁，可能会产生延迟。
  可以用Port Fast Forwarding (/cfg/port x/fastfwd/ena)来允许属于Spanning Tree的端口绕过监听和学习状态，直接进入
  转发状态。 在转发状态中，端口通过监听BPDU来检查是否有回路，若有，则进入封锁模式。此功能可使GbE Switch Module在
  快速Spanning Tree网络中运转*/
uint32 rtk_stp_mstpState_set(rtk_stp_msti_id_t msti, rtk_port_t port, rtk_stp_state_t stp_state);
uint32 rtk_stp_mstpState_get(rtk_stp_msti_id_t msti, rtk_port_t port, rtk_stp_state_t *pStp_state);

/******************************  LUT  **************************************************/
int32 rtk_l2_addr_add(rtk_mac_t *pMac, rtk_l2_ucastAddr_t *pL2_data);
int32 rtk_l2_addr_get(rtk_mac_t *pMac, uint32 fid, rtk_l2_ucastAddr_t *pL2_data);
int32 rtk_l2_addr_del(rtk_mac_t *pMac, uint32 fid); 
int32 rtk_l2_mcastAddr_add(rtk_mac_t *pMac, uint32 fid, rtk_portmask_t portmask);
int32 rtk_l2_mcastAddr_get(rtk_mac_t *pMac, uint32 fid, rtk_portmask_t *pPortmask);
int32 rtk_l2_mcastAddr_del(rtk_mac_t *pMac, uint32 fid);    
uint32 rtk_l2_limitLearningCnt_set(rtk_port_t port, rtk_mac_cnt_t mac_cnt);
uint32 rtk_l2_limitLearningCnt_get(rtk_port_t port, rtk_mac_cnt_t *pMac_cnt);
uint32 rtk_l2_limitLearningCntAction_set(rtk_port_t port, rtk_l2_limitLearnCntAction_t action);
int32 rtk_l2_limitLearningCntAction_get(rtk_port_t port, rtk_l2_limitLearnCntAction_t *pAction);
uint32 rtk_l2_learningCnt_get(rtk_port_t port, rtk_mac_cnt_t *pMac_cnt);

/******************************  CPU Port  *********************************************/
uint32 rtk_cpu_enable_set(rtk_enable_t enable);
int32 rtk_cpu_enable_get(rtk_enable_t *pEnable);
int32 rtk_cpu_tagPort_set(rtk_port_t port, rtk_cpu_insert_t mode);
int32 rtk_cpu_tagPort_get(rtk_port_t *pPort, rtk_cpu_insert_t *pMode);

/******************************  Port Mirror端口镜像  **********************************/
uint32 rtk_mirror_portBased_set(rtk_port_t mirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask);
uint32 rtk_mirror_portBased_get(rtk_port_t* pMirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask);

/******************************  802.1X  ***********************************************/
/*	802.1x协议是基于Client/Server的访问控制和认证协议。它可以限制未经授权的用户/设备通过接入端口
(access port)访问LAN/WLAN。在获得交换机或LAN提供的各种业务之前，802.1x对连接到交换机端口上的
用户/设备进行认证。在认证通过之前，802.1x只允许EAPoL（基于局域网的扩展认证协议）数据通过设备连接的
交换机端口；认证通过以后，正常的数据可以顺利地通过以太网端口。
*/
uint32 rtk_dot1x_unauthPacketOper_set(rtk_port_t port, rtk_dot1x_unauth_action_t unauth_action);
int32 rtk_dot1x_unauthPacketOper_get(rtk_port_t port, rtk_dot1x_unauth_action_t *pUnauth_action);
int32 rtk_dot1x_portBasedEnable_set(rtk_port_t port, rtk_enable_t enable);
int32 rtk_dot1x_portBasedEnable_get(rtk_port_t port, rtk_enable_t *pEnable);
int32 rtk_dot1x_portBasedAuthStatus_set(rtk_port_t port, rtk_dot1x_auth_status_t port_auth);
int32 rtk_dot1x_portBasedAuthStatus_get(rtk_port_t port, rtk_dot1x_auth_status_t *pPort_auth);
int32 rtk_dot1x_portBasedDirection_set(rtk_port_t port, rtk_dot1x_direction_t port_direction);
int32 rtk_dot1x_portBasedDirection_get(rtk_port_t port, rtk_dot1x_direction_t *pPort_direction);
int32 rtk_dot1x_macBasedEnable_set(rtk_port_t port, rtk_enable_t enable);
int32 rtk_dot1x_macBasedEnable_get(rtk_port_t port, rtk_enable_t *pEnable);
uint32 rtk_dot1x_macBasedDirection_set(rtk_dot1x_direction_t mac_direction);
int32 rtk_dot1x_macBasedDirection_get(rtk_dot1x_direction_t *pMac_direction);
int32 rtk_dot1x_macBasedAuthMac_add(rtk_port_t port, rtk_mac_t *pAuth_mac, uint32 fid);
int32 rtk_dot1x_macBasedAuthMac_del(rtk_port_t port, rtk_mac_t *pAuth_mac, uint32 fid);

/*****************************  SVLAN QINQ  ************************************************/
/*	  QinQ技术〔也称Stacked VLAN 或Double VLAN〕。标准出自IEEE 802.1ad,其实现将用户私网VLAN Tag封装
  在公网VLAN Tag中，使报文带着两层VLAN Tag穿越运营商的骨干网络（公网）。
  QinQ技术通过在以太帧中堆叠两个802.1Q包头，有效地扩展了VLAN数目，使  QinQ
	  VLAN的数目最多可达4096x4096个。同时，多个VLAN能够被复用到一个核心VLAN中。MSP通常为每个客户建立
  一个VLAN模型，用通用属性注册协议/通用VLAN注册协议（GARP/GVRP）自动监控整个主干网络的VLAN，并通过扩
  展生成树协议（STP）来加快网络收敛速度，从而为网络提供弹性。QinQ技术作为初始的解决方案是不错的，但
  随着用户数量的增加，SVLAN模型也会带来可扩展性的问题。因为有些用户可能希望在分支机构间进行数据传输时
  可以携带自己的VLAN ID，这就使采用QinQ技术的MSP面临以下两个问题：
  	第一，第一名客户的VLAN标识可能与其他客户冲突；
	第二，服务提供商将受到客户可使用标识数量的严重限制。如果允许用户按他们自己的方式使用各自的VLAN ID
		  空间，那么核心网络仍存在4096个VLAN的限制。
*/
uint32 rtk_svlan_init(void);
uint32 rtk_svlan_servicePort_add(rtk_port_t port);
uint32 rtk_svlan_servicePort_del(rtk_port_t port);
uint32 rtk_svlan_servicePort_get(rtk_portmask_t *pSvlan_portmask);
uint32 rtk_svlan_tpidEntry_set(rtk_svlan_tpid_t svlan_tag_id);
uint32 rtk_svlan_tpidEntry_get(rtk_svlan_tpid_t *pSvlan_tag_id);
uint32 rtk_svlan_portPvid_set(rtk_port_t port, rtk_vlan_t pvid, rtk_pri_t priority, rtk_dei_t dei);
uint32 rtk_svlan_portPvid_get(rtk_port_t port, rtk_vlan_t *pPvid, rtk_pri_t* pPriority, rtk_dei_t *pDei);

/*****************************  ACL  *******************************************************/
/*	  访问控制列表（Access Control List，ACL） 是路由器和交换机接口的指令列表，用来控制端口进出的数据包。
  ACL适用于所有的被路由协议，如IP、IPX、AppleTalk等。这张表中包含了匹配关系、条件和查询语句，表只是一个
  框架结构，其目的是为了对某种访问进行控制。
  	  信息点间通信，内外网络的通信都是企业网络中必不可少的业务需求，但是为了保证内网的安全性，需要通过
  安全策略来保障非授权用户只能访问特定的网络资源，从而达到对访问进行控制的目的。简而言之，ACL可以过滤
  网络中的流量，控制访问的一种网络技术手段。
	 ACL可以限制网络流量、提高网络性能。例如，ACL可以根据数据包的协议，指定数据包的优先级。ACL提供对通信
  流量的控制手段。例如，ACL可以限定或简化路由更新信息的长度，从而限制通过路由器某一网段的通信流量。ACL是
  提供网络安全访问的基本手段。ACL允许主机A访问人力资源网络，而拒绝主机B访问。ACL可以在路由器端口处决定哪
  种类型的通信流量被转发或被阻塞。例如，用户可以允许E-mail通信流量被路由，拒绝所有的Telnet通信流量。
*/
int32 rtk_filter_igrAcl_init(void);
int32 rtk_filter_igrAcl_rule_add(rtk_filter_rule_t *pRule);
int32 rtk_filter_igrAcl_rule_get(rtk_filter_rule_t *pRule);
int32 rtk_filter_igrAcl_rule_del(rtk_filter_rule_t *pRule);	

uint32 RTL8306EWRRConfig( rtl8306e_qosSchPara_t sch_para);

#ifdef __cplusplus
   }
#endif

#endif   /*__RTK_API_EXT_H__*/
