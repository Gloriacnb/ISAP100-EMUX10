/*
 * CExtCard4E1.cpp
 *
 *  Created on: 2012-12-26
 *      Author: Administrator
 */

#include "Chip4E1Logic.h"
#include "CExtCard4E1.h"
#include <string.h>
#include "CUnframeE1.h"
#include "UID.h"
#include "CExtCard4E1_define.h"

CExtCard4E1::~CExtCard4E1() {
	destroy();
}

CExtCard4E1::CExtCard4E1(uint8 slot, std::string& name) :
		CBaseCard(name, slot) {
//	slotNumber = slot;

	EZ_FLASH_DATA_T storeInfo = { Data_Part(slot + 1), sizeof(configData),
			(uint32) &configData };
	FlashDriver.setInfo(storeInfo);
	if (!FlashDriver.ReadData()) {
		//restore default data

		RestoreDefaultConfig();
	}

	InitExtChip4E1(slot, &configData);

	for (int i = 0; i < 4; i++) {
		int lid = getSn() * 4 + i;
		int hid = lid + HardBaseSn;
		ST_E1 info = { lid / 4 + 1, lid % 4 };
		uint32 uid = UID::makeUID(&info);

		e1s[i] = new CUnframeE1(lid, hid, uid, &configData.e1[i], &FlashDriver);
	}
}

int CExtCard4E1::GetCartTypeID() {
	return itsTypeID;
}

void CExtCard4E1::destroy() {
	for (int i = 0; i < itsE1Number; i++) {
		delete e1s[i];
	}
}

void CExtCard4E1::RestoreDefaultConfig(void) {
	memset(&configData, 0, sizeof(configData));
	configData.pwm = 0x57;
	for (int i = 0; i < itsE1Number; i++) {
		defaultE1Config(i);
	}
	FlashDriver.SaveData();
}

void CExtCard4E1::defaultE1Config(int sn) {
	configData.e1[sn].enable = 1;
	/* 复用段 告警属性 默认 等级 紧急 */
	for (int i = 0; i < E1_type_size; i++) {
		Alarm_property_T* app = &configData.e1[sn].alarm_property[i];
		app->level = primary;
		app->mask = 0;
		app->trap = 1;
		app->typeID = E1_type_base + i;
	}
}

int CExtCard4E1::getNextVersionIndex(uint8 sn) {
	if (sn >= ext4E1VersionSize) {
		return -1;
	}
	return sn + 1;
}
int CExtCard4E1::getVersion(uint8 id, STVersion& ver) {
	switch (id) {
	case ext4E1VersionPCB:
		ver.uiVerNum = 16;
		strcpy(ver.ucpVerName, "Ext4E1PCBVersion");
		return 1;
	case ext4E1VersionChip:
		strcpy(ver.ucpVerName, "Ext4E1ChipVersion");
		ver.uiVerNum = get4E1ChipVersion(getSn());
		return 1;
	}
	return -1;
}

//void CExtCard4E1::GreatTaskLed(void) {
//	t_led_E1 = os_tsk_create(T_LED_E1, P_LED);
//}

//CExt4E1ConfigData::CExt4E1ConfigData() {
//	EZ_FLASH_DATA_T info;
//	info.BlockFirst = SYS_Attribut_Block_Start;
//	info.BufAddr  = (uint32)&cfData;
//	info.ByteNums = sizeof(cfData);
//	int a = info.ByteNums/2048;
//	info.SecsUsed = (info.ByteNums % 2048) ? (a+1) : a;
//	setInfo(info);
//}
