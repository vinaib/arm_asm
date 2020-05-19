/*
 * stm32f446re_spi.c
 *
 *  Created on: 30-Apr-2020
 *      Author: GAYATHRI
 */
#include<stddef.h>
#include<stm32f446re_spi.h>

/* ****************************************************************************************
* @fn 				- SPIx_clk_control
*
* @breif			- Peripheral clock enable disable
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void SPIx_clk_control(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		if(pSPIx == SPI1) {
			SPI1_CLK_EN();
		}else if(pSPIx == SPI2) {
			SPI2_CLK_EN();
		}else if(pSPIx == SPI3) {
			SPI3_CLK_EN();
		}else if(pSPIx == SPI4) {
			SPI4_CLK_EN();
		}
	}else if(EnorDi == DISABLE) {
		if(pSPIx == SPI1) {
			SPI1_CLK_DI();
		}else if(pSPIx == SPI2) {
			SPI2_CLK_DI();
		}else if(pSPIx == SPI3) {
			SPI3_CLK_DI();
		}else if(pSPIx == SPI4) {
			SPI4_CLK_DI();
		}
	} else {
		/* error invalid param */
	}
}

/* Init and De-init */
/* ****************************************************************************************
* @fn 				- SPIx_Init
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
void SPIx_Init(SPI_Handle_t *pSPIHandle)
{
	// configure SPI_CR1 register
	uint32_t tempreg = 0;

	// 1 configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_BIT_MSTR;

	// 2. configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX) {
		// bidi mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIT_BIDIMODE);
	} else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX) {
		// bidi mode should be set
		tempreg |= ( 1 << SPI_CR1_BIT_BIDIMODE);
	} else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY) {
		// bidi mode should be cleared
		tempreg &= ~( 1 << SPI_CR1_BIT_BIDIMODE);
		// Rxonly bit must be set
		tempreg |= (1 << SPI_CR1_BIT_RXONLY);
	}else {
		// error handle
	}

	// 3. configure the clk speed
	tempreg |= (pSPIHandle->SPIConfig.SPI_ClkSpeed << SPI_CR1_BIT_BR);

	// 4. configure DFF
	tempreg |= (pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_BIT_DFF);

	// 5. configure CPOL
	tempreg |= (pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_BIT_CPOL);

	// 6. configure CPHA
	tempreg |= (pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_BIT_CPHA);

	// 7. configure SSM
	tempreg |= (pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_BIT_SSM);

	pSPIHandle->pSPIx->CR1 = tempreg;
}

/* ****************************************************************************************
* @fn 				- SPIx_DeInit
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
void SPIx_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1) {
		SPI1_REG_RESET();
	}else if(pSPIx == SPI2) {
		SPI2_REG_RESET();
	}else if(pSPIx == SPI3) {
		SPI3_REG_RESET();
	}else if(pSPIx == SPI4) {
		SPI4_REG_RESET();
	}
}

/* ****************************************************************************************
* @fn 				- SPI_GetFlagStatus
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
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t flag)
{
	if(pSPIx->SR & flag) {
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*
 * Data send and receive
 * Remember length will always be uint32_t type, this is standard practice
 */
/* ****************************************************************************************
* @fn 				- SPI_SendData
*
* @breif			- blocking call
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t* pTxBuffer, uint32_t len)
{
	// loop until len becomes 0
	while(len > 0) {

		// 1. wait until tx buffer is empty
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// 2. check the DFF bit
		if(pSPIx->CR1 & (1 << SPI_CR1_BIT_DFF)) {
			//16 bit DFF
			// load the data into data register
			pSPIx->DR = *(uint16_t*)pTxBuffer;
			len -= 2;
			(uint16_t*)pTxBuffer++;
		} else {
			// 8bit DFF
			pSPIx->DR = *pTxBuffer;
			len--;
			pTxBuffer++;
		}
	}
}

/* ****************************************************************************************
* @fn 				- SPI_ReceiveData
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
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t* pRxBuffer, uint32_t len)
{
	// loop until len becomes 0
	while(len > 0) {

		// 1. wait until rx buffer is not empty
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		// 2. check the DFF bit
		if(pSPIx->CR1 & (1 << SPI_CR1_BIT_DFF)) {
			//16 bit DFF
			// load the data from data register
			*(uint16_t *)pRxBuffer = (uint16_t)pSPIx->DR;
			len -= 2;
			(uint16_t*)pRxBuffer++;
		} else {
			// 8bit DFF
			*(uint8_t*)pRxBuffer = (uint8_t)pSPIx->DR;
			len--;
			pRxBuffer++;
		}

		len --;
	}
}

/*
 * IRQ configuration and ISR handling
 */
/* ****************************************************************************************
* @fn 				- SPI_SendDataIT
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
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t* pTxBuffer, uint32_t len)
{
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX) {
		// 1.Save the TX buffer address and Length information in some global variables
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = len;

		// 2.Mark the SPI state as busy in transmission so that no other code can take over same
		//   SPI peripheral until transmission is over
		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		// 3.Enable the TXEIE control bit to get the interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_BIT_TXEIE);

		// 4. Data transmission will be handled by the ISR code
	}

	return state;
}

/*
 * IRQ configuration and ISR handling
 */
/* ****************************************************************************************
* @fn 				- SPI_ReceiveDataIT
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
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t* pRxBuffer, uint32_t len)
{
	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX) {
		// 1.Save the RX buffer address and Length information in some global variables
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = len;

		// 2.Mark the SPI state as busy in transmission so that no other code can take over same
		//   SPI peripheral until transmission is over
		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		// 3.Enable the RXNEIE control bit to get the interrupt whenever RXNE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_BIT_RXNEIE);

		// 4. Data transmission will be handled by the ISR code
	}

	return state;
}

/*
 * IRQ configuration and ISR handling
 */
