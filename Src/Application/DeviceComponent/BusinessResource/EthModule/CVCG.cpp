/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **								
 **										ISAP100_Realese
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CVCG.cpp
 ** File path:			/ISAP100_Realese/Src/Application/DeviceComponent/BusinessResource/EthModule/CVCG.cpp
 ** Created by:          Shqp
 ** Created date:        2013-3-19
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
 * CVCG.cpp
 *
 *  Created on: 2013-3-19
 *      Author: Shqp
 */

#include "CVCG.h"
#include "CVC12.h"
#include "Mid_RC6400App.h"
#include "CSTM.h"
#include "RC6400.h"
#include "CPPTools.h"
#include "CMSSave.h"
#include "Mid_RC7880A1App.h"
#include "AlarmVCGSite.h"
#include "CVCGMember.h"
#include "UID.h"

#include "DeviceLocal.h"
#include "SDHGroup.h"

CVCG::CVCG(int sn, uint32 uid, vcg_config_T* data,  CMSSave* store) {
	// TODO Auto-generated constructor stub
	itsHardId = sn;
	itsUid = uid;
	itsConfig = data;
	storer = store;
	for( int i = 0; i < data->band; i++ ) {
		if( !BandMember(data->member[i].vc12, i) ) {
			throw 222;
		}
		uint8 portBack = DeviceLocal::instance().GetSdhObject().getPortBackup();
		if( portBack == 0 ) {
			if( !realSNCP(data->member[i].vc12, data->member[i].sncp) ) {
				throw 223;
			}
		}
	}

	name = "VCG-" + CPPTools::number2string(sn+1);

	/*
	 * 恢复配置
	 */
	RC6400_VCAT_En_Tx_Set(itsHardId, itsConfig->enable);
	RC6400_VCAT_En_Rx_Set(itsHardId, itsConfig->enable);

	RC6400_LCAS_En_Rx_Set(itsHardId, itsConfig->lcas);

	/* alarm site */
	for( int i = 0; i < VCG_type_size; i++ ) {
		data->alarmProperty[i].typeID = VCG_type_base+i;
		AlarmElement* ap = new AlarmVCGSite(&data->alarmProperty[i], this, (VCG_alarm_type_E)i);
		mapAlarm.insert( std::pair<uint32, AlarmElement*>( VCG_type_base+i, ap ) );
	}

}

CVCG::~CVCG() {
	// TODO Auto-generated destructor stub
}


bool CVCG::BandMember(uint32 uid, uint32 sn) {
	CVC12* pvc12 = CSTM::GetVc12Object(uid);
	if( pvc12 == 0 ) {
		return false;
	}
	if( pvc12->ifOccupied() ) {
		return false;
	}
	pvc12->occupyIt(itsUid);
	CVCGMember* pm = new CVCGMember(pvc12, sn, &itsConfig->alarmProperty[VCG_type_size]);
	if( !pm ) {
		return false;
	}
	mapMember.insert(std::pair<uint32, CVCGMember*>(uid, pm));
	RC7880Vc4UnitDxcConfigWrite(pvc12->GetHid(), direct_CD);
	AddTu12ToVCGSimple(pvc12->GetHid(), itsHardId);

	UN_Info info = UID::breakUID(uid);
	uint8 bus = info.stm.stm;
	AssignTu12Bus(pvc12->GetHid(), bus);
	return true;
}

bool CVCG::addMember(uint32 uid) {
	if( !BandMember(uid, itsConfig->band) ) {
		return false;
	}
	itsConfig->member[itsConfig->band].vc12 = uid;
	itsConfig->band++;
	return storer->SaveData();
}


bool CVCG::delMember(uint32 uid) {
	it = mapMember.find(uid);
	if( it != mapMember.end() ) {
		CVC12* pvc12 = it->second->getVC12();
		pvc12->occupyIt(0);
		DeleteTu12FromVCGSimple(pvc12->GetHid());

		/*
		 * 增加对当前vc12的同编号vc12连接情况的判断
		 * 只有当同编号vc12未占用时，才将空分交叉设置为bypass
		 */
		uint32 Partner = pvc12->getPartnerUID();
		CVC12* partnervc12 = CSTM::GetVc12Object(Partner);
		if( partnervc12 == 0 ) {
			return false;
		}
		if( !(partnervc12->ifOccupied()) ) {
			RC7880Vc4UnitDxcConfigWrite(pvc12->GetHid(), direct_AB);
		}
		RC6400_TU12_Bus_Sel_Mode_Rx_Set(pvc12->GetHid(), 1); //删除绑定同时解除SNCP

		delete it->second;
		mapMember.erase(uid);
		return true;
	}
	return false;
}

