/****************************************Copyright (c)*****************************************************************
 **
 **                               Easy Broadband Technology Co., Ltd.
 **
 **                                  http://www.ebbnetwork.com
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CAttributeSave.h
 ** Created by:          wang ying
 ** Created date:        2011-7-19
 ** Descriptions:        设备属性的存储
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:
 ** Modified date:
 ** Version:
 ** Descriptions:
 ** Rechecked by:
 ***********************************************************************************************************************/
#ifndef CATTRIBUTESAVE_H_
#define CATTRIBUTESAVE_H_

#include "EZ_types.h"
#include "CCheckData.h"
//#include "CMSSave.h"

/*typedef  struct
 {                 //__align(1)
 uint8 ucPower;
 uint8 ucProducePlace;
 uint8 ucActVersion;
 uint8 ucConsumer[2];
 uint8 ucSerialNumber[2];
 uint8 DeviceVersionDate[3];
 uint8 ucReserve1[13];
 }STVersionStore;

 typedef struct
 {
 uint8 ucDeviceName[32];
 uint8 ucUserName[32];
 uint8 ucDescriberName[32];
 uint8 ucOther[32];
 uint8 ucExtIP[4];
 uint8 ucExtMask[4];
 uint8 ucGatIP[4];
 uint8 ucIntIP[4];
 uint8 ucIntMask[4];
 uint8 ucMacAdd[6];
 uint8 ucBasePort[2];
 uint8 ucTrapIP[4];
 STVersionStore stVersion;
 uint8 ucContact[32];
 uint8 ucLocation[32];
 uint8 ucReserve2[20];
 uint32 uiCRCResult;
 
 uint32 uiFlag[2];
 }STDeviceAttributeStore;*/

class CAttributeSave {

public:
	//STDeviceAttributeStore  stAttributeStore;
	CAttributeSave();
	virtual ~CAttributeSave();

	virtual uint32 AttributeRecover(void) = 0;
	virtual uint32 SetDeviceName(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetDeviceName(uint32* uipLength) = 0;
	virtual uint32 SetUserName(uint8* uipBuffer, uint32 uiLength) = 0;
	virtual uint8* GetUserName(uint32* uipLength) = 0;
	virtual uint32 SetDescriberName(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetDescriberName(uint32* uipLength) = 0;
	virtual uint32 SetOther(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetOther(uint32* uipLength) = 0;
	virtual uint32 SetContact(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetContact(uint32* uipLength) = 0;
	virtual uint32 SetLocation(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetLocation(uint32* uipLength) = 0;

	virtual uint32 SetExtIP(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetExtIP(uint32* uipLength) = 0;
	virtual uint32 SetExtMask(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetExtMask(uint32* uipLength) = 0;
	virtual uint32 SetGatIP(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetGatIP(uint32* uipLength) = 0;
	virtual uint32 SetIntIP(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetIntIP(uint32* uipLength) = 0;
	virtual uint32 SetIntMask(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetIntMask(uint32* uipLength) = 0;
	virtual uint32 SetMacAdd(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetMacAdd(uint32* uipLength) = 0;
	virtual uint32 SetTrapIP(uint8* ucpBuffer, uint32 uiLength) = 0;
	virtual uint8* GetTrapIP(uint32* uipLength) = 0;
	virtual uint32 SetBasePort(uint16 usPort) = 0;
	virtual uint32 GetBasePort(uint16* uspPort) = 0;

	virtual uint32 SetVerionPower(uint32 uiVersion) = 0;
	virtual uint32 GetVerionPower(uint32* uipVersion) = 0;
	virtual uint32 SetVerionProducePlace(uint32 uiVersion) = 0;
	virtual uint32 GetVerionProducePlace(uint32* uipVersion) = 0;
	virtual uint32 SetVerionActing(uint32 uiVersion) = 0;
	virtual uint32 GetVerionActing(uint32* uipVersion) = 0;
	virtual uint32 SetVerionConsumer(uint32 uiVersion) = 0;
	virtual uint32 GetVerionConsumer(uint32* uipVersion) = 0;
	virtual uint32 SetVerionSerialNumber(uint32 uiVersion) = 0;
	virtual uint32 GetVerionSerialNumber(uint32* uipVersion) = 0;
	virtual uint32 SetVerionDate(uint32 uiVersion) = 0;
	virtual uint32 GetVerionDate(uint32* uipVersion) = 0;

};

#endif /* CATTRIBUTESAVE_H_ */
