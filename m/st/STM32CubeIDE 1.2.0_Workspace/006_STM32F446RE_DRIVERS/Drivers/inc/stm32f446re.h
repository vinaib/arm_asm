/*
 * stm32f446re.h
 *
 *  Created on: Apr 19, 2020
 *      Author: GAYATHRI
 */

#ifndef INC_STM32F446RE_H_
#define INC_STM32F446RE_H_

#include<stdint.h>

/*******Start: Processor specific address details ***********/
/**
 * ARM Cortex MX processor NVIC ISERx register Address
 * By default all interrupts are disabled
 */
#define NVIC_ISER0					((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1					((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2					((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3					((volatile uint32_t*)0xE000E10C)

/**
 * ARM Cortex MX processor NVIC ICERx register Address
 */
#define NVIC_ICER0					((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1					((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2					((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3					((volatile uint32_t*)0xE000E18C)

/**
 * ARM Cortex MX processor NVIC Priority register Address calculation
 * There are 59 priority registers. Each register is of 32 bits and
 * defines priority for 4 IRQ numbers. 60 * 4 = 260 irq's
 * Each IRQ has got 8bit priority field.
 * Out of 8 bits, low order 4 bits are not implemented. only higher 8 bits
 * are implemented..
 */
#define NVIC_PR_BASE_ADDR			((volatile uint32_t*)0xE000E400)
#define NO_PR_BITS_IMPLEMENTED		4

/*******End: Processor specific address details   ***********/

/*
 * base address of flash and rom
 **/

#define FLASH_BASEADDR				0x08000000U
#define SRAM1_BASEADDR				0x20000000U 	/*size of SRAM1 is 112KB */
#define SRAM2_BASEADDR				0x2001C000U 	/* SRAM1_BASEADDR + Size of SRAM1*/
#define ROM_BASEADDR				0x1FFF0000U		/* system memory is ROM, from which device boots */
#define SRAM						SRAM1_BASEADDR

#define APB1_OFFSET					0x00000000U
#define APB2_OFFSET					0x00010000U
#define AHB1_OFFSET					0x00020000U
#define AHB2_OFFSET					0x10000000U
#define AHB3_OFFSET					0x60000000U

/* peripheral base */

#define PERIPHERAL_BASEADDR			0x40000000U
#define APB1_BASEADDR				PERIPHERAL_BASEADDR
#define APB2_BASEADDR				0x40010000U
#define AHB1_BASEADDR				0x40020000U
#define AHB2_BASEADDR				0x50000000U
#define AHB3_BASEADDR				0xA0000000U

/* AHB1 Peripherals */
#define GPIOA_OFFSET				0x0000U
#define GPIOB_OFFSET				0x0400U
#define GPIOC_OFFSET				0x0800U
#define GPIOD_OFFSET				0x0C00U
#define GPIOE_OFFSET				0x1000U
#define GPIOF_OFFSET				0x1400U
#define GPIOG_OFFSET				0x1800U
#define GPIOH_OFFSET				0x1C00U

#define GPIOA_BASEADDR				(AHB1_BASEADDR + GPIOA_OFFSET)
#define GPIOB_BASEADDR				(AHB1_BASEADDR + GPIOB_OFFSET)
#define GPIOC_BASEADDR				(AHB1_BASEADDR + GPIOC_OFFSET)
#define GPIOD_BASEADDR				(AHB1_BASEADDR + GPIOD_OFFSET)
#define GPIOE_BASEADDR				(AHB1_BASEADDR + GPIOE_OFFSET)
#define GPIOF_BASEADDR				(AHB1_BASEADDR + GPIOF_OFFSET)
#define GPIOG_BASEADDR				(AHB1_BASEADDR + GPIOG_OFFSET)
#define GPIOH_BASEADDR				(AHB1_BASEADDR + GPIOH_OFFSET)

#define RCC_OFFSET					0x3800U

#define RCC_BASEADDR				(AHB1_BASEADDR + RCC_OFFSET)

/* APB1 Peripherals */
#define I2C1_OFFSET					0x5400U
#define I2C2_OFFSET					0x5800U
#define I2C3_OFFSET					0x5C00U
#define SPI2_OFFSET					0x3800U
#define SPI3_OFFSET					0x3C00U
#define I2S2_OFFSET					SPI2_OFFSET
#define I2S3_OFFSET					SPI3_OFFSET
#define USART2_OFFSET				0x4400U
#define USART3_OFFSET				0x4800U
#define UART4_OFFSET				0x4C00U
#define UART5_OFFSET				0x5000U

