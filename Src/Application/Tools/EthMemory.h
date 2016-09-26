/*
 * EthMemory.h
 *
 *  Created on: 2013-7-18
 *      Author: Administrator
 */

#ifndef ETHMEMORY_H_
#define ETHMEMORY_H_

#if defined (__cplusplus)
extern "C"
{
#endif
	
#include "EZ_types.h"	

typedef struct {
	uint16 length;
	uint8* frame;
}LAYER2FRAME;

void InitEthMemory(void);

LAYER2FRAME* alloc_Eth_mem(uint16 len);
void free_Eth_mem(LAYER2FRAME* f);

#if defined (__cplusplus)
}
#endif
#endif /* ETHMEMORY_H_ */
