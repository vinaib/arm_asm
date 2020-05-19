/*
 * stm32f466re_i2c.c
 *
 *  Created on: 06-May-2020
 *      Author: GAYATHRI
 */
#include<stddef.h>
#include<stm32f446re_rcc.h>
#include <stm32f446re_i2c.h>

/*
 *  STATIC FUNCTIONS
 */

/* ****************************************************************************************
* @fn 				- I2C_Generate_Start_condition
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
static void I2C_Generate_Start_condition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

/* ****************************************************************************************
* @fn 				- I2C_ExecuteAddressPhaseWrite
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
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t slaveAddr)
{
	slaveAddr |= (slaveAddr << 1);
	slaveAddr &= ~(1 << 0);		//r/nw bit
	pI2Cx->DR = slaveAddr;
}

/* ****************************************************************************************
* @fn 				- I2C_ExecuteAddressPhaseRead
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
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t slaveAddr)
{
	slaveAddr |= (slaveAddr << 1);
	slaveAddr |= (1 << 0);		//r/nw bit
	pI2Cx->DR = slaveAddr;
}

/* ****************************************************************************************
* @fn 				- I2C_Generate_Start_condition
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
static void I2C_clear_addr_flag(I2C_Handle_t *pI2CHandle)
{
	/* read sr1 and sr2 */
	uint16_t dummy_read;

	//check for device mode
	if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL)) {
		//device is in master mode
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX) {
			if(pI2CHandle->RxSize == 1) {
				//first disable ACK
				I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

				//clear the ADDR flag
				dummy_read = pI2CHandle->pI2Cx->SR1;
				dummy_read = pI2CHandle->pI2Cx->SR2;
				(void)dummy_read;
			}
		}
		else {
			// Not busy in RX
			//clear the ADDR flag
			dummy_read = pI2CHandle->pI2Cx->SR1;
			dummy_read = pI2CHandle->pI2Cx->SR2;
			(void)dummy_read;
		}
	}
	else {
		// device is in slave mode
		//clear the ADDR flag
		dummy_read = pI2CHandle->pI2Cx->SR1;
		dummy_read = pI2CHandle->pI2Cx->SR2;
		(void)dummy_read;
	}

}

/* ****************************************************************************************
* @fn 				- I2C_Generate_Stop_condition
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
void I2C_Generate_Stop_condition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

/* ****************************************************************************************
* @fn 				- I2C_CloseReceive_Data
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
void I2C_CloseReceive_Data(I2C_Handle_t *pI2CHandle)
{
	//Implement the code to disable ITBUFEN Control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);

	//Implement the code to disable ITEVFEN control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->pRxBuffer = NULL;
	pI2CHandle->RxLen = 0;
	pI2CHandle->RxSize = 0;
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE){
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
	}
}

/* ****************************************************************************************
* @fn 				- I2C_CloseSendData
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
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle)
{
	//Implement the code to disable ITBUFEN Control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);

	//Implement the code to disable ITEVFEN control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->pTxBuffer = NULL;
	pI2CHandle->TxLen = 0;
	// Why ack enable is not required in closesenddata
	/*
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE){
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
	}*/
}

/*
 * DRIVER API's
 */

/* ****************************************************************************************
* @fn 				- I2Cx_clk_control
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
void I2Cx_clk_control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		if(pI2Cx == I2C1) {
			I2C1_CLK_EN();
		}else if(pI2Cx == I2C2) {
			I2C2_CLK_EN();
		}else if(pI2Cx == I2C3) {
			I2C3_CLK_EN();
		}
	}else if(EnorDi == DISABLE) {
		if(pI2Cx == I2C1) {
			I2C1_CLK_DI();
		}else if(pI2Cx == I2C2) {
			I2C2_CLK_DI();
		}else if(pI2Cx == I2C3) {
			I2C3_CLK_DI();
		}
	} else {
		/* error invalid param */
	}
}

