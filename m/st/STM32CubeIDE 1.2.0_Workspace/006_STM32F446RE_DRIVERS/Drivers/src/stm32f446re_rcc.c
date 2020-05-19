/*
 * stm32f446re_rcc.c
 *
 *  Created on: 16-May-2020
 *      Author: GAYATHRI
 */

#include<stm32f446re_rcc.h>

uint16_t AHB_Prescaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB_Prescaler[4] = {2,4,8,16};

/* ****************************************************************************************
* @fn 				- RCC_GetPLLOutputClk
*
* @breif			- Get current APB value to which I2C is attached
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- TODO
**/
static uint32_t RCC_GetPLLOutputClk(void)
{
	uint32_t pllClk = 0;

	return pllClk;
}


/* ****************************************************************************************
* @fn 				- RCC_GetPCLK1Value
*
* @breif			- Get current APB value to which I2C is attached
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1;

	uint8_t clksrc, temp;
	uint16_t ahbp = 0;
	uint8_t apb1p = 0;
	uint32_t SystemClk = 0;

	clksrc = (RCC->CFGR >> 2) & 0x03;

	if(clksrc == 0) SystemClk = 16000000;
	else if(clksrc == 1) SystemClk = 8000000;
	else if(clksrc == 2) SystemClk = RCC_GetPLLOutputClk();

	// FOR AHB1
	temp = ((RCC->CFGR >> 4) & 0xF);
	if(temp < 8) {
		ahbp = 1;
	} else {
		ahbp = AHB_Prescaler[temp - 8];
	}

	// FOR APB1
	temp = (RCC->CFGR >> 10) & 0x07;
	if(temp < 4) {
		apb1p = 1;
	} else {
		apb1p = APB_Prescaler[temp - 4];
	}

	pclk1 = (SystemClk / ahbp) / apb1p;

	return pclk1;
}

uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2;

	uint8_t clksrc, temp;
	uint16_t ahbp = 0;
	uint8_t apb2p = 0;
	uint32_t SystemClk = 0;

	/* use system clock switch status */
	clksrc = (RCC->CFGR >> 2) & 0x03;

	if(clksrc == 0) SystemClk = 16000000;
	else if(clksrc == 1) SystemClk = 8000000;
	else if(clksrc == 2) SystemClk = RCC_GetPLLOutputClk();

	// FOR AHB1
	temp = ((RCC->CFGR >> 4) & 0xF);
	if(temp < 8) {
		ahbp = 1;
	} else {
		ahbp = AHB_Prescaler[temp - 8];
	}

	// FOR APB2
	temp = (RCC->CFGR >> 13) & 0x07;
	if(temp < 4) {
		apb2p = 1;
	} else {
		apb2p = APB_Prescaler[temp - 4];
	}

	pclk2 = (SystemClk / ahbp) / apb2p;

	return pclk2;

}
