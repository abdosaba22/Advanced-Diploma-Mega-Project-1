/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 GPIO									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 10, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


#define GPIOA_BASE_ADDRESS      		0x40010800U
#define GPIOB_BASE_ADDRESS      		0x40010C00U
#define GPIOC_BASE_ADDRESS      		0x40011000U


/******************* GPIO Register Definition Structure **************/

typedef struct
{
    volatile uint32_t  CRL;        /*!< GPIO port configuration register low,                   Address offset: 0x00 */
    volatile uint32_t  CRH;        /*!< GPIO port configuration register high,                  Address offset: 0x04 */
    volatile uint32_t  IDR;        /*!< GPIO port input data register,                          Address offset: 0x08 */
    volatile uint32_t  ODR;        /*!< GPIO port output data register,                         Address offset: 0x0C */
    volatile uint32_t  BSRR;       /*!< GPIO port bit set/reset register,                       Address offset: 0x10 */
    volatile uint32_t  BRR;        /*!< GPIO port bit reset register,                           Address offset: 0x14 */
    volatile uint32_t  LCKR;       /*!< GPIO port configuration lock register,                  Address offset: 0x18 */
} GPIO_RegDef_t;


/******************* AFIO Register Definition Structure **************/

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t MAPR2;
} AFIO_RegDef_t;

/******************* GPIO Peripheral Definition **************/

#define GPIOA               			((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB               			((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC               			((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)

#define GPIO_AFIO            			((AFIO_RegDef_t*)AFIO_BASE_ADDRESS)


/**********************/

#define ONEBIT_MSAK  			1u
#define MODECNFBIT_MASK         0x0FU

#define MODECNFSHIFTPIN 		4U



#endif