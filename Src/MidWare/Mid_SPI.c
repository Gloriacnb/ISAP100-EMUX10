/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			Mid_SPI.cpp
 ** File path:			/ISAP100_Mainsoft/Src/EZSoft/MidWare/Mid_SPI.cpp
 ** Created by:          Administrator
 ** Created date:        2012-12-7
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
#include "Mid_SPI.h"
#include "lpc32xx_gpio_driver.h"
#include "lpc32xx_ssp_driver.h"
#include "ChipGluLogic.h"
#include <rtl.h>
/* SSP device handles */
static INT_32 sspdev;
OS_MUT mut_spi;

uint32 SpiSend(uint8* buff, uint32 len) {
	uint8 dump[2] = { 0 };
	uint32 bytes_all = 0;
	while (bytes_all < len) {
		bytes_all += ssp_write(sspdev, &buff[bytes_all], 1);
	}
	while (ssp_read(sspdev, dump, 1) != 0)
		; //clear fifo
	return TRUE;
}

uint32 SpiReceive(uint8* buff, uint32 len) {
	uint8 dump = 0;
	uint32 bytes_all = 0;
	while (bytes_all < len) {
		bytes_all += ssp_write(sspdev, &dump, 1);
	}
	bytes_all = 0;
	while (bytes_all < len) {
		bytes_all += ssp_read(sspdev, &buff[bytes_all], 1);
	}
	return TRUE;

}

/***********************************************************************
 *
 * Function: SpiChipRead
 *
 * Purpose: Read a byte by SSP1
 *
 * Processing:
 *
 *
 * Parameters:
 *     addr   : Register address in accessed chip
 *     addrWidth : the addr's number in bytes. 1 or 2
 *     dataWidth :
 *
 * Outputs: None
 *
 * Returns: _ERROR if the configuration setup failed, otherwise _NO_ERROR
 *
 * Notes: None
 *
 **********************************************************************/
enum {
	MAX_SPI_Bytes = 4
};

int SpiChipRead(uint16 addr, uint8 addrWidth, uint8 dataWidth) {
	uint8 buf[MAX_SPI_Bytes] = { 0 };
	uint8 dump = 0;
	int sendLen = addrWidth + dataWidth;
	int bytes = 0;

	if (sspdev == 0) {
		return -1;
	}

	if (addrWidth == 1) {
		if (dataWidth == 1) {
			buf[0] = (uint8) addr;
			buf[1] = 0xff;
		} else {
			buf[0] = (uint8) addr;
			buf[1] = 0xff;
			buf[2] = 0xff;
		}
	} else {
		if (dataWidth == 1) {
			buf[0] = (addr >> 8) & 0x7F;
			buf[1] = (addr >> 0) & 0xFF;
			buf[2] = 0xff;
		} else {
			buf[0] = (addr >> 8) & 0x7F;
			buf[1] = (addr >> 0) & 0xFF;
			buf[2] = 0xff;
			buf[3] = 0xff;
		}
	}

	while (ssp_read(sspdev, &dump, 1) != 0)
		; //从sspdev中取出1字节数据放到dump，当dump为空
	ssp_write(sspdev, buf, sendLen); //sendlen字节的buf寄存器地址发送出去

	while (bytes < sendLen) {
		bytes += ssp_read(sspdev, &buf[bytes], 1); //把寄存器中的数据放到buf中来。
	}

	if (addrWidth == 1) {
		if (dataWidth == 1) {
			return buf[1];
		} else {
			return (buf[1] << 8) | buf[2];
		}
	} else {
		if (dataWidth == 1) {
			return buf[2];
		} else {
			return (buf[2] << 8) | buf[3];
		}
	}

}
enum {
	MAX_Bytes = 18
};

int SpiChipRamRead(uint16 addr, uint16* data) {
	uint8 buf[MAX_Bytes] = { 0 };
	uint8 dump = 0;
	int i;
	int bytes = 0;
	if (sspdev == 0) {
		return -1;
	}
	buf[0] = ((uint8) (addr)) | 0x60;
	while (ssp_read(sspdev, &dump, 1) != 0)
		; //从sspdev中取出1字节数据放到dump，当dump为空
	for (i = 0; i < 18; i++) {
//		printf("\nbuf[%d] = %x\n", i, buf[i]);
		ssp_write(sspdev, buf + i, 1); //sendlen字节的buf寄存器地址发送出去

		ssp_read(sspdev, buf + i, 1); //把寄存器中的数据放到buf中来。
//	printf("\nbuf[%d] = %x\n", i, buf[i]);
	}
	if (buf[1] != 0x81)
		return -1;
	if (data != NULL) {
		for (i = 0; i < 8; i++) {
			data[i] = (buf[2 * i + 2] << 8) | (buf[2 * i + 3]);
		}
	}
//	printf("\ndata[0] = %x\n", data[0]);
	return 0;
}

