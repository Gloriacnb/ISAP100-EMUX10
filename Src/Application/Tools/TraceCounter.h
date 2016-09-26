/*
 * TraceCounter.h
 *
 *  Created on: 2013-3-14
 *      Author: Administrator
 */

#ifndef TRACECOUNTER_H_
#define TRACECOUNTER_H_

// #if defined (__cplusplus)
// extern "C"
// {
// #endif

#include "EZ_types.h"

typedef struct {
	uint32 interrupt;
	uint32 rcv;
	uint32 rcv_valid;
	uint32 local;
	uint32 transmit;
	uint32 broadcast;
	uint32 transmit_up;
} Trace_T;
//extern static uint32 eth_interrupt;
//extern static uint32 eth_rcv;
//extern static uint32 eth_rcv_valid;
//extern static uint32 eth_local;
//extern static uint32 eth_transmit;
//extern static uint32 eth_broadcast;
//
//extern static uint32 dcc_rcv;
//extern static uint32 dcc_local;
//extern static uint32 dcc_transmit;

extern Trace_T eth_trace;
extern Trace_T dcc_trace;

extern uint32 stack_res_eth;
extern uint32 stack_res_dcc;

// #if defined (__cplusplus)
// }
// #endif

#endif /* TRACECOUNTER_H_ */
