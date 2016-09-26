/*
 * RTC.cpp
 *
 *  Created on: 2013-3-12
 *      Author: Administrator
 */

#include "RTC.h"

#include <time.h>
#include <string>
#include "CPPTools.h"
#include <rtl.h>

extern "C" time_t bootTime;


RTC::RTC() {
	// TODO Auto-generated constructor stub
//	time_t t = time(NULL);
//	clock_t c = clock();

}

RTC::~RTC() {
	// TODO Auto-generated destructor stub
}

std::string RTC::getCurrentStringTime(void) {
	time_t info = time(0);
// 	if( time( &info ) < 0 ) {
// 		std::string s("error");
// 		return s;
// 	}
	struct tm* st = localtime(&info);

	std::string curtime =
			CPPTools::number2string(st->tm_year+1900) + "-" +
			CPPTools::number2string(st->tm_mon+1)  + "-" +
			CPPTools::number2string(st->tm_mday) + " " +
			CPPTools::number2string(st->tm_hour) + ":" +
			CPPTools::number2string(st->tm_min) + ":" +
			CPPTools::number2string(st->tm_sec);


	return curtime;
}

uint32 RTC::getCurrentSecsTime(void) {
//	time_t info;
	return time(0);
}

void RTC::setUTC(uint32 nv) {
	bootTime = nv - os_time_get()/100;
}

uint32 RTC::converClockToUTC(uint32 clocks) {
	return bootTime + clocks/100;
}


uint32 RTC::getRunningSecs(void) {
	return os_time_get()/100;
}
uint32 RTC::converRunningSecsToUTC(uint32 secs) {
	return bootTime + secs;
}