bool CVCG::removeMember(uint32 uid) {
	/* make config data and save it*/
	it = mapMember.find(uid);
	if( it == mapMember.end() ) {
		return false;
	}
	for( int i = it->second->getSn(); i < itsConfig->band - 1; i++ ) {
		itsConfig->member[i].vc12 = itsConfig->member[i+1].vc12;
		itsConfig->member[i].sncp = itsConfig->member[i+1].sncp;
		it = mapMember.find(itsConfig->member[i].vc12);
		if( it == mapMember.end() ) {
			return false;
		}
		it->second->setSn(i);
	}
	(itsConfig->band)--;

	if( !delMember(uid) ) {
		return false;
	}
	return storer->SaveData();
}


bool CVCG::clrMember(void) {

	while( mapMember.begin() != mapMember.end()) {
		it = mapMember.begin();
		delMember(it->first);
	}
	itsConfig->band = 0;
	return storer->SaveData();
}

bool CVCG::ifVCGAlarm(VCG_alarm_type_E sn) {

	/*端口 禁止后无告警*/
	if( itsConfig->enable == 0 ) {
		return false;
	}
	switch( sn ) {
	case VCG_NoMember:
		break;
	case LaVCR_RxQFull: {
		uint8 vcgAlarm;
		RC6400_VCAT_AlarmR_Read(itsHardId,&vcgAlarm);
		if( (vcgAlarm >> 3) & 1 != 0 ) {
			return true;
		}
	}
	break;
	case LaVCR_GIDM: {
		uint8 vcgAlarm;
		RC6400_VCAT_AlarmR_Read(itsHardId,&vcgAlarm);
		if( (vcgAlarm >> 2) & 1 != 0 ) {
			return true;
		}
	}
	break;
	case LaVCR_GLOA: {
		uint8 vcgAlarm;
		RC6400_VCAT_AlarmR_Read(itsHardId,&vcgAlarm);
		if( (vcgAlarm >> 1) & 1 != 0 ) {
			return true;
		}
	}
	break;
	case LaGR_SYNLoss:
		if(RC6400_DeFrame_Syn_Alarm_Read(itsHardId) == 0) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}


void CVCG::setEnable(uint8 en) {
	itsConfig->enable = en;
	RC6400_VCAT_En_Tx_Set(itsHardId, itsConfig->enable);
	RC6400_VCAT_En_Rx_Set(itsHardId, itsConfig->enable);
	storer->SaveData();
}


bool CVCG::setLcas(uint8 lcas) {
	itsConfig->lcas = lcas;
	RC6400_LCAS_En_Rx_Set(itsHardId, itsConfig->lcas);
	RC6400_LCAS_En_Tx_Set(itsHardId, itsConfig->lcas);
	return storer->SaveData();
}

void CVCG::SetDesc( uint8* desc, uint8 len ) {
	itsConfig->descLen = len;
	memcpy (itsConfig->desc, desc, len);
	storer->SaveData();
}

uint8 CVCG::getSNCP(uint32 muid) {
	it = mapMember.find(muid);
	if( it == mapMember.end() ) {
		return false;
	}
	return itsConfig->member[it->second->getSn()].sncp;
}


bool CVCG::realSNCP(uint32 uid, uint32 en) {
	it = mapMember.find(uid);
	if( it == mapMember.end() ) {
		return false;
	}
	CVC12* pvc12 = it->second->getVC12();
	uint8 protectMode = 0;
	if( en == 1 ) {
		protectMode = 0;//AUTO_PROTECT;
	}
	else {
		protectMode = 1;//disable protect;
	}

	RC6400_TU12_Bus_Sel_Mode_Rx_Set(pvc12->GetHid(), protectMode);
	return true;
}

bool CVCG::setSNCP(uint32 muid, uint8 en) {

	if ( !realSNCP(muid, en) ) {
		return false;
	}
	/* save data */

	itsConfig->member[it->second->getSn()].sncp = en;
	return storer->SaveData();
}

void CVCG::processAlarm(void) {
	std::map<uint32, AlarmElement*>::iterator italm = mapAlarm.begin();
	while( italm != mapAlarm.end() ) {
		italm->second->Run();
		italm++;
	}
	it = mapMember.begin();
	while( it != mapMember.end() ) {
		it->second->processAlarm();
		it++;
	}
}
