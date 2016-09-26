/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CE1Channel.cpp
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/BusinessResource/E1Module/CE1Channel.cpp
 ** Created by:          Shqp
 ** Created date:        2013-3-4
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/
/*
 * CE1Channel.cpp
 *
 *  Created on: 2013-3-4
 *      Author: Shqp
 *      是2m级别空分交叉的一侧，每槽4个 + 4个内部E1，共24个
 */

#include "CE1Channel.h"
#include <sstream>
#include "UID.h"

std::map<uint32, CE1Channel*> CE1Channel::E1_Channel_group;
std::map<uint32, CE1Channel*>::iterator CE1Channel::it;

CE1Channel::CE1Channel(uint8 slot, uint8 hid, uint8 sn) {
	// TODO Auto-generated constructor stub
	ST_E1 info = {slot+1, sn};
	iUID = UID::makeUID(&info);
	active = false;
	iSn = sn;
	Hid = hid;
	mapingPartner = 0;
	std::ostringstream s;
	s << "E1-Channel-" << sn+1;
	name = s.str();
	E1_Channel_group.insert( std::pair<uint32, CE1Channel*>(iUID, this) );

}

CE1Channel::~CE1Channel() {
	// TODO Auto-generated destructor stub
	E1_Channel_group.erase(iSn);
}

