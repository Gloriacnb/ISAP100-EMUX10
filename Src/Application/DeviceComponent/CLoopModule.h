/*
 * CLoopModule.h
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#ifndef CLOOPMODULE_H_
#define CLOOPMODULE_H_

#include <map>
#include "EZ_types.h"
#include "RealPortBase.h"
#include <rtl.h>
#include "RTC.h"
#include "SysError.h"
#include <iostream>

class CLoopRecord {
	RealPortBase* port;
	uint32 startSeconds;
	uint32 duration;  //unit seconds
	uint8 type;

public:
	CLoopRecord(uint32 uid, int tp, uint32 seconds) {
		port = RealPortBase::getPortInstance(uid);
		if( !port ) {
			throw SysError("!!!no port!!!");
		}
		type = tp;
		startSeconds = RTC::getRunningSecs();
		duration = seconds;
		port->setLoop(type);
	};
	~CLoopRecord() {
		port->setLoop(no_loop);
	};

	uint8 getLoopType(void) {
		return type;
	};
	uint32 getStartTime(void) {
		return RTC::converRunningSecsToUTC(startSeconds);
	};

	uint32 getEndTime(void) {
		return getStartTime() + duration;
	};

	bool timeOut(void) {
		if( RTC::getRunningSecs() > startSeconds+duration ) {
			return true;
		}
		return false;
	};

};

class CLoopModule {
	CLoopModule();
	CLoopModule(const CLoopModule&);
	CLoopModule& operator= (CLoopModule&);
	virtual ~CLoopModule();
	static CLoopModule loopModule;
public:
	static CLoopModule& instance(void) {
		static bool inited = false;
		if( !inited ) {
			inited = true;
			os_mut_init(mut);
		}
		return loopModule;
	};

	int addLoopRecord(uint32 uid, int type, uint32 secs) {
		try{
			CLoopRecord* rd = new CLoopRecord(uid, type, secs);
			if( rd ) {
				os_mut_wait(mut, 0xffff);
				mapLoop.insert( std::pair<uint32, CLoopRecord*>(uid, rd));
				os_mut_release(mut);
				return 0x5A;
			}
		}
		catch(SysError& e) {
			std::cout << e.what() << std::endl;
		}
		return -1;
	};

	int deleteLoopRecord(uint32 uid) {
		std::map<uint32, CLoopRecord*>::iterator it = mapLoop.find(uid);
		if( it != mapLoop.end() ) {
			delete it->second;
			os_mut_wait(mut, 0xffff);
			mapLoop.erase(it);
			os_mut_release(mut);
			return 0x5A;
		}
		return -1;
	};

	uint32 getFirstLoopPortUID(void) {
		std::map<uint32, CLoopRecord*>::iterator it = mapLoop.begin();
		if( it != mapLoop.end() ) {
			return it->first;
		}
		return 0;
	};

	uint32 getNextLoopPortUID(uint32 suid) {
		std::map<uint32, CLoopRecord*>::iterator it = mapLoop.find(suid);
		if( it != mapLoop.end() ) {
			it++;
			if( it != mapLoop.end() ) {
				return it->first;
			}
		}
		return 0;
	};

	CLoopRecord* getLoopRecord(uint32 uid) {
		std::map<uint32, CLoopRecord*>::iterator it = mapLoop.find(uid);
		if( it != mapLoop.end() ) {
			return it->second;
		}
		return 0;

	};

	void runLoopCheck(void) {
		os_mut_wait(mut, 0xffff);
		std::map<uint32, CLoopRecord*>::iterator it = mapLoop.begin();
		while( it != mapLoop.end() ) {
			if( it->second->timeOut() ) {
				delete it->second;
				mapLoop.erase(it);
			}
			it++;
		}
		os_mut_release(mut);
	};

	uint32 getLoopRecordNumber(void) {
		return mapLoop.size();
	};

private:
//	bool inited;
	static OS_MUT mut;
	std::map<uint32, CLoopRecord*> mapLoop;

};

#endif /* CLOOPMODULE_H_ */
