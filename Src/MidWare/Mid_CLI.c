/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_CLI.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_CLI.c
** Created by:          Administrator
** Created date:        2012-11-27
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
#include "lpc_types.h"
#include "Mid_CLI.h"
#include "s1l_line_input.h"
#include "lpc_string.h"
#include "s1l_cmds.h"
#include "CLI_Config_cmd_group.h"
#include "CLI_Debug_cmd_group.h"
#include "CLI_FILE_cmd_group.h"

static UNS_8 str[255];

void CliManagerInit(void) {

	UNS_8 prmpt[16] = "EZ_ISAP100:> ";

	/* Initialize commands */
	CLI_config_add_commands();
	CLI_debug_add_commands();
	CLI_file_add_commands();

	/* Initialize line prompt and parser */
	key_line_init(prmpt);
}

void CLI_Process(void) {
	key_get_command(str);
	str_upper_to_lower(str);
	cmd_process(str);

}

