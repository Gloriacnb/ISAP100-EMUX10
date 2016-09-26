/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpMib.h
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

#ifndef CSNMPMIB_H_
#define CSNMPMIB_H_
#include "EZ_types.h"
#include "CSnmpDataInOut.h"
#include "CMibImpl.h"
class CCommunication;
class CSnmpMib
{
private:
//	CCommunication* objpCommunication;				//上级通信对象指针
	CSnmpDataInOut objDataInOut;					//SNMP数据输入输出对象
	CMibImpl objMibImpl;							//MIB库实现
public:
	CSnmpMib();
	virtual ~CSnmpMib();

	uint32 InitialClassObject(void/*CCommunication* objpIn*/);    //  初始化类对象
	//获得上级通信对象指针
//	CCommunication* GetCommunication();
	//获得SNMP数据输入输出对象
	CSnmpDataInOut* GetSnmpDataInOut();
	//获得MIB库实现
	CMibImpl* GetMibImpl();

};

#endif /* CSNMPMIB_H_ */
