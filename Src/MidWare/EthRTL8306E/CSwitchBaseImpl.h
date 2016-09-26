/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ebbnetwork.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Wang changrong
** Created date:			2010-12-27
** Version:					1.0
** Descriptions:			以太网交换芯片功能通用实现接口，定义以太网交换芯片应该实现的基本功能
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
** Descriptions:			端口告警结构
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
** Varialble：				ucLinkDown：	连接状态告警，可取值
**											CCommonValueDefine::uiConstAlarmHasAlarm:					有告警
**											CCommonValueDefine::uiConstAlarmNoAlarm:					没有告警
**							ucANFailure：	自动协商告警，可取值
**											CCommonValueDefine::uiConstAlarmHasAlarm:					有告警
**											CCommonValueDefine::uiConstAlarmNoAlarm:					没有告警
**							ucHalfDuplex：	当处于自动协商状态时，协商成半双工状态告警，可取值
**											CCommonValueDefine::uiConstAlarmHasAlarm:					有告警
**											CCommonValueDefine::uiConstAlarmNoAlarm:					没有告警
**							ucSpeedLow：	当处于自动协商状态时，协商成低速率状态告警，大多数情况下可取值
**											CCommonValueDefine::uiConstAlarmHasAlarm:					有告警
**											CCommonValueDefine::uiConstAlarmNoAlarm:					没有告警
**											当端口为千兆以太口时，可取值
**											CCommonValueDefine::uiConstAlarmNoAlarm:					没有告警
**											CCommonValueDefine::uiConstAlarmHasAlarmSpeedLow100M:		100M告警
**											CCommonValueDefine::uiConstAlarmHasAlarmSpeedLow10M:		10M告警
**							ucLoopback：	自动协商告警，可取值
**											CCommonValueDefine::uiConstAlarmHasAlarm:					有告警
**											CCommonValueDefine::uiConstAlarmNoAlarm:					没有告警
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
** Descriptions:			端口配置结构
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
** Varialble：				ucANEnabled：	自动协商使能，可取值
**											CSwitchBaseImpl::uiConstEnabled:			使能
**											CSwitchBaseImpl::uiConstDisabled:			不使能
**							ucLinkSpeed：	强制模式下的端口速率参数，可取值
**											CSwitchBaseImpl::uiConstLinkSpeed10M:		10M
**											CSwitchBaseImpl::uiConstLinkSpeed100M:		100M
**											CSwitchBaseImpl::uiConstLinkSpeed1000M:		1000M
**							ucFullDuplex：	强制模式下的端口双工模式参数，可取值
**											CSwitchBaseImpl::uiConstHalfDuplex:			半双工
**											CSwitchBaseImpl::uiConstFullDuplex:			全双工
**							ucCapability：	自动协商时能够支持的最大协商能力参数，可取值
**											CSwitchBaseImpl::uiConstCapabilit10MHalf	自动协商能力，10M半双工
**											CSwitchBaseImpl::uiConstCapabilit10MFULL	自动协商能力，10M全双工
**											CSwitchBaseImpl::uiConstCapabilit100MHalf	自动协商能力，100M半双工
**											CSwitchBaseImpl::uiConstCapabilit100MFULL	自动协商能力，100M全双工
**											CSwitchBaseImpl::uiConstCapabilit1000MHalf	自动协商能力，1000M半双工
**											CSwitchBaseImpl::uiConstCapabilit1000MFULL	自动协商能力，1000M全双工
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
** Descriptions:			优先级选择结构
** Created by:				Wang changrong                                           
** Created date:			2010-12-27
** Varialble：				ucDot1QEnabled：	802.1Q优先级使能参数
**							ucDSCPEnabled：		DSCP优先级使能参数
**							ucPortEnabled：		端口优先级使能参数
**							ucVIDEnabled：		VLANID优先级使能参数
**												它们的取值范围如下
**												CSwitchBaseImpl::uiConstEnabled:			使能
**												CSwitchBaseImpl::uiConstDisabled:			不使能
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
** Descriptions:			以太网交换芯片功能通用实现接口类
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
	static const uint32 uiConstDisabled 					= 0;	//不使能
	static const uint32 uiConstEnabled 						= 1;	//使能

