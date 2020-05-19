/*
 * stm32f466re_gpio.c
 *
 *  Created on: 20-Apr-2020
 *      Author: GAYATHRI
 */

#include <stm32f446re_gpio.h>

/* GPIO Driver APIS
 * 1. GPIO Initialization
 * 2. Enable/Disable GPIO Port Clock
 * 3. Read from a GPIO Pin
 * 4. Write to GPIO Pin
 * 5. Configure alternate functionality
 * 6. Interrupt Handling
 *
 * ****************************************************************************************
 * @fn 				- GPIOx_clk_control
 *
 * @breif			- Enables/disables gpio port clock
 *
 * @param[in]		- base address of the gpio peripheral
 * @param[in]		- ENABLE or DISABLE macros
 * @param[in]		-
 *
 * @return			- none
 *
 * @note			- none
 **/
void GPIOx_clk_control(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		if(pGPIOx == GPIOA) {
			GPIOA_CLK_EN();
		}else if(pGPIOx == GPIOB) {
			GPIOB_CLK_EN();
		}else if(pGPIOx == GPIOC) {
			GPIOC_CLK_EN();
		}else if(pGPIOx == GPIOD) {
			GPIOD_CLK_EN();
		}else if(pGPIOx == GPIOE) {
			GPIOE_CLK_EN();
		}else if(pGPIOx == GPIOF) {
			GPIOF_CLK_EN();
		}else if(pGPIOx == GPIOG) {
			GPIOG_CLK_EN();
		}else if(pGPIOx == GPIOH) {
			GPIOH_CLK_EN();
		}
	}else if(EnorDi == DISABLE) {
		if(pGPIOx == GPIOA) {
			GPIOA_CLK_DI();
		}else if(pGPIOx == GPIOB) {
			GPIOB_CLK_DI();
		}else if(pGPIOx == GPIOC) {
			GPIOC_CLK_DI();
		}else if(pGPIOx == GPIOD) {
			GPIOD_CLK_DI();
		}else if(pGPIOx == GPIOE) {
			GPIOE_CLK_DI();
		}else if(pGPIOx == GPIOF) {
			GPIOF_CLK_DI();
		}else if(pGPIOx == GPIOG) {
			GPIOG_CLK_DI();
		}else if(pGPIOx == GPIOH) {
			GPIOH_CLK_DI();
		}
	} else {
		/* error invalid param */
	}

}

