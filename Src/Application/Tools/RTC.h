/*
 * RTC.h
 *
 *  Created on: 2013-3-12
 *      Author: Administrator
 */

#ifndef RTC_H_
#define RTC_H_

#include <string>
#include "EZ_types.h"


class RTC {
public:
	RTC();
	virtual ~RTC();

	static std::string getCurrentStringTime(void);
	static uint32 getCurrentSecsTime(void);
	static void setUTC(uint32);
	static uint32 converClockToUTC(uint32 clocks);
	static uint32 getRunningSecs(void);
	static uint32 converRunningSecsToUTC(uint32 secs);
};

#endif /* RTC_H_ */
