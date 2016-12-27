/*
 * Task_define.h
 *
 *  Created on: 2013-2-16
 *      Author: Administrator
 */

#ifndef TASK_DEFINE_H_
#define TASK_DEFINE_H_

#include "EZ_types.h"
#include <rtl.h>

#if defined (__cplusplus)
extern "C"
{
#endif

static const uint8 P_Reset  		= 1;
static const uint8 P_WDT			= 1;
static const uint8 P_CLI_Process 	= 220;
static const uint8 P_Online_Check 	= 3;
static const uint8 P_ETH_RCV		= 99;
static const uint8 P_DCC_RCV		= 98;
static const uint8 P_LED_RUN		= 200;
static const uint8 P_TCP_Main		= 100;
static const uint8 P_TCP_Time   	= P_TCP_Main+1;
static const uint8 P_Agint_MAC		= 4;
static const uint8 P_CFG_Store		= 5;
static const uint8 P_LED			= 10;
static const uint8 P_Alarm_Process  = 7;
static const uint8 P_UI_Active		= 11;
static const uint8 P_MT             = 110;


void CLI_init(void);
void CommunicationInit(int mode);

extern OS_TID t_cli_process;

//__task void T_Device_Reset(void);
extern __task void T_Online_Check(void);
extern __task void T_Device_Reset(void);
extern __task void T_LED_SYS(void);
extern __task void T_Config_Store(void);
extern __task void T_Alarm_process_ISAP(void);
extern __task void T_Alarm_process_PCM(void);
extern __task void T_Aging(void );
extern __task void T_WDT(void);
extern __task void T_LED_UP_E1(void);
extern __task void T_UActive(void* pui);

extern OS_MBX MailPOC;
extern OS_TID t_dcc_rcv;
extern OS_TID t_reset;
extern OS_TID t_led;
extern OS_TID t_alarm_process;
extern OS_TID t_tcpTask;
extern OS_TID t_aging;
extern OS_TID t_wdt;
extern OS_TID t_led_upE1;

#define evt_sdh_store (1<<0)
#define evt_vcg_store (1<<1)

#define evt_store (evt_sdh_store | evt_vcg_store)

#if defined (__cplusplus)
}
#endif
#endif /* TASK_DEFINE_H_ */
