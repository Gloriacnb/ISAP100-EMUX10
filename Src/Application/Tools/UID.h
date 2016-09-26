/*
 * UID.h
 *
 *  Created on: 2013-2-26
 *      Author: Administrator
 */

#ifndef UID_H_
#define UID_H_

#include "EZ_types.h"
//typedef unsigned char uint8;
//typedef unsigned int  uint32;
enum {
    subtype_dcc = 0,
    subtype_sabit,
    subtype_tsdcn,
	subtype_dcn,
};

typedef struct {
	uint8 slot;
	uint8 stm;
	uint8 hp;
	uint8 lp;
} ST_SDH_VC12;

typedef struct {
	uint8 slot;
	uint8 stm;
} ST_SDH_STM;

typedef struct {
	uint8 slot;
	uint8 vcg;
} ST_VCG;

typedef struct {
	uint8 slot;
	uint8 vcg;
	uint8 member;
} ST_VCG_Member;

typedef struct {
	uint8 slot;
	uint8 E1;
} ST_E1;

typedef struct {
	uint8 slot;
	uint8 port;
} ST_FE;

typedef struct {
	uint8 slot;
	uint8 port;
} ST_FX;

typedef struct {
	uint8 slot;
	uint8 E1;
	uint8 TS;
} ST_Time_Slot;

typedef struct {
	uint8 slot;
	uint8 stbus;
} ST_Stbus;

typedef struct {
    uint8 slot;
    uint8 subtype;
    uint8 sn;
}ST_NM_Channel;

typedef union {
	ST_SDH_VC12 vc12;
	ST_SDH_STM stm;
	ST_VCG vcg;
	ST_VCG_Member member;
	ST_E1 E1;
	ST_FE FE;
	ST_FX FX;
	ST_Time_Slot ts;
	ST_Stbus stbus;
	ST_NM_Channel nm;
} UN_Info;

class UID {
public:
	UID();
	virtual ~UID();
	static UN_Info breakUID(uint32 id);
	static uint32 makeUID(UN_Info* info);
	static uint32 makeUID(ST_SDH_VC12*);
	static uint32 makeUID(ST_SDH_STM*);
	static uint32 makeUID(ST_E1*);
	static uint32 makeUID(ST_FE*);
	static uint32 makeUID(ST_FX*);

	static uint32 makeUID(ST_Time_Slot*);
	static uint32 makeUID(ST_VCG*);
	static uint32 makeUID(ST_VCG_Member*);
	static uint32 makeUID(ST_Stbus*);
    static uint32 makeUID(ST_NM_Channel*);

	static uint8 getPortTypeByUID(uint32 id);

	static const uint8 type_SDH = 1;
	static const uint8 type_VCG = 0x40;
	static const uint8 type_E1 = 0x20;
	static const uint8 type_FE = 0x30;
	static const uint8 type_FX = 0x31;
	static const uint8 type_TS = 0x70;
	static const uint8 type_stbus = 0x60;
	static const uint8 type_nm_channel = 0x55;
};

#endif /* UID_H_ */