#define SPI_Write_CMD  0x80
void SpiChipWrite(uint16 addr, uint16 data, uint8 addrWidth, uint8 dataWidth) {
	static uint8 buf[MAX_SPI_Bytes] = { 0 };
	uint8 dump = 0;
	int sendLen = addrWidth + dataWidth;
//	int bytes = 0;

	if (sspdev == 0) {
		return;
	}

	if (addrWidth == 1) {
		if (dataWidth == 1) {
			buf[0] = addr | SPI_Write_CMD;
			buf[1] = (uint8) data;
		} else {
			buf[0] = addr | SPI_Write_CMD;
			buf[1] = (uint8) (data >> 8);
			buf[2] = (uint8) data;
		}
	} else {
		if (dataWidth == 1) {
			buf[0] = (addr >> 8) | SPI_Write_CMD;
			buf[1] = (addr >> 0) & 0xFF;
			buf[2] = (uint8) data;
		} else {
			buf[0] = (addr >> 8) | SPI_Write_CMD;
			buf[1] = (addr >> 0) & 0xFF;
			buf[2] = (uint8) (data >> 8);
			buf[3] = (uint8) data;
		}
	}

	ssp_write(sspdev, buf, sendLen);
	while (ssp_read(sspdev, &dump, 1) != 0)
		;

}

void SpiChipRamWrite(uint8 addr, uint16* data) {
	static uint8 buf[17] = { 0 };
	uint8 dump = 0;
	int i;
//	int bytes = 0;
	if (sspdev == 0) {
		return;
	}
	for (i = 0; i < 17; ++i) {
		buf[i] = 0x00;
	}
	buf[0] = (addr) | 0xE0;
	for (i = 0; i < 8; ++i) {
		buf[2 * i + 1] = data[i] >> 8;
		buf[2 * i + 2] = data[i] & 0x00ff;
	}
//	for ( i = 0; i < 17; ++i) {
//		printf("\nbuf[%d] = %x\n", i, buf[i]);
//	}
	while (ssp_read(sspdev, &dump, 1) != 0)
		;

	for (i = 0; i < 17; i++) {
		ssp_write(sspdev, buf + i, 1);
		//ssp_read(sspdev, buf+i, 1);
	}
}

uint32 ExtCPLDRegWriteBit(uint8 spiCh, uint16 regAddr, uint8 bitpos,
		uint8 value) {
	uint8 temp = 0;
	ExtCPLDRegReadByte(spiCh, regAddr, &temp);
	temp &= ~(1 << bitpos);
	temp |= (value << bitpos);
	ExtCPLDRegWriteByte(spiCh, regAddr, temp);
	return TRUE;
}

uint32 ExtCPLDRegWriteByte(uint8 spiCh, uint16 regAddr, uint8 value) {
	if (spiCh < SPI_IDLE_MAX) {
		os_mut_wait(mut_spi, 0xffff);
		glulogic->SPI_SEL = spiCh | 0x03;	//patch
		glulogic->SPI_SEL = spiCh;
		SpiChipWrite(regAddr, value, 2, 1);
		glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
		os_mut_release(mut_spi);

		return TRUE;
	}
	return FALSE;
}
uint32 ExtCPLDRegReadByte(uint8 spiCh, uint16 regAddr, uint8* value) {
	if (spiCh < SPI_IDLE_MAX) {	//16
		os_mut_wait(mut_spi, 0xffff);
		glulogic->SPI_SEL = spiCh | 0x03;	//patch
		glulogic->SPI_SEL = spiCh;
		*value = SpiChipRead(regAddr, 2, 1);
		glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
		os_mut_release(mut_spi);
		return TRUE;
	}
	return FALSE;
}
uint32 ExtIDTRegReadByte(uint8 spiCh, uint8 regAddr, uint8* value) {
	uint16 result = 0;
	os_mut_wait(mut_spi, 0xffff);
	glulogic->SPI_SEL = spiCh | 0x03;	//patch
	glulogic->SPI_SEL = spiCh;
	result = SpiChipRead(regAddr, 1, 2);
	glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
	os_mut_release(mut_spi);
	if ((result >> 8) != 0x81) {
		return FALSE;
	}
	*value = (uint8) result;
	return TRUE;
}

uint32 ExtIDTRegWriteByte(uint8 spiCh, uint16 regAddr, uint8 value) {
	if (spiCh < SPI_IDLE_MAX) {
		os_mut_wait(mut_spi, 0xffff);
		glulogic->SPI_SEL = spiCh | 0x03;	//patch
		glulogic->SPI_SEL = spiCh;
		SpiChipWrite(regAddr, value, 1, 2);
		glulogic->SPI_SEL = SPI_IDLE_MAX | 0x03;
		os_mut_release(mut_spi);

		return TRUE;
	}
	return FALSE;
}

