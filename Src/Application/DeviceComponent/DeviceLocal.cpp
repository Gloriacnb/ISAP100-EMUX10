/*
 * DeviceLocal.cpp
 *
 *  Created on: 2013-2-21
 *      Author: Administrator
 */

#include "DeviceLocal.h"
#include <Net_Config.h>
#include "Task_define.h"
#include <string.h>
#include "CISAP100Factory.h"
#include "CSlotManager.h"
#include "Mid_NandFlash.h"
#include "Mid_FlashData.h"
#include "Mid_Spi.h"
#include "TerminalUart.h"
//#include "ChipGluLogic.h"
//#include "ChipSlotLogic.h"
//#include "ChipOptLogic.h"
//#include "Mid_RC6400App.h"
#include "Mid_RC7880A1App.h"
//#include "SlotLogicLX9.h"
//#include "Chip8306E.h"
#include "CCommonDefine.h"
//#include "CSTM.h"
#include "SDHGroup.h"
#include "CVCGGroup.h"
#include "CVC12CrossConnectionMagager.h"
#include "CTSCrossConnectionManager.h"
#include "ISAP100Led.h"
#include "CMainBoard.h"
#include "ChipLM75A.h"
#include "switchPortSNMP.h"
#include "SwitchPortCPU.h"
#include "InnerDCCManager.h"
#include "CEMUX10Factory.h"
#include "CTMFactory.h"
#include "EthBoard.h"
#include "MidoptDCC.h"
#include "lpc32xx_intc_driver.h"
#include "SysError.h"
#include <stdio.h>

DeviceLocal DeviceLocal::dev;

extern U8 own_hw_adr[];
extern U8 lhost_name[];


DeviceLocal::DeviceLocal() {
	// TODO Auto-generated constructor stub
	factory = 0;
	slots = 0;
	DevAttr = 0;
	eth = 0;
	vcgGroup = 0;
	XcManager = 0;
	sdh = 0;
	mb = 0;
	eth = 0;
	MappingManager = 0;
}

DeviceLocal::~DeviceLocal() {
	// TODO Auto-generated destructor stub
}

void DeviceLocal::DeviceRun(void) {


}

void DeviceLocal::DeviceInit(void) {
	/* 修改MAC地址
	 * Note: 必须在TCP协议栈初始化前
	 */
	SIC_2_Disable();
	int_enable(IRQ_SUB1IRQ);
	TerminalUARTInit();
	term_dat_out((UNS_8 *)"Main build date:");
	term_dat_out((UNS_8 *) __DATE__);
	term_dat_out((UNS_8 *) " ");
	term_dat_out_crlf((UNS_8 *) __TIME__);
	InitSPI();
	if( Init_data_storage() == 0 ) {
		throw SysError("!!!Nandflash init failed!");
	}

 	InitLEDModule();
	DevAttr = new CDeviceAttribute();
	if( !DevAttr ) { throw SysError("!!!SDRAM Error!"); }
	DevAttr->InitialSystem();

	uint32 subType = DevAttr->DevAttr.GetSysSubDevice();
	switch ( subType ) {
	case type_isap_A_4eth_iso:
	case type_isap_A_8eth_iso:
	case type_isap_8eth:
	case type_isap_4eth_switch:
	case type_isap_4eth_isolation:
	case type_isap_4eth_iso2: {
		factory = new CISAP100Factory();
	}
		break;
	case type_tm_4eth_switch:
		factory = new CTMFactory();
		break;
	case type_emux_v10:
	case type_emux_v12:
		factory = new CEMUX10Factory();
		break;
	default:
		throw SysError("!!!Unknown subtype!");
	}

	if( !factory ) { throw SysError("!!!Factory creat failed!"); }
	factory->initChips();
	DevAttr->SetSysClock(DevAttr->GetSysClock(), false);
	DevAttr->SetPcmClock(DevAttr->GetPcmClock(), false);

	switch( subType ) {
	case type_isap_4eth_switch:
		eth = new EthBoard(4, true);
		break;
	case type_isap_8eth:
	case type_isap_A_8eth_iso:
		eth = new EthBoard(8, false);
		break;
	case type_isap_4eth_iso2:
	case type_isap_A_4eth_iso:
		eth = new EthBoard(4, false);
		break;
	}

	mb = new CMainBoard(CCommonDefine::uiConstMainBoardIndex, DevAttr->DevAttr.GetSysSubDevice());
	slots = new CSlotManager(CCommonDefine::uiconstSlotNumber, factory);
	if( !slots ) { throw SysError("!!!SlotManager creat failed!"); }
	if( subType != type_emux_v10 && subType != type_emux_v12 ) {
		sdh = new SDHGroup(2);
		vcgGroup = new CVCGGroup(4);
		MappingManager = new CVC12CrossConnectionMagager();
	}
	XcManager = new CTSCrossConnectionManager();

	new ChipLM75A();
	new switchPortSNMP();
	new SwitchPortCPU();
	new InnerDCCManager();

	uint32 len = 6;
	uint8* mac = DevAttr->ReadMACAddress();
	printf( "\n mac is :");
	for (int i = 0; i < len; ++i) {
		printf( " %02x.", mac[i] );
	}
	printf( "\n");
	
 	memcpy (own_hw_adr, mac, len);
//   	memcpy (lhost_name, DevAttr->GetDeviceName(&len), len);



}

