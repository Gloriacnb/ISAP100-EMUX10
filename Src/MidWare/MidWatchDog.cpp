/*
 * MidWatchDog.cpp
 *
 *  Created on: 2013-7-24
 *      Author: Administrator
 */

#include "MidWatchDog.h"
#include "ChipGluLogic.h"
#include "lpc32xx_wdt_driver.h"
#include "lpc32xx_clkpwr_driver.h"

int MidWatchDog::w = none;
int MidWatchDog::wdtdev;
static WDT_SETUP_T wdtsetup;

MidWatchDog::MidWatchDog() {
	// TODO Auto-generated constructor stub

}

MidWatchDog::~MidWatchDog() {
	// TODO Auto-generated destructor stub
}


void MidWatchDog::WatchDogInitial(void) {
//	if( glulogic->chip_ver == 0 ) {
		//EXT WDT无效，启用片内WD
		ChipWDInitial();
		w = onchip;
//	}
//	else {
//		//启用外部看门狗
//		ExtWDInitial();
//		w = offchip;
//	}
}
void MidWatchDog::feed(void) {
	wdt_ioctl(wdtdev, WDT_COUNTER_WRITE, 0);

}
void MidWatchDog::start(void) {
	wdt_ioctl(wdtdev, WDT_TIMER_CONTROL, WDT_TIMER_GO);
}
void MidWatchDog::stop(void) {
	wdt_ioctl(wdtdev, WDT_TIMER_CONTROL, WDT_TIMER_STOP);
}


void MidWatchDog::ChipWDInitial(void) {

	/* Enable simple WDT clock */
	clkpwr_clk_en_dis(CLKPWR_WDOG_CLK, 1);

	wdtdev = wdt_open(WDT, 0);
	if( wdtdev == 0 ) {
		return;
	}
	wdt_ioctl(wdtdev, WDT_COUNTER_WRITE, 0);
	wdtsetup.initial_setup = TRUE;
	wdtsetup.pause = 1;
	wdtsetup.resfrc2 = 0;
	wdtsetup.resfrc1 = 0;
	wdtsetup.m_res2 = 0;
	wdtsetup.m_res1 = 1;
	wdtsetup.ext_match_setup = WDT_EXT_MATCH_HIGH;
	wdtsetup.match_setup = WDT_MATCH_EN_INT_RESET;
	wdtsetup.match0 = 5000 * 13000; //1000ms
	wdtsetup.match0_update = TRUE;
	wdtsetup.counter_update = FALSE;
	wdtsetup.pulse_update = FALSE;
	wdt_ioctl(wdtdev, WDT_SETUP, (UNS_32) &wdtsetup);
}

void MidWatchDog::ExtWDInitial(void) {

}

