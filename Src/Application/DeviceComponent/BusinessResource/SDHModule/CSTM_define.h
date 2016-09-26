/*
 * CSTM_define.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef CSTM_DEFINE_H_
#define CSTM_DEFINE_H_


#if defined (__cplusplus)
extern "C"
{
#endif

#include "CVC12_define.h"

typedef enum {
	MS_LOF,
	MS_LOM,
	MS_LOS,
	MS_OOF,
	MS_AIS,
	MS_RDI,
	J0_TIM,
	B1_EXC,
	B2_EXC,
	RS_BIP,
	MS_BIP,
	MS_EXC,
	MS_DEG,
	MS_type_size,
	MS_type_base = 526
}MS_alarm_type_E;

typedef enum {
	AU4_LOP,
	AU4_AIS,
	AU_type_size,
	AU_type_base = 544
}AU_alarm_type_E;

typedef enum {
	VC4_AIS,
	VC4_UNEQ,
	VC4_RDI,
	VC4_SLM,
	VC4_TIM,
	VC4_LOM,
	VC4_EXC,
	VC4_REI,
	VC4_BIP,
	VC4_OOM,
	VC4_DEG,
	VC_type_size,
	VC_type_base = 560
}VC_alarm_type_E;

#define STM_Alarm_size (MS_type_size + AU_type_size + VC_type_size)

typedef struct {
	Alarm_property_T alarm_property[STM_Alarm_size];
	VC12_config_data vc12_data[63];
	uint8 enable;
	uint8 als;	//bit7~4 enalbe bit 3~0 mode
	uint8 desc[32];
	uint8 descLen;
	uint8 J0Transmit[16];
	uint8 JTLen;
	uint8 J0Expected[16];
	uint8 JELen;
}STM_config_data;


#if defined (__cplusplus)
}
#endif
#endif /* CSTM_DEFINE_H_ */
