/*
 * stm32f466re_i2c.h
 *
 *  Created on: 06-May-2020
 *      Author: GAYATHRI
 */

#ifndef INC_STM32F446RE_I2C_H_
#define INC_STM32F446RE_I2C_H_

#include<stm32f446re.h>

/*
 * CONFIGURATION STRUCTURE FOR I2C PERIPHERAL
 */
typedef struct {
	uint32_t I2C_SCLSpeed;
	uint8_t	 I2C_DeviceAddress;
	uint8_t  I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
}I2C_Config_t;

/*
 * Handle structure for I2C peripheral
 */
typedef struct {
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config;
	uint8_t *pTxBuffer;			/* To store app Tx Buffer address */
	uint8_t *pRxBuffer;			/* To store app Rx Buffer address */
	uint32_t TxLen;				/* To store app Tx Len */
	uint32_t RxLen;				/* To store app Rx Len */
	uint8_t TxRxState;			/* To store Communication state, as I2C is half duplex so one variable is enough */
	uint8_t DevAddr;			/* To store slave/device address */
	uint32_t RxSize;				/* To store Rx size */
	uint8_t Sr;					/* To store repeated start value */
}I2C_Handle_t;

/*
 * @I2C_SCLSpeed
 */
#define I2C_SCK_SPEED_SM	100000
#define I2C_SCK_SPEED_FM4K	400000
#define I2C_SCK_SPEED_FM2K	200000

/*
 * @I2C_ACKControl
 */
#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISABLE		0

/*
 * @I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2			0
#define I2C_FM_DUTY_16_9		1

/*
 * I2C related status flags
 */
#define I2C_SR1_FLAG_SB			(1 << I2C_SR1_SB)
#define I2C_SR1_FLAG_ADDR		(1 << I2C_SR1_ADDR)
#define I2C_SR1_FLAG_BTF		(1 << I2C_SR1_BTF)
#define I2C_SR1_FLAG_ADD10		(1 << I2C_SR1_ADD10)
#define I2C_SR1_FLAG_STOPF		(1 << I2C_SR1_STOPF)
#define I2C_SR1_FLAG_RXNE		(1 << I2C_SR1_RXNE)
#define I2C_SR1_FLAG_TXE		(1 << I2C_SR1_TXE)
#define I2C_SR1_FLAG_BERR		(1 << I2C_SR1_BERR)
#define I2C_SR1_FLAG_ARLO		(1 << I2C_SR1_ARLO)
#define I2C_SR1_FLAG_AF			(1 << I2C_SR1_AF)
#define I2C_SR1_FLAG_OVR		(1 << I2C_SR1_OVR)
#define I2C_SR1_FLAG_PECERR		(1 << I2C_SR1_PECERR)
#define I2C_SR1_FLAG_TIMEOUT	(1 << I2C_SR1_TIMEOUT)
#define I2C_SR1_FLAG_SMBALERT	(1 << I2C_SR1_SMBALERT)

#define I2C_SR2_FLAG_MSL		(1 << I2C_SR2_MSL)
#define I2C_SR2_FLAG_BUSY		(1 << I2C_SR2_BUSY)
#define I2C_SR2_FLAG_TRA		(1 << I2C_SR2_TRA)
#define I2C_SR2_FLAG_GENCALL	(1 << I2C_SR2_GENCALL)
#define I2C_SR2_FLAG_SMBDEFAULT	(1 << I2C_SR2_SMBDEFAULT)
#define I2C_SR2_FLAG_SMBHOST	(1 << I2C_SR2_SMBDEFAULT)
#define I2C_SR2_FLAG_DUALF		(1 << I2C_SR2_DUALF)
#define I2C_SR2_FLAG_PEC		(0XFF << I2C_SR2_PEC_7_0)

#define I2C_DISABLE_SR 	RESET
#define I2C_ENABLE_SR	SET

/*
 * I2C application event macros
 */
#define I2C_EV_TX_CMPLT		0
#define I2C_EV_RX_CMPLT		1
#define I2C_EV_STOP			2
#define I2C_ERROR_BERR  	3
#define I2C_ERROR_ARLO  	4
#define I2C_ERROR_AF    	5
#define I2C_ERROR_OVR   	6
#define I2C_ERROR_TIMEOUT 	7
#define I2C_EV_DATA_REQ		8
#define I2C_EV_DATA_RCV		9
/*
 * @TxRxState
 */
#define I2C_READY 			0
#define I2C_BUSY_IN_RX		1
#define I2C_BUSY_IN_TX		2


/* APIS supported by driver */

/* Peripheral clock enable disable*/
void I2Cx_clk_control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/* Init and De-init */
void I2Cx_Init(I2C_Handle_t *pI2CHandle);
void I2Cx_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Data send and receive
 * Remember length will always be uint32_t type, this is standard practice
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr);

uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t len, uint8_t slaveAddr, uint8_t sr);

void I2C_CloseReceive_Data(I2C_Handle_t *pI2CHandle);
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);

/* send/receive data byte by byte */
void I2C_SlaveSendData(I2C_RegDef_t *pI2C, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2C);

void I2C_Generate_Stop_condition(I2C_RegDef_t *pI2Cx);
/*
 * IRQ configuration and ISR handling
 */
void I2Cx_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2Cx_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

/*
 * Other peripheral control API's
 */
void I2Cx_peripheral_control(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
uint8_t I2Cx_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/*
 * Application call back
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pHandle, uint8_t AppEv);


#endif /* INC_STM32F446RE_I2C_H_ */
