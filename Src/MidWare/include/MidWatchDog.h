/*
 * MidWatchDog.h
 *
 *  Created on: 2013-7-24
 *      Author: Administrator
 */

#ifndef MIDWATCHDOG_H_
#define MIDWATCHDOG_H_

class MidWatchDog {
public:
	MidWatchDog();
	virtual ~MidWatchDog();

	static void WatchDogInitial(void);
	static void feed(void);
	static void start(void);
	static void stop(void);

private:
	static void ChipWDInitial(void);
	static void ExtWDInitial(void);
	typedef enum {
		none,
		onchip,
		offchip
	}WorkingWD;

	static int w;
	static int wdtdev;
};

#endif /* MIDWATCHDOG_H_ */