/* ****************************************************************************************
* @fn 				- I2Cx_Init
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
void I2Cx_Init(I2C_Handle_t *pI2CHandle)
{
	// 1. configure the mode (standard or fast)
	// 2. configure the speed of serial clock
	// 3. configure the device address (in slave mode only)
	// 4. Enable acking
	// 5. configure the rise time for i2c pins (for scl and sda)
	// rise time: time taken to reach from ground level to vcc or slew rate, this must be configured according to specification

	// All above configuration must be done when the peripheral is disabled in the control register
	uint32_t tempreg = 0;

	// enable the clock for i2cx peripheral
	I2Cx_clk_control(pI2CHandle->pI2Cx, ENABLE);

	// ACK control bit
	tempreg |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK);
	pI2CHandle->pI2Cx->CR1 = tempreg;

	// configure FREQ field in CR2
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 1000000u;
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3f);

	//program the device own address, assuming it is always 7 bit address
	tempreg = pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1 << 14);	// as per manual
	pI2CHandle->pI2Cx->OAR1 |= tempreg;

	// ccr calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCK_SPEED_SM) {
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempreg |= ccr_value & 0xFFF;
	} else {
		// set fast mode
		tempreg |= (1 << 15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2) {
			ccr_value |= RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		} else {
			ccr_value |= RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}
		tempreg |= (ccr_value & 0xFFF);
	}

	pI2CHandle->pI2Cx->CCR = tempreg;

	//TRISE configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCK_SPEED_SM) {
		tempreg = (RCC_GetPCLK1Value() /1000000U) + 1;
	} else {
		tempreg = ((RCC_GetPCLK1Value() * 300) /1000000000U) + 1;
	}

	pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);

}

/* ****************************************************************************************
* @fn 				- I2Cx_DeInit
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
void I2Cx_DeInit(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx == I2C1) {
		I2C1_REG_RESET();
	}else if(pI2Cx == I2C2) {
		I2C2_REG_RESET();
	}else if(pI2Cx == I2C3) {
		I2C3_REG_RESET();
	}
}

/* ****************************************************************************************
* @fn 				- I2Cx_IRQInterruptConfig
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
void I2Cx_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
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
* @fn 				- I2Cx_IRQPriorityConfig
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
void I2Cx_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	//1. first let find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |= (uint32_t)(IRQPriority << shift_amount);
}

/* ****************************************************************************************
* @fn 				- I2Cx_peripheral_control
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
void I2Cx_peripheral_control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE) {
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	} else {
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}

}

/* ****************************************************************************************
* @fn 				- I2Cx_GetFlagStatus
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
uint8_t I2Cx_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
		return FLAG_SET;

	return FLAG_RESET;
}

/* ****************************************************************************************
* @fn 				- I2C_ApplicationEventCallback
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
__attribute__((weak)) void I2C_ApplicationEventCallback(I2C_Handle_t *pHandle, uint8_t AppEv)
{

}

/* ****************************************************************************************
* @fn 				- I2C_MasterSendData
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
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr)
{
	// 1. Generate START condition
	I2C_Generate_Start_condition(pI2CHandle->pI2Cx);

	// 2. Confirm that start generation is completed by checking the SB flag in the SR1
	// Note: until SB is cleared SCL will be stretched (pulled to low)
	// as per RM pg:788, SB is cleared by software by reading the SR1 register followed by
	//writing the DR register, or by hardware when PE=0
	while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_SB));

	// 3 send the address of the slave with r/nw bit set to w(0)
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, slaveAddr);

	// 4. wait until address phase is completed by checking the ADDR flag in the SR1
	while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_ADDR));

	// 5. clear the ADDR flag according to its software sequence
	// note until ADDR is cleared SCL will be stretched (pulled to low)
	I2C_clear_addr_flag(pI2CHandle);

	// 6. send the data until len becomes 0
	while(len > 0) {
		// wait till TXE is set
		while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_TXE));
		pI2CHandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		len--;
	}

	// 7. when len becomes 0, wait for TXE=1 and BTF=1 before generating the STOP condition
	// note: TXE=1,  BTF=1 means that both SR and DR are empty and next transmission should begin
	// when BTF=1 SCL will be stretched (pulled to LOW)
	while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_TXE));

	while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_BTF));

	// 8. Generate STOP condition and master need not wait for the completion of stop condition
	// Note: generating stop, automatically clears the BTF
	if(sr == I2C_DISABLE_SR) {
		I2C_Generate_Stop_condition(pI2CHandle->pI2Cx);
	}
}

/* ****************************************************************************************
* @fn 				- I2C_MasterReceiveData
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
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr)
{
	//1. Generate Start condition
	I2C_Generate_Start_condition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	// Note. Until SB is cleared SCL will be stretched (pulled to low)
	while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_SB));

	//3.send the address of the slave with r/nw bit set to Rd(1)
	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, slaveAddr);

	// 4. wait until address phase is completed by checking the ADDR flag in the SR1
	while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_ADDR));

	//Procedure to read only 1 byte from slave
	if(len == 1) {
		// Disable ACK
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

		// generate stop condition
		if(sr == I2C_DISABLE_SR) {
			I2C_Generate_Stop_condition(pI2CHandle->pI2Cx);
		}

		// clear the addr flag
		I2C_clear_addr_flag(pI2CHandle);

		// wait until RXNE becomes 1
		while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_RXNE));

		// read data in to buffer
		*pRxBuffer = pI2CHandle->pI2Cx->DR;
	}

	//procedure to read data from slave when len > 1
	if(len > 1) {
		// clear the addr flag
		I2C_clear_addr_flag(pI2CHandle);

		// read the data until len becomes zero
		for(uint32_t i = len; i>0; i--) {
			// wait until RXNE becomes 1
			while(!I2Cx_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_FLAG_RXNE));

			// if last 2 bytes are remaining
			if(i==2) {
				// Disable ACK
				I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

				// generate stop condition
				if(sr == I2C_DISABLE_SR) {
					I2C_Generate_Stop_condition(pI2CHandle->pI2Cx);
				}
			}
			// read the data from data register in to buffer
			*pRxBuffer = pI2CHandle->pI2Cx->DR;

			// increment the buffer address
			pRxBuffer++;
		}
	}

	// re-enable ack
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE) {
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
	}
}

/* ****************************************************************************************
* @fn 				- I2C_ManageAcking
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
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_ENABLE) {
		pI2Cx->CR1 |= (I2C_ACK_ENABLE << I2C_CR1_ACK);
	} else {
		pI2Cx->CR1 &= ~(I2C_ACK_ENABLE << I2C_CR1_ACK);
	}
}

/* ****************************************************************************************
* @fn 				- I2C_MasterSendDataIT
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
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr)
{
	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer = pTxBuffer;
		pI2CHandle->TxLen = len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddr = slaveAddr;
		pI2CHandle->Sr = sr;

		//Implement code to Generate START Condition
		I2C_Generate_Start_condition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);


	}

	return busystate;

}

/* ****************************************************************************************
* @fn 				- I2C_MasterReceiveDataIT
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
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr)
{

	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer = pRxBuffer;
		pI2CHandle->RxLen = len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize = len; //Rxsize is used in the ISR code to manage the data reception
		pI2CHandle->DevAddr = slaveAddr;
		pI2CHandle->Sr = sr;

		//Implement code to Generate START Condition
		I2C_Generate_Start_condition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);
	}

	return busystate;
}

/* ****************************************************************************************
* @fn 				- I2C_SlaveSendData
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
void I2C_SlaveSendData(I2C_RegDef_t *pI2C, uint8_t data)
{
	pI2C->DR = data;
}

/* ****************************************************************************************
* @fn 				- I2C_SlaveReceiveData
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
uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2C)
{
	return (uint8_t)pI2C->DR;
}

/* ****************************************************************************************
* @fn 				- I2C_EV_IRQHandling
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
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	// interrupt handling for both master and slave mode of device
	uint32_t temp1, temp2, temp3;

	temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITEVTEN);
	temp2 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITBUFEN);

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_FLAG_SB);
	// 1. Handle for interrupt generated by SB event
	// Note: SB flag is only applicable in master mode not in slave mode
	if(temp1 && temp3) {
		// Interrupt is generated because of SB event
		// In this block execute the next phase, i.e. address phase
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX) {
			I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, pI2CHandle->DevAddr);
		}
		else if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX) {
			I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, pI2CHandle->DevAddr);
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (I2C_SR1_FLAG_ADDR);
	// 2. Handle for interrupt generated by ADDR event
	// Note: When master mode: Address is sent
	// When slave mode address is matched with own address
	if(temp1 && temp3) {
		// Interrupt is generated by ADDR event, clear the ADDR flag
		I2C_clear_addr_flag(pI2CHandle);
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (I2C_SR1_FLAG_BTF);
	// 3. Handle for interrupt generated by BTF (Byte Transfer Finished event)
	// when BTF flag is set:
	// Case TXE = 1
	//		Shift Register (SR) and Data Register (DR)  are empty
	// Case RXNE = 1
	//	SR and DR are full
	if(temp1 && temp3) {
		// BTF flag is set
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX) {
			// make sure that TXE is also set
			if(pI2CHandle->pI2Cx->SR1 & (I2C_SR1_FLAG_TXE)) {
				// BTF and TXE are 1
				if(pI2CHandle->TxLen == 0) {
					//1. Generate stop the condition
					if(pI2CHandle->Sr == I2C_DISABLE_SR) {
						I2C_Generate_Stop_condition(pI2CHandle->pI2Cx);
					}

					//2. reset all the member elements of the Handle structure
					I2C_CloseSendData(pI2CHandle);

					//3. notify the application about transmission complete
					I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_TX_CMPLT);
				}
			}

		}
		else if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX) {
			;
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (I2C_SR1_FLAG_STOPF);
	// 4. Handle for interrupt generated by STOPF event
	// Note: Stop Detection flag is applicable only in slave mode. For master this flag will never be set
	// below code block will not be executed by the master since STOPF will not set in master mode
	if(temp1 && temp3) {
		// STOPF flag is set
		// Clear the STOPF (i.e read SR1 and write to CR1)
		//Read is done above, and with STOPF flag
		// write to CR1, do not write anything which is not valid
		pI2CHandle->pI2Cx->CR1 |= 0x0000;

		//Notify the application that STOP is detected
		I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_STOP);
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (I2C_SR1_FLAG_TXE);
	// 5. Handle for interrupt generated by TXE event
	if(temp1 && temp2 && temp3) {

		// check for device mode, execute following only when device is in master mode
		if(pI2CHandle->pI2Cx->SR2 & (I2C_SR2_FLAG_MSL)) {

			// TXE flag is set
			// we have to do the data transmission
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX) {

				if(pI2CHandle->TxLen > 0) {
					// 1. Load the data in to DR
					pI2CHandle->pI2Cx->DR = *(pI2CHandle->pTxBuffer);

					// 2. Decrement the TxLen
					pI2CHandle->TxLen--;

					// 3. Increment the buffer address
					pI2CHandle->pTxBuffer++;
				}
			}
		}
		else {
			// Slave mode
			if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_TRA)) {
				I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_DATA_REQ);
			}
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (I2C_SR1_FLAG_RXNE);
	// 6. Handle for interrupt generated by RXNE event
	if(temp1 && temp2 && temp3) {
		// RXNE flag is set
		// check for device mode, execute following only when device is in master mode
		if(pI2CHandle->pI2Cx->SR2 & (I2C_SR2_FLAG_MSL)) {

			// Do only when application is in Busy in Rx
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX) {
				// we have to do the data reception
				if(pI2CHandle->RxSize == 1) {
					*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
					pI2CHandle->RxLen--;
				}

				if(pI2CHandle->RxSize > 1) {
					if(pI2CHandle->RxLen == 2) {
						// clear the ack bit
						I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
					}

					//read DR
					*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
					pI2CHandle->pRxBuffer++;
					pI2CHandle->RxLen--;
				}

				if(pI2CHandle->RxLen == 0) {
					// Close the I2C Data reception and notify the application

					// 1. generate the stop condition
					if(pI2CHandle->Sr == I2C_DISABLE_SR) {
						I2C_Generate_Stop_condition(pI2CHandle->pI2Cx);
					}

					// 2. Close the I2C rx
					I2C_CloseReceive_Data(pI2CHandle);

					// 3. Notify the application
					I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_RX_CMPLT);
				}
			}
		}
		else {
			// Slave mode
			if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_TRA)) {
				I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_DATA_RCV);
			}

		}
	}

}

/* ****************************************************************************************
* @fn 				- I2C_ER_IRQHandling
*
* @breif			-
*
* @param[in]		-
* @param[in]		-
* @param[in]		-
*
* @return			- none
*
* @Note              - Complete the code also define these macros in the driver
**/
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	uint32_t temp1,temp2;

    //Know the status of  ITERREN control bit in the CR2
	temp2 = (pI2CHandle->pI2Cx->CR2) & ( 1 << I2C_CR2_ITERREN);


/***********************Check for Bus error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1<< I2C_SR1_BERR);
	if(temp1  && temp2 )
	{
		//This is Bus error

		//Implement the code to clear the buss error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_BERR);

		//Implement the code to notify the application about the error
	   I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_BERR);
	}

/***********************Check for arbitration lost error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_ARLO );
	if(temp1  && temp2)
	{
		//This is arbitration lost error

		//Implement the code to clear the arbitration lost error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_ARLO);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_ARLO);

	}

/***********************Check for ACK failure  error************************************/

	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_AF);
	if(temp1  && temp2)
	{
		//This is ACK failure error

	    //Implement the code to clear the ACK failure error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_AF);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_AF);
	}

/***********************Check for Overrun/underrun error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_OVR);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun

	    //Implement the code to clear the Overrun/underrun error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_OVR);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_OVR);
	}

/***********************Check for Time out error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_TIMEOUT);
	if(temp1  && temp2)
	{
		//This is Time out error

	    //Implement the code to clear the Time out error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_TIMEOUT);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_TIMEOUT);
	}
}
