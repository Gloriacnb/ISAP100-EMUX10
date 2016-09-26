/*
 * RealPortBase.h
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#ifndef REALPORTBASE_H_
#define REALPORTBASE_H_

#include <map>
#include "EZ_types.h"
#include <string>

typedef enum {
	dev_and_line_loop,
	dev_loop,
	line_loop,
	no_loop
}LOOP_TYPE_E;

class RealPortBase {
	static std::map<uint32, RealPortBase*> mapPort;
public:

	RealPortBase(uint32 uid);
	virtual ~RealPortBase();

	/* group option */
	static RealPortBase* getPortInstance(uint32 uid) {
		std::map<uint32, RealPortBase*>::iterator it = mapPort.find(uid);
		if( it != mapPort.end() ) {
			return it->second;
		}
		return 0;
	};

	static RealPortBase* getFirstInstance(void) {
		std::map<uint32, RealPortBase*>::iterator it = mapPort.begin();
		if( it != mapPort.end() ) {
			return it->second;
		}
		return 0;
	};

	static RealPortBase* getNextInstance(uint32 suid) {
		std::map<uint32, RealPortBase*>::iterator it = mapPort.find(suid);
		if( it != mapPort.end() ) {
			it++;
			if( it != mapPort.end() ) {
				return it->second;
			}
		}
		return 0;
	};


	virtual int setLoop(const int type) = 0;
	virtual std::string& getName(void) = 0;
	virtual int getPortSpeed(void) = 0;
	uint32 getUID(void) {
		return itsUID;
	};

private:
	const uint32 itsUID;
};

#endif /* REALPORTBASE_H_ */
