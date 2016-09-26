/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CSnmpDataInOut.h
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

#ifndef CSNMPDATAINOUT_H_
#define CSNMPDATAINOUT_H_
#include "EZ_types.h"
class CSnmpMib;
//class CUDPInterface;
class CUDPData;
class CSnmpDataInOut
{
public:

	static const uint32 uiConstResponseBufferSize = 2048;				//响应Buffer大小

	CSnmpDataInOut();
	virtual ~CSnmpDataInOut();
	//初始化类对象
	uint32 InitialClassObject(CSnmpMib* objpIn);

	//接收数据
	uint32 ReceiverData(CUDPData* objData);
	//获得SNMP响应数据包缓存Buffer
	uint8* GetResponseBuffer();
private:
	CSnmpMib* objpSnmpMib;										//上级SNMP和MIB对象指针
	uint8 ucResponseBuffer[uiConstResponseBufferSize];			//SNMP响应数据包缓存Buffer
};

#endif /* CSNMPDATAINOUT_H_ */
