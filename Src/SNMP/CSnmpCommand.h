/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpCommand.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-1
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSNMPCOMMAND_H_
#define CSNMPCOMMAND_H_

#include "CThreadTask.h"
#include "CUDPData.h"
class CSnmpDataInOut;
//class CUDPInterface;
class CSnmpCommand: public CThreadTask
{
private:
	CSnmpDataInOut* objpSnmpDataInOut;				//SNMP数据接收对象
//	CUDPInterface* objpUDPInterface;				//UDP数据包来源对象
	CUDPData objData;								//UDP数据包对象
	uint32 uiRequestID;								//SNMP请求ID
	uint8 ucCurrentVersion;							//版本
	uint8 ucCurrentType;							//SNMP请求类型
	uint32 uiCurrentErrorStatus;							//SNMP差错状态
	uint32 uiCurrentErrorIndex;							//SNMP差错索引

public:
	CSnmpCommand(CSnmpDataInOut* objpIn);
	virtual ~CSnmpCommand();
	//初始化对象，废弃
	//uint32 InitialObject(CUDPInterface* objpIn,CUDPData* objpData);
	//从数据Buffer中解码
	uint32 Decode(uint8* ucpData,uint32 uiLength);
	//从对象中编码到CSnmpDataInOut的响应数据Buffer
	uint32 Encode(uint32* uipDataLength);
	//获得SNMP请求类型
	uint32 GetCurrentRequestType();
	//设置SNMP请求类型
	uint32 SetCurrentRequestType(uint8 ucType);
	//获得SNMP请求ID
	uint32 GetCurrentRequestID();
	//设置SNMP请求ID
	uint32 SetCurrentRequestID(uint32 uiID);
	//获得SNMP请求版本
	uint32 GetCurrentRequestVersion();
	//设置SNMP请求版本
	uint32 SetCurrentRequestVersion(uint8 ucVersion);
	//获得SNMP请求差错状态
	uint32 GetCurrentRequestErrorStatus();
	//设置SNMP请求差错状态
	uint32 SetCurrentRequestErrorStatus(uint32 uiStatus);
	//获得SNMP请求差错索引
	uint32 GetCurrentRequestErrorIndex();
	//设置SNMP请求差错索引
	uint32 SetCurrentRequestErrorIndex(uint32 uiIndex);
	//获得UDP数据包对象
    CUDPData* GetUDPData();
    //设置UDP数据包对象
    uint32 SetUDPData(CUDPData* objpData);
    //获得UDP数据包来源对象
//    CUDPInterface* GetUDPInterface();
    //设置UDP数据包来源对象
//    uint32 SetUDPInterface(CUDPInterface* objpInterface);

    //根据设置的CUDPData值，进行MIB库搜索
    uint32 StartMibSearch();
    //发送命令
    uint32 SendSnmpCommand();
    //获得SNMP数据接收对象
    CSnmpDataInOut* GetSnmpDataInOut();

    //清除下联SNMPCell
    uint32 Clear();

	//任务唤醒,在其他类中调用
//	virtual uint32 Notify(uint32 uiNotifyType,CThreadTask* objpSourceTask);

	//对象克隆
	uint32 Clone(CSnmpCommand* objpSnmp);
	//事件完成动作虚方法
//	virtual uint32 EventCompleted();
};

#endif /* CSNMPCOMMAND_H_ */
