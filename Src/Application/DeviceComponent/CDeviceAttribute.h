/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ezwell-tech.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** Created by:				Liu Weifeng
** Created date:			2011-06-22
** Version:				    1.0
** Descriptions:			
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**********************************************************************************************************************/

#ifndef CDeviceAttribute_H
#define CDeviceAttribute_H

//#include "CDeviceAttribute.h"
#include "EZ_types.h"
//#include "CMain.h"
#include "CAttributeSave.h"
#include "CAttributeFlash.h"

#define DEFMaxNameNumber    31

typedef enum {
	ver_boot,
	ver_mainsoft,
	ver_pcb,
	ver_glulogic,	//xo2 640
	ver_slotlogic,	//lx9
	ver_optlogic,	//xo2 1200
	ver_size

}version_E;

typedef struct {
	uint16 year;
	uint8 month;
	uint8 day;
	uint8 hour;
	uint8 minute;
	uint8 second;
}DATE_TIME_T;


typedef enum {
	type_isap_8eth = 10,			//8��̫���� ��Ƭ8306E�˿ڷ���ʵ�֣�����4��VCG
	type_isap_4eth_switch = 11,		//4��̫��������8306Eʵ�֣�����VLAN��QOS��
	type_isap_4eth_isolation = 16,	//4��̫����AC104�������
	type_isap_4eth_iso2 = 12,		//4��̫����8306E�˿ڷ���ʵ��
	type_emux_v10 = 13,
	type_tm_4eth_switch = 14,		//TM 4��̫����������VCG
	type_emux_v12 = 23,
	type_isap_A_4eth_iso = 24,
	type_isap_A_8eth_iso = 25,
}Dev_Sub_type_E;
//class CMain;
//class CSystem;
class CDeviceAttribute {
private:
//	STVersion stVersion[ver_size];

    uint8 *ucpExternalIP;
    uint8 *ucpExternalMask;
    uint8 *ucpGatewayIP;
    uint8 *ucpInternalIP;
    uint8 *ucpInternalMask;
    uint8 ucMACAddress[6];
	uint16 usBasePort;
    uint8 *ucpTrapDestIP;
  
    uint8 ucExtIPTmp[4];
public:
    static const uint8 ver_num_V10 = 16;
//    CMain *objpCMain;
//    CSystem *objpCSystem;
    CAttributeFlash *objpAttSave;
	CAttributeFlash DevAttr;

	CDeviceAttribute();
    ~CDeviceAttribute();

//    uint32 InitialClassObject(CSystem* objpAttribute);
    uint32 InitialSystem(void);         //  ��ʼ��ϵͳ

    uint8* GetDeviceName(uint32* uipLength);
	uint8* GetDeviceUser(uint32* uipLength);
	uint8* GetDeviceDescription(uint32* uipLength);
    uint8* GetDeviceBaseOther(uint32* uipLength);

    uint32 SetDeviceName(uint8* ucpName, uint32 uiLength);
	uint32 SetDeviceUser(uint8* ucpName, uint32 uiLength);
	uint32 SetDeviceDescription(uint8* ucpName, uint32 uiLength);
    uint32 SetDeviceBaseOther( uint8* ucpName, uint32 uiLength );

    uint8* GetDeviceContact(uint32* uipLength);							//����豸��ϵ��
    uint8* GetDeviceLocation(uint32* uipLength);						//����豸λ������
    uint32 SetDeviceContact(uint8* ucpName, uint32 uiLength);			//�����豸��ϵ��
    uint32 SetDeviceLocation(uint8* ucpName, uint32 uiLength);			//�����豸λ������


    //Communication parameter
    uint32  GetExternalIP(void);
    uint32  GetExternalMask(void);
	uint32  GetGatewayIP(void);
	uint32  GetInternalIP(void);
	uint32  GetInternalMask(void);

	uint8*  GetMACAddress(void) {
		return ucMACAddress;
	}
	uint32  GetBasePort(void);
	uint32  GetTrapDestIP(void);


	uint32 SetExternalIP(uint8* ucpIP);
	uint32 SetExternalMask(uint8* ucpIP);
	uint32 SetGatewayIP(uint8* ucpIP);
	uint32 SetInternalIP(uint8* ucpIP);
	uint32 SetInternalMask(uint8* ucpIP);

    uint32 SetMACAddress(uint8* ucpMac);
    uint32 SetBasePort(uint16 usPort);
    uint32 SetTrapDestIP(uint8* ucpIP);

	uint32 SetSerialNumber(uint32 uiVersion);
	uint32 GetSerialNumber(void);
	uint32 SetProductionDate(DATE_TIME_T* s);
	char* GetProductionDate(void);

    //Version
    int GetVersion(uint32 uiIndex, STVersion&);
//	uint32 SetVersionB(uint32 uiIndex,uint32 uiValue);
//	uint32 FetchVersionB(void);
	static uint32 GetNextVersionIndexbyIndex(uint32 uiIndex, uint32* uiNextIndex);
	//��õ�һ���汾����
	static uint32 GetFirstVersionIndex();

  	uint8* ReadExternalIP(void) {
  		return ucpExternalIP;
  	};
	uint8* ReadExternalMask(void){
		return ucpExternalMask;
	};
	uint8* ReadGatewayIP(void){
		return ucpGatewayIP;
	};
	uint8* ReadInternalIP(void){
		return ucpInternalIP;
	};
	uint8* ReadInternalMask(void){
		return ucpInternalMask;
	};

    uint8* ReadMACAddress(void){
    	return ucMACAddress;
    };
    uint16 ReadBasePort(void){
    	return usBasePort;
    };
    uint8* ReadTrapDestIP(void){
    	return ucpTrapDestIP;
    };


    uint32 GetSysClock(void);
    uint32 SetSysClock(uint32 mode, bool save = true);

    uint32 GetPcmClock(void);
    uint32 SetPcmClock(uint32 mode, bool save = true);

    uint32 GetDeviceSubtype(void);


 //   void initialize( CMain* objpMain );

};

#endif