#define I2C1_BASEADDR				(APB1_BASEADDR + I2C1_OFFSET)
#define I2C2_BASEADDR				(APB1_BASEADDR + I2C2_OFFSET)
#define I2C3_BASEADDR				(APB1_BASEADDR + I2C3_OFFSET)
#define SPI2_BASEADDR				(APB1_BASEADDR + SPI2_OFFSET)
#define SPI3_BASEADDR				(APB1_BASEADDR + SPI3_OFFSET)
#define USART2_BASEADDR				(APB1_BASEADDR + USART2_OFFSET)
#define USART3_BASEADDR				(APB1_BASEADDR + USART3_OFFSET)
#define UART4_BASEADDR				(APB1_BASEADDR + UART4_OFFSET)		/* does not support synchronous communication */
#define UART5_BASEADDR				(APB1_BASEADDR + UART5_OFFSET)

/* APB2 Peripherals */
#define EXTI_OFFSET					0x3C00U
#define SYSCFG_OFFSET				0x3800U
#define SPI1_OFFSET					0x3000U
#define SPI4_OFFSET					0x3400U
#define USART1_OFFSET				0x1000U
#define USART6_OFFSET				0x1400U

#define EXTI_BASEADDR				(APB2_BASEADDR + EXTI_OFFSET)
#define SYSCFG_BASEADDR				(APB2_BASEADDR + SYSCFG_OFFSET)
#define SPI1_BASEADDR				(APB2_BASEADDR + SPI1_OFFSET)
#define SPI4_BASEADDR				(APB2_BASEADDR + SPI4_OFFSET)
#define USART1_BASEADDR				(APB2_BASEADDR + USART1_OFFSET)
#define USART6_BASEADDR				(APB2_BASEADDR + USART6_OFFSET)

/* peripheral register definition structure for GPIO */
typedef struct {
	volatile uint32_t MODER;					/* Mode register 0x0*/
	volatile uint32_t OTYPER;				/* Output type register 0x4*/
	volatile uint32_t OSPEEDR;				/* output speed register 0x8*/
	volatile uint32_t PUPDR;					/* Pull up Pull Down register 0x0c*/
	volatile uint32_t IDR;					/* Input data register 0x10*/
	volatile uint32_t ODR;					/* Output data register 0x14*/
	volatile uint32_t BSRR;					/* Bit set reset register 0x18*/
	volatile uint32_t LCKR;					/* Configuration lock register 0x1C*/
	volatile uint32_t AFRL;					/* Alternate function Low register 0x20*/
	volatile uint32_t AFRH;					/* Alternate function High register 0x24*/
}GPIO_RegDef_t;

/*
GPIO_RegDef_t *pGPIOA = (GPIO_RegDef_t*)GPIOA_BASEADDR;
GPIO_RegDef_t *pGPIOB = (GPIO_RegDef_t*)GPIOB_BASEADDR;
GPIO_RegDef_t *pGPIOC = (GPIO_RegDef_t*)GPIOC_BASEADDR;
GPIO_RegDef_t *pGPIOD = (GPIO_RegDef_t*)GPIOD_BASEADDR;
GPIO_RegDef_t *pGPIOE = (GPIO_RegDef_t*)GPIOE_BASEADDR;
GPIO_RegDef_t *pGPIOF = (GPIO_RegDef_t*)GPIOF_BASEADDR;
GPIO_RegDef_t *pGPIOG = (GPIO_RegDef_t*)GPIOG_BASEADDR;
GPIO_RegDef_t *pGPIOH = (GPIO_RegDef_t*)GPIOH_BASEADDR;
*/
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)


/* peripheral register definition structure for I2C */
typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;
}I2C_RegDef_t;
/*
I2C_RegDef_t *pI2C1 = (I2C_RegDef_t*)I2C1_BASEADDR;
I2C_RegDef_t *pI2C2 = (I2C_RegDef_t*)I2C2_BASEADDR;
I2C_RegDef_t *pI2C3 = (I2C_RegDef_t*)I2C3_BASEADDR;
*/

/* or */
#define I2C1 ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2 ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3 ((I2C_RegDef_t*)I2C3_BASEADDR)

