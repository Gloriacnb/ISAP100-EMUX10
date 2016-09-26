/*
 * UID.cpp
 *
 *  Created on: 2013-2-26
 *      Author: Administrator
 */

#include "UID.h"

UID::UID() {
	// TODO Auto-generated constructor stub

}

UID::~UID() {
	// TODO Auto-generated destructor stub
}

UN_Info UID::breakUID(uint32 id) {
	UN_Info info;
	uint8 type = (id >> 16) & 0xff;
	uint8 sub_type = (id>>6) & 0x3;
	uint8 slot = id >> 24;
	switch( type ) {
	case type_SDH:
		if(sub_type == 0) {
			info.stm.slot = slot;
			info.stm.stm = (id >> 12) & 0x0f;
		}
		else if( sub_type == 2 ) {
			info.vc12.slot = slot;
			info.vc12.stm = (id >> 12) & 0x0f;
			info.vc12.hp  = (id >>  8) & 0x0f;
			info.vc12.lp  = (id >>  0) & 0x3f;
		}
		else {
			throw 1;
		}
		break;
	case type_nm_channel: {
	    info.nm.slot = slot;
	    info.nm.subtype = sub_type;
	    info.nm.sn = id & 0xf;
	}
	    break;
	case type_E1:
		info.E1.slot = slot;
		info.E1.E1 = (id >> 8) & 0xff;
		break;
	case type_FE:
		info.FE.slot = slot;
		info.FE.port = (id >> 8) & 0xff;
		break;
	case type_FX:
		info.FX.slot = slot;
		info.FX.port = (id >> 8) & 0xff;
		break;
	case type_TS:
		info.ts.slot = slot;
		info.ts.E1 = (id >> 8) & 0xff;
		info.ts.TS = (id >> 0) & 0x1f;
		break;
	case type_VCG:
		if(sub_type == 0) {
			info.vcg.slot = slot;
			info.vcg.vcg = (id >> 8) & 0xff;
		}
		else if( sub_type == 2 ) {
			info.member.slot = slot;
			info.member.vcg = (id >> 8) & 0xff;
			info.member.member = (id >> 0) & 0x3f;
		}
		else {
			throw 1;
		}
		break;
	case type_stbus:
		info.stbus.slot = slot;
		info.stbus.stbus = (id >> 8) & 0xff;
		break;
	default:
		throw 2;
//		break;
	}

	return info;
}

uint32 UID::makeUID(ST_SDH_VC12* info) {
	return ( info->slot << 24) |
			(info->stm << 12) |
			(info->hp  <<  8) |
			(info->lp  <<  0) |
			(type_SDH  << 16) |
			(2         <<  6) ;
}
uint32 UID::makeUID(ST_SDH_STM* info) {
	return (info->slot << 24) |
			(info->stm << 12) |
			(type_SDH  << 16) ;
}
uint32 UID::makeUID(ST_E1* info) {
	return (info->slot << 24) |
			(info->E1  <<  8) |
			(type_E1   << 16) ;

}
uint32 UID::makeUID(ST_NM_Channel* info) {
    return (info->slot << 24) |
           (type_nm_channel << 16) |
           ((info->subtype & 3) << 6) |
           (info->sn) ;
}

uint32 UID::makeUID(ST_FE* info) {
	return (info->slot << 24) |
			(info->port  <<  8) |
			(type_FE   << 16) ;
}
uint32 UID::makeUID(ST_FX* info) {
	return (info->slot << 24) |
			(info->port  <<  8) |
			(type_FX   << 16) ;

}

uint32 UID::makeUID(ST_Time_Slot* info) {
	return ( info->slot << 24) |
			(info->E1   <<  8) |
			(info->TS   <<  0) |
			(type_TS    <<  16);
}
uint32 UID::makeUID(ST_VCG* info) {
	return ( info->slot << 24) |
			(info->vcg  << 8)  |
			(type_VCG   << 16) ;
}

uint32 UID::makeUID(ST_VCG_Member* info) {
	return ( info->slot  << 24) |
			(info->vcg   <<  8) |
			(info->member<<  0) |
			(2           <<  6) |
			(type_VCG    <<  16);
}

uint32 UID::makeUID(ST_Stbus* info) {
	return (info->slot << 24) |
			(info->stbus  <<  8) |
			(type_stbus   << 16) ;

}



uint8 UID::getPortTypeByUID(uint32 id) {
	return  (id >> 16) & 0xff;
}
