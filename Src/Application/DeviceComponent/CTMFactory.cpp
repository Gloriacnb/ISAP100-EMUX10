/*
 * CTMFactory.cpp
 *
 *  Created on: 2013-11-5
 *      Author: Administrator
 */

#include "CTMFactory.h"

#include "ChipGluLogic.h"
#include "SlotLogicLX9.h"
//#include "ChipSlotLogic.h"
#include "ChipOptLogic.h"
#include "Mid_RC6400App.h"
#include "Mid_RC7880A1App.h"
#include "SysError.h"

CTMFactory::CTMFactory() {
	// TODO Auto-generated constructor stub

}

CTMFactory::~CTMFactory() {
	// TODO Auto-generated destructor stub
}

void CTMFactory::initChips(void) {
	/* Init chip 1 */
	if (glulogic_open(&GluConfig) != TRUE) {
		  throw SysError("!!!Glulogic chip init failed!");
	}

	/* Init chip 2 */
	SlotLogic_LX9 lx9;
	lx9.OpenSlotLogic();

	/* Init chip 3 */
	if (optlogic_open(OptLogic_REGPTR) != TRUE) {
		  throw SysError("!!!Optlogic chip init failed!");
	}

	/* Init chip 4 */
	if (open_rc7880a1(2) != TRUE) {
		  throw SysError("!!!Rc7880 chip init failed!");
	}

	/* Init chip 5 */
	if (open_rc6400() != TRUE) {
		  throw SysError("!!!Rc6400 chip init failed!");
	}
}
