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

	static uint8 VF_port_channel_Map[]; //��·�˿���ͨ����64kʱ϶����Ӧ��
	static uint8 slot_stbus_map[];      //��λ��ӦstbusӲ����Ŷ�Ӧ��
	static uint8 upE1_channel_map[];    //����E1���ڲ�E1����Ӳ��ͨ����Ŷ�Ӧ��
	static uint8 slotE1_channel_map[4][4];
};

#endif /* CISAP100HARDWAREDESC_H_ */
