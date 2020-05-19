/*
 * stm32f466re_gpio.h
 *
 *  Created on: 20-Apr-2020
 *      Author: GAYATHRI
 */

#ifndef INC_STM32F446RE_GPIO_H_
#define INC_STM32F446RE_GPIO_H_

#include<stm32f446re.h>

typedef struct {
	uint8_t GPIO_PinNumber;				/* possible values from @GPIO_PIN_NUMBERS*/
	uint8_t GPIO_PinMode;				/* possible values from @GPIO_PIN_MODES*/
	uint8_t GPIO_PinSpeed;				/* possible values from @GPIO_PIN_SPEED*/
	uint8_t GPIO_PinPuPdControl;		/* @GPIO_PinPuPdControl */
	uint8_t GPIO_PinOPType;				/* @GPIO_PinOPType */
	uint8_t GPIO_PinAltFunMode;			/* possible values from @GPIO_PIN_ALT_MODE*/
}GPIO_PinConfg_t;

typedef struct
{
	GPIO_RegDef_t *pGPIOx;				/* holds the base address of the GPIO port to which the pin belongs*/
	GPIO_PinConfg_t GPIO_PinConfg;		/* holds the GPIO pin configuration settings */

}GPIO_Handle_t;

/*
* @GPIO_PIN_NUMBERS
*
*/
#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 **/
#define GPIO_MODE_IN 			0		/* input mode */
#define GPIO_MODE_OUT 			1		/* output mode*/
#define GPIO_MODE_ALTFN 		2		/* alternate function mode */
#define GPIO_MODE_ANALOG 		3		/* analog mode */
#define GPIO_MODE_IT_FT			4		/* interrupt falling edge trigger */
#define GPIO_MODE_IT_RT			5		/* interrupt raising edge trigger */
#define GPIO_MODE_IT_RFT		6		/* interrupt raising and falling edge trigger */

/*
 * @GPIO_PinOPType
 * GPIO Port output type
 */
#define GPIO_OP_TYPE_PP			0
#define GPIO_OP_TYPE_OD			1

/*
 * @GPIO_PIN_SPEED
 * GPIO Pin possible output speeds
 */
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3

/* @GPIO_PinPuPdControl
 * GPIO Pin pull up and pull down configuration macros
 */
#define GPIO_NO_PUPD			0
#define GPIO_PIN_PU				1
#define GPIO_PIN_PD				2

/*
 * @GPIO_PIN_ALT_MODE
 * GPIO alternate modes
 */
#define GPIO_ALT_MODE_0			0
#define GPIO_ALT_MODE_1			1
#define GPIO_ALT_MODE_2			2
#define GPIO_ALT_MODE_3			3
#define GPIO_ALT_MODE_4			4
#define GPIO_ALT_MODE_5			5
#define GPIO_ALT_MODE_6			6
#define GPIO_ALT_MODE_7			7
#define GPIO_ALT_MODE_8			8
#define GPIO_ALT_MODE_9			9
#define GPIO_ALT_MODE_10		10
#define GPIO_ALT_MODE_11		11
#define GPIO_ALT_MODE_12		12
#define GPIO_ALT_MODE_13		13
#define GPIO_ALT_MODE_14		14
#define GPIO_ALT_MODE_15		15

/* APIS supported by driver */

/* Peripheral clock enable disable*/
void GPIOx_clk_control(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Init and De-init */
void GPIOx_Init(GPIO_Handle_t *pGPIOHandle);
void GPIOx_DeInit(GPIO_RegDef_t *pGPIOx);

/* Data read and write */
uint8_t GPIOx_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);
uint16_t GPIOx_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIOx_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value);
void GPIOx_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIOx_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);

/* IRQ Handing and configuration */
void GPIOx_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIOx_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t pinNumber);

#endif /* INC_STM32F446RE_GPIO_H_ */