/*
 * I2C Control register CR1
 */
#define I2C_CR1_PE			0	/*PERIPHERAL ENABLE */
#define I2C_CR1_SMBUS		1	/*SMBUS MODE 1, I2C MODE 0*/
#define I2C_CR1_SMBTYPE		2
#define I2C_CR1_ENARP		4
#define I2C_CR1_ENPEC		5
#define I2C_CR1_ENGC		6
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10
#define I2C_CR1_POS			11
#define I2C_CR1_PEC			12
#define I2C_CR1_ALERT		13
#define I2C_CR1_SWRST		15	/*SOFTWARE RESET*/

/*
 * I2C CONTROL REGSITER 2 (CR2)
 */
#define I2C_CR2_FREQ		0	/* 5 BITS */
#define I2C_CR2_ITERREN		8
#define I2C_CR2_ITEVTEN		9
#define I2C_CR2_ITBUFEN		10
#define I2C_CR2_DMAEN		11
#define I2C_CR2_LAST		12

/*
 * I2C OWN ADDRESS REGISTER 1 (I2C_OAR1)
 */
#define I2C_OAR1_ADD0		0	/* INTERFACE ADDRESS, 7BIT ADDRESS DNX, 10BIT ADDRESS BITO*/
#define I2C_OAR1_ADD_7_1	1
#define I2C_OAR1_ADD_8_9	8	/* INTERFACE ADDRESS, 7BIT DONOT CARE(DNX), 10 BIT ADDRESS BIT 8 AND 9*/
#define I2C_OAR1_ADDMODE	15	/* 0 7BIT SLAVE ADDRESS, 1 10BIT SLAVE ADDRESS */

/*
 * I2C OWN ADDRESS REGISTER 2(I2C_OAR2)
 */
#define I2C_OAR2_ENDUAL		0
#define I2C_OAR2_ADD2		1	/*1-7: 7BIT ADDRESSING */

/*
 * I2C STATUS REGISTER 1 (I2C_SR1)
 */
#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RXNE		6
#define I2C_SR1_TXE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_PECERR		12
#define I2C_SR1_TIMEOUT		14
#define I2C_SR1_SMBALERT	15

/*
 * I2C STATUS REGISTER 2 (I2C_SR2)
 */
#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_SMBDEFAULT	5
#define I2C_SR2_SMBHOST		6
#define I2C_SR2_DUALF		7
#define I2C_SR2_PEC_7_0		8

/*
 * I2C CLOCK CONTROL REGISTER (I2C_CCR)
 */
#define I2C_CCR_CCR_0_11	0
#define I2C_CCR_DUTY		14
#define I2C_CCR_FORS		15

/*
 * I2C TRISE REGISTER (I2C_TRISE)
 */
#define I2C_TRISE_TRISE_0_5	0

/*
 * I2C FILTER REGISTER (I2C_FLTR)
 */
#define I2C_FLTR_DNF		0	/* DIGITAL NOISE FILTER */
#define I2C_FLTR_ANOFF		4	/* ANALOG NOISE FILTER */
/*****************************************************************************************************************/
/* peripheral register definition structure for SPI */
typedef struct {
	volatile uint32_t	CR1;			/* offset 0x0 */
	volatile uint32_t	CR2;			/* offset 0x4 */
	volatile uint32_t	SR;				/* offset 0x8 */
	volatile uint32_t	DR;				/* offset 0xC */
	volatile uint32_t	CRCPR;			/* offset 0x10 */
	volatile uint32_t	RXCRCR;			/* offset 0x14 */
	volatile uint32_t	TXCRCR;			/* offset 0x18 */
	volatile uint32_t	I2SCFGR;		/* offset 0x1C */
	volatile uint32_t	I2SPR;			/* offset 0x20 */
}SPI_RegDef_t;

/*
SPI_RegDef_t *pSPI1 = (SPI_RegDef_t*)SPI1_BASEADDR;
SPI_RegDef_t *pSPI2 = (SPI_RegDef_t*)SPI2_BASEADDR;
SPI_RegDef_t *pSPI3 = (SPI_RegDef_t*)SPI3_BASEADDR;
*/
#define SPI1 ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4 ((SPI_RegDef_t*)SPI4_BASEADDR)

/*
 * SPI_CR1 BIT DEFINITIONS
 */
