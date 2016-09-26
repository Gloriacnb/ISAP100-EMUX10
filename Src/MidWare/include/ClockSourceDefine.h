/*
 * ClockSourceDefine.h
 *
 *  Created on: 2014Äê12ÔÂ15ÈÕ
 *      Author: Administrator
 */


#ifndef CLOCKSOURCEDEFINE_H_
#define CLOCKSOURCEDEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

typedef enum {
	FREE_RUN,
	RECOVER_A,
	RECOVER_B,
	RECOVER_C,
	RECOVER_D,
	HOLD_OVER

}CLOCK_SOURCE_OP_E;

#if defined (__cplusplus)
}
#endif
#endif /* CLOCKSOURCEDEFINE_H_ */
