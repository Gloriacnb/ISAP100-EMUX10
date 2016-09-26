/*
 * Task_CLI.cpp
 *
 *  Created on: 2013-2-16
 *      Author: Administrator
 */
#include <rtl.h>
#include "Task_define.h"
#include "TerminalUart.h"
#include "Mid_CLI.h"

OS_TID t_cli_process;

//U8 dataBuf[256] = {0};

__task void T_CLI_Process(void) {
//	TerminalUARTInit();
	CliManagerInit();
	while(1) {
		CLI_Process();
	}
}

void CLI_init(void) {
	t_cli_process = os_tsk_create(T_CLI_Process, P_CLI_Process);
}
