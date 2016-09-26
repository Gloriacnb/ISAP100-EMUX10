/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			CLI_Config_cmd_group.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/CLI_Commands/CLI_Config_cmd_group.c
** Created by:          Administrator
** Created date:        2012-11-27
** Version:             V0.1
** Descriptions:        cmd_creat_dxc
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:				
** Descriptions:        
**
** Rechecked by:        
***********************************************************************************************************************/

#include "s1l_cmds.h"
#include "s1l_line_input.h"
#include "CLI_Config_cmd_group.h"
#include "TerminalUart.h"
#include "rc7880regdriverfunclib.h"
#include "lpc_string.h"
#include "Mid_RC6400App.h"
#include "ChipSlotLogic.h"

#include "Mid_FlashData.h"
#include "DeviceLocal.h"
#include <string.h>
#include "CVCGGroup.h"
#include "CVC12CrossConnectionMagager.h"
#include "SDHGroup.h"
#include "DeviceLocal.h"
#include "CBaseCard.h"
#include "CSlotManager.h"
#include "ChipLM75A.h"
#include "CPPTools.h"

/* private functions declaration*/
static BOOL_32 cmd_creat_dxc(void);
static BOOL_32 cmd_setmap(void);

static BOOL_32 cmd_tuadd(void);
static BOOL_32 cmd_tudel(void);

static BOOL_32 cmd_slcmd(void);

static BOOL_32 cmd_syscfg(void);

