/*
 * CTSCrossConnectionManager.h
 *
 *  Created on: 2013-5-2
 *      Author: Administrator
 */

#ifndef CTSCROSSCONNECTIONMANAGER_H_
#define CTSCROSSCONNECTIONMANAGER_H_

#include "EZ_types.h"
#include <map>
#include <string>
#include "CMSSave.h"
typedef std::string MyString;

typedef struct {
	uint32 west;
	uint32 east;
	uint8 name[32];
	uint8 desc[32];
}ts_cross_conn_data_T;

typedef struct {
	uint32 size;
	ts_cross_conn_data_T ccdata[32];
	uint32 crc;
}ts_cross_store_T;

class CCrossConnection;
class CTSCrossConnectionManager {
	CMSSave FlashDriver;
	EZ_FLASH_DATA_T storeInfo;
	ts_cross_store_T storeData;
	uint32 CreatConnection_start(uint32 uiSour, uint32 uiDest);
	uint32 SetXcName_start(uint32 uiXcUID, MyString& name);
	uint32 SetXcDescription_start(uint32 uiXcUID, MyString& desc);
public:
	CTSCrossConnectionManager();
	virtual ~CTSCrossConnectionManager();

	uint32 CreatConnection(uint32 uiSour, uint32 uiDest);

	uint32 DeleteOneTSXCConnect(uint32 uiUID);
	int GetFirstSnOfConnection(void);
	int GetNextSnConnection(int iStartSn);
	uint32 SetXcName(uint32 uiXcUID, MyString& name);
	uint32 SetXcDescription(uint32 uiXcUID, MyString& desc);

	uint32 GetXcName(uint32 uiXcUID, MyString&);
	uint32 GetXcDescription(uint32 uiXcUID, MyString&);

	uint32 GetWestID(uint32 uiNodeUID);
	uint32 GetEastID(uint32 uiNodeUID);
	void RestoreDefaultConfig(void);
	uint32 GetCurrentMappingNumber(void);

private:
	static int currentSn;
	std::map<int, CCrossConnection*> cc;
	std::map<int, CCrossConnection*>::iterator it;
	void makeConfigData(void);
};

#endif /* CTSCROSSCONNECTIONMANAGER_H_ */
