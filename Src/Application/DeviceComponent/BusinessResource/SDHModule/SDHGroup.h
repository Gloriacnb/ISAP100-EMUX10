/*
 * SDHGroup.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef SDHGROUP_H_
#define SDHGROUP_H_

#include "CMSSave.h"
#include "CSTM_define.h"
#include <map>

typedef struct {
	STM_config_data stm_data[2];
	uint8 portBackup;
	uint8 als_mode;
	uint32 crc;
}SDH_Config_all;

class CSTM;
class SDHGroup {
public:
	SDHGroup(int stmnum);
	virtual ~SDHGroup();
	void RestoreDefaultConfig(void);
	void StoreConfigData(void);

	uint32 GetFirstUid(void) {
		return mapSTM.begin()->first;
	};
	uint32 GetNextUid(uint32 suid) {
		std::map<uint32, CSTM*>::iterator it = mapSTM.find(suid);
		if( it != mapSTM.end() ) {
			++it;
			if( it != mapSTM.end() ) {
				return it->first;
			}
		}
		return 0;
	};

	CSTM* GetStmObjByUid(uint32 uid) {
		std::map<uint32, CSTM*>::iterator it = mapSTM.find(uid);
		if( it != mapSTM.end() ) {
			return (*it).second;
		}
		return 0;
	};

	uint8 getPortBackup(void) {
		return configData.portBackup;
	};
	void setPortBackup(uint8 en);

	uint8 getALSMode(void) {
		return configData.als_mode;
	};
	void setALSMode(uint8 mode);

private:
	int stmNumber;
	CMSSave FlashDriver;
	std::map<uint32, CSTM*> mapSTM;
	SDH_Config_all configData;

	void AlarmPropertyDefault(int sn);
	void setPortBackupChip(uint8 en);
	bool SetSTMAlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl);
	bool SetSTMAlarmProperty(uint32 stmUID, uint32 typeID, Alarm_Property_Option opt, uint32 newVl);
	bool SetVC12AlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl);
	bool SetVC12AlarmProperty(uint32 stmUID, uint32 typeID, Alarm_Property_Option opt, uint32 newVl);
};

#endif /* SDHGROUP_H_ */
