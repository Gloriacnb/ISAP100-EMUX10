/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CUDPData.h
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

#ifndef CUDPDATA_H_
#define CUDPDATA_H_
#include "EZ_types.h"
class CUDPData
{
private:
	uint8 ucSourceMAC[6];						//源MAC
	uint8 ucDestinationMAC[6];					//目的MAC
	uint8 ucSourceIP[4];						//源IP
	uint8 ucDestinationIP[4];					//目的IP
	uint16 usSourcePort;						//源端口
	uint16 usDestinationPort;					//目的端口
	uint8* ucpUDPData;							//UDP数据Buffer
	uint32 uiDataLength;						//UDP数据长度
public:
	CUDPData();
	CUDPData(uint8* remip, uint16 remport, uint8* pdata, uint16 len);
	virtual ~CUDPData();
	//从UDP数据包中解码出UDP数据
	uint32 Decode(uint8* ucpBuffer,uint32 uiLength);
	//交换源和目的
	uint32 Switch();
	//获得源MAC
	uint8* GetSourceMAC();
	//获得目的MAC
	uint8* GetDestinationMAC();
	//获得源IP
	uint8* GetSourceIP();
	//获得目的IP
	uint8* GetDestinationIP();
	//获得源端口
	uint16 GetSourcePort();
	//获得目的端口
	uint16 GetDestinationPort();
	//获得数据
	uint8* GetData(uint32* uipDataLength);
	//克隆UDP数据对象
	uint32 Clone(CUDPData* objpData);
	//设置数据
	uint32 SetData(uint8* ucpBuffer,uint32 uiLength);
	//从IP包中解码出UDP数据
	uint32 DecodeFromIPPackage(uint8* ucpBuffer,uint32 uiLength);
    uint32 SetDestinationMAC(uint8* ucpDestMAC);
};

#endif /* CUDPDATA_H_ */