#define SPI_CR1_BIT_CPHA		0
#define SPI_CR1_BIT_CPOL		1
#define SPI_CR1_BIT_MSTR		2
#define SPI_CR1_BIT_BR			3		/* @SPI_ClkSpeed : Baudrate */
#define SPI_CR1_BIT_SPE			6
#define SPI_CR1_BIT_LSBFIRST	7
#define SPI_CR1_BIT_SSI			8
#define SPI_CR1_BIT_SSM			9
#define SPI_CR1_BIT_RXONLY		10
#define SPI_CR1_BIT_DFF			11
#define SPI_CR1_BIT_CRCNEXT		12
#define SPI_CR1_BIT_CRCEN		13
#define SPI_CR1_BIT_BIDIOE		14
#define SPI_CR1_BIT_BIDIMODE	15

/*
 * SPI_CR2 BIT DEFINITIONS *
 */
#define SPI_CR2_BIT_RXDMAEN		0
#define SPI_CR2_BIT_TXDMAEN		1
#define SPI_CR2_BIT_SSOE		2
#define SPI_CR2_BIT_FRF			4
#define SPI_CR2_BIT_ERRIE		5
#define SPI_CR2_BIT_RXNEIE		6
#define SPI_CR2_BIT_TXEIE		7

/*
 * SPI_SR BIT DEFINITIONS *
 */
#define SPI_SR_BIT_RXNE			0
#define SPI_SR_BIT_TXE			1
#define SPI_SR_BIT_CHSIDE		2
#define SPI_SR_BIT_UDR			3
#define SPI_SR_BIT_CRCERR		4
#define SPI_SR_BIT_MODF			5
#define SPI_SR_BIT_OVR			6
#define SPI_SR_BIT_BSY			7
#define SPI_SR_BIT_FRE			8

/*
USART_RegDef_t *pUSART1 = (USART_RegDef_t*)USART1_BASEADDR;
USART_RegDef_t *pUSART2 = (USART_RegDef_t*)USART2_BASEADDR;
USART_RegDef_t *pUSART3 = (USART_RegDef_t*)USART3_BASEADDR;
USART_RegDef_t *pUSART6 = (USART_RegDef_t*)USART6_BASEADDR;
*/

/* peripheral register definition structure for USART */
typedef struct {
	volatile uint32_t SR;					/* 0x00 */
	volatile uint32_t DR;					/* 0x04 */
	volatile uint32_t BRR;					/* 0x08 */
	volatile uint32_t CR1;					/* 0x0C */
	volatile uint32_t CR2;					/* 0x10 */
	volatile uint32_t CR3;					/* 0x14 */
	volatile uint32_t GTPR;					/* 0x18 */
}USART_RegDef_t;

#define USART1 ((USART_RegDef_t *)USART1_BASEADDR)
#define USART2 ((USART_RegDef_t *)USART2_BASEADDR)
#define USART3 ((USART_RegDef_t *)USART3_BASEADDR)
#define UART4  ((USART_RegDef_t *)UART4_BASEADDR)
#define UART5  ((USART_RegDef_t *)UART5_BASEADDR)
#define USART6 ((USART_RegDef_t *)USART6_BASEADDR)

#define	USART_SR_PE			0
#define	USART_SR_FE			1
#define	USART_SR_NF			2
#define	USART_SR_ORE		3
#define	USART_SR_IDLE		4
#define	USART_SR_RXNE		5
#define	USART_SR_TC			6
#define	USART_SR_TXE		7
#define	USART_SR_LBD		8
#define	USART_SR_CTS		9

#define	USART_FLAG_SR_PE			(1 << USART_SR_PE)
#define	USART_FLAG_SR_FE			(1 << USART_SR_FE)
#define	USART_FLAG_SR_NF			(1 << USART_SR_NF)
#define	USART_FLAG_SR_ORE			(1 << USART_SR_ORE)
#define	USART_FLAG_SR_IDLE			(1 << USART_SR_IDLE)
#define	USART_FLAG_SR_RXNE			(1 << USART_SR_RXNE)
#define	USART_FLAG_SR_TC			(1 << USART_SR_TC)
#define	USART_FLAG_SR_TXE			(1 << USART_SR_TXE)
#define	USART_FLAG_SR_LBD			(1 << USART_SR_LBD)
#define	USART_FLAG_SR_CTS			(1 << USART_SR_CTS)

