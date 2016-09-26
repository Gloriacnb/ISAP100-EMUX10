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
#ifndef CATTRIBUTEFLASH_H_
#define CATTRIBUTEFLASH_H_

#include "EZ_types.h"

#include "CMSSave.h"
#include "CAttributeSave.h"

typedef struct {                 //__align(1)
	uint8 ucPower;
	uint8 ucProducePlace;
	uint8 ucActVersion;
	uint8 ucConsumer[2];
	uint8 ucSerialNumber[2];
	uint8 DeviceVersionDate[3];
	uint8 ucReserve1[13];
} STVersionStore;

typedef struct {
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
//	STVersionStore stVersion;
	uint8 ucContact[32];
	uint8 ucLocation[32];
	uint8 ucSysClock;
	uint8 ucSysSubDevice;
	uint16 ucSerialNumber;
	char cProductiDate[19];
	uint8 ucPcmClock;
	uint32 uiCRCResult;

	uint32 uiFlag[2];
} STDeviceAttributeStore;

class CFlashImpl;
class CAttributeFlash: public CMSSave                 //, public CAttributeSave
{
	static const int uiPkgSize = 128;
	void LoadAttributeDefault(void);
	STDeviceAttributeStore stAttributeStore;
public:
	CAttributeFlash();
	virtual ~CAttributeFlash();
	uint32 InitialBussiness(void);      //  初始化业务
	uint32 AttributeRecover(void);
	uint32 SetDeviceName(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetDeviceName(uint32* uipLength);
	uint32 SetUserName(uint8* uipBuffer, uint32 uiLength);
	uint8* GetUserName(uint32* uipLength);
	uint32 SetDescriberName(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetDescriberName(uint32* uipLength);
	uint32 SetOther(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetOther(uint32* uipLength);
	uint32 SetContact(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetContact(uint32* uipLength);
	uint32 SetLocation(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetLocation(uint32* uipLength);

	uint32 SetExtIP(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetExtIP(uint32* uipLength);
	uint32 SetExtMask(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetExtMask(uint32* uipLength);
	uint32 SetGatIP(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetGatIP(uint32* uipLength);
	uint32 SetIntIP(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetIntIP(uint32* uipLength);
	uint32 SetIntMask(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetIntMask(uint32* uipLength);
	uint32 SetMacAdd(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetMacAdd(uint32* uipLength);
	uint32 SetTrapIP(uint8* ucpBuffer, uint32 uiLength);
	uint8* GetTrapIP(uint32* uipLength);
	uint32 SetBasePort(uint16 usPort);
	uint32 GetBasePort(uint16* uspPort);

//	virtual uint32 SetVerionPower(uint32 uiVersion);
//	virtual uint32 GetVerionPower(uint32* uipVersion);
//	virtual uint32 SetVerionProducePlace(uint32 uiVersion);
//	virtual uint32 GetVerionProducePlace(uint32* uipVersion);
//	virtual uint32 SetVerionActing(uint32 uiVersion);
//	virtual uint32 GetVerionActing(uint32* uipVersion);
//	virtual uint32 SetVerionConsumer(uint32 uiVersion);
//	virtual uint32 GetVerionConsumer(uint32* uipVersion);
	uint32 SetVerionSerialNumber(uint32 uiVersion);
	uint32 GetVerionSerialNumber(void);
	uint32 SetVerionDate(const char* s);
	char* GetVerionDate(void);

	uint32 GetSlotAttribute(uint32 uiSlotNum, uint32* uipCardType); //  通过槽位号获得槽位的属性
	uint32 ClearFlashDeviceAttribute();
	uint32 GetDeviceAttributeData(uint32 uiPkgNum, uint8* ucBuffer);
	uint32 SetDeviceAttributeData(uint32 uiPkgNum, uint8* ucBuffer);
	uint32 GetSysClock(void);
	uint32 SetSysClock(uint32 mode);
	uint32 GetSysSubDevice(void);
	uint32 SetSysSubDevice(uint32 type);
	uint32 GetPcmClock(void);
	uint32 SetPcmClock(uint32 mode);


};

#endif /* CATTRIBUTESAVE_H_ */