/*-----------------------Commands define-------------------------------------*/
/* DxcConfig command */
static UNS_32 cmd_creat_dxc_plist[] =
{
	(PARSE_TYPE_STR), /* The "dxcConfig" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T creat_dxc_cmd =
{
	(UNS_8 *) "creatdxc",
	cmd_creat_dxc,
	(UNS_8 *) "Set the upSource(1:AB, 2:GH, 3:LOOP, 4:CD) of a tu12.",
	(UNS_8 *) "creatdxc [tu12ID][upSource]",
	cmd_creat_dxc_plist,
	0//NULL
};


/* MAP Config command */
static UNS_32 cmd_setmap_plist[] =
{
	(PARSE_TYPE_STR), /* The "setmap" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T setmap_cmd =
{
	(UNS_8 *) "setmap",
	cmd_setmap,
	(UNS_8 *) "Set the map from a E1(0~23) to a tu12(0~62).if tu12ID is 63, clear the map",
	(UNS_8 *) "setmap [DEC E1ID][DEC tu12ID]",
	cmd_setmap_plist,
	0//NULL
};



/* RC6400 debug command */
static UNS_32 cmd_tuadd_plist[] =
{
	(PARSE_TYPE_STR), /* The "tuadd" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T tuadd_cmd =
{
	(UNS_8 *) "tuadd",
	cmd_tuadd,
	(UNS_8 *) "add a tu12 to a VCG",
	(UNS_8 *) "tuadd [tu12][vcg]",
	cmd_tuadd_plist,
	0//NULL
};


static UNS_32 cmd_tudel_plist[] =
{
	(PARSE_TYPE_STR), /* The "tudel" command */
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T tudel_cmd =
{
	(UNS_8 *) "tudel",
	cmd_tudel,
	(UNS_8 *) "delelt a tu12 from any VCG",
	(UNS_8 *) "tudel [tu12]",
	cmd_tudel_plist,
	0//NULL
};



static UNS_32 cmd_slcmd_plist[] =
{
	(PARSE_TYPE_STR), /* The "slcmd" command */
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T slcmd_cmd =
{
	(UNS_8 *) "slcmd",
	cmd_slcmd,
	(UNS_8 *) "select the slotLogic work mode. 235 is test mode",
	(UNS_8 *) "slcmd [mode]",
	cmd_slcmd_plist,
	0//NULL
};




static UNS_32 cmd_syscfg_plist[] =
{
	(PARSE_TYPE_STR), /* The "syscfg" command */
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T syscfg_cmd =
{
	(UNS_8 *) "syscfg",
	cmd_syscfg,
	(UNS_8 *) "config simple system work mode.",
	(UNS_8 *) "syscfg <option> <value> ...\r\n"
			  	"		option 0 Get factory infomation.\r\n"
				"		option 1 set device subtype.\r\n"
				"			value 10 ISAP100 8ETH, 8306E.\r\n"
				"			value 16 ISAP100 4ETH, isolation.\r\n"
				"			value 12 ISAP100 4ETH, isolation 8306E.\r\n"
				"			value 11 ISAP100 4ETH, switch 8306E.\r\n"
				"			value 13 EMUX10 v1.0.\r\n"
				"			value 14 TM 4ETH, 8306E.\r\n"
				"			value 15 TM 4ETH, isolation.\r\n"
				"			value 23 EMUX10 v1.2.\r\n"
				"			value 24 ISAP100-A 4ETH, isolation 8306E.\r\n"
				"			value 25 ISAP100-A 4ETH, isolation 8306E.\r\n"
				"		option 2 set serial number.\r\n"
				"		option 3 set ProductionDate.\r\n"
				"		option 4 set ip address.\r\n"
				"		option 5 set net mask.\r\n"
				"		option 6 set net gateway.\r\n"
				"		option 7 Restore config.\r\n"
				"			value 1 restore vcg.\r\n"
				"			value 2 restore xc.\r\n"
				"			value 3 restore sdh.\r\n"
				"		option 8 get MAC address.\r\n"
				"		option 9 get device temperature.\r\n",
	cmd_syscfg_plist,
	0//NULL
};

/* .......................config group................................ */
GROUP_LIST_T config_group =
{
	(UNS_8 *) "config", /* NAND group */
	(UNS_8 *) "Config command group",
	0,//NULL,
	0//NULL
};


/* ---------------------private functions ---------------------------------------*/
static UNS_8 tu12rangeerr_msg[] = "tu12ID range is invalid, 0~62 is valid";
static UNS_8 upSourceRangerr_msg[] = "upSource range is invalid, 1~4 is valid";
static UNS_8 configcomplete_msg[] = "config OK!";
static UNS_8 configfailed_msg[] = "config failed!";
static UNS_8 e1Rangerr_msg[] = "E1 range is invalid, 0~23 is valid";
static UNS_8 channelrangeerr_msg[] = "channel range is invalid, 0~3 is valid";

BOOL_32 cmd_creat_dxc(void) {
	UNS_8 tu12ID = 0;
	UNS_8 upSource = 0;

	/* Get arguments */
	tu12ID = cmd_get_field_val(1);
	upSource = cmd_get_field_val(2);
	if( tu12ID > 62 ) {
		term_dat_out_crlf(tu12rangeerr_msg);
		return FALSE;
	}
	if( upSource > 4 || upSource == 0 ) {
		term_dat_out_crlf(upSourceRangerr_msg);
		return FALSE;
	}
	/* config DXC */
	RC7880Vc4UnitDxcConfigWrite(tu12ID, upSource);
	term_dat_out_crlf(configcomplete_msg);
	return TRUE;
}


BOOL_32 cmd_setmap(void) {
	UNS_8 e1ID = 0;
	UNS_8 tu12ID = 0;
	e1ID = cmd_get_field_val(1);
	tu12ID = cmd_get_field_val(2);

	if( tu12ID > 63 ) {
		term_dat_out_crlf(tu12rangeerr_msg);
		return FALSE;
	}
	if( e1ID > 23 ) {
		term_dat_out_crlf(e1Rangerr_msg);
		return FALSE;
	}
	/* config DXC */
	RC7880Tu12UnitTsSelectWrite(e1ID, tu12ID);
	term_dat_out_crlf(configcomplete_msg);
	return TRUE;
}




BOOL_32 cmd_tuadd(void) {
	UNS_8 tu12 = cmd_get_field_val(1);
	UNS_8 vcg = cmd_get_field_val(2);
	if( tu12 > 62 ) {
		term_dat_out(tu12rangeerr_msg);
		return FALSE;
	}
	if( vcg > 3 ) {
		term_dat_out(channelrangeerr_msg);
		return FALSE;
	}

	if( AddTu12ToVCGSimple(tu12, vcg) != TRUE ) {
		term_dat_out(configfailed_msg);
		return FALSE;
	}
	else {
		term_dat_out(configcomplete_msg);
	}
	return TRUE;
}
BOOL_32 cmd_tudel(void) {
	UNS_8 tu12 = cmd_get_field_val(1);
	if( tu12 > 62 ) {
		term_dat_out(tu12rangeerr_msg);
		return FALSE;
	}
	if( DeleteTu12FromVCGSimple(tu12) != TRUE ) {
		term_dat_out(configfailed_msg);
		return FALSE;
	}
	else {
		term_dat_out_crlf(configcomplete_msg);
	}
	return TRUE;
}

BOOL_32 cmd_slcmd(void) {
	UNS_8 mode = cmd_get_field_val(1);
	SetTempWorkMode(mode);
	if( mode == 235 ) {
		term_dat_out_crlf((UNS_8*)"NOTE:  SlotLogic work in test mode");
		term_dat_out_crlf((UNS_8*)"       slot 1's VF connect to slot 2 one by one");
	}
	term_dat_out_crlf(configcomplete_msg);
	return TRUE;
}

void displayVersion(STVersion& v,int pot=0 ) {
	UNS_8 t[10];
	term_dat_out((uint8*)v.ucpVerName);
	term_dat_out((uint8*)"	");
	if( pot != 0 ) {
		str_makedec(t, v.uiVerNum >> 8);
		term_dat_out(t);
		term_dat_out((UNS_8*)".");
		str_makedec(t, v.uiVerNum & 0xff);
	}
	else {
		str_makedec(t, v.uiVerNum >> 4);
		term_dat_out(t);
		term_dat_out((UNS_8*)".");
		str_makedec(t, v.uiVerNum & 0x0f);
	}
	term_dat_out_crlf(t);
}

BOOL_32 cmd_syscfg(void) {
	UNS_8 t[10];
 	UNS_8 option = cmd_get_field_val(1);
	switch( option ) {
		case 0: {
			for( int i = 1; i < ver_size; i++ ) {
				STVersion v;
				DeviceLocal::instance().GetDeviceAttributeObject().GetVersion(i, v);
				if( i == 1 ) {
					displayVersion(v, 1);
				}
				else{
					displayVersion(v);
				}
			}

			CBaseCard* c = DeviceLocal::instance().GetSlotManager().getFirstCard();
			while( c ) {
				for( int i = 1; i < 3; i++) {
					STVersion v;
					if( c->getVersion(i, v) > 0 ) {
						displayVersion(v);
					}
				}
				c = DeviceLocal::instance().GetSlotManager().getNextCard(c->getSn());
			}
		}
			break;
		case 1: {
			if( parse_get_entry_count() > 2 ) {
				uint8 sub_type = cmd_get_field_val(2);
				DeviceLocal::instance().GetDeviceAttributeObject().DevAttr.SetSysSubDevice(sub_type);
			}
			uint8 deviceSubType = DeviceLocal::instance().GetDeviceAttributeObject().DevAttr.GetSysSubDevice();
			str_makedec(t, deviceSubType);
			term_dat_out(t);
			term_dat_out((uint8*)" ");
		}break;

		case 2: {
	 		if( parse_get_entry_count() > 2  ) {
	 			if( parse_get_entry_count() == 3 ) {
	 				UNS_16 value =  cmd_get_field_val(2);
					DeviceLocal::instance().GetDeviceAttributeObject().SetSerialNumber(value);
	 			}
	 			else{
	 				term_dat_out_crlf((uint8*)"Invalid Para!");
	 			}
	 		}
			uint16 sn =
					DeviceLocal::instance().GetDeviceAttributeObject().GetSerialNumber();

			str_makedec(t,sn);
			term_dat_out_crlf(t);

		}break;

		case 3: {
 			if(parse_get_entry_count() >= 8) {

 				DATE_TIME_T sdate;
 				sdate.year = cmd_get_field_val(2);
 				sdate.month = cmd_get_field_val(3);
 				sdate.day = cmd_get_field_val(4);
 				sdate.hour = cmd_get_field_val(5);
 				sdate.minute = cmd_get_field_val(6);
 				sdate.second = cmd_get_field_val(7);
 				DeviceLocal::instance().GetDeviceAttributeObject().SetProductionDate(&sdate);
 			}
			char* s = DeviceLocal::instance().GetDeviceAttributeObject().GetProductionDate();
			term_dat_out((uint8*)s);

		}break;

		case 4: {
	 		if( parse_get_entry_count() > 5 ) {
				UNS_8 ip[4];
				for( int i = 0; i < 4; i++ ) {
					ip[i] = cmd_get_field_val(i+2);
				}
				DeviceLocal::instance().GetDeviceAttributeObject().SetExternalIP(ip);
	 		}
	  		uint8* cip =
	 				DeviceLocal::instance().GetDeviceAttributeObject().ReadExternalIP();
			term_dat_out((uint8*)"Device IP:	");
			for( int i = 0; i < 4; i++ ) {
				str_makedec(t, cip[i]);
				term_dat_out(t);
				if( i != 3 )
					term_dat_out((uint8*)".");
			}
		}break;
		case 5: {
	 		if( parse_get_entry_count() > 5 ) {
				UNS_8 ip[4];
				for( int i = 0; i < 4; i++ ) {
					ip[i] = cmd_get_field_val(i+2);
				}
				DeviceLocal::instance().GetDeviceAttributeObject().SetExternalMask(ip);
	 		}
	  		uint8* cip =
	 				DeviceLocal::instance().GetDeviceAttributeObject().ReadExternalMask();
			term_dat_out((uint8*)"Device IP mask:	");
			for( int i = 0; i < 4; i++ ) {
				str_makedec(t, cip[i]);
				term_dat_out(t);
				if( i != 3 )
					term_dat_out((uint8*)".");
			}
		}break;

		case 6: {
	 		if( parse_get_entry_count() > 5 ) {
				UNS_8 ip[4];
				for( int i = 0; i < 4; i++ ) {
					ip[i] = cmd_get_field_val(i+2);
				}
				DeviceLocal::instance().GetDeviceAttributeObject().SetGatewayIP(ip);
	 		}
	  		uint8* cip =
	 				DeviceLocal::instance().GetDeviceAttributeObject().ReadGatewayIP();
			term_dat_out((uint8*)"Device gate way:	");
			for( int i = 0; i < 4; i++ ) {
				str_makedec(t, cip[i]);
				term_dat_out(t);
				if( i != 3 )
					term_dat_out((uint8*)".");
			}
		}break;

		case 8: {
	 		if( parse_get_entry_count() > 7 ) {
				UNS_8 mac[6];
				for( int i = 0; i < 6; i++ ) {
					mac[i] = cmd_get_field_val(i+2);
				}
				DeviceLocal::instance().GetDeviceAttributeObject().SetMACAddress(mac);
	 		}
	 		uint8* cmac = DeviceLocal::instance().GetDeviceAttributeObject().ReadMACAddress();
			for( int i = 0; i < 6; i++ ) {
				str_makehex(t, cmac[i], 2);
				term_dat_out(t);
				term_dat_out((uint8*)" ");
			}
		}break;

		case 7: {
			if( parse_get_entry_count() > 2 ) {
				uint8 sub_opt = cmd_get_field_val(2);
				if( sub_opt == 1 ) {
					//�ָ���̫Ĭ������
					DeviceLocal::instance().GetVcgGroupObject().RestoreDefauleConfig();
					term_dat_out_crlf((uint8*)"Restore vcg config succeed!");
				}
				else if( sub_opt == 2 ) {
					//�ָ�E1-vc12��������Ĭ������
					DeviceLocal::instance().GetMappingManager().RestoreDefaultConfig();
					term_dat_out_crlf((uint8*)"Restore xc config succeed!");
				}
				else if( sub_opt == 3 ) {
					//�ָ�SDHĬ������
					DeviceLocal::instance().GetSdhObject().RestoreDefaultConfig();
					term_dat_out_crlf((uint8*)"Restore SDH config succeed!");
				}

			}
		}break;

		case 9: {
			int temp = ChipLM75A::getDeviceTemperature();
			std::string s = CPPTools::number2string(temp);
			term_dat_out((uint8*)s.c_str());
		}break;
		default:
	 		term_dat_out_crlf( (UNS_8*)"input parse error!" );
			break;

	}
 	return TRUE;
}
/*--------------------------public function----------------------------*/
void CLI_config_add_commands(void) {
	/* Add NAND group */
	cmd_add_group(&config_group);

	/* Add commands to the config group */
	cmd_add_new_command(&config_group, &creat_dxc_cmd);
	cmd_add_new_command(&config_group, &setmap_cmd);
	cmd_add_new_command(&config_group, &tuadd_cmd);
	cmd_add_new_command(&config_group, &tudel_cmd);
	cmd_add_new_command(&config_group, &slcmd_cmd);
	cmd_add_new_command(&config_group, &syscfg_cmd);

}
