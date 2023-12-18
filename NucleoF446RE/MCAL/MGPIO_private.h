/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 GPIO								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 15, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */


#ifndef _MGPIO_PRIVATE_H_
#define _MGPIO_PRIVATE_H_


/********************* MGPIO Peripheral Base Addresses *****************/

#define GPIOA_BASE_ADDRESS  		(0x40020000UL)
#define GPIOB_BASE_ADDRESS  		(0x40020400UL)
#define GPIOC_BASE_ADDRESS  		(0x40020800UL)
#define GPIOD_BASE_ADDRESS  		(0x40020C00UL)
// #define GPIOE_BASE_ADDRESS  		(0x40021000UL)
/***************************************************************/


/******************* MGPIO Register Definition Structure **************/
typedef struct
{
	volatile u32 	MODER;		/*!< GPIO port mode register, 				0x00 		*/
	volatile u32 	OTYPER;		/*!< GPIO port output type register,		0x04 		*/
	volatile u32 	OSPEEDR;	/*!< GPIO port output speed register,		0x08 		*/
	volatile u32 	PUPDR;		/*!< GPIO port pull-up/pull-down register,	0x0C 		*/
	volatile u32 	IDR;		/*!< GPIO port input data register,			0x10 		*/
	volatile u32 	ODR;		/*!< GPIO port output data register,		0x14 		*/
	volatile u32 	BSRR;		/*!< GPIO port bit set/reset register,		0x18 		*/
	volatile u32 	LCKR;		/*!< GPIO port configuration lock register,	0x1C 		*/
	volatile u32 	ARF[2];		/*!< GPIO alternate function low register,	0x20 		*/
}MGPIO_REGDEf_t;
/******************************************************************/


/******************* MGPIO Peripheral Definition **************/
#define GPIOA                		((MGPIO_REGDEf_t*)GPIOA_BASE_ADDRESS)
#define GPIOB                		((MGPIO_REGDEf_t*)GPIOB_BASE_ADDRESS)
#define GPIOC                		((MGPIO_REGDEf_t*)GPIOC_BASE_ADDRESS)
#define GPIOD                		((MGPIO_REGDEf_t*)GPIOD_BASE_ADDRESS)


/************************** Defines Needed in Code ********************************/
#define MGPIO_PERIPHERAL_NUM  	    		4U

#define MGPIO_MODEBIT_MASK					3U
#define MGPIO_MODE_NBITS	 				2U

#define MGPIO_PUPDBIT_MASK					3U
#define MGPIO_PUPD_NBITS	 				2U

#define MGPIO_SPEEDBIT_MASK					3U
#define MGPIO_SPEED_NBIS		 			2U

#define MGPIO_OTYPEBIT_MASK					1U

#define MGPIO_ALTFUNCBIT_MASK				0X0F
#define MGPIO_ALTFUNC_NBITS		 			4U
#define MGPIO_ALTFUNCPINSHIFTING			8U
#define MGPIO_ARFLH_PIN_SHIFITR				3U
#define MGPIO_ARFLH_PIN_MASK				0x07U /* to reads only 3-LSB */


#define MGPIO_BSRR_OFFSET					16U

#define MGPIO_ODRBIT_MASK					1U
#define MGPIO_IDRBIT_MASK					1U




#endif