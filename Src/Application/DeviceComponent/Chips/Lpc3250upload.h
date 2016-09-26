/*
 * Lpc3250upload.h
 *
 *  Created on: 2013-3-16
 *      Author: Administrator
 */

#ifndef LPC3250UPLOAD_H_
#define LPC3250UPLOAD_H_

#include "CMSSave.h"
#include "cfg_save_nand.h"


class Lpc3250_upload {
	S1L_CFG_T cfg;
	EZ_FLASH_DATA_T saveinfo;
	CMSSave savefile;
	uint8 filename[20];
public:
	Lpc3250_upload() {};
	Lpc3250_upload(uint8* fname, uint8 nLen);

	bool startUpload(void);
	virtual ~Lpc3250_upload();
};

//int updata_main(uint8* fname);

#endif /* LPC3250UPLOAD_H_ */
