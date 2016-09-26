/*
 * CUInterface.h
 *
 *  Created on: 2013-7-29
 *      Author: Administrator
 */

#ifndef CUINTERFACE_H_
#define CUINTERFACE_H_

#include "RealPortBase.h"
#include <string>
#include "CUInterface_define.h"
#include <rtl.h>


typedef enum {
	int_error,
	int_act,
	int_M4,
	int_eoc,
}MC_Interrupt_E;

typedef enum {
	act_failed,
	act_success,
	act_continue,

}MC_Active_Result_E;

class CMSSave;
class CE1Channel;
class MidMC145572;

class CUInterface : public RealPortBase {
	static std::map<uint32, CUInterface*> UIF_group;
	static std::map<uint32, CUInterface*>::iterator it;
public:
	CUInterface(int sn, uint32 uid, UInterface_config_data*, CMSSave*, MidMC145572*);
	virtual ~CUInterface();

	virtual int setLoop(const int type);
	virtual std::string& getName(void);
	virtual int getPortSpeed(void);

	static CUInterface* getPort(uint32 n) {
		it = UIF_group.find(n);
		if( it != UIF_group.end() ) {
			return (*it).second;
		}
		return 0;
	};
	static uint32 GetFirstUid(void) {
		if( UIF_group.empty() ) {
			return 0;
		}
		return UIF_group.begin()->first;
	};
	static uint32 GetNextUid(uint32 suid) {
		it = UIF_group.find(suid);
		if( it != UIF_group.end() ) {
			++it;
			if( it != UIF_group.end() ) {
				return (*it).first;
			}
		}
		return 0;

	};

	int getPortSn() {
		return portSn+1;
	};
	int getPortSlot() {
		return getUID() >> 24;
	};

	uint8 getEnable(void) {
		return configData->enable;
	};

	char* getDescription(uint32* len) {
		*len = configData->dlen;
		return configData->desc;
	};

	uint8 getMode(void) {
		return configData->mode;
	};

	int setEnable(uint8 en);
	int setDescription(char*, uint8 len);
	int setMode(uint8 mode, bool save = true );

	MidMC145572* itsDriver(void) {
		return driver;
	};

	bool active(void);


private:
	int portSn;
	std::string name;
	CMSSave* storer;
	UInterface_config_data* configData;
	CE1Channel* linkChannel;
	MidMC145572* driver;
	bool Actived();
	bool activing();
	bool activeError();

	bool activeStarted;
	bool stoped;

	void startActive();
	OS_TID task_UActive;

	bool haveInterrupt();
	MC_Interrupt_E getInterruptType(void);

	void initLT();
	void initNT();

	MC_Active_Result_E isrLT();
	MC_Active_Result_E isrNT();
};

#endif /* CUINTERFACE_H_ */
