/*
 * MidoptDCC.h
 *
 *  Created on: 2013-3-12
 *      Author: Administrator
 */

#ifndef MIDOPTDCC_H_
#define MIDOPTDCC_H_

//#include <Net_Config.h>
#include "EZ_types.h"
#include "EthMemory.h"

#if defined (__cplusplus)
extern "C"
{
#endif

#define DEF_DCC_MTU	1022
#define DEF_DCN_MTU 1022

typedef struct {
	uint32 chuid;
	LAYER2FRAME* frame;
}DCC_FRAME;

void Dcc_interrupt_enable(void);
void Dcc_interrupt_disable(void);
void SIC_2_Enable(void);
void SIC_2_Disable(void);

void transportOtherDCC(DCC_FRAME*);
void transport2DCC(LAYER2FRAME*);
void transportByDcc(uint8 ch, LAYER2FRAME* frame);
void SdhDccSendDirect(uint8 ch, uint8* d, uint32 len);


#if defined (__cplusplus)
}
#endif
#endif /* MIDOPTDCC_H_ */
