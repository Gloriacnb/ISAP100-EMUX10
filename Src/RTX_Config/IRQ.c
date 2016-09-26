/******************************************************************************/
/* IRQ.c: IRQ Handlers                                                        */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2007-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <RTL.h>
#include <LPC325x.H>


extern void os_clock_interrupt (void);
extern void interrupt_ethernet (void);
extern void os_def_interrupt   (void) __irq;
extern void dma_interrupt(void);


#ifndef OS_TIM_
#define OS_TIM_ (1 << 5)
#endif



/*--------------------------- IRQ_Handler -----------------------------------*/

/* User Interrupt Functions*/
// extern __irq void IRQx (void);                 // User IRQx Function
// extern __irq void IRQy (void);                 // User IRQy Function

// #define mIRQx       (1 <<  7)                  // User IRQx Mask
// #define mIRQy       (1 << 10)                  // User IRQy Mask

extern __irq void uart5_int_handler(void);
extern __irq void IntHandler_DCC(void);
extern __irq void i2c2_user_interrupt(void);
extern __irq void adc_user_interrupt(void);

__asm void IRQ_Handler_RTX (void) {
   /* Common IRQ Handler */
        PRESERVE8
        ARM
//;MIC
        STMDB   SP!,{R0}                       ; Save R0
        LDR     R0,=__cpp((U32)&MIC_SR)        ; Load MIC_SR Address
        LDR     R0,[R0]                        ; Load MIC_SR Value

        TST     R0,#OS_TIM_                    ; Check High Speed Timer Flag
        LDMNEIA SP!,{R0}                       ; Restore R0
        LDRNE   PC,=__cpp(os_clock_interrupt)  ; OS Clock IRQ Function

         TST     R0,#(1 << 29)                  ; Check Ethernet Flag
         LDMNEIA SP!,{R0}                       ; Restore R0
         LDRNE   PC,=__cpp(interrupt_ethernet)

         TST     R0,#(1 << 9)                   ; Check UART5 Flag
         LDMNEIA SP!,{R0}                       ; Restore R0
         LDRNE   PC,=__cpp(uart5_int_handler)

         TST     R0,#(1 << 28)                   ; Check UART5 Flag
         LDMNEIA SP!,{R0}                       ; Restore R0
         LDRNE   PC,=__cpp(dma_interrupt)
//;SIC1
         TST     R0,#(1 << 0)                   ; Check SIC1 Flag
         LDR     R0,=__cpp((U32)&SIC1_SR)
         LDR     R0,[R0]
                     TST     R0,#(1 << 18)      ;I2C-2 interrupt
                     LDMNEIA SP!,{R0}
                     LDRNE   PC,=__cpp(i2c2_user_interrupt)

					 TST     R0,#(1 << 7)       ;ADC interrupt
					 LDMNEIA SP!,{R0}
					 LDRNE   PC,=__cpp(adc_user_interrupt)
//;SIC2
         TST     R0,#(1 << 1)                   ; Check SIC2 Flag
         LDR     R0,=__cpp((U32)&SIC2_SR)
         LDR     R0,[R0]

                     TST     R0,#(1 << 9)      ;GPI_08 interrupt
                     LDMNEIA SP!,{R0}
                     LDRNE   PC,=__cpp(IntHandler_DCC)
//      TST     R0,#mIRQx                      ; Check IRQx Flag
//      LDMNEIA SP!,{R0}                       ; Restore R0
//      LDRNE   PC,=__cpp(IRQx)                ; IRQx Function

//      TST     R0,#mIRQy                      ; Check IRQy Flag
//      LDMNEIA SP!,{R0}                       ; Restore R0
//      LDRNE   PC,=__cpp(IRQy)                ; IRQy Function

        LDMIA   SP!,{R0}                       ; Restore R0
        LDR     PC,=__cpp(os_def_interrupt)    ; OS Default IRQ Function
}


