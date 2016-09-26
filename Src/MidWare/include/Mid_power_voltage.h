/*
 * Mid_power_voltage.h
 *
 *  Created on: 2013-11-2
 *      Author: Administrator
 */

#ifndef MID_POWER_VOLTAGE_H_
#define MID_POWER_VOLTAGE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"	

void powerSlotInit(void);
bool PowerCardExist(uint8 sn);


#if defined (__cplusplus)
}
#endif
#endif /* MID_POWER_VOLTAGE_H_ */