//	static const uint32 uiConstDontConfigChip 				= 0;	//不需要配置芯片寄存器
//	static const uint32 uiConstNeedConfigChip 				= 1;	//需要配置芯片寄存器
	
	static const uint32 uiConstMaxPacketLength1518 			= 0;	//最大包长选项----1518
	static const uint32 uiConstMaxPacketLength1536 			= 1;	//最大包长选项----1536
	static const uint32 uiConstMaxPacketLength1552 			= 2;	//最大包长选项----1552
	static const uint32 uiConstMaxPacketLength1916 			= 3;	//最大包长选项----1916
	static const uint32 uiConstMaxPacketLength2047 			= 4;	//最大包长选项----2047
	
	static const uint32 uiConstTaggingModeNone				= 0;	//不插入且不移除Tag包
	static const uint32 uiConstTaggingModeInsert			= 1;	//只插入且不移除Tag包
	static const uint32 uiConstTaggingModeRemove			= 2;	//不插入且只移除Tag包
	static const uint32 uiConstTaggingModeInsertAndRemove	= 3;	//即插入且又移除Tag包
	
	static const uint32 uiConstCounterModeByte				= 0;	//统计计数采用字节方式
	static const uint32 uiConstCounterModePackage			= 1;	//统计计数采用包方式
	static const uint32 uiConstCounterModeBit				= 2;	//统计计数采用比特方式
	
	static const uint32 uiConstLinkSpeed10M					= 0;	//十兆速率	
	static const uint32 uiConstLinkSpeed100M				= 1;	//百兆速率
	static const uint32 uiConstLinkSpeed1000M				= 2;	//千兆速率	
	
	static const uint32 uiConstHalfDuplex					= 0;	//半双工模式	
	static const uint32 uiConstFullDuplex					= 1;	//全双工模式
	
	static const uint32 uiConstCapabilit10MHalf				= 0;	//自动协商能力，10M半双工
	static const uint32 uiConstCapabilit10MFULL				= 1;	//自动协商能力，10M全双工
	static const uint32 uiConstCapabilit100MHalf			= 2;	//自动协商能力，100M半双工
	static const uint32 uiConstCapabilit100MFULL			= 3;	//自动协商能力，100M全双工
	static const uint32 uiConstCapabilit1000MHalf			= 4;	//自动协商能力，1000M半双工
	static const uint32 uiConstCapabilit1000MFULL			= 5;	//自动协商能力，1000M全双工

	static const uint32 uiConstPriorityLevelHigh            = 1;	//高优先级
	static const uint32 uiConstPriorityLevelLow             = 0;	//低优先级
	
