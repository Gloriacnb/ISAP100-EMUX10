/*
 * SwitchModule.h
 *
 *  Created on: 2014-4-17
 *      Author: Administrator
 */

#ifndef SWITCHMODULE_H_
#define SWITCHMODULE_H_
#include "EZ_types.h"

typedef struct {
	uint8 mode;
	uint8 mtu;
}Switch_Base_cfg_T;

class EthBoard;
class CMSSave;

class SwitchModule {
	SwitchModule();
public:
	SwitchModule(EthBoard* b, Switch_Base_cfg_T* cfg, CMSSave* save);
	virtual ~SwitchModule();

	static SwitchModule* getInstance(void) {
		return obj;
	};

	uint8 getSwitchMode(void) {
		return ConfigData->mode;
	};
	uint8 getSwitchMTU(void) {
		return ConfigData->mtu;
	};

	bool setSwitchMode(uint8 mode, bool save = true );
	bool setSwitchMTU(uint8 m, bool save = true);

private:
	Switch_Base_cfg_T* ConfigData;
	EthBoard* Board;
	static SwitchModule* obj;
	CMSSave* storer;
};

#endif /* SWITCHMODULE_H_ */