#define USART_BRR_DIV_FRACTION	0
#define USART_BRR_DIV_MANTISSA	4

#define USART_CR1_SBK		0
#define USART_CR1_RWU		1
#define USART_CR1_RE		2
#define USART_CR1_TE		3
#define USART_CR1_IDLEIE	4
#define USART_CR1_RXNEIE	5
#define USART_CR1_TCIE		6
#define USART_CR1_TXEIE		7
#define USART_CR1_PEIE		8
#define USART_CR1_PS		9
#define USART_CR1_PCE		10
#define USART_CR1_WAKE		11
#define USART_CR1_M			12
#define USART_CR1_UE		13
#define USART_CR1_OVER8		15

#define USART_CR2_ADD		0
#define USART_CR2_LBDL		5
#define USART_CR2_LBDIE		6
#define USART_CR2_LBCL		8
#define USART_CR2_CPHA		9
#define USART_CR2_CPOL		10
#define USART_CR2_CLKEN		11
#define USART_CR2_STOP		12
#define USART_CR2_LINEN		14

#define USART_CR3_EIE		0
#define USART_CR3_IREN		1
#define USART_CR3_IRLP		2
#define USART_CR3_HDSEL		3
#define USART_CR3_NACK		4
#define USART_CR3_SCEN		5
#define USART_CR3_DMAR		6
#define USART_CR3_DMAT		7
#define USART_CR3_RTSE		8
#define USART_CR3_CTSE		9
#define USART_CR3_CTSIE		10
#define USART_CR3_ONEBIT	11

#define USART_GTPR_PSC		0
#define USART_GTPR_GT		8

/*****************************************************************************************************************/
/* peripheral register definition structure for RCC */
typedef struct {
	volatile uint32_t CR;					/* 0X00 */
	volatile uint32_t PLLCFGR;				/* 0X04 */
	volatile uint32_t CFGR;					/* 0X08 */
	volatile uint32_t CIR;					/* 0X0C */
	volatile uint32_t AHB1RSTR;				/* 0X10 */
	volatile uint32_t AHB2RSTR;				/* 0X14 */
	volatile uint32_t AHB3RSTR;				/* 0X18 */
	volatile uint32_t RESERVED0;			/* 0X1C */
	volatile uint32_t APB1RSTR;				/* 0X20 */
	volatile uint32_t APB2RSTR;				/* 0X24 */
	volatile uint32_t RESERVED1;			/* 0X28 */
	volatile uint32_t RESERVED2;			/* 0X2C */
	volatile uint32_t AHB1ENR;				/* 0X30 */
	volatile uint32_t AHB2ENR;				/* 0X34 */
	volatile uint32_t AHB3ENR;				/* 0X38 */
	volatile uint32_t RESERVED3;			/* 0X3C */
	volatile uint32_t APB1ENR;				/* 0X40 */
	volatile uint32_t APB2ENR;				/* 0X44 */
	volatile uint32_t RESERVED4;			/* 0X48 */
	volatile uint32_t RESERVED5;			/* 0X4C */
	volatile uint32_t AHB1LPENR;			/* 0X50 */
	volatile uint32_t AHB2LPENR;			/* 0X54 */
	volatile uint32_t AHB3LPENR;			/* 0X58 */
	volatile uint32_t RESERVED6;			/* 0X5C */
	volatile uint32_t APB1LPENR;			/* 0X60 */
	volatile uint32_t APB2LPENR;			/* 0X64 */
	volatile uint32_t RESERVED7;			/* 0X68 */
	volatile uint32_t RESERVED8;			/* 0X6C */
	volatile uint32_t BDCR;					/* 0X70 */
	volatile uint32_t CSR;					/* 0X74 */
	volatile uint32_t RESERVED9;			/* 0X78 */
	volatile uint32_t RESERVED10;			/* 0X7C */
	volatile uint32_t SSCGR;				/* 0X80 */
	volatile uint32_t PLLI2SCFGR;			/* 0X84 */
	volatile uint32_t PLLSAICFGR;			/* 0X88 */
	volatile uint32_t DCKCFGR;				/* 0X8C */
	volatile uint32_t CKGATENR;				/* 0X90 */
	volatile uint32_t DCKCFGR2;				/* 0X94 */
}RCC_RegDef_t;

#define RCC		((RCC_RegDef_t *) RCC_BASEADDR)

