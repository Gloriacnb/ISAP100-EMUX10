/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpCell.h
 ** Created by:				WangChangRong
 ** Created date:			2011-8-2
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#ifndef CSNMPCELL_H_
#define CSNMPCELL_H_
#include "EZ_types.h"
#include "CThreadTask.h"
#include "CSnmpVariable.h"
#include "CSnmpVariableBinding.h"
class CSnmpCommand;
class CSnmpCell: public CThreadTask
{
private:
	CSnmpCommand* objpCommand;						//所属的SNMP命令对象
	CSnmpVariableBinding objRequestVB;				//请求的SNMP VB对象
	CSnmpVariable objCurrentVariable;				//当前正在处理的OID对象
	CSnmpVariableBinding objResponseVB;				//响应VB对象
	uint8 ucErrorStatus;							//差错状态
public:
	CSnmpCell(CSnmpCommand* objpIn);
	virtual ~CSnmpCell();
	//获得SNMP命令对象
	CSnmpCommand* GetSnmpCommand();
	//获得请求VB对象
	CSnmpVariableBinding* GetRequestVB();
	//获得正在处理的VB对象
	CSnmpVariable* GetCurrentVariable();
	//获得响应VB对象
	CSnmpVariableBinding* GetResponseVB();
	//获得差错状态
	uint8 GetErrorStatus();
	//设置差错状态
	uint32 SetErrorStatus(uint8 ucError);
	//启动MIB检索和查询，获取响应
	uint32 StartMibSearch();
	//设置请求
	uint32 SetRequest(CSnmpVariable* objpOID,CSnmpVariable* objpValue);
	//设置响应
	uint32 SetResponse(CSnmpVariable* objpOID,CSnmpVariable* objpValue);
	//设置错误响应
	uint32 SetErrorResponse(CSnmpVariable* objpOID,uint8 ucError);
	//任务唤醒,在其他类中调用
//	virtual uint32 Notify(uint32 uiNotifyType,CThreadTask* objpSourceTask);
	//对象克隆
	uint32 Clone(CSnmpCell* objpCell);

};

#endif /* CSNMPCELL_H_ */
