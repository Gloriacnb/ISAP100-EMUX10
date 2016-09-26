/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    BLINKY.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>
#include <LPC325x.h>                    /* LPC325x definitions               */
#include "lpc32xx_intc_driver.h"
//#include "RTX_SWI.h"
#include "Task_define.h"
#include "SNMP_Process.h"
#include "DeviceLocal.h"
//#include <iostream>
#include "TerminalUart.h"
#include <string.h>
#include <Net_Config.h>
#include "CDeviceAttribute.h"
#include "SysError.h"
#include <iostream>
#include "TopoManager.h"

//using namespace std;

int sys_init_status = 0;		//0 δ��ʼ����1��ʼ��������-1���쳣

OS_TID t_toggleRun;                  /* assigned task id of task: toggleRun  */
OS_TID t_tcpTask;

U8 udp_soc;
extern U16 Process_SNMP(U8 socket, U8 *remip, U16 remport, U8 *buf, U16 len);


#define LED_RUN   (1<<2)

#define LED_ON(led)  P3_OUTP_CLR = led;
#define LED_OFF(led) P3_OUTP_SET = led;

extern LOCALM localm[];

extern "C" {
	void lpc32xx_irq_handler(void);
	void os_clock_interrupt (void);
	void interrupt_ethernet (void);
}
/*----------------------------------------------------------------------------
 *        Task 1 'phaseA': Phase A output
 *---------------------------------------------------------------------------*/
__task void toggleRun (void) {
  for (;;) {
    LED_ON (LED_RUN);
    os_dly_wait (50);
    LED_OFF(LED_RUN);
    os_dly_wait (50);
  }
}
__task void tcp_tick (void) {
  os_itv_set (10);
  while (1) {
    os_itv_wait ();
    /* Timer tick every 100 ms */
    timer_tick ();
//	os_evt_set(0x0001, t_tcpTask);

  }
}

//static void ping_cback (U8 event) {
//  switch (event) {
//    case ICMP_EVT_SUCCESS:
//      term_dat_out_crlf ((UNS_8*)"Remote host responded to ping.\n");
//      break;
//    case ICMP_EVT_TIMEOUT:
//      /* Timeout, try again. */
//      term_dat_out_crlf ((UNS_8*)"Ping timeout, no response.\n");
//      break;
//  }
//}
//void ping_host (void) {
//  U8 hostip[4] = {192,168,2,12};
//
//  if (icmp_ping (&hostip[0], ping_cback) == __TRUE) {
//    term_dat_out_crlf((UNS_8*)"Ping started.\n");
//  }
//  else {
//    term_dat_out_crlf((UNS_8*)"Ping not started, ICMP not ready or bad parameters.\n");
//  }
//}


__task void tcp_main (void) {
	init_TcpNet ();
	memcpy (localm[0].IpAdr,
			DeviceLocal::instance().GetDeviceAttributeObject().ReadExternalIP(),
			4 );
	memcpy (localm[0].NetMask,
			DeviceLocal::instance().GetDeviceAttributeObject().ReadExternalMask(),
			4 );
	memcpy (localm[0].DefGW,
			DeviceLocal::instance().GetDeviceAttributeObject().ReadGatewayIP(),
			4 );
	udp_soc = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, Process_SNMP);
	if (udp_soc != 0) {
	/* Open UDP port 161 for communication */
		udp_open (udp_soc, 161);
	}
	while (1) {
		os_evt_wait_and(0x0001, 0xFFFF);
		while(main_TcpNet () == __TRUE);
	}
}

__task void snmp_init(void) {
	Init_SNMP();
	os_tsk_delete_self ();
}

/*----------------------------------------------------------------------------
 *        Task 5 'init': Initialize
 *---------------------------------------------------------------------------*/


__task void init (void) {

	LED_OFF (LED_RUN);
	try {
		DeviceLocal::instance().DeviceInit();
		sys_init_status = 1;
	}
	catch (SysError& e) {
		sys_init_status = -1;
		std::cout << e.what() << std::endl;
	}
	if( sys_init_status <= 0 ) {
		CLI_init();
		t_toggleRun = os_tsk_create (toggleRun, 200);  /* start task phaseA                */
		os_tsk_create(T_Online_Check, P_Online_Check);
	}
	else {
		static uint8 snmpStack[4096];
		os_tsk_create_user(snmp_init, 2, snmpStack, sizeof(snmpStack));

		os_tsk_create (tcp_tick, P_TCP_Time);
		static uint8 tcpStack[4096];
		t_tcpTask = os_tsk_create_user(tcp_main, P_TCP_Main, tcpStack, sizeof(tcpStack));

		CLI_init();
		t_reset = os_tsk_create (T_Device_Reset, P_Reset);

		if( DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceSubtype() != type_emux_v10 &&
				DeviceLocal::instance().GetDeviceAttributeObject().GetDeviceSubtype() != type_emux_v12 ) {
			CommunicationInit(0);
			t_alarm_process = os_tsk_create(T_Alarm_process_ISAP, P_Alarm_Process);
			t_led = os_tsk_create(T_LED_SYS, P_LED);
		}
		else {
			CommunicationInit(0);
			t_alarm_process = os_tsk_create(T_Alarm_process_PCM, P_Alarm_Process);
			t_led_upE1 = os_tsk_create(T_LED_UP_E1, P_LED);
		}




		t_toggleRun = os_tsk_create (toggleRun, 200);  /* start task phaseA                */
		os_tsk_create(T_Online_Check, P_Online_Check);

		DeviceLocal::instance().DeviceRun();
	}
	t_wdt = os_tsk_create(T_WDT, P_WDT);

    TopoManager::startTopoSearch();

	os_tsk_delete_self ();
}

/*----------------------------------------------------------------------------
 *        Main: Initialize and start RTX Kernel
 *---------------------------------------------------------------------------*/

int main (void) {
	finit(NULL);
	fformat ("");

	os_sys_init(init);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

