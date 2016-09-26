/****************************************Copyright (c)*****************************************************************
**                           
**                               Easy Broadband Technology Co., Ltd.                       
**                         
**                                  http://www.ebbnetwork.com  
**
**
**--------------File Info----------------------------------------------------------------------------------------------
** File name:			CLI_Debug_cmd_group.c
** File path:			/ISAP100_Mainsoft/Src/EZSoft/CLI_Commands/CLI_Debug_cmd_group.c
** Created by:          Administrator
** Created date:        2012-12-6
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
#include "lpc_string.h"
#include "s1l_cmds.h"
#include "s1l_line_input.h"
#include "CLI_Debug_cmd_group.h"
#include "TerminalUart.h"
#include "ChipGluLogic.h"
#include "ChipOptLogic.h"
#include "ChipSlotLogic.h"
#include "Mid_RC6400App.h"
#include "Mid_RC7880A1App.h"
#include "Mid_SPI.h"
#include "Mid_SMI.h"
#include "Mid_I2C.h"

#include <string.h>
#include "Task_define.h"
#include "FVIdt821054Access.h"
#include "MidMC145572.h"
#include "UID.h"
#include "CUInterface.h"
//#ifdef EZ_Debug
#include "TraceCounter.h"
#include <rtl.h>
//#endif
#include <stdio.h>

extern "C" {
void int_enable_eth_real(void);
void int_disable_eth_real(void);
void Dcc_interrupt_disable(void);
void Dcc_interrupt_enable(void);
}

void out_trace( Trace_T * trace, uint8* sbuf);

static BOOL_32 cmd_sread(void);
static BOOL_32 cmd_swrite(void);
static BOOL_32 cmd_iread(void);
static BOOL_32 cmd_iwrite(void);
static BOOL_32 cmd_i2crd(void);
static BOOL_32 cmd_i2cwr(void);

static BOOL_32 cmd_update(void);

static BOOL_32 cmd_coeread(void);
static BOOL_32 cmd_coewrite(void);

static BOOL_32 cmd_dcc_test(void);
static BOOL_32 cmd_dcn_test(void);

static BOOL_32 cmd_mreg(void);
//static BOOL_32 cmd_slotinfo(void);
/* Peek saved data */
static UNS_32 last_addr = 0;
static UNS_32 last_width = 4;

