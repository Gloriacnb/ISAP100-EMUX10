/*
 * AlarmElement_define.h
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#ifndef ALARMELEMENT_DEFINE_H_
#define ALARMELEMENT_DEFINE_H_

#include "EZ_types.h"
#if defined (__cplusplus)
extern "C"
{
#endif

typedef enum {
	alarm_nochange,
	alarm_raise,
	alarm_clear,
}Alarm_event_E;

typedef enum {
	emerg = 1,
	primary,
	secondary,
	prompt,
}Alarm_level_E;

typedef enum {
	normal,
	alarm,
}Alarm_status_E;

typedef enum {
	opt_level,
	opt_trap,
	opt_mask,
	opt_size

}Alarm_Property_Option;

typedef struct {
	uint32 typeID;
	Alarm_level_E level;
	uint8 trap;
	uint8 mask;
}Alarm_property_T;


#if defined (__cplusplus)
}
#endif
#endif /* ALARMELEMENT_DEFINE_H_ */
