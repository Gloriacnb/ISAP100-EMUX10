/*
 * Lpc3250upload.cpp
 *
 *  Created on: 2013-3-16
 *      Author: Administrator
 */

#include "Lpc3250upload.h"

//#include <fstream>
#include <stdio.h>
#include <string.h>


//extern "C" int updata_main(uint8* name, uint8 len);

extern "C" {
	void __swi(8)  EnterCritical (void);
	void __swi(9)  ExitCritical (void);
}
using namespace std;

Lpc3250_upload::Lpc3250_upload(uint8* name, uint8 nLen) {
	// TODO Auto-generated constructor stub
	cfg_load(&cfg);
	if( nLen > 20 ) {
		throw;
	}
	memcpy( filename, name, nLen);
	filename[nLen] = 0;
};

Lpc3250_upload::~Lpc3250_upload() {
	// TODO Auto-generated destructor stub
}

bool Lpc3250_upload::startUpload(void) {
//	ifstream inf((const char*)fname, ios::in | ios::binary);
//	if( inf.is_open() ) {
//		saveinfo.BlockFirst = cfg.fsave.block_first;
//		inf.seekg(0, inf.end);
//		uint32 size = inf.tellg();
//		inf.seekg(0, inf.beg);
//	    char* contents = new char [size];
//		saveinfo.BufAddr = (uint32)contents;
//		saveinfo.ByteNums = size;
//		EnterCritical();
//
//		inf.read(contents, size);
////		inf.rdbuf()->sgetn(contents, size);
//		ExitCritical();
//
//		savefile.setInfo(saveinfo);
//		savefile.SaveData(0);
//		cfg.fsave.num_bytes = saveinfo.ByteNums;
//		cfg.fsave.secs_used = savefile.getInfo()->SecsUsed;
//		cfg.fsave.blocks_used = savefile.getInfo()->BlockUsed;
//		cfg_save(&cfg);
//
//		delete [] contents;
//		return true;
//	}
//	return false;
	FILE* inf = fopen((const char*)filename, "rb");
	if( inf != NULL ) {
		saveinfo.BlockFirst = cfg.fsave.block_first;
		fseek(inf, 0, SEEK_END);
		uint32 size = ftell(inf);
		fseek(inf, 0, SEEK_SET);
	    char* contents = new char [size];
		saveinfo.BufAddr = (uint32)contents;
		fread(contents, 1, size, inf);
		saveinfo.ByteNums = size;
		fclose(inf);

		savefile.setInfo(saveinfo);
		savefile.SaveData(0);
		cfg.fsave.num_bytes = saveinfo.ByteNums;
		cfg.fsave.secs_used = savefile.getInfo()->SecsUsed;
		cfg.fsave.blocks_used = savefile.getInfo()->BlockUsed;
		cfg_save(&cfg);

		delete [] contents;
		return true;

	}
	return false;
}

int updata_main(uint8* s, uint8 len) {
	try{
		Lpc3250_upload up3250(s, len);

		if( up3250.startUpload() ) {
			return 1;
		}
	}
	catch(...) {
		return -1;
	}
	return -1;
}
