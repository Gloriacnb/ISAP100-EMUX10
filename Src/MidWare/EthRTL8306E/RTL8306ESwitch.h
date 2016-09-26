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
	
	virtual uint32 InitializeSwitch(uint32 uiConfig);	 //芯片开电初始化		
	virtual uint32 GetSwitchChipID(uint32* uipChipID );  //获得交换芯片ID	

	/*   交换模式设置  */
	virtual uint32 InitializeFullSwitchMode(void); 	     //全交换模式初始化
	virtual uint32 InitializeAggregationMode(void); 	 //汇聚模式(隔离)初始化	
	virtual uint32 InitializeTagAwareMode(void);         //802.1Q模式初始化
	
	/*   交换芯片全局设置  */	
	virtual uint32 SetSwitchMaxPacketLength(uint32 uiLength); //设置最大包长 	
	virtual uint32 SetSwitchBroadcastFilter(uint32 uiEnabled); //设置广播风暴抑制使能	
	virtual uint32 SetSwitchFlowControl(uint32 port, uint32 uiEnabled); 		//设置流量控制使能
	
	/*   VLAN设置  */
	virtual uint32 CreateVLANGroup(uint32 uiVID); 	//创建VLAN组
	virtual uint32 DeleteVLANGroup(uint32 uiVID);  	//删除VLAN组	
	virtual uint32 AddPortMemberToVLANGroup(uint32 uiVID, uint32 uiPort); //添加VLAN组成员
	
	virtual uint32 DeletePortMemberFromVLANGroup(uint32 uiVID, uint32 uiPort); 	  //删除VLAN组成员
	virtual uint32 SetPortVID(uint32 uiPort,uint32 uiPVID);  	//设置端口的PVID
	virtual uint32 SetVLANTaggingMode(uint32 uiVid,uint32 uiPort,uint32 uiMode);  	//设置端口对Tag的处理模式（插入、移除Tag等）
	virtual uint32 SetPortAcceptFrameType(uint32 uiPort, uint32 uiMode);
	
	/*   端口统计计数   */
	virtual uint32 SetCounterMode(uint32 uiMode);		//设置以太数据字节/包计数方式	
	virtual uint32 GetRxCounter(uint32 uiPort, uint32 *uipValue); //获得端口以太数据接收计数
	virtual uint32 GetTxCounter(uint32 uiPort, uint32 *uipValue);  	//获得端口以太数据发送计数
	virtual uint32 GetDropCounter(uint32 uiPort, uint32 *uipValue); 	//获得端口以太数据丢弃计数
	virtual uint32 GetRxCounterNoClear(uint32 uiPort, uint32 *uipValue);  	//获得端口以太数据接收计数，不清零
	virtual uint32 GetTxCounterNoClear(uint32 uiPort, uint32 *uipValue);  	//获得端口以太数据发送计数，不清零
	virtual uint32 GetDropCounterNoClear(uint32 uiPort, uint32 *uipValue);		//获得端口以太数据丢弃计数，不清零
	virtual	uint32 getCrcErrorCounterNoClear(uint32 port, uint32* value);
	
	/*   端口模式设置  */
	virtual uint32 SetEthernetPHY(uint32 uiPort, stPortEthernetPHY* stpPHYMode);   	//设置端口模式 
	virtual uint32 GetPortAlarmStatus(uint32 uiPort,stPortAlarmStatus *stpStatus); 	 	//获得端口告警状态
	virtual uint32 SetPortPowerDown(uint32 uiPort,uint32 uiEnabled);  	//设置端口关断使能
	
	/*   QoS配置   */
	virtual uint32 InitializeQoS(uint32 uiQueueNumber);    	//QoS初始化，设置优先级队列个数
	virtual uint32 SetPortRxBandWidth(uint32 uiPort,uint32 uiBandWidth); 	//端口收方向带宽配置
	virtual uint32 SetPortTxBandWidth(uint32 uiPort,uint32 uiBandWidth); 		//端口发方向带宽配置
	virtual uint32 SetQoSPrioritySelection(stQosPrioritySelection* stpSelection); 	 	//设置QoS的不同类型优先级比较关系
	virtual uint32 SetPortPriority(uint32 uiPort,uint32 uiPriority);	   	//设置端口优先级
	virtual uint32 SetDSCPPriority(uint32 uiDSCPType,uint32 uiPriority); 		//设置DSCP优先级 
	virtual uint32 SetDot1QPriority(uint32 uiDot1QType,uint32 uiPriority); 			//设置802.1Q优先级	
	
	virtual uint32 SetQosWrr(uint8 mode);	
};

#endif

