/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			EZ_types.h
** File path:			/ISAP100_Mainsoft/Src/EZSoft/include/EZ_types.h
** Created by:          Administrator
** Created date:        2012-11-20
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


#ifndef EZ_TYPES_H_
#define EZ_TYPES_H_

typedef unsigned int   BOOL;
typedef unsigned char  uint8;                                           /*  �޷���8λ���ͱ���           */
typedef signed   char  int8;                                            /*  �з���8λ���ͱ���           */
typedef unsigned short uint16;                                          /*  �޷���16λ���ͱ���          */
typedef signed   short int16;                                           /*  �з���16λ���ͱ���          */
typedef unsigned int   uint32;                                          /*  �޷���32λ���ͱ���          */
typedef signed   int   int32;                                           /*  �з���32λ���ͱ���          */
typedef float          fp32;                                            /*  �����ȸ�������32λ���ȣ�    */
typedef double         fp64;                                            /*  ˫���ȸ�������64λ���ȣ�    */
typedef unsigned long long uint64;

typedef unsigned char  INT8U;                                           /*  �޷���8λ���ͱ���           */
typedef signed   char  INT8S;                                           /*  �з���8λ���ͱ���           */
typedef unsigned short INT16U;                                          /*  �޷���16λ���ͱ���          */
typedef signed   short INT16S;                                          /*  �з���16λ���ͱ���          */
typedef unsigned int   INT32U;                                          /*  �޷���32λ���ͱ���          */
typedef signed   int   INT32S;                                          /*  �з���32λ���ͱ���          */
typedef float          FP32;                                            /*  �����ȸ�������32λ���ȣ�    */
typedef double         FP64;                                            /*  ˫���ȸ�������64λ���ȣ�    */

#ifndef NULL
#define NULL 0
#endif

//#define SUCCESS 0x5A
//#define FAILED  0xEE
#ifndef FALSE
/* FALSE macro */
#define FALSE (0==1)
#endif
#ifndef TRUE
/* TRUE macro */
#define TRUE (!(FALSE))
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef DISABLE
#define DISABLE	0
#endif


/* ���¶������128MB SDRAM */
#define DEF_SDRAM_ADDR_END	0x88000000
#define DEF_LARGE_BUF_ADDR	0x87000000		//16M for configuration data or FPGA file buffer

#define DEF_EZWELL_OUI  0x008888
#define LongToBin(n) \
(                    \
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >>  9) & 0x08) | \
((n >>  6) & 0x04) | \
((n >>  3) & 0x02) | \
((n      ) & 0x01)   \
)
#define Bin(n) LongToBin(0x##n##l)	//write binary charactor set,exsample : Bin(11111111) = 0xff

typedef struct STVersion
{
        char ucpVerName[32];
        uint16 uiVerNum;
} STVersion;

typedef struct nm_frame {
	uint16 length;
	uint8 data[512];
} NM_FRAME;

#endif /* EZ_TYPES_H_ */
