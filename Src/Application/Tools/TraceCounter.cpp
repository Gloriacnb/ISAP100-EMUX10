/*
 * TraceCounter.cpp
 *
 *  Created on: 2013-3-14
 *      Author: Administrator
 */

#include "TraceCounter.h"

//static uint32 eth_interrupt = 0;
//static uint32 eth_rcv = 0;
//static uint32 eth_rcv_valid = 0;
//static uint32 eth_local = 0;
//static uint32 eth_transmit = 0;
//static uint32 eth_broadcast = 0;
//
//static uint32 dcc_interrupt = 0;
//static uint32 dcc_rcv = 0;
//static uint32 dcc_rcv_valid = 0;
//static uint32 dcc_local = 0;
//static uint32 dcc_transmit = 0;
//static uint32 dcc_broadcast = 0;

Trace_T eth_trace = {0};
Trace_T dcc_trace = {0};

uint32 stack_res_eth = 0;
uint32 stack_res_dcc = 0;
