/*
 * CNME1Port_define.h
 *
 *  Created on: 2015Äê12ÔÂ28ÈÕ
 *      Author: Administrator
 */


#ifndef CNME1PORT_DEFINE_H_
#define CNME1PORT_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "AlarmElement_define.h"

typedef enum {
	FE1_LOS,
	FE1_AIS,
	FE1_LOF,
	FE1_type_size,
	FE1_type_base = 1024
}UFE1_alarm_type_E;

typedef struct {
	Alarm_property_T alarm_property[FE1_type_size];
	uint8 enable;
	uint8 mode;
	uint8 desc[32];
	uint8 dlen;
}UFE1_Config_Data_T;

#if defined (__cplusplus)
}
#endif
#endif /* CNME1PORT_DEFINE_H_ */
