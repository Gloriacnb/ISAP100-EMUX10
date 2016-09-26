/*
 * CVCG_define.h
 *
 *  Created on: 2013-4-8
 *      Author: Administrator
 */

#ifndef CVCG_DEFINE_H_
#define CVCG_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "AlarmElement_define.h"


typedef enum {
	VCG_NoMember,
	LaVCR_RxQFull,
	LaVCR_GIDM,
	LaVCR_GLOA,
	LaGR_SYNLoss,
	VCG_type_size,
	VCG_type_base = 780

}VCG_alarm_type_E;

typedef enum {
	LaVCT_DNU,
	LaVCR_TSF,
	LaVCR_LOMF2,
	LaVCR_FAIL,
	LaVCR_CRCE,
	LaVCR_SQM,
	Member_type_size,
	Member_type_base = 800

}Member_alarm_type_E;

#define VCG_alarm_size (VCG_type_size + Member_type_size)

typedef struct {
	uint32 vc12;
	uint8 sncp;
}vcg_member_cfg_T;

typedef struct {
	uint8 enable;
	uint8 band;
	vcg_member_cfg_T member[63];
	uint8 desc[32];
	uint8 descLen;
	uint8 lcas;
	Alarm_property_T alarmProperty[VCG_alarm_size];

}vcg_config_T;


#if defined (__cplusplus)
}
#endif
#endif /* CVCG_DEFINE_H_ */
