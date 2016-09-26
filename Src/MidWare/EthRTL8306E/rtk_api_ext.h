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
/*******************************����˵��******************************************/
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
/*	  QoS��Quality of Service�������������������һ�ְ�ȫ����, ��������������ӳٺ������������һ�ּ����� 
  ����������£��������ֻ�����ض�����ʱ�����Ƶ�Ӧ��ϵͳ��������ҪQoS������WebӦ�ã���E-mail���õȡ�
  ���ǶԹؼ�Ӧ�úͶ�ý��Ӧ�þ�ʮ�ֱ�Ҫ����������ػ�ӵ��ʱ��QoS ��ȷ����Ҫҵ���������ӳٻ�����ͬʱ��֤����ĸ�Ч���С�

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
/*    Spanning Tree Group (STG)���Ⲣ����Žӻ򽻻������е��߼���·��
      STG��ǿ����������·������standby (blocked)״̬�������ڶ�·��ʱ��Spanning Tree����switchֻ�����ݵ�·����
  ������·��ʧ�ܣ����Զ��л�����һ��·����
	 ����Spanning Tree�ļ�����ѧϰ����ת������������ܻ�����ӳ١�
  ������Port Fast Forwarding (/cfg/port x/fastfwd/ena)����������Spanning Tree�Ķ˿��ƹ�������ѧϰ״̬��ֱ�ӽ���
  ת��״̬�� ��ת��״̬�У��˿�ͨ������BPDU������Ƿ��л�·�����У���������ģʽ���˹��ܿ�ʹGbE Switch Module��
  ����Spanning Tree��������ת*/
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

/******************************  Port Mirror�˿ھ���  **********************************/
uint32 rtk_mirror_portBased_set(rtk_port_t mirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask);
uint32 rtk_mirror_portBased_get(rtk_port_t* pMirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask);

/******************************  802.1X  ***********************************************/
/*	802.1xЭ���ǻ���Client/Server�ķ��ʿ��ƺ���֤Э�顣����������δ����Ȩ���û�/�豸ͨ������˿�
(access port)����LAN/WLAN���ڻ�ý�������LAN�ṩ�ĸ���ҵ��֮ǰ��802.1x�����ӵ��������˿��ϵ�
�û�/�豸������֤������֤ͨ��֮ǰ��802.1xֻ����EAPoL�����ھ���������չ��֤Э�飩����ͨ���豸���ӵ�
�������˿ڣ���֤ͨ���Ժ����������ݿ���˳����ͨ����̫���˿ڡ�
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
/*	  QinQ������Ҳ��Stacked VLAN ��Double VLAN������׼����IEEE 802.1ad,��ʵ�ֽ��û�˽��VLAN Tag��װ
  �ڹ���VLAN Tag�У�ʹ���Ĵ�������VLAN Tag��Խ��Ӫ�̵ĹǸ����磨��������
  QinQ����ͨ������̫֡�жѵ�����802.1Q��ͷ����Ч����չ��VLAN��Ŀ��ʹ  QinQ
	  VLAN����Ŀ���ɴ�4096x4096����ͬʱ�����VLAN�ܹ������õ�һ������VLAN�С�MSPͨ��Ϊÿ���ͻ�����
  һ��VLANģ�ͣ���ͨ������ע��Э��/ͨ��VLANע��Э�飨GARP/GVRP���Զ�����������������VLAN����ͨ����
  չ������Э�飨STP�����ӿ����������ٶȣ��Ӷ�Ϊ�����ṩ���ԡ�QinQ������Ϊ��ʼ�Ľ�������ǲ���ģ���
  �����û����������ӣ�SVLANģ��Ҳ���������չ�Ե����⡣��Ϊ��Щ�û�����ϣ���ڷ�֧������������ݴ���ʱ
  ����Я���Լ���VLAN ID�����ʹ����QinQ������MSP���������������⣺
  	��һ����һ���ͻ���VLAN��ʶ�����������ͻ���ͻ��
	�ڶ��������ṩ�̽��ܵ��ͻ���ʹ�ñ�ʶ�������������ơ���������û��������Լ��ķ�ʽʹ�ø��Ե�VLAN ID
		  �ռ䣬��ô���������Դ���4096��VLAN�����ơ�
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
/*	  ���ʿ����б�Access Control List��ACL�� ��·�����ͽ������ӿڵ�ָ���б��������ƶ˿ڽ��������ݰ���
  ACL���������еı�·��Э�飬��IP��IPX��AppleTalk�ȡ����ű��а�����ƥ���ϵ�������Ͳ�ѯ��䣬��ֻ��һ��
  ��ܽṹ����Ŀ����Ϊ�˶�ĳ�ַ��ʽ��п��ơ�
  	  ��Ϣ���ͨ�ţ����������ͨ�Ŷ�����ҵ�����бز����ٵ�ҵ�����󣬵���Ϊ�˱�֤�����İ�ȫ�ԣ���Ҫͨ��
  ��ȫ���������Ϸ���Ȩ�û�ֻ�ܷ����ض���������Դ���Ӷ��ﵽ�Է��ʽ��п��Ƶ�Ŀ�ġ������֮��ACL���Թ���
  �����е����������Ʒ��ʵ�һ�����缼���ֶΡ�
	 ACL����������������������������ܡ����磬ACL���Ը������ݰ���Э�飬ָ�����ݰ������ȼ���ACL�ṩ��ͨ��
  �����Ŀ����ֶΡ����磬ACL�����޶����·�ɸ�����Ϣ�ĳ��ȣ��Ӷ�����ͨ��·����ĳһ���ε�ͨ��������ACL��
  �ṩ���簲ȫ���ʵĻ����ֶΡ�ACL��������A����������Դ���磬���ܾ�����B���ʡ�ACL������·�����˿ڴ�������
  �����͵�ͨ��������ת�������������磬�û���������E-mailͨ��������·�ɣ��ܾ����е�Telnetͨ��������
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