public:
	CSwitchBaseImpl();
	virtual ~CSwitchBaseImpl();
	
	/*   以下功能需重载以实现实际功能  */
	//芯片开电初始化
	virtual uint32 InitializeSwitch(uint32 uiConfig) = 0;
	//获得交换芯片ID
	virtual uint32 GetSwitchChipID(uint32* uipChipID ) = 0;
	
	/*   交换模式设置  */
	//全交换模式初始化
	virtual uint32 InitializeFullSwitchMode(void) = 0;
	//汇聚模式(隔离)初始化
	virtual uint32 InitializeAggregationMode(void) = 0;
	//802.1Q模式初始化
	virtual uint32 InitializeTagAwareMode(void) = 0;
	
	/*   交换芯片全局设置  */
	//设置最大包长 
	virtual uint32 SetSwitchMaxPacketLength(uint32 uiLength) = 0;
	//设置广播风暴抑制使能
	virtual uint32 SetSwitchBroadcastFilter(uint32 uiEnabled) = 0;
	//设置流量控制使能
	virtual uint32 SetSwitchFlowControl(uint32 port, uint32 uiEnabled) = 0;
	
	/*   VLAN设置  */
	//创建VLAN组
	virtual uint32 CreateVLANGroup(uint32 uiVID) = 0;
	//删除VLAN组
	virtual uint32 DeleteVLANGroup(uint32 uiVID) = 0;
	//添加VLAN组成员
	virtual uint32 AddPortMemberToVLANGroup(uint32 uiVID, uint32 uiPort) = 0;
	//删除VLAN组成员
	virtual uint32 DeletePortMemberFromVLANGroup(uint32 uiVID, uint32 uiPort) = 0;
	//设置端口的PVID
	virtual uint32 SetPortVID(uint32 uiPort,uint32 uiPVID) = 0;
	//设置端口对Tag的处理模式（插入、移除Tag等）
	virtual uint32 SetVLANTaggingMode(uint32 uiVid,uint32 uiPort,uint32 uiMode) = 0;
	//设置进入端口时 是否可以带Tag
	virtual uint32 SetPortAcceptFrameType(uint32 uiPort, uint32 uiMode) = 0;
	
	/*   端口统计计数   */
	//设置以太数据字节/包计数方式
	virtual uint32 SetCounterMode(uint32 uiMode) = 0;
	//获得端口以太数据接收计数
	virtual uint32 GetRxCounter(uint32 uiPort, uint32 *uipValue) = 0;
	//获得端口以太数据发送计数
	virtual uint32 GetTxCounter(uint32 uiPort, uint32 *uipValue) = 0;
	//获得端口以太数据丢弃计数
	virtual uint32 GetDropCounter(uint32 uiPort, uint32 *uipValue) = 0;
	//获得端口以太数据接收计数，不清零
	virtual uint32 GetRxCounterNoClear(uint32 uiPort, uint32 *uipValue) = 0;
	//获得端口以太数据发送计数，不清零
	virtual uint32 GetTxCounterNoClear(uint32 uiPort, uint32 *uipValue) = 0;
	//获得端口以太数据丢弃计数，不清零
	virtual uint32 GetDropCounterNoClear(uint32 uiPort, uint32 *uipValue) = 0;

	virtual	uint32 getCrcErrorCounterNoClear(uint32 port, uint32* value) = 0;

	/*   端口模式设置  */
	//设置端口模式 
	virtual uint32 SetEthernetPHY(uint32 uiPort, stPortEthernetPHY* stpPHYMode) = 0;
	//获得端口告警状态
	virtual uint32 GetPortAlarmStatus(uint32 uiPort,stPortAlarmStatus *stpStatus) = 0;
	//设置端口关断使能
	virtual uint32 SetPortPowerDown(uint32 uiPort,uint32 uiEnabled) = 0;
	
	/*   QoS配置   */
	//QoS初始化，设置优先级队列个数
	virtual uint32 InitializeQoS(uint32 uiQueueNumber) = 0;
	//端口收方向带宽配置
	virtual uint32 SetPortRxBandWidth(uint32 uiPort,uint32 uiBandWidth) = 0;
	//端口发方向带宽配置
	virtual uint32 SetPortTxBandWidth(uint32 uiPort,uint32 uiBandWidth) = 0;
	//设置QoS的不同类型优先级比较关系
	virtual uint32 SetQosWrr(uint8 mode) = 0;
	//设置端口队列权重
	virtual uint32 SetQoSPrioritySelection(stQosPrioritySelection* stpSelection) = 0;
	//设置端口优先级
	virtual uint32 SetPortPriority(uint32 uiPort,uint32 uiPriority) = 0;
	//设置DSCP优先级 
	virtual uint32 SetDSCPPriority(uint32 uiDSCPType,uint32 uiPriority) = 0;
	//设置802.1Q优先级
	virtual uint32 SetDot1QPriority(uint32 uiDot1QType,uint32 uiPriority) = 0;
	//其他功能请加入	
};
#endif