/* ****************************************************************************************
* @fn 				- GPIOx_Init
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIOx_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	// 1. configure the mode of GPIO pin
	if(pGPIOHandle->GPIO_PinConfg.GPIO_PinMode <= GPIO_MODE_ANALOG) {
		/* non interrupt mode */
		temp = (pGPIOHandle->GPIO_PinConfg.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber));
		/* before set, clearing the bits */
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER |= temp;

	} else {
		/* interrupt mode */
		if(pGPIOHandle->GPIO_PinConfg.GPIO_PinMode == GPIO_MODE_IT_FT) {
			//1. configure the Falling Edge trigger (FTSR)
			EXTI->EXTI_FTSR |= ( 1<< pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
			// clear the corresponding RTSR bit
			EXTI->EXTI_RTSR &= ~( 1<< pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfg.GPIO_PinMode == GPIO_MODE_IT_RT) {
			//1. configure the Raising Edge trigger (RTSR)
			//1. configure the Falling Edge trigger (FTSR)
			EXTI->EXTI_RTSR |= ( 1<< pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
			// clear the corresponding RTSR bit
			EXTI->EXTI_FTSR &= ~( 1<< pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfg.GPIO_PinMode == GPIO_MODE_IT_RFT) {
			//1. configure the Rising Falling Edge trigger (FTSR and RTSR)
			//1. configure the Falling Edge trigger (FTSR)
			EXTI->EXTI_FTSR |= ( 1<< pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
			// clear the corresponding RTSR bit
			EXTI->EXTI_RTSR |= ( 1<< pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
		}

		//2. configure the GPIO port selection in SYSCFG_EXTIR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber/4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber%4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_CLK_ENABLE();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

		//3. Enable the EXTI interrupt delivery using IMR
		EXTI->EXTI_IMR |= (1<<pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);

	}

	temp = 0;

	// 2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfg.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;
	// 3. configure the pupd settings
	temp = (pGPIOHandle->GPIO_PinConfg.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	// 4. configure the optype
	temp = 0;
	temp = (pGPIOHandle->GPIO_PinConfg.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	// 5. configure the alternate functionality
	temp = 0;
	if(pGPIOHandle->GPIO_PinConfg.GPIO_PinMode == GPIO_MODE_ALTFN) {
		if(pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber <= 7) {
			temp = (pGPIOHandle->GPIO_PinConfg.GPIO_PinAltFunMode << (4 * pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber));
			pGPIOHandle->pGPIOx->AFRL &= ~(0xF << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
			pGPIOHandle->pGPIOx->AFRL |= temp;
		} else {
			temp = (pGPIOHandle->GPIO_PinConfg.GPIO_PinAltFunMode << (4 * (pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber % 8)));
			pGPIOHandle->pGPIOx->AFRH &= ~(0xF << pGPIOHandle->GPIO_PinConfg.GPIO_PinNumber);
			pGPIOHandle->pGPIOx->AFRH |= temp;
		}
	}
	temp = 0;
}

/* ****************************************************************************************
* @fn 				- GPIOx_DeInit
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/

void GPIOx_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA) {
		GPIOA_REG_RESET();
	}else if(pGPIOx == GPIOB) {
		GPIOB_REG_RESET();
	}else if(pGPIOx == GPIOC) {
		GPIOC_REG_RESET();
	}else if(pGPIOx == GPIOD) {
		GPIOD_REG_RESET();
	}else if(pGPIOx == GPIOE) {
		GPIOE_REG_RESET();
	}else if(pGPIOx == GPIOF) {
		GPIOF_REG_RESET();
	}else if(pGPIOx == GPIOG) {
		GPIOG_REG_RESET();
	}else if(pGPIOx == GPIOH) {
		GPIOH_REG_RESET();
	}

}

/* ****************************************************************************************
* @fn 				- GPIOx_ReadFromInputPin
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
uint8_t GPIOx_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> pinNumber) & 0x00000001);
	return value;
}

/* ****************************************************************************************
* @fn 				- GPIOx_ReadFromInputPort
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
uint16_t GPIOx_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;
}

/* ****************************************************************************************
* @fn 				- GPIOx_WriteToOutputPin
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIOx_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET) {
		pGPIOx->ODR |= (1 << pinNumber);
	} else {
		pGPIOx->ODR &= ~(1 << pinNumber);
	}
}

/* ****************************************************************************************
* @fn 				- GPIOx_WriteToOutputPort
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIOx_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}

/* ****************************************************************************************
* @fn 				- GPIOx_ToggleOutputPin
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIOx_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
	pGPIOx->ODR ^= (1 << pinNumber);
}

/* ****************************************************************************************
* @fn 				- GPIOx_IRQInterruptConfig
*
* @breif			- Enable interrupts at NVIC
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIOx_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		if(IRQNumber <= 31) {		//0 to 31
			//Program ISER0 register
			*(NVIC_ISER0) |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64) {	//32 to 63
			//Program ISER1 register
			*(NVIC_ISER1) |= (1 << (IRQNumber %32));
		}else if(IRQNumber >=64  && IRQNumber < 96) {	//64 to 95
			//Program ISER2 register
			*(NVIC_ISER2) |= (1 << (IRQNumber %64));
		}
	} else {
		if(IRQNumber <= 31) {		//0 to 31
			//Program ICER0 register
			*(NVIC_ICER0) |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64) {	//32 to 63
			//Program ICER1 register
			*(NVIC_ICER1) |= (1 << (IRQNumber %32));
		}else if(IRQNumber >=64  && IRQNumber < 96) {	//64 to 95
			//Program ICSER2 register
			*(NVIC_ICER2) |= (1 << (IRQNumber %64));
		}
	}

}

/* ****************************************************************************************
* @fn 				- GPIOx_IRQPriorityConfig
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIOx_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	//1. first let find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |= (uint32_t)(IRQPriority << shift_amount);
}

/* ****************************************************************************************
* @fn 				- GPIO_IRQHandling
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void GPIO_IRQHandling(uint8_t pinNumber)
{
	//clear the EXTI PR register corresponding to the pin number
	if(EXTI->EXTI_PR &(1 << pinNumber)){
		//clear
		EXTI->EXTI_PR |= (1 << pinNumber);
	}
}

