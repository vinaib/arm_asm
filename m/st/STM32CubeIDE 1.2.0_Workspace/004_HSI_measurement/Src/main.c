/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#include<stdint.h>

#define RCC_BASE_ADDR 				0x40023800UL
#define RCC_CFGR_REG_OFFSET			0x08UL
#define RCC_CFGR_REG_ADDR 			(RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define RCC_CLK_AHB1ENR_OFFSET		0x30UL

#define GPIOA_BASE_ADDR 			0x40020000UL
#define GPIO_MODE_REG_OFFSET		0x0UL
#define GPIO_ALF_HIGH_REG_OFFSET	0x24UL

int main(void)
{

	uint32_t *pRccCfgrReg = (uint32_t*)RCC_CFGR_REG_ADDR;

	//configure RCC_CFGR MCO1 bit fields to select HSI as clock source, write 00 in bit 21 and 22
	*pRccCfgrReg &= ~(0x3 << 21);

	/* configure prescaler /2 */
	//*pRccCfgrReg |= (0x04 << 24);

	/* configure prescaler /4 */
	//*pRccCfgrReg |= (0x06 << 24);

	/* configure prescaler /5 */
	*pRccCfgrReg |= (0x07 << 24);

	// enable the peripheral clock for GPIOA peripheral
	uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + RCC_CLK_AHB1ENR_OFFSET);
	*pRCCAhb1Enr |= (1 << 0);


	// configure the mode of GPIOA pin8 as alternate function mode
	uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + GPIO_MODE_REG_OFFSET);
	*pGPIOAModeReg &= ~(0x03 << 16); //clear
	*pGPIOAModeReg |= (0x02 << 16); //set

	// configure the alternation function register to set the alternate function mode as 0 for GPIOA 8 pin
	uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + GPIO_ALF_HIGH_REG_OFFSET);
	*pGPIOAAltFunHighReg &= ~(0xf << 0);	//clear

	for(;;);
}
