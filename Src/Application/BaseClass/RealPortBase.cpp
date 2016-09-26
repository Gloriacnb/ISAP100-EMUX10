/*
 * RealPortBase.cpp
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#include "RealPortBase.h"


std::map<uint32, RealPortBase*> RealPortBase::mapPort;

RealPortBase::RealPortBase(uint32 uid) : itsUID(uid) {
	mapPort.insert( std::pair<uint32, RealPortBase*>(itsUID, this));

}

RealPortBase::~RealPortBase() {
//	std::map<uint32, RealPortBase*>::iterator it = mapPort.find(itsUID);
//	if( it != mapPort.end() ) {
//		mapPort.erase(it);
//	}
	mapPort.erase(itsUID);

}