/* peripheral register definition structure for EXTI */
typedef struct {
	volatile uint32_t EXTI_IMR;					/* Interrupt mask register 0x00*/
	volatile uint32_t EXTI_EMR;					/* Event mask register 0x04*/
	volatile uint32_t EXTI_RTSR;				/* Rising trigger selection register 0x08*/
	volatile uint32_t EXTI_FTSR;				/* Fallin trigger selection register 0x0C*/
	volatile uint32_t EXTI_SWIER;				/* software interrupt event register 0x10*/
	volatile uint32_t EXTI_PR;					/* pending register 0x14*/
}EXTI_RegDef_t;

#define EXTI		((EXTI_RegDef_t *) EXTI_BASEADDR)

/* peripheral register definition structure for SYSCFG */
typedef struct {
	volatile uint32_t MEMRMP;					/* Memory Remap register 0x00*/
	volatile uint32_t PMC;						/* Peripheral mode configuration register 0x04*/
	volatile uint32_t EXTICR[4];				/* External interrupt configuration register 1 0x08 - 0x14*/
	volatile uint32_t RSVD1[2];					/* Reserved 1 0x018- 0x1C */
	volatile uint32_t CMPCR;					/* compensation cell control register 0x20*/
	volatile uint32_t RSVD2[2];					/* Reserved 1 0x024 - 0x28 */
	volatile uint32_t CFGR;						/* configuration register 0x2C*/
}SYSCFG_RegDef_t;

#define SYSCFG		((SYSCFG_RegDef_t *) SYSCFG_BASEADDR)

/**************************************************************************/

/* GPIO CLK EN and DI macros*/
#define GPIOA_CLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOA_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOB_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOC_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOD_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOE_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLK_EN()		(RCC->AHB1ENR |= (1 << 5))
#define GPIOF_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLK_EN()		(RCC->AHB1ENR |= (1 << 6))
#define GPIOG_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLK_EN()		(RCC->AHB1ENR |= (1 << 7))
#define GPIOH_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 7))

/* Macros to reset GPIO peripherals
 * do-while is a technique in "C" programming to execute multiple "C" statements using single "C" macro.
 * After peripheral reset bit is set in the register, the same bit must be reset after set. Otherwise if
 * bit is not reset then peripheral will continuously resets.
 * */
#define GPIOA_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 0); (RCC->AHB1RSTR) &= ~(1 << 0);} while(0)
#define GPIOB_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 1); (RCC->AHB1RSTR) &= ~(1 << 1);} while(0)
#define GPIOC_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 2); (RCC->AHB1RSTR) &= ~(1 << 2);} while(0)
#define GPIOD_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 3); (RCC->AHB1RSTR) &= ~(1 << 3);} while(0)
#define GPIOE_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 4); (RCC->AHB1RSTR) &= ~(1 << 4);} while(0)
#define GPIOF_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 5); (RCC->AHB1RSTR) &= ~(1 << 5);} while(0)
#define GPIOG_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 6); (RCC->AHB1RSTR) &= ~(1 << 6);} while(0)
#define GPIOH_REG_RESET()	 	do {(RCC->AHB1RSTR) |= (1 << 7); (RCC->AHB1RSTR) &= ~(1 << 7);} while(0)

#define GPIO_BASEADDR_TO_CODE(x)	( 	(x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:\
										(x == GPIOD)?3:\
										(x == GPIOE)?4:\
										(x == GPIOF)?5:\
										(x == GPIOG)?6:\
										(x == GPIOH)?7:0 )

/* I2C CLK EN and DI macros */
#define I2C1_CLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C1_CLK_DI()		(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C2_CLK_DI()		(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_CLK_EN()		(RCC->APB1ENR |= (1 << 23))
#define I2C3_CLK_DI()		(RCC->APB1ENR &= ~(1 << 23))

#define I2C1_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 21); (RCC->APB1RSTR) &= ~(1 << 21);}while(0);
#define I2C2_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 22); (RCC->APB1RSTR) &= ~(1 << 22);}while(0);
#define I2C3_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 23); (RCC->APB1RSTR) &= ~(1 << 23);}while(0);

/* SPI CLK EN and DI macros*/
#define SPI1_CLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI1_CLK_DI()		(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI2_CLK_DI()		(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_EN()		(RCC->APB1ENR |= (1 << 15))
#define SPI3_CLK_DI()		(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_CLK_EN()		(RCC->APB2ENR |= (1 << 13))
#define SPI4_CLK_DI()		(RCC->APB2ENR &= ~(1 << 13))

