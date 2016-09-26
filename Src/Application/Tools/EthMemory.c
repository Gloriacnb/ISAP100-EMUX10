/*
 * EthMemory.cpp
 *
 *  Created on: 2013-7-18
 *      Author: Administrator
 */

#include "EthMemory.h"
#include <rtl.h>

_declare_box(datapool,1024,32);
_declare_box(framepool,16,32);

void InitEthMemory(void) {
	_init_box(datapool, sizeof(datapool), 1024);
	_init_box(framepool, sizeof(framepool), 16);
}

LAYER2FRAME* alloc_Eth_mem(uint16 len) {
	LAYER2FRAME* f = _calloc_box(framepool);
	if( f ) {
		f->length = len;
		f->frame = _calloc_box(datapool);
		if( f->frame == 0 ) {
			_free_box(framepool, f);
			return 0;
		}
	}
	return f;
}
void free_Eth_mem(LAYER2FRAME* f) {
	if( f ) {
		_free_box(datapool, f->frame);
		_free_box(framepool, f);
	}
}