int InitSPI(void) {
	SSP_CONFIG_T sspcfg;
	os_mut_init(mut_spi);

	/* The SSP can control the SSEL signal */
	GPIO->p2_mux_set = P2_GPIO04_SSEL1;
	GPIO->p2_dir_set = P2_DIR_GPIO(4);

	/* The MISO, MOSI, and SCK signals are controlled by the SSP */
	GPIO->p_mux_set = (P_SPI2DATAIO_MOSI1 |
	P_SPI2DATAIN_MISO1 | P_SPI2CLK_SCK1);

	/* Open SSP */
	sspcfg.databits = 8;
	sspcfg.mode = SSP_CR0_FRF_SPI;
	sspcfg.highclk_spi_frames = TRUE;
	sspcfg.usesecond_clk_spi = TRUE;
	sspcfg.ssp_clk = 3000000;	//4000000;
	sspcfg.master_mode = TRUE;
	sspdev = ssp_open(SSP1, (INT_32) &sspcfg);
	if (sspdev == 0) {
		/* Error */
		return -1;
	}

	/* Enable SSP*/
	ssp_ioctl(sspdev, SSP_ENABLE, 1);
	return 0;
}

int InitSPIforFPGA(void) {
	SSP_CONFIG_T sspcfg;

	/* The SSP can control the SSEL signal */
	GPIO->p2_mux_set = P2_GPIO04_SSEL1;
	GPIO->p2_dir_set = P2_DIR_GPIO(4);

	/* The MISO, MOSI, and SCK signals are controlled by the SSP */
	GPIO->p_mux_set = (P_SPI2DATAIO_MOSI1 |
	P_SPI2DATAIN_MISO1 | P_SPI2CLK_SCK1);

	/* Open SSP */
	sspcfg.databits = 8;
	sspcfg.mode = SSP_CR0_FRF_SPI;
	sspcfg.highclk_spi_frames = FALSE;
	sspcfg.usesecond_clk_spi = TRUE;
	sspcfg.ssp_clk = 4000000;
	sspcfg.master_mode = TRUE;
	sspdev = ssp_open(SSP1, (INT_32) &sspcfg);
	if (sspdev == 0) {
		/* Error */
		return -1;
	}

	/* Enable SSP*/
	ssp_ioctl(sspdev, SSP_ENABLE, 1);
	return 0;
}

enum {
	Top_Bytes = 3, Read_command = 0x80
};
int SpiMCRead(uint8 addr, uint8 addrBits, uint8 dataBits) {
	static uint8 buf[MAX_SPI_Bytes] = { 0 };
	uint8 dump = 0;
	int bytes = 0;
	int sendLen = (addrBits + dataBits) / 8;

	if (((addrBits + dataBits) % 8) != 0) {
		return -1;
	}

	switch (addrBits) {
	case 4:
		switch (dataBits) {
		case 4:
		case 12:
			buf[0] = (addr << 4) | Read_command;
			break;
		default:
			return -1;
		}
		break;
	case 8:
		switch (dataBits) {
		case 8:
			buf[0] = addr | Read_command;
			break;
		default:
			return -1;
		}
		break;
	default:
		return -1;
	}

	while (ssp_read(sspdev, &dump, 1) != 0)
		;
	ssp_write(sspdev, buf, sendLen);
	while (bytes < sendLen) {
		bytes += ssp_read(sspdev, &buf[bytes], 1);	//把寄存器中的数据放到buf中来。
	}
	if ((addrBits == 4) && (dataBits == 4)) {
		return buf[0] & 0xf;
	} else if ((addrBits == 4) && (dataBits == 12)) {
		return ((buf[0] & 0xf) << 8) | buf[1];
	} else if ((addrBits == 8) && (dataBits == 8)) {
		return buf[1];
	}
	return -1;
}
int SpiMCWrite(uint8 addr, uint16 data, uint8 addrBits, uint8 dataBits) {
	static uint8 buf[MAX_SPI_Bytes] = { 0 };
	uint8 dump = 0;
	int sendLen = (addrBits + dataBits) / 8;
	if (((addrBits + dataBits) % 8) != 0) {
		return -1;
	}
//	int bytes = 0;

	if (sspdev == 0) {
		return -1;
	}

	if ((addrBits == 4) && (dataBits == 4)) {
		buf[0] = ((addr << 4) | (data & 0x0f)) & 0x7f;
	} else if ((addrBits == 4) && (dataBits == 12)) {
		buf[0] = ((addr << 4) | ((data >> 8) & 0x0f)) & 0x7f;
		buf[1] = data & 0xff;
	} else if ((addrBits == 8) && (dataBits == 8)) {
		buf[0] = addr;
		buf[1] = data;

	}

	ssp_write(sspdev, buf, sendLen);
	while (ssp_read(sspdev, &dump, 1) != 0)
		;
	return 1;
}

