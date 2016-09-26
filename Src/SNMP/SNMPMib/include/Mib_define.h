/*
 * Mib_define.h
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#ifndef MIB_DEFINE_H_
#define MIB_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"


typedef enum {
	table_entry = 1,
	Max_oid_size = 256,
	Max_value_octect_size = 100,
	Max_index_size = 5,
	Mib_read_only = 1,
	Mib_read_write,
	Mib_write_only

}Mib_T;

typedef struct {
	uint8 table_sn;
	uint8 table_col_num;
	uint8 table_index_num;
}table_info_T;

typedef struct {
	uint8 col_sn;
	uint8 col_access;
	uint8 col_value_type;
}column_info_T;

typedef struct {
	uint8 index_number;
	uint32 index[Max_index_size];
}index_info_T;
#if defined (__cplusplus)
}
#endif
#endif /* MIB_DEFINE_H_ */
