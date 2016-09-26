/*
 * Mid_ADC.h
 *
 *  Created on: 2013-11-2
 *      Author: Administrator
 */

#ifndef MID_ADC_H_
#define MID_ADC_H_

#if defined (__cplusplus)
extern "C"
{
#endif

void ADC_INIT(void);
int getADCData(uint8 ch);

void readADC(void);

#if defined (__cplusplus)
}
#endif
#endif /* MID_ADC_H_ */
