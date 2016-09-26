/*
 * CVC12_define.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef CVC12_DEFINE_H_
#define CVC12_DEFINE_H_

#include "AlarmElement_define.h"

#if defined (__cplusplus)
extern "C"
{
#endif

typedef enum {
	TU12_LOP,
	TU_type_size,
	TU_type_base = 608
}TU_Alarm_type_E;

typedef enum {
	VC12_AIS,
	VC12_UNEQ,
	VC12_RDI,
	VC12_SLM,
	VC12_TIM,
	VC12_EXC,
	VC12_REI,
	VC12_RFI,
	VC12_BIP,
	VC12_K4_B1_LOM,
	VC12_K4_B1_PLM,
	LP_type_size,
	LP_type_base = 624
}LP_Alarm_type_E;

#define VC12_Alarm_size (TU_type_size+LP_type_size)

typedef struct {
	Alarm_property_T alarm_Property[VC12_Alarm_size];
}VC12_config_data;

#if defined (__cplusplus)
}
#endif
#endif /* CVC12_DEFINE_H_ */