#define SPI1_REG_RESET()	do{(RCC->APB2RSTR) |= (1 << 12); (RCC->APB2RSTR) &= ~(1 << 12);} while(0);
#define SPI2_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 14); (RCC->APB1RSTR) &= ~(1 << 14);} while(0);
#define SPI3_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 15); (RCC->APB1RSTR) &= ~(1 << 15);} while(0);
#define SPI4_REG_RESET()	do{(RCC->APB2RSTR) |= (1 << 13); (RCC->APB2RSTR) &= ~(1 << 13);} while(0);

/* USART CLK EN and DI macros */
#define USART1_CLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define USART1_CLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define USART2_CLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define USART2_CLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_EN()		(RCC->APB1ENR |= (1 << 18))
#define USART3_CLK_DI()		(RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_EN()		(RCC->APB1ENR |= (1 << 19))
#define UART4_CLK_DI()		(RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_EN()		(RCC->APB1ENR |= (1 << 20))
#define UART5_CLK_DI()		(RCC->APB1ENR &= ~(1 << 20))
#define USART6_CLK_EN()		(RCC->APB2ENR |= (1 << 5))
#define USART6_CLK_DI()		(RCC->APB2ENR &= ~(1 << 5))

#define USART1_REG_RESET()	do{(RCC->APB2RSTR) |= (1 << 4); (RCC->APB2RSTR) &= ~(1 << 4);} while(0);
#define USART2_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 17); (RCC->APB1RSTR) &= ~(1 << 17);} while(0);
#define USART3_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 18); (RCC->APB1RSTR) &= ~(1 << 18);} while(0);
#define UART4_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 19); (RCC->APB1RSTR) &= ~(1 << 19);} while(0);
#define UART5_REG_RESET()	do{(RCC->APB1RSTR) |= (1 << 20); (RCC->APB1RSTR) &= ~(1 << 20);} while(0);
#define USART6_REG_RESET()	do{(RCC->APB2RSTR) |= (1 << 5); (RCC->APB2RSTR) &= ~(1 << 5);} while(0);

/* SYSCFG CLK ENABLE */
#define SYSCFG_CLK_ENABLE()		(RCC->APB2ENR |= (1 << 14))
#define SYSCFG_CLK_DISABLE()	(RCC->APB2ENR &= ~(1 << 14))

/* IRQ numbers of STM32f446re MCu
 * Note: update these macros with valid values according to your MCU
 * TODO: Complete this list for other peripherals
 * */
#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			23
#define IRQ_NO_EXTI15_10		40

#define IRQ_NO_SPI1				35
#define IRQ_NO_SPI2				36
#define IRQ_NO_SPI3				51
#define IRQ_NO_SPI4				84

#define IRQ_NO_I2C1_EV			31		/*EV: Event interrupt */
#define IRQ_NO_I2C1_ER			32		/*ER: Error interrupt */
#define IRQ_NO_I2C2_EV			33
#define IRQ_NO_I2C2_ER			34
#define IRQ_NO_I2C3_EV			72
#define IRQ_NO_I2C3_ER			73


/* Macros for all the possible priority levels
 * */
#define NVIC_IRQ_PRIORITY_0			0
#define NVIC_IRQ_PRIORITY_1			1
#define NVIC_IRQ_PRIORITY_2			2
#define NVIC_IRQ_PRIORITY_3			3
#define NVIC_IRQ_PRIORITY_4			4
#define NVIC_IRQ_PRIORITY_5			5
#define NVIC_IRQ_PRIORITY_6			6
#define NVIC_IRQ_PRIORITY_7			7
#define NVIC_IRQ_PRIORITY_8			8
#define NVIC_IRQ_PRIORITY_9			9
#define NVIC_IRQ_PRIORITY_10		10
#define NVIC_IRQ_PRIORITY_11		11
#define NVIC_IRQ_PRIORITY_12		12
#define NVIC_IRQ_PRIORITY_13		13
#define NVIC_IRQ_PRIORITY_14		14
#define NVIC_IRQ_PRIORITY_15		15

/* generic macros */
#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_SET		SET
#define FLAG_RESET		RESET
#endif /* INC_STM32F446RE_H_ */
