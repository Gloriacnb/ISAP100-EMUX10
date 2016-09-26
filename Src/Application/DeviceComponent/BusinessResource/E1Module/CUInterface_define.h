/*
 * CUInterface_define.h
 *
 *  Created on: 2013-7-29
 *      Author: Administrator
 */

#ifndef CUINTERFACE_DEFINE_H_
#define CUINTERFACE_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

typedef struct {
	uint8 mode;
	uint8 enable;
	char desc[32];
	uint8 dlen;
}UInterface_config_data;

#if defined (__cplusplus)
}
#endif
#endif /* CUINTERFACE_DEFINE_H_ */
