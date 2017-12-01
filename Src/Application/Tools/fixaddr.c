/*  write by Liu Weifeng 20110302 */
#define Hardware_V1		100
#define Hardware_V2		10
#define Hardware_V3		1
#define Hardware_Vpot	2
#define PCBVersion		((Hardware_V3<<4)+Hardware_Vpot)

#define Main_Vr			3		//  main�汾��
#define Main_Vn			25		//  main���±�־��0Ϊ���Ǹ���

unsigned char const vertion_end[32]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	Hardware_V1,Hardware_V2,PCBVersion,Main_Vr,Main_Vn,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
