/*
 * stm32f446re_spi.h
 *
 *  Created on: 30-Apr-2020
 *      Author: GAYATHRI
 */

#ifndef INC_STM32F446RE_SPI_H_
#define INC_STM32F446RE_SPI_H_

#include<stm32f446re.h>

typedef struct {
	uint8_t SPI_DeviceMode;			/* @SPI_DeviceMode */
	uint8_t SPI_BusConfig;			/* @SPI_BusConfig */
	uint8_t SPI_ClkSpeed;			/* @SPI_ClkSpeed */
	uint8_t SPI_DFF;				/* @SPI_DFF */
	uint8_t SPI_CPOL;				/* @SPI_CPOL */
	uint8_t SPI_CPHA;				/* @SPI_CPHA */
	uint8_t SPI_SSM;				/* @SPI_SSM */
}SPI_Config_t;

typedef struct {
	SPI_RegDef_t 	*pSPIx;			/* This holds the base address of SPI[1..4] peripheral */
	SPI_Config_t 	SPIConfig;
	uint8_t 		*pTxBuffer;		/* to store application Tx buffer address */
	uint8_t 		*pRxBuffer;		/* to store application Rx buffer address */
	uint32_t		TxLen;			/* to store Tx Len */
	uint32_t		RxLen;			/* to store Rx Len */
	uint8_t 		TxState;		/* to store Tx State */
	uint8_t 		RxState;		/* to store Rx State */
}SPI_Handle_t;

/*
 * @SPI_DeviceMode
*/
#define SPI_DEVICE_MODE_SLAVE	0				/* by default */
#define SPI_DEVICE_MODE_MASTER	1

/*
 * @SPI_BusConfig
*/
#define SPI_BUS_CONFIG_FULL_DUPLEX		1
#define SPI_BUS_CONFIG_HALF_DUPLEX		2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3

/*
 * @SPI_ClkSpeed
 */
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

/*
 * @SPI_DFF
 */
#define SPI_DATA_FORMAT_8_BITS 			0		/* by default */
#define SPI_DATA_FORMAT_16_BITS 		1

/*
 * @SPI_CPOL
 */
#define SPI_CPOL_LOW					0		/* by default: clk is 0 when idle */
#define SPI_CPOL_HIGH					1		/* clk is 1 when idle */

/*
 * @SPI_CPHA
 */
#define SPI_CPHA_LOW					0		/* by default: The first clk transition is the first data capture edge */
#define SPI_CPHA_HIGH					1		/* the second clk transition is the first data capture edge */

/*
 * @SPI_SSM
 */
#define SPI_SSM_DI						0		/* by default: software mgmt is disabled, hw is enabled */
#define SPI_SSM_EN						1		/* sw mgmt is enabled */

/*
 * Define flag mask
 */
#define SPI_RXNE_FLAG					(1 << SPI_SR_BIT_RXNE)
#define SPI_TXE_FLAG					(1 << SPI_SR_BIT_TXE)			// gives masking value of TXE field
#define SPI_CHSIDE_FLAG					(1 << SPI_SR_BIT_CHSIDE)
#define SPI_UDR_FLAG					(1 << SPI_SR_BIT_UDR)
#define SPI_CRCERR_FLAG					(1 << SPI_SR_BIT_CRCERR)
#define SPI_MODF_FLAG					(1 << SPI_SR_BIT_MODF)
#define SPI_OVR_FLAG					(1 << SPI_SR_BIT_OVR)
#define SPI_BSY_FLAG					(1 << SPI_SR_BIT_BSY)
#define SPI_FRE_FLAG					(1 << SPI_SR_BIT_FRE)

/*
 * Possible Application States
 */
#define SPI_READY						0
#define SPI_BUSY_IN_RX					1
#define SPI_BUSY_IN_TX					2

/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_CMPLT				1
#define SPI_EVENT_RX_CMPLT				2
#define SPI_EVENT_OVR_ERR				3
#define SPI_EVENT_CRC_ERR				4

/* APIS supported by driver */

/* Peripheral clock enable disable*/
void SPIx_clk_control(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/* Init and De-init */
void SPIx_Init(SPI_Handle_t *pSPIHandle);
void SPIx_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data send and receive
 * Remember length will always be uint32_t type, this is standard practice
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t* pTxBuffer, uint32_t len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t* pRxBuffer, uint32_t len);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t* pTxBuffer, uint32_t len);

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t* pRxBuffer, uint32_t len);

/*
 * IRQ configuration and ISR handling
 */
void SPIx_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPIx_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/*
 * Other peripheral control API's
 */
void SPIx_peripheral_control(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPIx_SSI_config(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application call back
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pHandle, uint8_t AppEv);

#endif /* INC_STM32F446RE_SPI_H_ */
