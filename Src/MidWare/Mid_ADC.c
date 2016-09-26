/*
 * Mid_ADC.c
 *
 *  Created on: 2013-11-2
 *      Author: Administrator
 */

#include "lpc32xx_intc_driver.h"
#include "lpc32xx_clkpwr_driver.h"
#include "lpc32xx_adc_driver.h"
#include <rtl.h>

/* ADC device handle */
STATIC INT_32 adcdev;

/* ADC variables*/
volatile UNS_32 adc_int;

#define MAX_SAMPLES 12
UNS_32 sample_check[MAX_SAMPLES] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2};
UNS_32 adc_data[MAX_SAMPLES];

void start_conversion(void)
{
	/* Select channel */
	switch (sample_check[adc_int])
	{
	case 0:
		adc_ioctl(adcdev, ADC_CH_SELECT, ADCSEL_CH_0);
		break;

	case 1:
		adc_ioctl(adcdev, ADC_CH_SELECT, ADCSEL_CH_1);
		break;

	case 2:
		adc_ioctl(adcdev, ADC_CH_SELECT, ADCSEL_CH_2);
		break;
	}

	/* start A/D convert */
	if (adc_int < MAX_SAMPLES)
		adc_ioctl(adcdev, START_CONVERSION, 0);
}

/***********************************************************************
 *
 * Function: adc_user_interrupt
 *
 * Purpose: ADC user interrupt handler
 *
 * Processing:
 *     On an interrupt read
 *     the data from the ADC
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
void adc_user_interrupt(void) __irq
{
	/* A read of the ADC data register will clear the ADC interrupt */

	/* Read the ADC result */
	adc_data[adc_int] = (ADC->adc_dat & TSC_ADCDAT_VALUE_MASK);

	/* Set the Flag to tell main application we got the interrupt*/
	adc_int++;

	/* Start conversion on next channel */
	start_conversion();
}

void readADC(void) {
	/* Reset flag */
	adc_int = 0;

	/* enable ADC interupts */
	int_enable(IRQ_TS_IRQ);

	/* Start an 8 sample conversion process */
	start_conversion();

	/* wait for 8 conversions to complete */
	while (adc_int < MAX_SAMPLES);

    int_disable(IRQ_TS_IRQ);
}

int getADCData(UNS_8 ch) {
	int sp = 4*ch;
	return (adc_data[sp]+adc_data[sp+1]+adc_data[sp+2]+adc_data[sp+3])/4;
}
void ADC_INIT(void) {
    volatile UNS_32 i;

	/* Open the ADC device */
	adcdev = adc_open(ADC , 0);
	/* ADC conversion, 400KHz mode. */
	/* disable 32KHz clock to ADC block */
    clkpwr_clk_en_dis(CLKPWR_ADC_CLK, 0);

    /* Get the clock frequency for the peripheral clock*/
    i = clkpwr_get_base_clock_rate(CLKPWR_PERIPH_CLK);

	/* compute the divider needed to ensure we are at or
       below 400KHz ADC Sampling rate*/
	i = (i / 400000) + 1;

	/* Set the ADC to run off the PERIPH_CLK and
       400KHz sampling rate */
	clkpwr_setup_adc_ts(CLKPWR_ADCCTRL1_PCLK_SEL, i) ;

	/* Reset flag */
    adc_int = 0;

	/* enable ADC interupts */
    int_enable(IRQ_TS_IRQ);

	/* Start an 8 sample conversion process */
	start_conversion();

	/* wait for 8 conversions to complete */
	while (adc_int < MAX_SAMPLES);

    int_disable(IRQ_TS_IRQ);
//	term_dat_out("400KHz data values:", 20);
//	newline();
//	dump_adc_values();
//	dummy_delay(100000);

	/* ADC conversion, 4.5MHz mode. */
	/* disable 32KHz clock to ADC block */
    clkpwr_clk_en_dis(CLKPWR_ADC_CLK, 0);

    /* Get the clock frequency for the peripheral clock*/
    i = clkpwr_get_base_clock_rate(CLKPWR_PERIPH_CLK);

	/* compute the divider needed to ensure we are at or
       below 4.5MHz ADC Sampling rate*/
	i = (i / 4500000);

	/* PCLK base is 13MHz */
	/* clkpwr_setup_adc_ts() function changes ADC clock rate */

	/* Set the ADC to run off the PERIPH_CLK and
       400KHz sampling rate */
	clkpwr_setup_adc_ts(CLKPWR_ADCCTRL1_PCLK_SEL, i);
//	term_dat_out("ADC clock divider set to ", 25);
//	dumphex16(i);
//	newline();
}
