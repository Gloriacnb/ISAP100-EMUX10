/*
 * CIsap100HardwareDesc.h
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#ifndef CISAP100HARDWAREDESC_H_
#define CISAP100HARDWAREDESC_H_

#include "EZ_types.h"
class CIsap100HardwareDesc {
public:
	CIsap100HardwareDesc();
	virtual ~CIsap100HardwareDesc();

	static uint8 VF_port_channel_Map[]; //话路端口与通道（64k时隙）对应表
	static uint8 slot_stbus_map[];      //槽位对应stbus硬件编号对应表
	static uint8 upE1_channel_map[];    //上行E1（内部E1）与硬件通道编号对应表
	static uint8 slotE1_channel_map[4][4];
};

#endif /* CISAP100HARDWAREDESC_H_ */