/* ****************************************************************************************
* @fn 				- SPIx_IRQInterruptConfig
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
void SPIx_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
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
* @fn 				- SPIx_IRQPriorityConfig
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
void SPIx_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	//1. first let find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |= (uint32_t)(IRQPriority << shift_amount);
}

/* ****************************************************************************************
* @fn 				- spi_txe_interrupt_handle
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
static void spi_txe_interrupt_handle(SPI_Handle_t *pHandle)
{
	// 2. check the DFF bit
	if(pHandle->pSPIx->CR1 & (1 << SPI_CR1_BIT_DFF)) {
		//16 bit DFF
		// load the data into data register
		pHandle->pSPIx->DR = *(uint16_t*)pHandle->pTxBuffer;
		pHandle->TxLen -= 2;
		(uint16_t*)pHandle->pTxBuffer++;
	} else {
		// 8bit DFF
		pHandle->pSPIx->DR = *pHandle->pTxBuffer;
		pHandle->TxLen--;
		pHandle->pTxBuffer++;
	}

	if(!pHandle->TxLen) {
		// TXLen is zero, close the SPI transmission and inform the application that TX is over

		SPI_CloseTransmission(pHandle);
		SPI_ApplicationEventCallback(pHandle, SPI_EVENT_TX_CMPLT);
	}
}

/* ****************************************************************************************
* @fn 				- spi_rxe_interrupt_handle
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
static void spi_rxne_interrupt_handle(SPI_Handle_t *pHandle)
{
	// 2. check the DFF bit
	if(pHandle->pSPIx->CR1 & (1 << SPI_CR1_BIT_DFF)) {
		//16 bit DFF
		// load the data into data register
		*(uint16_t*)pHandle->pRxBuffer = (uint16_t)pHandle->pSPIx->DR;
		pHandle->RxLen -= 2;
		(uint16_t*)pHandle->pRxBuffer++;
	} else {
		// 8bit DFF
		*(uint8_t*)pHandle->pRxBuffer = (uint8_t)pHandle->pSPIx->DR;
		pHandle->RxLen--;
		(uint8_t*)pHandle->pRxBuffer++;
	}

	if(!pHandle->RxLen) {
		// RXLen is zero, close the SPI transmission and inform the application about RX

		SPI_CloseReception(pHandle);
		SPI_ApplicationEventCallback(pHandle, SPI_EVENT_RX_CMPLT);
	}
}

/* ****************************************************************************************
* @fn 				- spi_ovr_interrupt_handle
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
static void spi_ovr_interrupt_handle(SPI_Handle_t *pHandle)
{
	// clear the ovr flag by reading the SPI_DR followed by read access to SPI_SR register
	uint8_t temp;

	if(pHandle->TxState != SPI_BUSY_IN_TX) {
		temp = pHandle->pSPIx->DR;
		temp = pHandle->pSPIx->SR;
	}

	// fix warning, for unused variable
	(void)temp;

	// inform the application
	SPI_ApplicationEventCallback(pHandle, SPI_EVENT_OVR_ERR);
}

/* ****************************************************************************************
* @fn 				- SPI_IRQHandling
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
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint8_t temp1, temp2;

	// check for TXE flag
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_BIT_TXE);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_BIT_TXEIE);

	if(temp1 && temp2) {
		// Handle TXE
		spi_txe_interrupt_handle(pHandle);
	}

	// check for RXNE flag
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_BIT_RXNE);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_BIT_RXNEIE);

	if(temp1 && temp2) {
		// Handle RXNE
		spi_rxne_interrupt_handle(pHandle);
	}

	// check for OVRRN flag, not handling other error flags
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_BIT_OVR);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_BIT_ERRIE);

	if(temp1 && temp2) {
		// Handle OVR
		spi_ovr_interrupt_handle(pHandle);
	}

}

/* ****************************************************************************************
* @fn 				- SPIx_peripheral_control
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
void SPIx_peripheral_control(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		pSPIx->CR1 |= (1 << SPI_CR1_BIT_SPE);
	} else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIT_SPE);
	}
}

/* ****************************************************************************************
* @fn 				- SPIx_peripheral_control
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
void SPIx_SSI_config(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		pSPIx->CR1 |= (1 << SPI_CR1_BIT_SSI);
	} else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_BIT_SSI);
	}
}

/* ****************************************************************************************
* @fn 				- SPI_ClearOVRFlag
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
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;

	temp = pSPIx->DR;
	temp = pSPIx->SR;

	// fix warning, for unused variable
	(void)temp;
}

/* ****************************************************************************************
* @fn 				- SPI_CloseTransmission
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
void SPI_CloseTransmission(SPI_Handle_t *pHandle)
{
	//this prevents interrupts from setting up of TXE flag
	pHandle->pSPIx->CR2 &=  ~(1 << SPI_CR2_BIT_TXEIE);
	pHandle->pTxBuffer = NULL;
	pHandle->TxLen = 0;
	pHandle->TxState = SPI_READY;
}

/* ****************************************************************************************
* @fn 				- SPI_CloseReception
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
void SPI_CloseReception(SPI_Handle_t *pHandle)
{
	//this prevents interrupts from setting up of RXNE flag
	pHandle->pSPIx->CR2 &=  ~(1 << SPI_CR2_BIT_RXNEIE);
	pHandle->pRxBuffer = NULL;
	pHandle->RxLen = 0;
	pHandle->RxState = SPI_READY;
}

/* ****************************************************************************************
* @fn 				- SPI_CloseReception
*
* @breif			- Application has to implement this event call back
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @note				- none
**/
__attribute__((weak)) void SPI_ApplicationEventCallback(SPI_Handle_t *pHandle, uint8_t AppEv)
{

}