/* Peek command */
static BOOL_32 cmd_peek(void);
static UNS_32 cmd_peek_plist[] =
{
	(PARSE_TYPE_STR | PARSE_TYPE_OPT), /* The "peek" command */
	(PARSE_TYPE_HEX | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T core_peek_cmd =
{
	(UNS_8 *) "peek",
	cmd_peek,
	(UNS_8 *) "Displays a byte, half-word, or word value at an address",
	(UNS_8 *) "peek <hex address><1, 2, or 4 bytes>",
	cmd_peek_plist,
	(CMD_ROUTE_E*)NULL
};

/* Poke command */
static BOOL_32 cmd_poke(void);
static UNS_32 cmd_poke_plist[] =
{
	(PARSE_TYPE_STR), /* The "poke" command */
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T core_poke_cmd =
{
	(UNS_8 *) "poke",
	cmd_poke,
	(UNS_8 *) "Places a byte, half-word, or word value at an address",
	(UNS_8 *) "poke [hex address][hex value][1, 2, or 4 bytes]",
	cmd_poke_plist,
	(CMD_ROUTE_E*)NULL
};

/* Fill command */
static BOOL_32 cmd_fill(void);
static UNS_32 cmd_fill_plist[] =
{
	(PARSE_TYPE_STR), /* The "fill" command */
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T core_fill_cmd =
{
	(UNS_8 *) "fill",
	cmd_fill,
	(UNS_8 *) "Fills a range of memory with a value",
	(UNS_8 *) "fill [hex address][bytes to fill(hex)][hex value][1, 2, or 4 bytes]",
	cmd_fill_plist,
	(CMD_ROUTE_E*)NULL
};



/* dread command */
static BOOL_32 cmd_dread(void);
static UNS_32 cmd_dread_plist[] =
{
	(PARSE_TYPE_STR), /* The "dread" command */
	(PARSE_TYPE_HEX | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T dbg_dread_cmd =
{
	(UNS_8 *) "dread",
	cmd_dread,
	(UNS_8 *) "Direct read a range of register",
	(UNS_8 *) "dread [hex address][bytes to read][number of replication]",
	cmd_dread_plist,
	(CMD_ROUTE_E*)NULL
};

/* dwrite command */
static BOOL_32 cmd_dwrite(void);
static UNS_32 cmd_dwrite_plist[] =
{
	(PARSE_TYPE_STR), /* The "dwrite" command */
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_HEX | PARSE_TYPE_END)
};
static CMD_ROUTE_T dbg_dwrite_cmd =
{
	(UNS_8 *) "dwrite",
	cmd_dwrite,
	(UNS_8 *) "Direct write a register",
	(UNS_8 *) "dwrite [hex address][hex value]",
	cmd_dwrite_plist,
	(CMD_ROUTE_E*)NULL
};

/* SPI regs command */
static UNS_32 cmd_sread_plist[] =
{
	(PARSE_TYPE_STR), /* The "sread" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_HEX | PARSE_TYPE_OPT),
    (PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T sread_cmd =
{
	(UNS_8 *) "sread",
	cmd_sread,
	(UNS_8 *) "Read a chip register on extend card",
	(UNS_8 *) "sread [slot][chip][chip type][hex address][chip channel]\r\n"
              " chip      : 0 CPLD\r\n"
              "             1 first  1054\r\n"
              "             2 second 1054\r\n"
			  " chip type : 0 CPLD register \r\n"
			  "             1 IDT821054 global register \r\n"
			  "             2 READ LOCAL IDT821054 register \r\n"
              "	     		3 MC145572 Nibble register \r\n"
	  	  	  "             4 MC145572 byte register \r\n"
  	  	  	  "             5 MC145572 over register \r\n",
	cmd_sread_plist,
	(CMD_ROUTE_E*)NULL
};

static UNS_32 cmd_coeread_plist[] =
{
	(PARSE_TYPE_STR), /* The "coeread" command */
	(PARSE_TYPE_DEC),	//slot
	(PARSE_TYPE_DEC),	//chip
	(PARSE_TYPE_DEC),	//idt ch
	(PARSE_TYPE_DEC | PARSE_TYPE_END)	//coeRam block
};


static CMD_ROUTE_T coeread_cmd =
{
	(UNS_8 *) "coeread",
	cmd_coeread,
	(UNS_8 *) "Read a block of 82V1054 coe ram.",
	(UNS_8 *) "coeread [slot][chip][idtch][block]\r\n"
			  " [slot] :    0~3\r\n"
			  " [chip] :    0~1\r\n"
			  " [idtch]:    0~3\r\n"
	  	  	  " [block]:    0~4\r\n",
	cmd_coeread_plist,
	(CMD_ROUTE_E*)NULL
};


static UNS_32 cmd_coewrite_plist[] =
{
	(PARSE_TYPE_STR), /* The "coewrite" command */
	(PARSE_TYPE_DEC),	//slot
	(PARSE_TYPE_DEC),	//chip
	(PARSE_TYPE_DEC),	//idt ch
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),	//coeRam block
	(PARSE_TYPE_STR | PARSE_TYPE_END)
};

static CMD_ROUTE_T coewrite_cmd =
{
	(UNS_8 *) "coewrite",
	cmd_coewrite,
	(UNS_8 *) "write a block of 82V1054 coe ram.",
	(UNS_8 *) "coewrite [slot][chip][idtch][block]\r\n"
			  " [slot] : 	0~3\r\n"
			  " [chip] :    0~1\r\n"
			  " [idtch]:    0~3\r\n"
	  	  	  " [block]:    0~4\r\n"
	  	  	  " [file] :    config file name\r\n",
	cmd_coewrite_plist,
	(CMD_ROUTE_E*)NULL
};


static UNS_32 cmd_swrite_plist[] =
{
	(PARSE_TYPE_STR), /* The "swrite" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_HEX),
	(PARSE_TYPE_HEX | PARSE_TYPE_OPT),
    (PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T swrite_cmd =
{
	(UNS_8 *) "swrite",
	cmd_swrite,
	(UNS_8 *) "write a chip register on extend card by SPI",
	(UNS_8 *) "swrite [slot][chip][chip type][hex address][hex value][chip channel]\r\n"
			  " chip      : 0 CPLD\r\n"
			  "             1 first  1054\r\n"
			  "             2 second 1054\r\n"
			  " chip type : 0 CPLD register \r\n"
			  "             1 IDT821054 global register \r\n"
			  "             2 IDT821054 local register \r\n",
	cmd_swrite_plist,
	(CMD_ROUTE_E*)NULL
};


/* SMI debug command */
static UNS_32 cmd_iread_plist[] =
{
	(PARSE_TYPE_STR), /* The "iread" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T iread_cmd =
{
	(UNS_8 *) "iread",
	cmd_iread,
	(UNS_8 *) "Read a chip register on ehernet PHY",
	(UNS_8 *) "iread [chip][hex phy address][hex reg address]",
	cmd_iread_plist,
	(CMD_ROUTE_E*)NULL
};

static UNS_32 cmd_iwrite_plist[] =
{
	(PARSE_TYPE_STR), /* The "iwrite" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_HEX | PARSE_TYPE_END)
};
static CMD_ROUTE_T iwrite_cmd =
{
	(UNS_8 *) "iwrite",
	cmd_iwrite,
	(UNS_8 *) "write a chip register on ehernet PHY",
	(UNS_8 *) "iwrite [slot][hex phy address][hex reg address][hex value]",
	cmd_iwrite_plist,
	(CMD_ROUTE_E*)NULL
};

/* i2c regs command */
static UNS_32 cmd_i2crd_plist[] =
{
	(PARSE_TYPE_STR), /* The "i2crd" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T i2crd_cmd =
{
	(UNS_8 *) "i2crd",
	cmd_i2crd,
	(UNS_8 *) "Read SFP register by I2C",
	(UNS_8 *) "i2crd [channel][slave device][address]",
	cmd_i2crd_plist,
	(CMD_ROUTE_E*)NULL
};

static UNS_32 cmd_i2cwr_plist[] =
{
	(PARSE_TYPE_STR), /* The "i2cwr" command */
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_DEC),
	(PARSE_TYPE_HEX | PARSE_TYPE_END)
};
static CMD_ROUTE_T i2cwr_cmd =
{
	(UNS_8 *) "i2cwr",
	cmd_i2cwr,
	(UNS_8 *) "write a SFP register by i2c",
	(UNS_8 *) "i2cwr [channel][slave device][address] [hex value]",
	cmd_i2cwr_plist,
	(CMD_ROUTE_E*)NULL
};

static UNS_32 cmd_update_plist[] =
{
	(PARSE_TYPE_STR),/* The "update" command */
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT),
	(PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T update_cmd =
{
	(UNS_8 *) "update",
	cmd_update,
	(UNS_8 *) "update mcu(1) or lx9(2) & save file ",
	(UNS_8 *) "update <1/2> <filename>",
	cmd_update_plist,
	(CMD_ROUTE_E*)NULL
};

static UNS_32 cmd_dcc_test_plist[] =
{
	(PARSE_TYPE_STR | PARSE_TYPE_OPT), /* The "dcctest" command */
	(PARSE_TYPE_STR | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T cmd_dcc_test_cmd =
{
	(UNS_8 *) "dcctest",
	cmd_dcc_test,
	(UNS_8 *) "send a fix packet at selected dcc channel.",
	(UNS_8 *) "dcctest <read/write><dcc channel>",
	cmd_dcc_test_plist,
	(CMD_ROUTE_E*)NULL
};

static UNS_32 cmd_dcn_test_plist[] =
{
	(PARSE_TYPE_STR | PARSE_TYPE_OPT), /* The "dcntest" command */
	(PARSE_TYPE_STR | PARSE_TYPE_OPT),
	(PARSE_TYPE_DEC | PARSE_TYPE_END)
};
static CMD_ROUTE_T cmd_dcn_test_cmd =
{
	(UNS_8 *) "dcntest",
	cmd_dcn_test,
	(UNS_8 *) "send a fix packet at selected dcc channel.",
	(UNS_8 *) "dcntest <read/write><dcc channel>",
	cmd_dcn_test_plist,
	(CMD_ROUTE_E*)NULL
};

/*cmd_mreg*/
static UNS_32 cmd_mreg_plist[] =
{
	(PARSE_TYPE_STR ), /* The "mreg" command */
	(PARSE_TYPE_DEC), //slot
	(PARSE_TYPE_DEC), //chip
	(PARSE_TYPE_DEC), //reg type
	(PARSE_TYPE_DEC | PARSE_TYPE_OPT), //reg addr
	(PARSE_TYPE_DEC | PARSE_TYPE_END)  //reg data
};
static CMD_ROUTE_T cmd_mreg_cmd =
{
	(UNS_8 *) "mreg",
	cmd_mreg,
	(UNS_8 *) "read or write M145572 regs",
	(UNS_8 *) "mreg <0~3 slot><0 or 1 chip><reg type><reg addr><reg data>\r\n"
	"\t<reg type> 0 is Nibble Register and R6\r\n"
	"\t           1 is Byte Register\r\n"
	"\t           2 is Overlay Register\r\n"
	"\t<reg data> is option\r\n"
	"\t           if type <reg data>, said read operation,\r\n "
	"\t           otherwise said write operation.\r\n",
	cmd_mreg_plist,
	(CMD_ROUTE_E*)NULL
};


/* Debug group */
GROUP_LIST_T debug_group =
{
	(UNS_8 *) "debug", /* Debug group */
	(UNS_8 *) "ISAP100 debug command group",
	(CMD_ROUTE_E*)NULL,
	(GROUP_LIST_E*)NULL
};


/***********************************************************************
 *
 * Function: hex_dump
 *
 * Purpose: Dumps a series of data values
 *
 * Processing:
 *     Format and dump data based on address and width.
 *
 * Parameters:
 *     addr     : Starting address of dump
 *     width    : Width of the dump in bytes (1, 2, or 4)
 *     numtrans : Number of items to dump
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
static void hex_dump(UNS_32 addr,
					 UNS_32 width,
					 UNS_32 numtrans)
{
	int dumpsperline, ldspl, idx;
	UNS_32 tmp, laddr;
	UNS_8 daddr [16];

	/* Based on width, determine number of dumps per line */
	switch (width)
	{
		case 4:
			dumpsperline = 4;
			break;

		case 2:
			dumpsperline = 8;
			break;

		case 1:
		default:
			width = 1;
			dumpsperline = 8;
			break;
	}
	laddr = addr + (width * numtrans);

	/* Start dump */
	while (addr < laddr)
	{
		/* Dump address first */
		str_makehex(daddr, addr, 8);
		term_dat_out(daddr);
		term_dat_out((UNS_8 *) " : ");

		ldspl = dumpsperline;
		if (ldspl > numtrans)
		{
			ldspl = numtrans;
		}
		numtrans = numtrans - ldspl;

		/* Dump data in the line */
		for (idx = 0; idx < ldspl; idx++)
		{
			if (width == 4)
			{
				tmp = * (UNS_32 *) addr;
				addr = addr + 4;
			}
			else if (width == 2)
			{
				tmp = (UNS_32) (* (UNS_16 *) addr);
				addr = addr + 2;
			}
			else
			{
				tmp = (UNS_32) (* (UNS_8 *) addr);
				addr = addr + 1;
			}

			str_makehex(daddr, tmp, (width * 2));
			term_dat_out(daddr);
			term_dat_out((UNS_8 *) " ");
		}

		term_dat_out_crlf((UNS_8 *) "");
	}
}

    /***********************************************************************
 *
 * Function: cmd_peek
 *
 * Purpose: Peek command
 *
 * Processing:
 *     Parse the string elements for the peek command and display the
 *     peeked value.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
static BOOL_32 cmd_peek(void)
{
	UNS_32 newaddr, newwidth;

	/* If only 1 parsed command, then print at current address and
	   width */
	if (parse_get_entry_count() > 1)
	{
		/* Get address */
		newaddr = cmd_get_field_val(1);

		/* Width */
		newwidth = last_width;
		if (parse_get_entry_count() >= 3)
		{
			newwidth = cmd_get_field_val(2);
			if (!((newwidth == 1) || (newwidth == 2) ||
				(newwidth == 4)))
			{
				newwidth = 1;
			}
		}

		last_addr = newaddr;
		last_width = newwidth;
	}

	/* Based on width, limit address start */
	last_addr = last_addr & ~(last_width - 1);

	/* Dump data */
	hex_dump(last_addr, last_width, 1);

	return TRUE;
}

/***********************************************************************
 *
 * Function: cmd_poke
 *
 * Purpose: Poke command
 *
 * Processing:
 *     Parse the string elements for the poke command and update
 *     requested memory.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
static BOOL_32 cmd_poke(void)
{
	UNS_32 addr, width, fillval;

	/* Get address */
	addr = cmd_get_field_val(1);

	/* Hex fill value */
	fillval = cmd_get_field_val(2);

	/* Width */
	width = cmd_get_field_val(3);

	if (!((width == 1) || (width == 2) || (width == 4)))
	{
		width = 1;
	}

	/* Limit addressing size */
	addr = addr & ~(width - 1);

	if (width == 1)
	{
		UNS_8 *faddr = (UNS_8 *) addr;
		*faddr = (UNS_8) fillval;
	}
	else if (width == 2)
	{
		UNS_16 *faddr = (UNS_16 *) addr;
		*faddr = (UNS_16) fillval;
	}
	else
	{
		UNS_32 *faddr = (UNS_32 *) addr;
		*faddr = fillval;
	}

	return TRUE;
}

/***********************************************************************
 *
 * Function: cmd_fill
 *
 * Purpose: Fill command
 *
 * Processing:
 *     Parse the string elements for the fill command and fill the
 *     requested data range with data.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
static BOOL_32 cmd_fill(void) {
	UNS_32 addr, width, bytes, fillval;

	/* Get address */
	addr = cmd_get_field_val(1);

	/* Number of bytes */
	bytes = cmd_get_field_val(2);

	/* Hex fill value */
	fillval = cmd_get_field_val(3);

	/* Width */
	width = cmd_get_field_val(4);

	if (!((width == 1) || (width == 2) || (width == 4)))
	{
		width = 1;
	}

	/* Limit number of bytes based on addressing size */
	bytes = bytes & ~(width - 1);
	addr = addr & ~(width - 1);

	if (width == 1)
	{
		UNS_8 *faddr = (UNS_8 *) addr;
		while (bytes > 0)
		{
			*faddr = (UNS_8) fillval;
			faddr++;
			bytes--;
		}
	}
	else if (width == 2)
	{
		UNS_16 *faddr = (UNS_16 *) addr;
		while (bytes > 0)
		{
			*faddr = (UNS_16) fillval;
			faddr++;
			bytes -= 2;
		}
	}
	else
	{
		UNS_32 *faddr = (UNS_32 *) addr;
		while (bytes > 0)
		{
			*faddr = fillval;
			faddr++;
			bytes -= 4;
		}
	}

	return TRUE;
}

/***********************************************************************
 *
 * Function: cmd_dread
 *
 * Purpose: Read EMC register command
 *
 * Processing:
 *     read the registers value of chips, such as XO2640,XO21200,LX9,
 *     RC7880A1,RC6400 and so on.
 *     requested data range with data.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 cmd_dread(void) {
	UNS_32 iters, hexaddr, bytes;

	hexaddr = cmd_get_field_val(1) + 0xe3000000;
	bytes = 1;
	iters = 1;
	if( parse_get_entry_count() > 2 ) {
		bytes = cmd_get_field_val(2);
		if( parse_get_entry_count() > 3 ) {
			iters = cmd_get_field_val(3);
		}
	}
	while( iters > 0 ) {
		hex_dump(hexaddr, 1, bytes);
		iters--;
	}

	return TRUE;
}


/***********************************************************************
 *
 * Function: cmd_dwrite
 *
 * Purpose: Write EMC register command
 *
 * Processing:
 *     write the register value of chips, such as XO2640,XO21200,LX9,
 *     RC7880A1,RC6400 and so on.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/
BOOL_32 cmd_dwrite(void) {
	UNS_32 hexaddr, value;
	hexaddr = cmd_get_field_val(1);
	value = cmd_get_field_val(2) & 0xff;

//	*((UNS_8 *) hexaddr) = (UNS_8)value;

	if( hexaddr < 0x2000 ) {
		GluLogic_WriteReg(hexaddr,(UNS_8)value);
	}
	else if( hexaddr < 0x4000 ) {
		OptLogic_WriteReg(hexaddr-0x2000,(UNS_8)value);
	}
	else if( hexaddr < 0x6000 ) {
		SlotLogic_WriteReg(hexaddr-0x4000,(UNS_8)value);
	}
	else if( hexaddr < 0x8000 ) {
		Rc7880_WriteReg(hexaddr-0x6000,(UNS_8)value);
	}
	else if( hexaddr < 0xA000 ) {
		Rc6400_WriteReg(hexaddr-0x8000,(UNS_8)value);
	}
	else if( hexaddr < 0xC000 ) {
		SlotLogic_WriteReg(hexaddr-0x4000,(UNS_8)value);
	}
	else {
		return FALSE;
	}

	return TRUE;
}


static UNS_8 slotrangeerr_msg[] = "slot range is invalid, 0~3 is valid";
static UNS_8 parsrangeerr_msg[] = "channel range is invalid, 0~3 is valid";

/***********************************************************************
 *
 * Function: cmd_sread
 *
 * Purpose: Write slot chip register
 *
 * Processing:
 *     write the register value of chips on slot card, such as XO2640
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/


BOOL_32 cmd_sread(void) {
	UNS_8 slot = cmd_get_field_val(1);
	UNS_8 spich = cmd_get_field_val(2);//1个slot分配了4路spi channel，0-cpld/1、2-1054
	UNS_8 sel = cmd_get_field_val(3);
	UNS_16 addr = cmd_get_field_val(4);
	UNS_8 byte = 0;
	int temp = 0;
	UNS_8 daddr [16];
	if( slot > 3 || spich > 3 || sel > 5) {
		term_dat_out(parsrangeerr_msg);
		return FALSE;
	}

	switch( sel ) {
	case 0: {//read cpld spi

		if( ExtCPLDRegReadByte( ((slot<<2) | spich), addr, &byte) != TRUE ) {
			term_dat_out_crlf((UNS_8*)"read failed.");
			return FALSE;
		}
	}
		break;
	case 1: {//read global IDT821054 regs

		if( ReadIdtChipGlbRegister(((slot<<2) | spich), addr, &temp) < 0 ) {
			term_dat_out_crlf((UNS_8*)"read failed.");
			return FALSE;
		}
		byte = temp;
	}
		break;
	case 2: { //read local IDT821054 reg

		UNS_8 ch = 0;
		if( parse_get_entry_count() > 5) {
			ch = cmd_get_field_val(5);
		}
		else {
			break;
		}
		if( ReadIdtChipLocRegister(((slot<<2) | spich), ch, addr, &temp) < 0 ) {
			term_dat_out_crlf((UNS_8*)"read failed.");
			return FALSE;
		}
		byte = temp;
	}
		break;

	case 3: {//read MC145572 nibble reg
		ST_E1 info = {slot + 1, spich};
		uint32 uid = UID::makeUID(&info);
		CUInterface* ui = CUInterface::getPort(uid);
		if( ui ) {
			MidMC145572* dri = ui->itsDriver();
			if( dri ) {
				byte = dri->readNibbleReg(addr);
			}
			else {
				term_dat_out_crlf((UNS_8*)"read failed.");
				return FALSE;
			}
		}
		else {
			term_dat_out_crlf((UNS_8*)"chip not exist.");
			return FALSE;
		}
	}
		break;
	case 4: {//read MC145572 byte reg
		ST_E1 info = {slot + 1, spich};
		uint32 uid = UID::makeUID(&info);
		CUInterface* ui = CUInterface::getPort(uid);
		if( ui ) {
			MidMC145572* dri = ui->itsDriver();
			if( dri ) {
				byte = dri->readByteReg(addr);
			}
			else {
				term_dat_out_crlf((UNS_8*)"read failed.");
				return FALSE;
			}
		}
		else {
			term_dat_out_crlf((UNS_8*)"chip not exist.");
			return FALSE;
		}
	}
		break;
	case 5: {//read MC145572 over reg
		ST_E1 info = {slot + 1, spich};
		uint32 uid = UID::makeUID(&info);
		CUInterface* ui = CUInterface::getPort(uid);
		if( ui ) {
			MidMC145572* dri = ui->itsDriver();
			if( dri ) {
				byte = dri->readOverlayReg(addr);
			}
			else {
				term_dat_out_crlf((UNS_8*)"read failed.");
				return FALSE;
			}
		}
		else {
			term_dat_out_crlf((UNS_8*)"chip not exist.");
			return FALSE;
		}
	}
		break;
	default: {
		term_dat_out_crlf((UNS_8*)"parameters out of range.");
	}

	}
	str_makehex(daddr, addr, 4);
	term_dat_out(daddr);
	term_dat_out((UNS_8 *) " : ");

	str_makehex(daddr, byte, 2);
	term_dat_out(daddr);
	term_dat_out((UNS_8 *) " ");
	term_dat_out_crlf((UNS_8 *) "");
	return TRUE;

}

BOOL_32 cmd_swrite(void) {
	UNS_8 slot = cmd_get_field_val(1);
	UNS_8 ch = cmd_get_field_val(2);
	UNS_8 sel = cmd_get_field_val(3);
	UNS_16 addr = cmd_get_field_val(4);
	UNS_8 byte = cmd_get_field_val(5);
	if( slot > 3 || ch > 3 || sel > 2 ) {
		term_dat_out(parsrangeerr_msg);
		return FALSE;
	}
	switch( sel ) {
	case 0: {
		if(ExtCPLDRegWriteByte( ((slot<<2) | ch), addr, byte) == TRUE ) {
			term_dat_out_crlf((UNS_8*)"Option successful.");
		}
		else {
			term_dat_out_crlf((UNS_8*)"option failed.");
			return FALSE;
		}
	}
	break;
	case 1: {
		if(WriteIdtChipGlbRegister( ((slot<<2) | ch), addr, byte) < 0 ) {
			term_dat_out_crlf((UNS_8*)"option failed.");
			return FALSE;
		}
		else {
			term_dat_out_crlf((UNS_8*)"Option successful.");
		}
	}
	break;
	case 2: {
		if( parse_get_entry_count() > 6) {
			UNS_8 channel = cmd_get_field_val(6);
			if( WriteIdtChipLocRegister(((slot<<2) | ch), channel, addr, byte) < 0 ) {
				term_dat_out_crlf((UNS_8*)"option failed.");
				return FALSE;
			}
			else {
				term_dat_out_crlf((UNS_8*)"Option successful.");
			}
		}
		else {
			term_dat_out_crlf((UNS_8*)"Too few parse.");
			break;
		}
	}
	break;
	default: {
		term_dat_out_crlf((UNS_8*)"!!!Not support!!!");
	}
	}
	return TRUE;
}


/***********************************************************************
 *
 * Function: cmd_iread
 *
 * Purpose: indirect read/Write chip register
 *
 * Processing:
 *     write the register value of etherner phy chip
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/

BOOL_32 cmd_iread(void) {
	UNS_8 chip = cmd_get_field_val(1);
	UNS_8 phy = cmd_get_field_val(2);
	UNS_8 reg = cmd_get_field_val(3);
	UNS_16 word = 0;
	UNS_8 daddr [16];
	if( chip > 1 ) {
		term_dat_out_crlf(slotrangeerr_msg);
		return FALSE;
	}

	//read spi
	if( EthnetPHYRead( chip, phy, reg, &word) != TRUE ) {
		term_dat_out_crlf((UNS_8*)"option failed.");
		return FALSE;
	}


	str_makehex(daddr, phy, 2);
	term_dat_out(daddr);
	term_dat_out((UNS_8*)" ");
	str_makehex(daddr, reg, 2);
	term_dat_out(daddr);
	term_dat_out((UNS_8 *) " : ");

	str_makehex(daddr, word, 4);
	term_dat_out(daddr);
	term_dat_out((UNS_8 *) " ");
	term_dat_out_crlf((UNS_8 *) "");
	return TRUE;
}

BOOL_32 cmd_iwrite(void) {
	UNS_8 chip = cmd_get_field_val(1);
	UNS_8 phy = cmd_get_field_val(2);
	UNS_8 reg = cmd_get_field_val(3);
	UNS_16 word = cmd_get_field_val(4);
	if( chip > 1 ) {
		term_dat_out(slotrangeerr_msg);
		return FALSE;
	}

	if(EthnetPHYWrite( chip, phy, reg, word) == TRUE ) {
		term_dat_out_crlf((UNS_8*)"option successful");
		return FALSE;
	}
	else {
		term_dat_out_crlf((UNS_8*)"option failed.");
	}

	return TRUE;
}


/***********************************************************************
 *
 * Function: cmd_i2crd/cmd_i2cwr
 *
 * Purpose: indirect read/Write chip register
 *
 * Processing:
 *     write the register value of etherner phy chip
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: TRUE if the command was processed, otherwise FALSE
 *
 * Notes: None
 *
 **********************************************************************/

BOOL_32 cmd_i2crd(void) {
	UNS_8 ch = cmd_get_field_val(1);
	UNS_8 sid = cmd_get_field_val(2);
	UNS_8 reg = cmd_get_field_val(3);
	UNS_8 byte = 0;
	UNS_8 daddr [16];
	if( ch > 1 || sid > 1 ) {
		term_dat_out_crlf((UNS_8*)"ch or sid outof range, 0 or 1 is valid.");
		return FALSE;
	}

	//read sfp
	byte = I2C_read_byte(ch, sid, reg);

	str_makehex(daddr, reg, 2);
	term_dat_out(daddr);
	term_dat_out((UNS_8 *) " : ");

	str_makehex(daddr, byte, 2);
	term_dat_out(daddr);
	term_dat_out((UNS_8 *) " ");
	term_dat_out_crlf((UNS_8 *) "");
	return TRUE;
}

BOOL_32 cmd_i2cwr(void) {
	return TRUE;
}

//extern uint8 CLI_EN;
extern int updatafpga(UNS_8*, uint8);
extern int updata_main(UNS_8*, uint8);


BOOL_32 cmd_update(void) {
// 	CLI_EN = 0;
// 	term_dat_out_crlf((UNS_8 *) "CLI will stop...");
// 	term_dat_out_crlf((UNS_8 *) "Please press cli and enter if want to use CLI again.");
	UNS_8 opt = cmd_get_field_val(1);
	UNS_8* name = 0;
	if( opt == 1 ) {
		if( parse_get_entry_count() > 2 ) {
			name = (UNS_8*)cmd_get_field_val(2);
		}
		else {
			name = (uint8*)"main.bit";
		}
		if( updata_main(name, strlen((const char*)name)+1) < 0 ) {
			term_dat_out_crlf((UNS_8*)"Update MCU failed!");
		}
		else {
			term_dat_out_crlf((UNS_8*)"Update MCU seccessful!");
			os_evt_set(0x0001, t_reset);
		}
	}
	else if( opt == 2 ) {

		if( parse_get_entry_count() > 2 ) {
			name = (UNS_8*)cmd_get_field_val(2);
		}
		else {
			name = (uint8*)"slotlogic.bit";
		}
		int_disable_eth_real();
		Dcc_interrupt_disable();
		tsk_lock();
		if( updatafpga(name, strlen((const char*)name)+1) < 0 ) {
			term_dat_out_crlf((UNS_8*)"Update LX9 failed!");
		}
		else {
			term_dat_out_crlf((UNS_8*)"Update LX9 seccessful!");
			os_evt_set(0x0002, t_reset);
		}
		tsk_unlock();
		Dcc_interrupt_enable();
		int_enable_eth_real();

	}
	return TRUE;

}



static BOOL_32 cmd_dcc_test(void) {
	char* option = (char*)cmd_get_field_val(1);
	UNS_8 ch = cmd_get_field_val(2);
	UNS_16 rdLen;
	static uint8 col = 4;
	UNS_8 line;
	int i,j,point;
	UNS_8 daddr[10];
	UNS_8 rdbuf[200];
	static UNS_8 packet[] = {
			0x00, 0x00, 0x00, 0x18, 0x50, 0xE5, 0x49, 0x83,
			0x11, 0xF0, 0x00, 0x64, 0x10, 0x00, 0x00, 0x16,
			0x08, 0x00, 0x45, 0x00, 0x00, 0x4E, 0x00, 0x13,
			0x00, 0x00, 0x80, 0x11, 0xB4, 0xE7, 0xC0, 0xA8,
			0x02, 0x41, 0xC0, 0xA8, 0x02, 0x13, 0x00, 0xA1,
			0xD8, 0xE2, 0x00, 0x3A, 0x3B, 0x2F, 0x30, 0x30,
			0x02, 0x01, 0x00, 0x04, 0x06, 0x70, 0x75, 0x62,
			0x6C, 0x69, 0x63, 0xA2, 0x23, 0x02, 0x04, 0x5D,
			0x83, 0x28, 0x25, 0x02, 0x01, 0x00, 0x02, 0x01,
			0x00, 0x30, 0x15, 0x30, 0x13, 0x06, 0x08, 0x2B,
			0x06, 0x01, 0x02, 0x01, 0x01, 0x01, 0x00, 0x04,
			0x07, 0x49, 0x53, 0x41, 0x50, 0x31, 0x30, 0x30,
//			0xaa, 0x55, 0x7e, 0x7d
	};
	if( strcmp(option, "read") == 0 ) {
		rdLen = GetDCCPacket(ch, rdbuf);
		if( rdLen == 0 ) {
			term_dat_out_crlf((UNS_8*)"no packet received!");
		}
		else {
			if( rdLen % col ) {
				line = rdLen / col + 1;
			}
			else {
				line = rdLen / col;
			}
			for( i = 0; i < line; i++ ) {
				for( j = 0; j < col; j++ ) {
					point = i*col + j;
					if( point >= rdLen ) {
						return TRUE;
					}
					str_makehex(daddr, rdbuf[point], 2);
					term_dat_out(daddr);
					term_dat_out((UNS_8 *) " ");
				}
				term_dat_out_crlf((UNS_8*)"");
			}
		}

	}
	else if( strcmp(option, "write") == 0 ) {
//		for( i = 0; i < 10; i++ ) {
//
			DccSendPacket(ch, packet, sizeof(packet));
			packet[3]++;
//		}
		term_dat_out_crlf((UNS_8*)"packet send succeed!");
	}
	else if ( strcmp(option, "trace") == 0 ) {
		if( ch == 88 ) {
			int_disable_eth_real();
			Dcc_interrupt_disable();
			tsk_lock();
			memset(&eth_trace, 0, sizeof(eth_trace));
			memset(&dcc_trace, 0, sizeof(eth_trace));
			stack_res_eth = 0;
			stack_res_dcc = 0;
			tsk_unlock();
			Dcc_interrupt_enable();
			int_enable_eth_real();
		}
		term_dat_out_crlf((UNS_8*)"eth trace out:");
		out_trace(&eth_trace, rdbuf);

		term_dat_out_crlf((UNS_8*)"");
		term_dat_out_crlf((UNS_8*)"dcc trace out:");
		out_trace(&dcc_trace, rdbuf);

		term_dat_out_crlf((UNS_8*)"");
		term_dat_out((UNS_8*)"stack up:	");
		str_makedec(rdbuf, stack_res_eth);
		term_dat_out_crlf(rdbuf);

		term_dat_out((UNS_8*)"stack down: ");
		str_makedec(rdbuf, stack_res_dcc);
		term_dat_out_crlf(rdbuf);

}
	else {
		return FALSE;
	}
	return TRUE;
}

BOOL_32 cmd_dcn_test(void) {
	char* option = (char*)cmd_get_field_val(1);
	UNS_8 ch = cmd_get_field_val(2);
	UNS_16 rdLen;
	static uint8 col = 4;
	UNS_8 line;
	int i,j,point;
	UNS_8 daddr[10];
	UNS_8 rdbuf[200];
	static UNS_8 packet[] = {
			0x00, 0x00, 0x00, 0x18, 0x50, 0xE5, 0x49, 0x83,
			0x11, 0xF0, 0x00, 0x64, 0x10, 0x00, 0x00, 0x16,
			0x08, 0x00, 0x45, 0x00, 0x00, 0x4E, 0x00, 0x13,
			0x00, 0x00, 0x80, 0x11, 0xB4, 0xE7, 0xC0, 0xA8,
			0x02, 0x41, 0xC0, 0xA8, 0x02, 0x13, 0x00, 0xA1,
			0xD8, 0xE2, 0x00, 0x3A, 0x3B, 0x2F, 0x30, 0x30,
			0x02, 0x01, 0x00, 0x04, 0x06, 0x70, 0x75, 0x62,
			0x6C, 0x69, 0x63, 0xA2, 0x23, 0x02, 0x04, 0x5D,
			0x83, 0x28, 0x25, 0x02, 0x01, 0x00, 0x02, 0x01,
			0x00, 0x30, 0x15, 0x30, 0x13, 0x06, 0x08, 0x2B,
			0x06, 0x01, 0x02, 0x01, 0x01, 0x01, 0x00, 0x04,
			0x07, 0x49, 0x53, 0x41, 0x50, 0x31, 0x30, 0x30,
//			0xaa, 0x55, 0x7e, 0x7d
	};
	if( strcmp(option, "read") == 0 ) {
		if( ifSabitHavePacket(ch) == 0 ) {
			term_dat_out_crlf((UNS_8*)"no packet received!");
			return FALSE;
		}
		rdLen = getSabitPacketLen(ch);
		if( rdLen == 0 ) {
			term_dat_out_crlf((UNS_8*)"no packet received!");
		}
		else {
			getSabitPacket(ch, rdbuf, rdLen);
			if( rdLen % col ) {
				line = rdLen / col + 1;
			}
			else {
				line = rdLen / col;
			}
			for( i = 0; i < line; i++ ) {
				for( j = 0; j < col; j++ ) {
					point = i*col + j;
					if( point >= rdLen ) {
						return TRUE;
					}
					str_makehex(daddr, rdbuf[point], 2);
					term_dat_out(daddr);
					term_dat_out((UNS_8 *) " ");
				}
				term_dat_out_crlf((UNS_8*)"");
			}
		}

	}
	else if( strcmp(option, "write") == 0 ) {
//		for( i = 0; i < 10; i++ ) {
//
			sendSabitPacket(ch, packet, sizeof(packet));
			packet[3]++;
//		}
		term_dat_out_crlf((UNS_8*)"packet send succeed!");
	}
	else {
		return FALSE;
	}
	return TRUE;

}

void out_trace( Trace_T * trace, uint8* sbuf) {
	term_dat_out((UNS_8*)"	interrupt:	");
	str_makedec(sbuf, trace->interrupt);
	term_dat_out_crlf(sbuf);

	term_dat_out((UNS_8*)"	rcv:		");
	str_makedec(sbuf, trace->rcv);
	term_dat_out_crlf(sbuf);

	term_dat_out((UNS_8*)"	rcv_valid:	");
	str_makedec(sbuf, trace->rcv_valid);
	term_dat_out_crlf(sbuf);

	term_dat_out((UNS_8*)"	local:		");
	str_makedec(sbuf, trace->local);
	term_dat_out_crlf(sbuf);

	term_dat_out((UNS_8*)"	broadcast:	");
	str_makedec(sbuf, trace->broadcast);
	term_dat_out_crlf(sbuf);

	term_dat_out((UNS_8*)"	transmit:	");
	str_makedec(sbuf, trace->transmit);
	term_dat_out_crlf(sbuf);

	term_dat_out((UNS_8*)"	trans_up:	");
	str_makedec(sbuf, trace->transmit_up);
	term_dat_out_crlf(sbuf);
}



static BOOL_32 cmd_coeread(void) {
	if( parse_get_entry_count() < 5 ) {
		return FALSE;
	}
	UNS_8 slot = cmd_get_field_val(1);
	UNS_8 chip = cmd_get_field_val(2);
	UNS_8 channel = cmd_get_field_val(3);
	UNS_8 block = cmd_get_field_val(4);
	if( slot > 3 || chip > 1 || channel > 4 || block > 4 ) {
		printf("\nPlease check input data.\n");
		return FALSE;
	}

	UNS_16 data[8] = {0};

	int spichannel = (slot << 2) | (chip + 1);
	if( readIDTChipCoeRamBlock(spichannel, channel, block, data) >= 0 ) {
		for(int i =0; i < sizeof(data)/sizeof(data[0]); i++ ) {
			printf("\nword 0x%2x is: 0x%02x\n", (block<<3)+7-i, data[i]);
		}
		return TRUE;
	}
	printf("\n!!!Read failed!!!\n");
	return FALSE;
}
static BOOL_32 cmd_coewrite(void) {
	if( parse_get_entry_count() < 5 ) {
		return FALSE;
	}
	UNS_8 slot = cmd_get_field_val(1);
	UNS_8 chip = cmd_get_field_val(2);
	UNS_8 channel = cmd_get_field_val(3);
	UNS_8 block = cmd_get_field_val(4);
	if( slot > 3 || chip > 1 || channel > 4 || block > 4 ) {
		printf("\nPlease check input data.\n");
		return FALSE;
	}
	uint16 temp[8] = {0};

	if( parse_get_entry_count() == 5 ) {
		printf("\n输入0x1234格式的8个块数据，以空格间隔.\n");
		static char buff[64] = "0x1111 0x2222 0x3333 0x4444";
		int bytes = 0;
		memset(buff, '\0', sizeof(buff));
		while ( 1 ) {
			char c = getkey();
			if( c == 27 || c == 13) {
				break;
			}

			sendchar(c);

			buff[bytes++] = c;
		}
		int data[8];
		int result = sscanf(buff, "%x %x %x %x %x %x %x %x",
				&data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7] );
		for (int i = 0; i < 8; ++i) {
			temp[i] = (uint16)data[i];
		}
	}
	else { //读指定配置文件数据到temp
		FILE* f;
		char* fname = (char*)cmd_get_field_val(5);
		f = fopen(fname, "r");
		if( f ) {
			int data[8];
			int result = fscanf(f, "%x %x %x %x %x %x %x %x",
					&data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7] );
			for (int i = 0; i < 8; ++i) {
				temp[i] = (uint16)data[i];
			}
		}
		else {
			printf("\nFile isn't exist\n");
			return FALSE;
		}
	}
	int spichannel = (slot << 2) | (chip + 1);
    if( writeIDTChipCoeRamBlock(spichannel, channel, block, temp, 8) >= 0 ) {
    	printf("\nwrite succeed!\n");
    	return TRUE;
    }
	printf("\n!!!write failed!!!\n");
	return FALSE;
}

static BOOL_32 cmd_mreg(void) {
	if( parse_get_entry_count() < 5 ) {
		return FALSE;
	}
	UNS_8 slot = cmd_get_field_val(1);
	UNS_8 chip = cmd_get_field_val(2);
	UNS_8 rtype = cmd_get_field_val(3);
	UNS_8 raddr = cmd_get_field_val(4);
	ST_E1 info = {slot + 1, chip};
	uint32 uid = UID::makeUID(&info);
	CUInterface* ui = CUInterface::getPort(uid);
	if( ui == 0 ) {
		printf("\n!!!No chip!!!\n");
		return FALSE;
	}
	MidMC145572* c = ui->itsDriver();
	if( parse_get_entry_count() > 5 ) {
		//write
		UNS_8 rdata = cmd_get_field_val(5);
		printf("\nwrite register %d\n", raddr);
		switch( rtype ) {
		case 0:
			c->writeNibbleReg(raddr, rdata);
			break;
		case 1:
			c->writeByteReg(raddr, rdata);
			break;
		case 2:
			c->writeOverlayReg(raddr, rdata);
			break;
		default:
			printf("\n!!!please input <rtype> 0~2!!!\n");
			return FALSE;
		}
	}
	//read
	int result = 0;
	switch( rtype ) {
	case 0:
		result = c->readNibbleReg(raddr);
		break;
	case 1:
		result = c->readByteReg(raddr);
		break;
	case 2:
		result = c->readOverlayReg(raddr);
		break;
	default:
		printf("\n!!!please input <rtype> 0~2!!!\n");
		return FALSE;
	}
	printf("\nslot%d chip%d reg%d is: 0x%02x\n", slot, chip, raddr, result);
	return TRUE;
}


/***********************************************************************
 *
 * Function: cmd_core_add_commands
 *
 * Purpose: Initialize this command block
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void CLI_debug_add_commands(void)
{
	/* Add core group */
	cmd_add_group(&debug_group);

	/* Add commands to the core group */
	cmd_add_new_command(&debug_group, &core_fill_cmd);
	cmd_add_new_command(&debug_group, &core_peek_cmd);
	cmd_add_new_command(&debug_group, &core_poke_cmd);
	cmd_add_new_command(&debug_group, &dbg_dread_cmd);
	cmd_add_new_command(&debug_group, &dbg_dwrite_cmd);

	cmd_add_new_command(&debug_group, &sread_cmd);
	cmd_add_new_command(&debug_group, &swrite_cmd);
	cmd_add_new_command(&debug_group, &iread_cmd);
	cmd_add_new_command(&debug_group, &iwrite_cmd);
	cmd_add_new_command(&debug_group, &i2crd_cmd);
	cmd_add_new_command(&debug_group, &i2cwr_cmd); 
	cmd_add_new_command(&debug_group, &update_cmd);
	cmd_add_new_command(&debug_group, &cmd_dcc_test_cmd);
	cmd_add_new_command(&debug_group, &coeread_cmd);
	cmd_add_new_command(&debug_group, &coewrite_cmd);
	cmd_add_new_command(&debug_group, &cmd_mreg_cmd);
	cmd_add_new_command(&debug_group, &cmd_dcn_test_cmd);


}
