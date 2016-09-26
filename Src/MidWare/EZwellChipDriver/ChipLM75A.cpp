/*
 * ChipLM75A.cpp
 *
 *  Created on: 2013-5-28
 *      Author: Administrator
 *      desc: 温度传感器
 */

#include "ChipLM75A.h"
#include "lpc32xx_clkpwr_driver.h"


uint32 ChipLM75A::i2cdev2;
I2C_SETUP_T ChipLM75A::i2c_setup[2];

ChipLM75A::ChipLM75A() {

	/* open I2C2 */
	clkpwr_clk_en_dis(CLKPWR_I2C2_CLK,1);
	i2cdev2 = i2c_open(I2C2, 0);

	/* formally assign a 7-bit slave address 0x50 to I2C1    */
	/* I2C2 clock is 100 kHz, 50% duty cycle, high pin drive */
	i2c_setup[1].addr_mode  = ADDR7BIT;
	i2c_setup[1].sl_addr    = 0x50;
	i2c_setup[1].rate_option= I2C_RATE_RELATIVE;
	i2c_setup[1].rate       = 100000;
	i2c_setup[1].low_phase  = 50;
	i2c_setup[1].high_phase = 50;
	i2c_setup[1].pins_drive = I2C_PINS_HIGH_DRIVE;
	i2c_ioctl((UNS_32) i2cdev2, I2C_SETUP, (UNS_32) &i2c_setup[1]);
}

ChipLM75A::~ChipLM75A() {
	// TODO Auto-generated destructor stub
}

int ChipLM75A::getDeviceTemperature(void) {

	I2C_MTX_SETUP_T   i2c_mtx_setup;
	uint8 temp[2] = {0};
	i2c_mtx_setup.addr_mode = ADDR7BIT;
	i2c_mtx_setup.sl_addr = LM75A_SA;
	temp[0] = regTemp;
	i2c_mtx_setup.tx_data = temp;
	i2c_mtx_setup.tx_length = 1;
	i2c_mtx_setup.retransmissions_max = 5;
	i2c_ioctl(i2cdev2, I2C_MASTER_TX, (INT_32) &i2c_mtx_setup);
	while (( i2c_mtx_setup.status & I2C_SETUP_STATUS_DONE) == 0);

	I2C_MRX_SETUP_T   i2c_mrx_setup;
	i2c_mrx_setup.addr_mode = ADDR7BIT;
	i2c_mrx_setup.sl_addr = LM75A_SA;
	i2c_mrx_setup.retransmissions_max = 5;
	i2c_mrx_setup.rx_length = 2;
	i2c_mrx_setup.rx_data = temp;
	i2c_ioctl(i2cdev2, I2C_MASTER_RX, (INT_32) &i2c_mrx_setup);
    while (( i2c_mrx_setup.status & I2C_SETUP_STATUS_DONE) == 0);

    uint16 temperature = (temp[0] << 8) | temp[1];
    int result = 0;
    if( (temperature & 0x8000) == 0 ) {
    	//正温度
    	result = (temperature>>5) * 125;
    }
    else {
    	result = ((temperature & ~0x80) >> 5) * 125;
    	result = 0-result;
    }

	return result;
}
