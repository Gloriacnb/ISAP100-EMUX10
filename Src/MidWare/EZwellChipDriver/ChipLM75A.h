/*
 * ChipLM75A.h
 *
 *  Created on: 2013-5-28
 *      Author: Administrator
 */

#ifndef CHIPLM75A_H_
#define CHIPLM75A_H_

#include "EZ_types.h"
#include "lpc32xx_i2c_driver.h"



class ChipLM75A {
public:
	ChipLM75A();
	virtual ~ChipLM75A();

	/*
	 * 读取设备温度   单位0.001摄氏度
	 */
	static int getDeviceTemperature(void);

private:
	static uint32 i2cdev2;
	const static enum {
		regTemp,
		regConf,
		regThyst,
		regTos,
		LM75A_SA = 0x48,
	}LM75A_REG_T;

	static I2C_SETUP_T i2c_setup[2];

};

#endif /* CHIPLM75A_H_ */
