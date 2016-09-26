/*
 * InnerDCCManager.cpp
 *
 *  Created on: 2013-7-1
 *      Author: Administrator
 */

#include "InnerDCCManager.h"
#include "UID.h"
#include "SwitchPortInner.h"
#include "DCCChannelSnd.h"
#include "DCCChannelRcv.h"

InnerDCCManager::InnerDCCManager() {
	// TODO Auto-generated constructor stub
	EZ_FLASH_DATA_T storeInfo = {
			SYS_InnerDCC_Block_Start,
			sizeof(configData),
			(uint32)&configData };
	FlashDriver.setInfo(storeInfo);
	if( !FlashDriver.ReadData() ) {
		//restore default data

		RestoreDefaultConfig();
	}

	for( int i = 0; i < configData.portNum; i++ ) {
		SwitchPortInner* port = new SwitchPortInner(InnerPortDefaultSn+i);
		for( int j = 0; j < configData.port[i].chRNum; j++ ) {
			DCCChannelRcv* ch = DCCChannelRcv::getRcvDccByUID( configData.port[i].ch_rcv[j].uid );
			if( ch ) {
				port->addDcc(ch);
			}
		}

		for( int j = 0; j < configData.port[i].chSNum; j++ ) {
			DCCChannelSnd* ch = DCCChannelSnd::getSendDccByUID( configData.port[i].ch_snd[j].uid );
			if( ch ) {
				port->addDcc(ch);
			}
		}
	}

}

InnerDCCManager::~InnerDCCManager() {
	// TODO Auto-generated destructor stub
}


/*
 * 恢复默认配置，只有一个
 */
void InnerDCCManager::RestoreDefaultConfig() {
	configData.portNum = InnerPort;
	//sdh nmchannel
	ST_NM_Channel info;
	info.slot = 100;
	for( int i = 0; i < configData.portNum; i++ ) {
		configData.port[i].chRNum = 4;
		configData.port[i].chSNum = 4;
		info.sn = i;
		info.subtype = subtype_dcc;
		configData.port[i].ch_rcv[0].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_rcv[0].uid = UID::makeUID(&info);
		configData.port[i].ch_snd[0].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_snd[0].uid = UID::makeUID(&info);
		info.subtype = subtype_dcn;
		configData.port[i].ch_rcv[1].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_rcv[1].uid = UID::makeUID(&info);
		configData.port[i].ch_snd[1].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_snd[1].uid = UID::makeUID(&info);
		info.subtype = subtype_sabit;
		configData.port[i].ch_rcv[2].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_rcv[2].uid = UID::makeUID(&info);
		configData.port[i].ch_snd[2].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_snd[2].uid = UID::makeUID(&info);
		info.subtype = subtype_tsdcn;
		configData.port[i].ch_rcv[3].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_rcv[3].uid = UID::makeUID(&info);
		configData.port[i].ch_snd[3].portSn = InnerPortDefaultSn+i;
		configData.port[i].ch_snd[3].uid = UID::makeUID(&info);
	}

	FlashDriver.SaveData();
}
