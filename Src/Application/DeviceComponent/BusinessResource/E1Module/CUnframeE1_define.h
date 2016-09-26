/*
 * CUnframeE1_define.h
 *
 *  Created on: 2013-4-25
 *      Author: Administrator
 */

#ifndef CUNFRAMEE1_DEFINE_H_
#define CUNFRAMEE1_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif
#include "AlarmElement_define.h"

typedef enum {
	E1_LOS,
	E1_AIS,
	E1_type_size,
	E1_type_base = 1024
}UE1_alarm_type_E;

typedef struct {
	Alarm_property_T alarm_property[E1_type_size];
	uint8 enable;
	char desc[32];
	uint8 dlen;
}UE1_Config_Data_T;

#if defined (__cplusplus)
}
#endif
#endif /* CUNFRAMEE1_DEFINE_H_ */
