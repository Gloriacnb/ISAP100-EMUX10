/*
 * CVC12CrossConnectionMagager.h
 *
 *  Created on: 2013-2-25
 *      Author: Administrator
 */

#ifndef CVC12CROSSCONNECTIONMAGAGER_H_
#define CVC12CROSSCONNECTIONMAGAGER_H_

#include "EZ_types.h"
#include <map>
#include <string>
#include "CMSSave.h"
typedef std::string MyString;

typedef struct {
	uint32 E1;
	uint32 VC12;
	uint8 name[32];
	uint8 desc[32];
	uint8 sncp;
}cross_conn_data_T;

typedef struct {
	uint32 size;
	cross_conn_data_T ccdata[24];
	uint32 crc;
}cross_store_T;

class CCrossConnection;
class CVC12CrossConnectionMagager {
	CMSSave FlashDriver;
	EZ_FLASH_DATA_T storeInfo;
	cross_store_T storeData;
	uint32 CreatConnection_start(uint32 uiSour, uint32 uiDest);
	uint32 SetXcName_start(uint32 uiXcUID, MyString& name);
	uint32 SetXcDescription_start(uint32 uiXcUID, MyString& desc);
	uint32 setXcSncp_start(uint32 uiXcUID, uint32 en);
public:
	CVC12CrossConnectionMagager();
	virtual ~CVC12CrossConnectionMagager();

	uint32 CreatConnection(uint32 uiSour, uint32 uiDest);

	uint32 DeleteOneE1XCConnect(uint32 uiUID);
	int GetFirstSnOfConnection(void);
	int GetNextSnConnection(int iStartSn);
	uint32 GetXcName(uint32 uiXcUID, MyString&);
	uint32 GetXcDescription(uint32 uiXcUID, MyString&);
	uint32 SetXcName(uint32 uiXcUID, MyString& name);
	uint32 SetXcDescription(uint32 uiXcUID, MyString& desc);

	uint32 GetCCE1ID(uint32 uiNodeUID);
	uint32 GetCCVC12ID(uint32 uiNodeUID);

	uint32 getXcSncp(uint32 uiXcUID);
	uint32 setXcSncp(uint32 uiXcUID, uint32 en);

	void RestoreDefaultConfig(void);
	uint32 GetCurrentMappingNumber(void);

private:
	static int currentSn;
	std::map<int, CCrossConnection*> cc;
	std::map<int, CCrossConnection*>::iterator it;
	void makeConfigData(void);
};

#endif /* CVC12CROSSCONNECTIONMAGAGER_H_ */
