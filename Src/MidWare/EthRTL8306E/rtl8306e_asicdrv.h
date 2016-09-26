#ifndef __RTL8306E_ASICDRV_H__
#define __RTL8306E_ASICDRV_H__
#include "EZ_types.h"

#ifdef __cplusplus
   extern "C" {
#endif
/*save time of reading LUT*/
/*#define RTL8306_LUT_CACHE */

/*if you need backup asic info in cpu memroy in order to 
 *accellerate CPU process, please define this macro. If 
 *support IGMP snooping, this macro is required.
 */

#define RTL8306E_PHY_MAXNumber    4

//#define RTL8306_TBLBAK

#define RTL8306_PHY_NUMBER        7
#define RTL8306_PAGE_NUMBER      5
#define RTL8306_PORT_NUMBER      6
#define RTL8306_VLAN_ENTRYS      16            /*Vlan entry number*/ 
#define RTL8306_ACL_ENTRYNUM    16           /*ACL entry number*/

#define RTL8306_IDLE_TIMEOUT   100
#define RTL8306_QOS_RATE_INPUT_MAX     0x5F6
#define RTL8306_VIDMAX                       0XFFF
#define RTL8306_MAX_PORTMASK           0X3F


enum RTL8306E_REGPAGE
{
    RTL8306_REGPAGE0 = 0,
    RTL8306_REGPAGE1,
    RTL8306_REGPAGE2,
    RTL8306_REGPAGE3,
    RTL8306_REGPAGE4,    
    RTL8306_REGPAGE_END
    
};

enum RTL8306E_PORTNUM
{
    RTL8306_PORT0 = 0,
    RTL8306_PORT1,        
    RTL8306_PORT2,
    RTL8306_PORT3,  
    RTL8306_PORT4,
    RTL8306_PORT5,
    RTL8306_NOCPUPORT = 7    
};

enum RTL8306E_PHYMODE
{
    RTL8306_ETHER_AUTO_100FULL = 1,
    RTL8306_ETHER_AUTO_100HALF,
    RTL8306_ETHER_AUTO_10FULL,
    RTL8306_ETHER_AUTO_10HALF
};

enum RTL8306E_PHYSPD
{
    RTL8306_ETHER_SPEED_100 = 100,
    RTL8306_ETHER_SPEED_10 = 10        
};

enum RTL8306E_TAGMOD
{
    RTL8306_VLAN_IRTAG = 0,             /*The switch will remove VLAN tags and add new tags */
    RTL8306_VLAN_RTAG,                   /*The switch will remove VLAN tags */
    RTL8306_VLAN_ITAG,                   /*The switch will  add new VLANtag */
    RTL8306_VLAN_UNDOTAG            /*Do not insert or remove  VLAN tag */
};

enum RTL8306E_LEAKYVLAN
{
    RTL8306_VALN_LEAKY_UNICAST = 0,
    RTL8306_VALN_LEAKY_MULTICAST,
    RTL8306_VALN_LEAKY_ARP,
    RTL8306_VALN_LEAKY_MIRROR,
    RTL8306_VALN_LEAKY_END
};

/*ACL Packet processing method*/
enum RTL8306E_ACTION
{
    RTL8306_ACT_DROP = 0,    /*drop the packet*/    
    RTL8306_ACT_PERMIT,      /*permit the packet*/        
    RTL8306_ACT_TRAPCPU,   /*trap the packet to cpu*/
    RTL8306_ACT_MIRROR,     /*mirror the packet */
    RTL8306_ACT_FLOOD      /*flood the packet  */    
};

/*
  * PHY control register field definitions 
  */
#define RTL8306_SPEED_SELECT_100M                       (1 << 13)  
#define RTL8306_ENABLE_AUTONEGO                         (1 << 12)
#define RTL8306_RESTART_AUTONEGO                        (1 << 9)
#define RTL8306_SELECT_FULL_DUPLEX                      (1 << 8)

/* 
  *PHY auto-negotiation advertisement and link partner 
  *ability registers field definitions
  */
#define RTL8306_NEXT_PAGE_ENABLED                       (1 << 15)
#define RTL8306_ACKNOWLEDGE                                 (1 << 14)
#define RTL8306_REMOTE_FAULT                                 (1 << 13)
#define RTL8306_CAPABLE_PAUSE                               (1 << 10)
#define RTL8306_CAPABLE_100BASE_T4                      (1 << 9)
#define RTL8306_CAPABLE_100BASE_TX_FD                (1 << 8)
#define RTL8306_CAPABLE_100BASE_TX_HD                (1 << 7)
#define RTL8306_CAPABLE_10BASE_TX_FD                  (1 << 6)
#define RTL8306_CAPABLE_10BASE_TX_HD                  (1 << 5)
#define RTL8306_SELECTOR_MASK                               0x1F
#define RTL8306_SELECTOR_OFFSET                             0

enum RTL8306E_IGMPCTL
{
    RTL8306_IGMP = 0,
    RTL8306_MLD, 
    RTL8306_PPPOE
};

enum RTL8306E_IPMULTICAST
{
    RTL8306_IPV4_MULTICAST = 0,
    RTL8306_IPV6_MULTICAST
};

#define RTL8306_PORT_RX  0
#define RTL8306_PORT_TX  1

enum RTL8306E_QUENUM
{
    RTL8306_QUEUE0 = 0,
    RTL8306_QUEUE1,
    RTL8306_QUEUE2,
    RTL8306_QUEUE3
};

enum RTL8306E_PRISRC
{
    RTL8306_ACL_PRIO = 0,           /*ACL-based priority*/
    RTL8306_DSCP_PRIO,              /*DSCP-based priority*/
    RTL8306_1QBP_PRIO,              /*802.1Q-based priority*/ 
    RTL8306_PBP_PRIO,                /*port- based priority */
    RTL8306_CPUTAG_PRIO,          /*cpu tag priority*/
    RTL8306_IP_PRIO,                  /* ip address priority*/
    RTL8306_1QTAG_PRIO,           /* VLAN tag priority */
    RTL8306_PRI_1QDEFAULT      /* 802.1Q priority for untagged packet*/     
};


enum RTL8306E_1QPRI
{
    RTL8306_1QTAG_PRIO0 = 0,
    RTL8306_1QTAG_PRIO1,
    RTL8306_1QTAG_PRIO2,
    RTL8306_1QTAG_PRIO3,
    RTL8306_1QTAG_PRIO4,
    RTL8306_1QTAG_PRIO5,
    RTL8306_1QTAG_PRIO6,
    RTL8306_1QTAG_PRIO7,
    RTL8306_1QTAG_END
};

enum RTL8306E_PRI
{
    RTL8306_PRIO0 = 0,
    RTL8306_PRIO1,
    RTL8306_PRIO2,
    RTL8306_PRIO3,    
    RTL8306_PRI_END
};

enum RTL8306E_SCHSET
{
    RTL8306_QOS_SET0 = 0, 
    RTL8306_QOS_SET1        
};

enum RTL8306E_DSCPCODE
{
    RTL8306_DSCP_EF = 0,
    RTL8306_DSCP_AFL1,
    RTL8306_DSCP_AFM1,    
    RTL8306_DSCP_AFH1,
    RTL8306_DSCP_AFL2,
    RTL8306_DSCP_AFM2,
    RTL8306_DSCP_AFH2,
    RTL8306_DSCP_AFL3,
    RTL8306_DSCP_AFM3,
    RTL8306_DSCP_AFH3,
    RTL8306_DSCP_AFL4,
    RTL8306_DSCP_AFM4,
    RTL8306_DSCP_AFH4,
    RTL8306_DSCP_NC,
    RTL8306_DSCP_REG_PRI,
    RTL8306_DSCP_BF       
};

#define RTL8306_DSCP_USERA        0
#define RTL8306_DSCP_USERB        1
#define RTL8306_IPADD_A 0
#define RTL8306_IPADD_B 1

#define RTL8306_FCO_SET0            0x0
#define RTL8306_FCO_SET1            0x1
#define RTL8306_FCOFF                 0x0
#define RTL8306_FCON                   0x1
#define RTL8306_FCO_DSC             0x0
#define RTL8306_FCO_QLEN           0x1
#define RTL8306_FCO_FULLTHR      0x0
#define RTL8306_FCO_OVERTHR     0x1


#define RTL8306_ACL_INVALID       0x6
#define RTL8306_ACL_ANYPORT     0x7

enum RTL8306E_ACLPRO
{
    RTL8306_ACL_ETHER = 0,
    RTL8306_ACL_TCP,
    RTL8306_ACL_UDP,
    RTL8306_ACL_TCPUDP    
};

enum RTL8306E_MIBCNT
{
    RTL8306_MIB_CNT1 = 0,
    RTL8306_MIB_CNT2,
    RTL8306_MIB_CNT3,
    RTL8306_MIB_CNT4,
    RTL8306_MIB_CNT5 
};

enum RTL8306E_MIBOP
{
    RTL8306_MIB_RESET = 0, 
    RTL8306_MIB_START        
};

#define RTL8306_MIB_BYTE            0
#define RTL8306_MIB_PKT              1

#define RTL8306_MIR_INVALID       0x6

enum RTL8306E_LUT4WAY
{
    RTL8306_LUT_ENTRY0 = 0,
    RTL8306_LUT_ENTRY1,
    RTL8306_LUT_ENTRY2,
    RTL8306_LUT_ENTRY3    
};    

#define RTL8306_LUT_FULL         -2  /*Four way of the same entry are all written by cpu*/
#define RTL8306_LUT_NOTEXIST     -3

enum RTL8306E_LUTAGE
{
    RTL8306_LUT_AGEOUT = 0,
    RTL8306_LUT_AGE100 = 100,
    RTL8306_LUT_AGE200 = 200,
    RTL8306_LUT_AGE300 = 300   
};

#define RTL8306_LUT_DYNAMIC      0
#define RTL8306_LUT_STATIC       1
#define RTL8306_LUT_UNAUTH       0
#define RTL8306_LUT_AUTH         1

enum RTL8306E_SPAN_STATE
{
    RTL8306_SPAN_DISABLE = 0,
    RTL8306_SPAN_BLOCK,
    RTL8306_SPAN_LEARN,
    RTL8306_SPAN_FORWARD  
};

enum RTL8306E_DOT1X_STATE
{
    RTL8306_PORT_UNAUTH = 0, 
    RTL8306_PORT_AUTH
};

enum RTL8306E_DOT1X_PORT_DIR
{
    RTL8306_PORT_BOTHDIR = 0,
    RTL8306_PORT_INDIR      
};

enum RTL8306E_DOT1X_MAC_DIR
{
    RTL8306_MAC_BOTHDIR = 0,
    RTL8306_MAC_INDIR      
};

enum RTL8306E_ABNORMAL_PKT
{
    RTL8306_UNMATCHVID =0,
    RTL8306_DOT1XUNAUTH
};

enum RTL8306E_RMA
{
    RTL8306_RESADDRXX = 0, /*reserved address 01-80-c2-00-00-xx (exclude 00, 01, 02, 03, 10, 20, 21) */
    RTL8306_RESADDR21,       /*reserved address 01-80-c2-00-00-21*/        
    RTL8306_RESADDR20,       /*reserved address 01-80-c2-00-00-20*/
    RTL8306_RESADDR10,       /*reserved address 01-80-c2-00-00-10*/
    RTL8306_RESADDR03,      /*reserved address 01-80-c2-00-00-03*/
    RTL8306_RESADDR02,      /*reserved address 01-80-c2-00-00-02*/
    RTL8306_RESADDR00,      /*reserved address 01-80-c2-00-00-00*/
    RTL8306_RESADDR01     /*reserved address 01-80-c2-00-00-01*/
};

enum RTL8306E_PKT_TYPE
{
    RTL8306_UNICASTPKT = 0,  /*Unicast packet, but not include unknown DA unicast packet*/
    RTL8306_BROADCASTPKT,   /*Broadcast packet*/
    RTL8306_MULTICASTPKT,    /*Multicast packet*/
    RTL8306_UDAPKT             /*Unknown DA unicast packet*/
};


/*Max packet length*/
enum RTL8306E_PKT_LEN
{
    RTL8306_MAX_PKT_LEN_1518 = 0,  /*1518 bytes without any tag; 1522 bytes: with VLAN tag or CPU tag*/
    RTL8306_MAX_PKT_LEN_1536,       /*1536 bytes*/
    RTL8306_MAX_PKT_LEN_1552,       /*1552 bytes*/
    RTL8306_MAX_PKT_LEN_2000       /*1552 bytes*/
};

enum RTL8306E_STORM_THR
{
    RTL8306_STM_FILNUM64  =  0,     /*64 pkts will trigger storm fileter*/
    RTL8306_STM_FILNUM32,            /*32 pkts will trigger storm fileter*/
    RTL8306_STM_FILNUM16,            /*16 pkts will trigger storm fileter*/
    RTL8306_STM_FILNUM8,              /*8 pkts will trigger storm fileter*/
    RTL8306_STM_FILNUM128,          /*128 pkts will trigger storm fileter*/
    RTL8306_STM_FILNUM256,          /*256 pkts will trigger storm fileter*/
    RTL8306_STM_FILNUM_END    
};

enum RTL8306E_STORM_TIMEWIN
{
    RTL8306_STM_FIL800MS = 0,       /*filter 800ms after trigger storm filter*/
    RTL8306_STM_FIL400MS,            /*filter 400ms after trigger storm filter*/
    RTL8306_STM_FIL200MS,            /*filter 200ms after trigger storm filter*/
    RTL8306_STM_FIL100MS,            /*filter 100ms after trigger storm filter*/
    RTL8306_STM_FILTIM_END
};

typedef enum rtl8306e_acceptFrameType_e
{
    RTL8306E_ACCEPT_ALL = 0,                   /* untagged, priority-tagged and tagged */
    RTL8306E_ACCEPT_TAG_ONLY = 2,         /* tagged */
    RTL8306E_ACCEPT_UNTAG_ONLY = 3 ,    /* untagged and priority-tagged */
    RTL8306E_ACCEPT_TYPE_END
} rtl8306e_acceptFrameType_t;

typedef enum rtl8306e_vidSrc_e
{
    RTL8306E_VIDSRC_POVID = 0,              /*port-based outer tag vid*/
    RTL8306E_VIDSRC_NVID,                     /* new vid translated*/
    RTL8306E_VIDSRC_END    

} rtl8306e_vidSrc_t;

typedef enum rtl8306e_priSrc_e
{
    RTL8306E_PRISRC_PPRI = 0,              /*port-based outer tag priority*/
    RTL8306E_PRISRC_1PRMK,                /* 1p remarking priority*/
    RTL8306E_PRISRC_END
} rtl8306e_priSrc_t;


typedef struct rtl8306e_qosPriArbitPara_s 
{
    uint32 acl_pri_lev;
    uint32 dscp_pri_lev;
    uint32 dot1q_pri_lev;
    uint32 port_pri_lev;
    uint32 vid_pri_lev;
}rtl8306e_qosPriArbitPara_t;

typedef struct rtl8306e_qosSchPara_s
{
    uint8   q0_wt;
    uint8   q1_wt;
    uint8   q2_wt;
    uint8   q3_wt;
    uint16 q2_n64Kbps;
    uint16 q3_n64Kbps;    

}rtl8306e_qosSchPara_t;

#ifdef RTL8306_LUT_CACHE
#define RTL8306_MAX_LUT_NUM    2048
typedef struct RTL8306_LUT_s
{
    uint8   mac[6];
    union
    {
        struct 
        {
            uint8 auth;
            uint8 isStatic;
            uint8 spa;
            uint8 age;
            uint8 reserved;
        } unicast;
        struct 
        {
            uint8 auth;
            uint8 portMask;
            uint8 reserved;
        } multicast;
    }un;
}RTL8306_LUT;
#endif

#ifdef RTL8306_TBLBAK
typedef struct rtl8306_vlanConfigBakPara_s 
{
    uint8 enVlan;
    uint8 enArpVlan;
    uint8 enLeakVlan;
    uint8 enVlanTagOnly;
    uint8 enIngress;
    uint8 enTagAware;
    uint8 enIPMleaky;
    uint8 enMirLeaky;
} rtl8306_vlanConfigBakPara_t;

typedef struct rtl8306_vlanConfigPerPortBakPara_s 
{
    uint8 vlantagInserRm;
    uint8 en1PRemark;
    uint8 enNulPvidRep;         
} rtl8306_vlanConfigPerPortBakPara_t;

typedef struct  rtl8306_vlanTblBakPara_s 
{
    uint16 vid;
    uint8 memberPortMask;        
} rtl8306_vlanTblBakPara_t;

typedef struct rtl8306_aclTblBakPara_s 
{
    uint8 phy_port;
    uint8 proto;
    uint16 data;
    uint8 action;
    uint8 pri;
} rtl8306_aclTblBakPara_t;

typedef struct rtl8306_mirConfigBakPara_s
{
    uint8 mirPort;
    uint8 mirRxPortMask;
    uint8 mirTxPortMask;
    uint8 enMirself;
    uint8 enMirMac;
    uint8 mir_mac[6];
} rtl8306_mirConfigBakPara_t;
    

typedef struct rtl8306_ConfigBakPara_s  
{
    rtl8306_vlanConfigBakPara_t vlanConfig;                    /*VLAN global configuration*/
    rtl8306_vlanConfigPerPortBakPara_t vlanConfig_perport[6];   /*VLAN per-port configuration*/
    rtl8306_vlanTblBakPara_t vlanTable[16]; /*It backups VLAN table in cpu memory*/
    uint8 vlanPvidIdx[6];   /*per-port PVID index*/                  
    uint8 En1PremarkPortMask; /*Enable/disable 802.1P remarking  port mask */
    uint8 dot1PremarkCtl[4]; /*802.1p remarking table*/
    uint8 dot1DportCtl[6]; /*Spanning tree port state*/
    rtl8306_aclTblBakPara_t aclTbl[16];         /*ACL table*/
    rtl8306_mirConfigBakPara_t mir; /*mirror configuration*/                                                                         
} rtl8306_ConfigBakPara_t;

extern rtl8306_ConfigBakPara_t rtl8306_TblBak; 

#endif


#define RTL8306_GET_REG_ADDR(x, page, phy, reg) \
    do { (page) = ((x) & 0xFF0000) >> 16; (phy) = ((x) & 0x00FF00) >> 8; (reg) = ((x) & 0x0000FF);\
    } while(0) \

/*compute look up table index of a mac addrees, LUT index : MAC[13:15] + MAC[0:5]*/
#define RTL8306_MAC_INDEX(mac, index)    rtl8306e_l2_MacToIdx_get(mac, &index)


uint32 rtk_getAsicOUIID (uint8 Phy, uint16 *oui );
uint32 RTL8306E_setPowerDown(uint32 phyad, uint32 enabled);
uint32 RTL8306E_getPowerDown(uint32 phyad, uint32 *enabled);
/********************************  寄存器读写  *********************************************************************/
uint32 rtl8306e_reg_set(uint32 phyad, uint32 regad, uint32 npage, uint32 value);
uint32 rtl8306e_reg_get(uint32 phyad, uint32 regad, uint32 npage, uint16 *pvalue);
uint32 rtl8306e_regbit_set(uint32 phyad, uint32 regad, uint32 bit, uint32 npage,  uint32 value);
uint32 rtl8306e_regbit_get(uint32 phyad, uint32 regad, uint32 bit, uint32 npage,  uint32 * pvalue) ;
uint32 rtl8306e_phyReg_set(uint32 phyad, uint32 regad, uint32 npage, uint32 value);
uint32 rtl8306e_phyReg_get(uint32 phyad, uint32 regad, uint32 npage, uint16 *pvalue);

uint32 rtl8306e_asic_init(void);
								   
/*******************************  端口配置  **************************************************************************/
uint32 rtl8306e_phy_reset(uint32 phy);
uint32 rtl8306e_switch_maxPktLen_set(uint32 maxLen);
uint32 rtl8306e_switch_maxPktLen_get(uint32 *pMaxLen);
uint32 rtl8306e_port_etherPhy_set(uint32 phy, uint32 autoNegotiation, uint32 advCapability, uint32 speed, uint32 fullDuplex) ;
uint32 rtl8306e_port_etherPhy_get(uint32 phy, uint32 *pAutoNegotiation, uint32 *pAdvCapability, uint32 *pSpeed, uint32 *pFullDuplex);
uint32 rtl8306e_port_port5LinkStatus_set(uint32 enabled);		 //PORT5单独设置
uint32 rtl8306e_port_port5LinkStatus_get(uint32 *pEnabled);
uint32 rtl8306e_port_phyLinkStatus_get(uint32 phy, uint32 *plinkUp);
uint32 rtl8306e_port_phyAutoNegotiationDone_get(uint32 phy, uint32 *pDone) ;
uint32 rtl8306e_port_phyLoopback_set(uint32 phy, uint32 enabled);
uint32 rtl8306e_port_phyLoopback_get(uint32 phy, uint32 *pEnabled);
uint32 rtl8306e_portLearningAbility_set(uint32 port, uint32 enabled);
uint32 rtl8306e_port_isolation_set(uint32 isomsk);
uint32 rtl8306e_port_isolation_get(uint32 *pIsomsk);

/*******************************  VLAN功能  **************************************************************************/

uint32 rtl8306e_vlan_tagAware_set(uint32 enabled);
uint32 rtl8306e_vlan_tagAware_get(uint32 * pEnabled);
uint32 rtl8306e_vlan_IgrFilterEnable_set(uint32 enabled); 
uint32 rtl8306e_vlan_IgrFilterEnable_get(uint32 *pEnabled); 
uint32 rtl8306e_vlan_leaky_set(uint32 type, uint32 enabled);   //Configure switch to forward frames to other VLANs ignoring the egress rule
uint32 rtl8306e_vlan_leaky_get(uint32 type, uint32 *pEnabled);
uint32 rtl8306e_vlan_nullVidReplace_set(uint32 port, uint32 enabled);
uint32 rtl8306e_vlan_nullVidReplace_get(uint32 port, uint32 *pEnabled);
uint32 rtl8306e_vlan_portPvidIndex_set(uint32 port, uint32 vlanIndex);
uint32 rtl8306e_vlan_portPvidIndex_get(uint32 port, uint16 *pVlanIndex);
uint32 rtl8306e_vlan_portAcceptFrameType_set(uint32 port, rtl8306e_acceptFrameType_t accept_frame_type);
uint32 rtl8306e_vlan_portAcceptFrameType_get(uint32 port, rtl8306e_acceptFrameType_t *pAccept_frame_type);
uint32 rtl8306e_vlan_tagInsert_set(uint32 egPort, uint32 igPortMsk);	//ingress port mask
uint32 rtl8306e_vlan_tagInsert_get(uint32 egPort, uint32 * pIgPortMsk);	
uint32 rtl8306e_vlan_entry_set(uint32 vlanIndex, uint32 vid, uint32 mbrmsk, uint32 untagmsk );	// mbrmsk-VLAN member set portmask   untagmsk-VLAN untag set portmask
uint32 rtl8306e_vlan_entry_get(uint32 vlanIndex, uint16 *pVid, uint16 *pMbrmsk, uint16 *pUntagmsk);
uint32 rtl8306e_vlan_vlanBasedPriority_set(uint32 vlanIndex, uint32 pri);	  //unmatched VID could also be assigned an priority
uint32 rtl8306e_vlan_vlanBasedPriority_get(uint32 vlanIndex, uint32 *pPri);

/**************************  VLAN QinQ  **********************************************************/
uint32 rtl8306e_vlan_transEnable_set(uint32 enable, uint32 portmask);	   //the VLAN tranlation function and Q-in-Q(SVLAN) could not be enabled at the same time, user should choose one of them. 
uint32 rtl8306e_vlan_transEnable_get(uint32 *pEnable, uint32 *pPortMask);
uint32 rtl8306e_vlan_transparentEnable_set(uint32 enable);  //   enable or disable VLAN transparent
uint32 rtl8306e_vlan_transVid_set(uint32 vlanIndex, uint32 transVid);	  //  Set the translated VID
uint32 rtl8306e_vlan_transVid_get(uint32 vlanIndex, uint32 *pTransVid);
uint32 rtl8306e_svlan_tagAdmit_set(uint32 port, uint32 enable);	  //Q-in-Q  tag admit control 
uint32 rtl8306e_svlan_tagAdmit_get(uint32 port, uint32 *pEnable);
uint32 rtl8306e_svlan_otagSrc_set(uint32 port, uint32 ovidSrc, uint32 opriSrc);
uint32 rtl8306e_svlan_otagSrc_get(uint32 port, uint32 *pOvidsrc, uint32 *pOpriSrc);  //  how to decide outer tag vid and priority
uint32 rtl8306e_cpu_set(uint32 port, uint32 enTag); //  no port is assigned as cpu port
uint32 rtl8306e_cpu_get(uint32 *pPort, uint32 *pEnTag);

/***************************  QOS **********************************************************/
uint32 rtl8306e_qos_softReset_set(void);
uint32 rtl8306e_qos_queueNum_set(uint32 num);	  // queue number
uint32 rtl8306e_qos_queueNum_get(uint32 *pNum) ;
uint32 rtl8306e_qos_priToQueMap_set(uint32 priority, uint32 qid) ; //	Set priority to Queue ID mapping
uint32 rtl8306e_qos_priToQueMap_get(uint32 priority, uint32 *pQid) ;
uint32 rtl8306e_qos_portRate_set(uint32 port, uint32 n64Kbps, uint32 direction, uint32 enabled);	 //	n64Kbps,For output rate control, enable/disable is configured per port, but for input rate control, it is for all port.
uint32 rtl8306e_qos_portRate_get(uint32 port, uint32 *pN64Kbps, uint32 direction, uint32 *pEnabled);
uint32 rtl8306e_qos_1pRemarkEnable_set(uint32 port, uint32 enabled);	 //Set 802.1P remarking ability
uint32 rtl8306e_qos_1pRemarkEnable_get(uint32 port, uint32 *pEnabled) ;
uint32 rtl8306e_qos_1pRemark_set(uint32 priority, uint32 priority1p);		//Packet priority(0~4),	802.1P priority(0~7)
uint32 rtl8306e_qos_1pRemark_get(uint32 priority, uint32 *pPriority1p);
uint32 rtl8306e_qos_portPri_set(uint32 port, uint32 priority);	// Packet port-based priority(0~4)
uint32 rtl8306e_qos_portPri_get(uint32 port, uint32 *pPriority);
uint32 rtl8306e_qos_1pPriRemap_set(uint32 tagprio, uint32 prio) ;	// 1Q-tag priority mapping
uint32 rtl8306e_qos_1pPriRemap_get(uint32 tagprio, uint32 *pPrio);
uint32 rtl8306e_qos_dscpPriRemap_set(uint32 code, uint32 priority) ;
uint32 rtl8306e_qos_dscpPriRemap_get(uint32 code, uint32 *pPriority);
uint32 rtl8306e_qos_priSrcArbit_set(rtl8306e_qosPriArbitPara_t priArbit);	   //source arbitration level 五个优先级类型选择
uint32 rtl8306e_qos_priSrcArbit_get(rtl8306e_qosPriArbitPara_t *pPriArbit);
uint32 rtl8306e_qos_priSrcEnable_set(uint32 port, uint32 priSrc, uint32 enabled);	 //优先级源使能
uint32 rtl8306e_qos_priSrcEnable_get(uint32 port, uint32 priSrc, uint32 *pEnabled);
uint32 rtl8306e_qos_ipAddrPri_set(uint32 priority); 
uint32 rtl8306e_qos_ipAddrPri_get(uint32 *priority);
uint32 rtl8306e_qos_ipAddr_set(uint32 entry, uint32 ip, uint32 mask, uint32 enabled);
uint32 rtl8306e_qos_ipAddr_get(uint32 entry, uint32 *pIp, uint32 *pMask , uint32 *pEnabled); 
uint32 rtl8306e_qos_schedulingPara_set(uint32 set, rtl8306e_qosSchPara_t sch_para);		 //权重
uint32 rtl8306e_qos_schedulingPara_get(uint32 set, rtl8306e_qosSchPara_t *pSch_para);
uint32 rtl8306e_qos_portSchedulingMode_set(uint32 port, uint32 set, uint32 lbmsk);
uint32 rtl8306e_qos_portSchedulingMode_get(uint32 port, uint32 *pSet, uint32 *pLbmsk);


uint32 rtl8306e_qos_queFlcThr_set(uint32 queue, uint32 type, uint32 onoff, uint32 set, uint32 value);
uint32 rtl8306e_qos_queFlcThr_get(uint32 queue, uint32 type, uint32 onoff, uint32 set, uint32* pValue);
uint32 rtl8306e_qos_portFlcThr_set(uint32 port, uint32 onthr, uint32 offthr, uint32 direction );
uint32 rtl8306e_qos_portFlcThr_get(uint32 port, uint32 *pOnthr, uint32 *pOffthr, uint32 direction);
uint32 rtl8306e_qos_queFlcEnable_set( uint32 port, uint32 queue, uint32 enabled);
uint32 rtl8306e_qos_queFlcEnable_get(uint32 port, uint32 queue, uint32 *pEnabled);

uint32 rtl8306e_qos_portFlcMode_set(uint32 port, uint32 set);
uint32 rtl8306e_qos_portFlcMode_get(uint32 port , uint32 *set);

/******************************  ACL功能  **************************************************/
uint32 rtl8306e_acl_entry_set(uint32 entryadd, uint32 phyport, uint32 action, uint32 protocol, uint32 data, uint32 priority) ;
uint32 rtl8306e_acl_entry_get(uint32 entryadd, uint32 *pPhyport, uint32 *pAction, uint32 *pProtocol, uint32  *pData, uint32 *pPriority);

/******************************  MIB功能  **************************************************/
uint32 rtl8306e_mib_get(uint32 port, uint32 counter, uint32 *pValue); 
uint32 rtl8306e_mibUnit_set(uint32 port, uint32 counter, uint32 unit);		//读写计数单位（字节或包计数）
uint32 rtl8306e_mibUnit_get(uint32 port, uint32 counter, uint32 *pUnit);
uint32 rtl8306e_mib_reset(uint32 port);

/******************************  mirror  function镜像功能  *********************************/
uint32 rtl8306e_mirror_portBased_set(uint32 mirport, uint32 rxmbr, uint32 txmbr) ;
uint32 rtl8306e_mirror_portBased_get(uint32 *pMirport, uint32 *pRxmbr, uint32* pTxmbr);

/******************************  L2 table  function  ***************************************/
uint32 rtl8306e_l2_MacToIdx_get(uint8 *macAddr, uint32* pIndex);
uint32 rtl8306e_l2_unicastEntry_set(uint8 *macAddress, uint32 entry, uint32 age, uint32 isStatic, uint32 isAuth, uint32 port); 
uint32 rtl8306e_l2_unicastEntry_get(uint8 *macAddress, uint32 entryAddr, uint32 *pAge, uint32 *pIsStatic, uint32 *pIsAuth, uint32 *pPort) ;
uint32 rtl8306e_l2_multicastEntry_set(uint8 *macAddress, uint32 entry, uint32 isAuth, uint32 portMask);
uint32 rtl8306e_l2_multicastEntry_get(uint8 *macAddress, uint32 entryAddr, uint32 *pIsAuth, uint32 *pPortMask);
int32 rtl8306e_l2_unicastMac_add(uint8 *macAddress, uint32 age, uint32 isStatic, uint32 isAuth, uint32 port, uint32 *pEntryaddr);
int32 rtl8306e_l2_multicastMac_add(uint8 *macAddr,uint32 isAuth, uint32 portMask, uint32 *pEntryaddr);
int32 rtl8306e_l2_mac_get(uint8 *macAddr, uint32 *pIsStatic, uint32 *pIsAuth, uint32 *pPortInfo, uint32 *pEntryaddr); 

int32 rtl8306e_l2_mac_del(uint8 *macAddr, uint32 *pEntryaddr);
uint32 rtl8306e_l2_portMacLimit_set(uint32 port, uint32 enabled, uint32 macCnt) ;
uint32 rtl8306e_l2_portMacLimit_get(uint32 port, uint32 *pEnabled, uint32 *pMacCnt);
uint32 rtl8306e_l2_systemMacLimit_set(uint32 enabled, uint32 macCnt, uint32 mergMask);
uint32 rtl8306e_l2_systemMacLimit_get(uint32 *pEnabled, uint32 *pMacCnt, uint32 *pMergMask); 
uint32 rtl8306e_l2_macLimitAction_set(uint32 action); 
uint32 rtl8306e_l2_macLimitAction_get(uint32 *pAction);

#ifdef RTL8306_LUT_CACHE

uint32 rtl8306e_fastGetAsicLUTUnicastEntry(uint8 *macAddress, uint32 entryAddr, uint32 *age, uint32 *isStatic, uint32 *isAuth, uint32 *port);
uint32 rtl8306e_fastGetAsicLUTMulticastEntry(uint8 *macAddress, uint32 entryAddr, uint32 *isAuth, uint32 *portMask);

#endif

/*********************************  Spanning Tree  function  ****************************************/
uint32 rtl8306e_stp_set(uint32 port, uint32 state) ;
uint32 rtl8306e_stp_get(uint32 port, uint32 *pState) ;

/*********************************  802.1x  function  ***********************************************/
uint32 rtl8306e_dot1x_portBased_set(uint32 port, uint32 enabled, uint32 isAuth, uint32 direction);
uint32 rtl8306e_dot1x_portBased_get(uint32 port, uint32 *pEnabled, uint32 *pIsAuth, uint32 *pDirection) ;
uint32 rtl8306e_dot1x_macBased_set(uint32 port, uint32 enabled, uint32 direction);
uint32 rtl8306e_dot1x_macBased_get(uint32 port, uint32 *pEnabled, uint32 *pDirection); 


uint32 rtl8306e_trap_igmpCtrlPktAction_set(uint32 type, uint32 action);
uint32 rtl8306e_trap_igmpCtrlPktAction_get(uint32 type, uint32 *pAction);
uint32 rtl8306e_trap_unknownIPMcastPktAction_set(uint32 type, uint32 action);
uint32 rtl8306e_trap_unknownIPMcastPktAction_get(uint32 type, uint32 *pAction);
uint32 rtl8306e_trap_abnormalPktAction_set(uint32 type,  uint32 action);
uint32 rtl8306e_trap_abnormalPktAction_get(uint32 type,  uint32 *pAction);
uint32 rtl8306e_trap_rmaAction_set(uint32 type, uint32 action);
uint32 rtl8306e_trap_rmaAction_get(uint32 type, uint32 *pAction);

/**********************************  中断控制  ******************************************************/
uint32 rtl8306e_int_control_set(uint32 enInt, uint32 intmask);
uint32 rtl8306e_int_control_get(uint32 *pEnInt, uint32 *pIntmask);
uint32 rtl8306e_int_status_get(uint32 *pStatusMask);

/**********************************  storm filter  **************************************************/
uint32 rtl8306e_storm_filterEnable_set(uint32 type, uint32 enabled);
uint32 rtl8306e_storm_filterEnable_get(uint32 type, uint32 *pEnabled);
uint32 rtl8306e_storm_filter_set(uint32 trigNum, uint32 filTime, uint32 enStmInt);
uint32 rtl8306e_storm_filter_get(uint32 *pTrigNum, uint32 *pFilTime, uint32 *pEnStmInt);

#ifdef __cplusplus
   }
#endif

#endif


