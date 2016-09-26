/*
 * MidMC145572.h
 *
 *  Created on: 2013-7-30
 *      Author: Administrator
 */

#ifndef MIDMC145572_H_
#define MIDMC145572_H_

#include "EZ_types.h"

enum{
	NR0 = 0,NR1,NR2,NR3,NR4,NR5,
	BR0 = 0,BR1,BR2,BR3,BR4,BR5,BR6,BR7,BR8,BR9,BR10,
	OR0 = 0,OR1,OR2,OR3,OR4,OR5,OR6,OR7,OR8,OR9
};

class MidMC145572 {
public:
	MidMC145572(uint8 slot, uint8 sn);
	virtual ~MidMC145572();

	void initChip(bool cold=false);
	void softReset(void);

	int setMode(uint8 mode);
	int setEnable(uint8 en);
	int setLoopIn(uint8 loop);
	int setLoopOut(uint8 loop);

	int readNibbleReg(uint8 addr);
	int readByteReg(uint8 addr);
	int readOverlayReg(uint8 addr);
	int readR6Reg(void);

	int writeNibbleReg(uint8 addr, uint8 data);
	int writeByteReg(uint8 addr, uint8 data);
	int writeOverlayReg(uint8 addr, uint8 data);
	int writeR6Reg(uint16 data);
private:
	uint8 spiCH;
	uint8 slt;
	uint8 cid;
	/*NB*/




};

#endif /* MIDMC145572_H_ */
