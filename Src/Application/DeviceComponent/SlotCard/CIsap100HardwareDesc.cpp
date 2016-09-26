/*
 * CIsap100HardwareDesc.cpp
 *
 *  Created on: 2013-4-27
 *      Author: Administrator
 */

#include "CIsap100HardwareDesc.h"

CIsap100HardwareDesc::CIsap100HardwareDesc() {
	// TODO Auto-generated constructor stub

}

CIsap100HardwareDesc::~CIsap100HardwareDesc() {
	// TODO Auto-generated destructor stub
}

uint8 CIsap100HardwareDesc::VF_port_channel_Map[] =
		{ 1, 2, 3, 4, 17, 18, 19, 20 };
uint8 CIsap100HardwareDesc::slot_stbus_map[] = { 8, 9, 10, 11 };
uint8 CIsap100HardwareDesc::upE1_channel_map[] = { 16, 17, 18, 19 };
uint8 CIsap100HardwareDesc::slotE1_channel_map[4][4] = { { 0, 1, 2, 3 }, { 4, 5,
		6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 } };
