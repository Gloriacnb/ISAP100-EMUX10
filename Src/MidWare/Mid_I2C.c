/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			Mid_I2C.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_I2C.c
** Created by:          Administrator
** Created date:        2012-12-21
** Version:             V0.1
** Descriptions:        
**
**---------------------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:				
** Descriptions:        
**
** Rechecked by:        
***********************************************************************************************************************/
#include "Mid_I2C.h"
#include "ChipGluLogic.h"


#define I2C_Write_CMD  0
#define I2C_Read_CMD   1
#define SFP_Slave_Addr 0xA0


uint8 I2C_read_byte(uint8 ch, uint8 slaveDev, uint8 regAddr) {

	glulogic->I2C_SEL = ch+I2C_SEL_Base;

	/* set address of read from */
	glulogic->i2c_ctrlDataBytes = 0;		//no data send
	glulogic->i2c_ctrlAddrBytes = 1;		//one byte addr
	glulogic->i2c_RegAddr = regAddr;		//the i2c slave device's regAddr or command
	glulogic->i2c_SlaveAddr = SFP_Slave_Addr | I2C_Write_CMD | ((slaveDev & 1) << 1);	//set the slave address and command;
	glulogic->i2c_Start = 1;				//send one frame

	/* here expend a status of completed */
	while( (glulogic->i2c_Start & 0x80) == 0 );

	/* read a byte from regAddr */
	glulogic->i2c_ctrlDataBytes = 1;		//one byte read result
	glulogic->i2c_ctrlAddrBytes = 0;		//no addr send
	glulogic->i2c_SlaveAddr = SFP_Slave_Addr | I2C_Read_CMD | ((slaveDev & 1) << 1);
	glulogic->i2c_Start = 1;

	return glulogic->i2c_Data;
}

void I2C_write_byte(uint8 ch, uint8 slaveDev, uint8 regAddr, uint8 newData) {

	glulogic->I2C_SEL = ch+I2C_SEL_Base;

	glulogic->i2c_ctrlDataBytes = 1;	//one byte data
	glulogic->i2c_ctrlAddrBytes = 1;	//one byte address
	glulogic->i2c_RegAddr = regAddr;	//the i2c slave device's regAddr or command
	glulogic->i2c_Data = newData;		//the data to send
	glulogic->i2c_SlaveAddr = SFP_Slave_Addr | I2C_Write_CMD | ((slaveDev & 1) << 1);		//
	glulogic->i2c_Start = 1;

	/* here expend a status of completed */
	while( (glulogic->i2c_Start & 0x80) == 0 );
}

