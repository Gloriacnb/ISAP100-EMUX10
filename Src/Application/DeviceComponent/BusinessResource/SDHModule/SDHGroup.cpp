/*
 * SDHGroup.cpp
 *
 *  Created on: 2013-3-29
 *      Author: Administrator
 */

#include <string.h>
#include "CVC12.h"
#include "CSTM.h"
#include "UID.h"
#include "SDHGroup.h"
#include "Mid_RC7880A1App.h"
#include "RC6400.h"
#include "Mid_RC6400App.h"

SDHGroup::SDHGroup(int stmnum) {
	// TODO Auto-generated constructor stub

	stmNumber = stmnum;
	EZ_FLASH_DATA_T storeInfo = {
			MB_SDH_Config_Block_Start,
			sizeof(configData),
			(uint32)&configData };
	FlashDriver.setInfo(storeInfo);
	if( !FlashDriver.ReadData() ) {
		//restore default data

		RestoreDefaultConfig();
	}

	ST_SDH_STM info = {100, 0};
	for( int i = 0; i < stmNumber; i++ ) {
		info.stm = i;
		uint32 uid = UID::makeUID(&info);
		mapSTM.insert(
				std::pair<uint32, CSTM*> (
						uid,
						new CSTM(uid, &configData.stm_data[i], &FlashDriver)) );
	}
	/* �ָ�Ӳ������ */
	OpticalAlsMode( configData.als_mode );
	setPortBackupChip( configData.portBackup );


}

SDHGroup::~SDHGroup() {
	// TODO Auto-generated destructor stub
}

/*
 * ����SDH��Դ��Ĭ���������ݣ�
 * ��Ҫ������ 	STM (�ӿ����á��澯���ԡ���������)
 * 			VC12(�ӿ����á��澯���ԡ���������)
 * 			�澯ȫ���ϱ���������
 */
void SDHGroup::RestoreDefaultConfig(void) {
	memset( &configData, 0, sizeof(configData));

	configData.portBackup = 1; //Ĭ��1+1����
	configData.als_mode = 1;   //Ĭ��ALS��ģʽ
	for( int sn = 0; sn < stmNumber; sn++ ) {
		AlarmPropertyDefault(sn);
	}
	StoreConfigData();
}

void SDHGroup::StoreConfigData(void) {
	FlashDriver.SaveData();
}


void SDHGroup::AlarmPropertyDefault(int sn) {
	/* STM һ������ */
	configData.stm_data[sn].enable = 1;
	configData.stm_data[sn].als = 1;
	configData.stm_data[sn].descLen = 0;
	/* ���ö� �澯���� Ĭ�� �ȼ� ���� */
	for( int i = MS_LOF; i < MS_type_size; i++ ) {
		Alarm_property_T* app = &configData.stm_data[sn].alarm_property[i];
		app->level = emerg;
		app->mask = 0;
		app->trap = 1;
		app->typeID = MS_type_base + i;
	}

	/* �߽�ָ�� �澯����Ĭ�� �ȼ� ����*/
	for( int i = AU4_LOP; i < AU_type_size; i++ ) {
		Alarm_property_T* app = &configData.stm_data[sn].alarm_property[i+MS_type_size];
		app->level = primary;
		app->mask = 0;
		app->trap = 1;
		app->typeID = AU_type_base + i;
	}

	for( int i = VC4_AIS; i < VC_type_size; i++ ) {
		Alarm_property_T* app = &configData.stm_data[sn].alarm_property[i+MS_type_size+AU_type_size];
		app->level = primary;
		app->mask = 0;
		app->trap = 1;
		app->typeID = VC_type_base + i;
	}

	for( int i = 0; i < VC12Number; i++ ) {
		for( int j = TU12_LOP; j < TU_type_size; j++ ) {
			Alarm_property_T* app = &configData.stm_data[sn].vc12_data[i].alarm_Property[j];
			app->level = secondary;
			app->mask = 0;
			app->trap = 1;
			app->typeID = TU_type_base + j;
		}
		for( int j = VC12_AIS; j < LP_type_size; j++ ) {
			Alarm_property_T* app = &configData.stm_data[sn].vc12_data[i].alarm_Property[j+TU_type_size];
			app->level = secondary;
			app->mask = 0;
			app->trap = 1;
			app->typeID = LP_type_base + j;
		}
	}
}


/*
 * ����ָ���澯���͵ĸ澯���ԣ�ӵ�д˸澯���͵Ķ˿�ͬʱ����
 */
bool SDHGroup::SetSTMAlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl) {
	std::map<uint32, CSTM*>::iterator it = mapSTM.begin();
	while( it != mapSTM.end() ) {
		(*it).second->setAlarmProperty(typeID, opt, newVl);
		it++;
	}
	return true;
}

/*
 * ����ָ���˿� ָ���澯���͵ĸ澯����
 */
bool SDHGroup::SetSTMAlarmProperty(uint32 stmUID, uint32 typeID, Alarm_Property_Option opt, uint32 newVl) {
	std::map<uint32, CSTM*>::iterator it = mapSTM.find(stmUID);
	if( it != mapSTM.end() ) {
		return (*it).second->setAlarmProperty(typeID, opt, newVl);
	}
	return false;
}


/*
 * ����ָ���澯���͵ĸ澯���ԣ�ӵ�д˸澯���͵Ķ˿�ͬʱ����
 */
bool SDHGroup::SetVC12AlarmProperty(uint32 typeID, Alarm_Property_Option opt, uint32 newVl) {
	std::map<uint32, CSTM*>::iterator it = mapSTM.begin();
	while( it != mapSTM.end() ) {
		(*it).second->setVC12AlarmProperty(typeID, opt, newVl);
		it++;
	}
	return true;
}

/*
 * ����ָ���˿� ָ���澯���͵ĸ澯����
 */
bool SDHGroup::SetVC12AlarmProperty(uint32 vc12UID, uint32 typeID, Alarm_Property_Option opt, uint32 newVl) {
	return CSTM::GetVc12Object(vc12UID)->setAlarmProperty(typeID, opt, newVl);
}

/*
 * ����1+1����ʹ��
 */
void SDHGroup::setPortBackup(uint8 en) {
	setPortBackupChip(en);
	configData.portBackup = en;
	FlashDriver.SaveData();
}


void SDHGroup::setALSMode(uint8 mode) {

	OpticalAlsMode(mode);

	configData.als_mode = mode;
	FlashDriver.SaveData();
}


void SDHGroup::setPortBackupChip(uint8 en) {
	uint8 protectMode = 0;
	if( en == 1 ) {
		protectMode = AUTO_PROTECT;
	}
	else {
		protectMode = DISABLE_PROTECT;
	}
	for( uint8 e1ID = 0; e1ID < MAX_E1_Number; e1ID++ ) {
		RC7880Tu12UnitProtectModeWrite(e1ID, protectMode);
	}

	if( protectMode == DISABLE_PROTECT ) {
		--protectMode;
	}
	for( uint8 tu12num = 0; tu12num < MAX_TU12_NUM; tu12num++ ) {
		RC6400_TU12_Bus_Sel_Mode_Rx_Set(tu12num, protectMode);
	}
}
